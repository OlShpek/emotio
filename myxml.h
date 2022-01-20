#ifndef MYXML_H
#define MYXML_H


#include <QtCore>
#include <QtXml>
#include <map>
#include <vector>
#include <string>
#define PATH std::vector<std::pair<QString, std::vector<std::pair<QString, QString>>>>

class MyXml : public QObject
{
public:
    MyXml(const QString& name, QObject* parent = nullptr);
    QString get_attr_val(const PATH& path_to_tag, const QString& attr_name);
    QString get_tag_val(const PATH& path_to_tag);
    std::vector<std::pair<QString, QString>> get_all_attr(const PATH& path_to_tag);
    void write_to_xml(const PATH& path_to_tag, const QString& name, const std::vector<std::pair<QString, QString>>& attr, const QString& text = QString());
    void write_a_tag(const PATH& path_to_tag, const std::vector<std::pair<QString, QString>>& attr);
    void redact_attr(const PATH& path_to_tag, const std::vector<std::pair<QString, QString>>& attr);
    void redact_text(const PATH& path_to_tag, const QString& text);
private:
    QDomElement current_el(const PATH& path_to_tag);
    QDomDocument domdoc;
    QString name;
    QFile file;
};

#endif // MYXML_H
