#include "myxml.h"

MyXml::MyXml(const QString& name, QObject* parent)
    :QObject(parent), name(name)
{
    file.setFileName(name);
    if (!file.open(QIODevice::ReadWrite))
    {
          //throw exception
    }
    if (!domdoc.setContent(&file))
    {
        qDebug() << " A";
        //throw exception
    }
    file.close();
}

QDomElement MyXml::current_el(const PATH& path_to_tag)
{
    if (!file.open(QIODevice::ReadWrite))
    {
          return QDomElement();
    }
    QDomNode main_node = domdoc.documentElement();
    for (auto el = path_to_tag.begin(); el != path_to_tag.end(); el++)
    {
        qDebug() << main_node.toElement().nodeName();
        while (true)
        {
            if (main_node.toElement().nodeName() == el->first)
            {
                bool correct = true;
                //qDebug() << "A";
                for (int i = 0; i < el->second.size(); i++)
                {
                    if (main_node.toElement().attribute(el->second[i].first) != el->second[i].second)
                    {
                        correct = false;
                        break;
                    }
                }
                if (correct)
                {
                    //qDebug() << main_node.toElement().tagName();
                    //qDebug() << "COR";
                    break;
                }
            }
            if (main_node.isNull())
            {
                qDebug() << "D";
                //exception
                file.close();
                return QDomElement();
            }
            //qDebug() << main_node.previousSibling().toElement().tagName();
            main_node = main_node.nextSibling();
        }
        //qDebug() << main_node.toElement().tagName();
        auto it = el;
        it++;
        if (it == path_to_tag.end())
        {
            file.close();
            return main_node.toElement();
        }
        main_node = main_node.firstChild();
        //qDebug() << main_node.parentNode().toElement().tagName();
    }
    return main_node.toElement();
}

QString MyXml::get_attr_val(const PATH& path_to_tag, const QString &attr_name)
{
    if (current_el(path_to_tag).isNull())
    {
        return "NOTFIND";
    }
    return current_el(path_to_tag).attribute(attr_name);
}

QString MyXml::get_tag_val(const PATH& path_to_tag)
{
        if (current_el(path_to_tag).isNull())
        {
            return "NOTFIND";
        }
        return current_el(path_to_tag).text();
}

void MyXml::write_to_xml(const PATH& path_to_tag, const QString &name, const std::vector<std::pair<QString, QString>> &attr, const QString& text)
{
    QDomElement el = current_el(path_to_tag);
    if (el.isNull())
    {
        qDebug() << "A";
        return;
    }
    QDomElement new_el = domdoc.createElement(name);
    for (int i = 0; i < attr.size(); i++)
    {
        QDomAttr new_attr = domdoc.createAttribute(attr[i].first);
        new_attr.setValue(attr[i].second);
        new_el.setAttributeNode(new_attr);
    }
    if (!text.isEmpty())
    {
        QDomText txt = domdoc.createTextNode(text);
        new_el.appendChild(txt);
    }
    el.appendChild(new_el);
    if (file.open((QIODevice::WriteOnly)))
    {
        QTextStream(&file) << domdoc.toString();
        file.close();
    }
}

void MyXml::write_a_tag(const PATH& path_to_tag, const std::vector<std::pair<QString, QString>> &attr)
{
    QDomElement el = current_el(path_to_tag);
    if (el.isNull())
    {
        qDebug() << "A";
        return;
    }
    for (int i = 0; i < attr.size(); i++)
    {
        QDomAttr new_attr = domdoc.createAttribute(attr[i].first);
        new_attr.setValue(attr[i].second);
        el.setAttributeNode(new_attr);
    }
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream(&file) << domdoc.toString();
    }
    file.close();
}

std::vector<std::pair<QString, QString>> MyXml::get_all_attr(const PATH& path_to_tag)
{
    QDomElement el = current_el(path_to_tag);
    if (el.isNull())
    {
        qDebug() << "B";
        return {};
    }
    auto m = el.attributes();
    std::vector<std::pair<QString, QString>> v;
    for (int i = 0; i < m.size(); i++)
    {
        QDomAttr attr = m.item(i).toAttr();
        v.push_back({attr.name(), attr.value()});
    }
    return v;
}

void MyXml::redact_attr(const PATH& path_to_tag, const std::vector<std::pair<QString, QString>>& attr)
{
    QDomElement el = current_el(path_to_tag);
    if (el.isNull())
    {
        return;
    }
    for (int i = 0; i < attr.size(); i++)
    {
        QDomAttr at = domdoc.createAttribute(attr[i].first);
        at.setValue(attr[i].second);
        if (!el.attributeNode(attr[i].first).isNull())
        {
            el.removeAttribute(attr[i].first);
        }
        el.setAttributeNode(at);
    }
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream(&file) << domdoc.toString();
    }
    file.close();
}

void MyXml::redact_text(const PATH& path_to_tag, const QString &text)
{
    QDomElement el = current_el(path_to_tag);
    if (el.isNull())
    {
        qDebug() << "ERROR";
        return;
    }
    QDomText nel = el.firstChild().toText();
    if (!nel.isNull())
    {
        el.removeChild(nel);
    }
    QDomText txt = domdoc.createTextNode(text);
    txt.setNodeValue(text);
    el.appendChild(txt);
    if (file.open(QIODevice::ReadWrite))
    {
        qDebug() << domdoc.toString();
        QTextStream(&file) << domdoc.toString();
    }
    file.close();
}
