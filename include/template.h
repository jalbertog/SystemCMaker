#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <QString>
#include <QHash>
class Template
{
  public:
    Template(const QString &);

    void setTemplate(const QString &);

    QString getFilledTemplate(const QHash<QString,QString> &);

    bool saveToFile(const QString &, const QHash<QString,QString> &);
  private:



    QString templateFile;

};

#endif // TEMPLATE_H

