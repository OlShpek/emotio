#ifndef MYXML_H
#define MYXML_H


#include <QtCore>
#include <QtXml>
#include <map>
#include <vector>
#include <string>

class MyXml : public QObject
{
public:
    MyXml(const QString& name, QObject* parent = nullptr);
    QString get_attr_val(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag, const QString& attr_name);
    QString get_tag_val(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag);
    void write_to_xml(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag, const QString& name, const std::vector<std::pair<QString, QString>>& attr, const QString& text = QString());
    void write_a_tag(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag, const std::vector<std::pair<QString, QString>>& attr);
    std::vector<std::pair<QString, QString>> get_all_attr(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag);
private:
    QDomElement current_el(std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>& path_to_tag);
    QDomDocument domdoc;
    QString name;
    QFile file;
};

#endif // MYXML_H
