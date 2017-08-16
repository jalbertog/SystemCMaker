#ifndef CODEBUILDER_H
#define CODEBUILDER_H
#include <GraphicsViewDrop.h>
#include <template.h>
#include <QHash>

class CodeBuilder
{
    public:
    CodeBuilder(QGraphicsView *, const QString &mod);

    bool generate(const QString &, bool create=true);

    void setHeaderTemplateSource(const QString &);
    void setCppTemplateSource(const QString &);
    void setMakefileTemplateSource(const QString &);
    void setTestHTemplateSource(const QString &);
    void setTestCppTemplateSource(const QString &);

    QHash<QString,QString> componentClass;
    QHash<QString,QString> classHeader;

    private:
    void buildMaps();
    QString buildSignals();
    void buildHTemplate(const QString &);

    QGraphicsView *view;

    QHash<SvgDraggableItem *,QString> varComponents;
    QHash<SvgDraggableItem *,QString> varInput;
    QHash<SvgDraggableItem *,QString> varOutput;
    QList<PolyLinesItem *> wires;

    QStringList vNameSignals;
    QStringList vNameComponents;
    QStringList vInputs;
    QStringList vOutputs;


    QString templateHeaderSource;
    QString templateCppSource;
    QString templateMakefileSource;
    QString templateTestH;
    QString templateTestCpp;

    QString moduleName;
};
#endif // CODEBUILDER_H

