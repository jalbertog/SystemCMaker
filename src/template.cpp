#include <template.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Template::Template(const QString &file)
{
    if(QFile::exists(file))
       this->templateFile = file;
}


void Template::setTemplate(const QString &file)
{
    if(QFile::exists(file))
       this->templateFile = file;
}

QString Template::getFilledTemplate(const QHash<QString, QString> &dic)
{
    if(this->templateFile.isEmpty())
        return QString("File is empty");

    QFile file(this->templateFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return QString("Not Open");

    QTextStream in(&file);

    QString code;
    QString key;
    bool begin = false;
    bool wordMode = false;
    QChar ch;

    while(!in.atEnd())
    {
        in >> ch;
        if(wordMode)
        {
            if(ch == '%')
            {
                begin = false;
                continue;
            }
            else if (ch == ']' && !begin)
            {
                wordMode = false;
                qDebug() << "search " << key;
                code += dic.value(key,QString(""));
                key.clear();
                continue;
            }
            else
            {
                if(!ch.isSpace())
                    key += ch;
            }

        }
        else
        {
            if(ch == '[' && !begin)
            {
                begin = true;
                continue;
            }
            else if(ch == '%' && begin)
            {
                wordMode = true;
                continue;
            }
            else
                code += ch;
       }
    }

    file.close();
    return code;
}


bool Template::saveToFile(const QString &fileName, const QHash<QString, QString> &dic)
{
    QString code = getFilledTemplate(dic);
    if(code.isEmpty())
        return false;

    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << code;
    file.close();

    return true;
}
