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

QDomElement MyXml::current_el(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag)
{
    if (!file.open(QIODevice::ReadWrite))
    {
          return QDomElement();
    }
    QDomNode main_node = domdoc.documentElement();
    for (auto el = path_to_tag.begin(); el != path_to_tag.end(); el++)
    {
        //qDebug() << main_node.toElement().nodeName();
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
                    break;
                }
            }

            main_node = main_node.nextSibling();
            if (main_node.isNull())
            {
                //exception
                return QDomElement();
            }
        }
        main_node = main_node.firstChild();
    }
    file.close();
    return main_node.parentNode().toElement();
}

QString MyXml::get_attr_val(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>> &path_to_tag, const QString &attr_name)
{
    if (current_el(path_to_tag).isNull())
    {
        return "NOTFIND";
    }
    return current_el(path_to_tag).attribute(attr_name);
}

QString MyXml::get_tag_val(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>> &path_to_tag)
{
        if (current_el(path_to_tag).isNull())
        {
            return "NOTFIND";
        }
        return current_el(path_to_tag).text();
}

void MyXml::write_to_xml(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>> &path_to_tag, const QString &name, const std::vector<std::pair<QString, QString>> &attr, const QString& text)
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

void MyXml::write_a_tag(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>> &path_to_tag, const std::vector<std::pair<QString, QString>> &attr)
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
}
