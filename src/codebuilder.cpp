#include <codebuilder.h>
#include <stdexcept>
#include <QDir>
#include <PropertyComponent.h>
#include <PolyLinesItem.h>
#include <template.h>

CodeBuilder::CodeBuilder(QGraphicsView *v,const QString &mod)
{
    if(v == NULL)
        throw std::invalid_argument("QGraphics is null");

    view = v;
    templateCppSource = "templates/main.cppt";
    templateHeaderSource = "templates/header.ht";
    templateMakefileSource = "templates/Makefile.t";
    templateTestH = "templates/TestBench.ht";
    templateTestCpp = "templates/TestBench.cppt";

    moduleName = mod.isEmpty() ? "classDefault" : mod;
}


void CodeBuilder::buildMaps()
{
    QList<QGraphicsItem *> list = view->items();

    QList<QGraphicsItem *>::Iterator it = list.begin();
    QHash<QString, int> componentCount;

    for(it; it != list.end(); it++)
    {
        SvgDraggableItem *item = qgraphicsitem_cast<SvgDraggableItem*>(*it);
        if(item)
        {
            qDebug() << item->name <<"=====";
            QString typ =item->name;
            qDebug() << " name = " << item->getPropertyComponent().name << " type = " << typ;
            if(typ == "output")
            {
                QString name = item->text;
                varOutput.insert(item,name);
                vOutputs.append(name);
                qDebug() << "adding output = " <<name;
            }
            else if (typ == "input")
            {
                QString name = item->text;
                varInput.insert(item,name);
                vInputs.append(name);
                qDebug() << "adding input = " <<name;

            }
            else
            {
                QString cl = componentClass.value(item->name,QString("notFound"));
                qDebug() << "name = " <<cl << item->name;
                int nro = componentCount[cl]++;
                QString var = cl.toLower()+QString::number(nro);
                varComponents.insert(item,var);
                vNameComponents.append(var);
            }
        }
        else
        {
            PolyLinesItem *wire = qgraphicsitem_cast<PolyLinesItem*>(*it);
            if(wire)
                wires.append(wire);
        }
    }
}

QString CodeBuilder::buildSignals()
{
    if(wires.isEmpty())
        throw std::invalid_argument("buildMaps() empty");

    QList<PolyLinesItem *>::Iterator it = wires.begin();
    QString linkSeccion;
    for(it; it != wires.end(); it++)
    {
        PolyLinesItem *item = *it;

        PortItem *pin = item->inPort();
        PortItem *pout = item->outPort();

        SvgDraggableItem *moduleIn = qgraphicsitem_cast<SvgDraggableItem*>(pin->parentItem());
        SvgDraggableItem *moduleOut = qgraphicsitem_cast<SvgDraggableItem*>(pout->parentItem());

        bool modIn = moduleIn->name == "input";
        bool modOut = moduleOut->name == "output";

        if(modIn && !modOut)
            linkSeccion += "\t\t\t"+varComponents.value(moduleOut)+"."
                            +pout->getName()+"("+varInput.value(moduleIn)+");\n";
        else if(!modIn && modOut)
            linkSeccion += "\t\t\t"+varComponents.value(moduleIn)+"."
                            +pin->getName()+"("+varOutput.value(moduleOut)+");\n";
        else if (modIn && modOut)
            linkSeccion += "\t\t\t"+varOutput.value(moduleOut)+"("+varInput.value(moduleIn)+");\n";
        else
        {
            QString name1 = varComponents.value(moduleIn);
            QString name2 = varComponents.value(moduleOut);
            QString sig = name1.toLower()+"To"+name2.toLower()+"_sg";
            vNameSignals << sig;
            linkSeccion += "\t\t\t"+name1+"."+pin->getName()+QString("(%1)").arg(sig)+";\n"
                            +"\t\t\t"+name2+"."+pout->getName()+QString("(%1)").arg(sig)+";\n";

        }

    }

    return linkSeccion;
}

void CodeBuilder::buildHTemplate(const QString &prefix)
{
    QHash<QString, QString> dic;
    dic.insert("CLASS_NAME",moduleName);
    dic.insert("CLASSNAME_UPPERCAST",moduleName.toUpper());

    QString moduleHeader = moduleName.toLower()+".h";
    QString inclSec ;
    QString inPortsdec;
    QString outPortsdec;
    QString createCompSec;
    QString linkSecc =  buildSignals();
    QString cleanSecc;
    QString declSecc;

    foreach(QString var , vInputs)
        inPortsdec += QString("\t\tsc_in<bool> %1;\n").arg(var);

    foreach(QString var, vOutputs)
        outPortsdec += QString("\t\tsc_out<bool> %1;\n").arg(var);

    QHashIterator<SvgDraggableItem *,QString> it(varComponents);
    QHash<QString,QString> mod;
    while(it.hasNext())
    {
        it.next();
        QString className = componentClass.value(it.key()->name);
        QString var = it.value();
        createCompSec += QString("\t\t\t%1 = new %2(\"%3\");\n").arg(var,className,var);
        cleanSecc += QString("\t\t\tdelete %1;\n").arg(var);
        declSecc += QString("\t\t%1 *%2;\n").arg(className,var);

        if(!mod.contains(className))
        {
            inclSec += QString("#include \"%1\";\n").arg(classHeader.value(className));
            mod.insert(className,classHeader.value(className));
        }
    }

    foreach(QString var , vNameSignals)
        declSecc += QString("\t\tsc_signal<bool> %1;\n").arg(var);

    dic.insert("INCLUDE_SECTION",inclSec);
    dic.insert("IN_PORTS_DECL",inPortsdec);
    dic.insert("OUT_PORTS_DECL",outPortsdec);
    dic.insert("CREATE_COMPONENTS_SECTION",createCompSec);
    dic.insert("LINK__COMPONENTS_SECTION",linkSecc);
    dic.insert("CLEAN_UP_SECTION",cleanSecc);
    dic.insert("PRIVATE_MEMBERS_SECCION",declSecc);

    QHashIterator<QString,QString> modIt(mod);
    while(modIt.hasNext())
    {
        modIt.next();
        QString val = modIt.value();
        QFile::copy(QString("basic/%1").arg(val),QString("%1/%2").arg(prefix,val));
    }

    Template htemp(templateHeaderSource);
    htemp.saveToFile(prefix+"/"+moduleHeader,dic);


}

bool CodeBuilder::generate(const QString &prefix, bool create)
{
    QDir dir;
    if(!dir.exists(prefix))
    {
        if(create)
            dir.mkdir(prefix);
        else
            return false;
    }
    buildMaps();
    buildHTemplate(prefix);
    qDebug() << "Finish";
    return true;
}



void CodeBuilder::setCppTemplateSource(const QString &file)
{
    if(!QFileInfo::exists(file))
        throw std::invalid_argument("file "+file.toStdString()+ " not exist");

    templateCppSource = file;
}

void CodeBuilder::setHeaderTemplateSource(const QString &file)
{
    if(!QFileInfo::exists(file))
        throw std::invalid_argument("file "+file.toStdString()+ " not exist");

    templateHeaderSource = file;
}

void CodeBuilder::setMakefileTemplateSource(const QString &file)
{
    if(!QFileInfo::exists(file))
        throw std::invalid_argument("file "+file.toStdString()+ " not exist");

    templateMakefileSource = file;
}

void CodeBuilder::setTestCppTemplateSource(const QString &file)
{
    if(!QFileInfo::exists(file))
        throw std::invalid_argument("file "+file.toStdString()+ " not exist");

    templateTestCpp = file;
}

void CodeBuilder::setTestHTemplateSource(const QString &file)
{
    if(!QFileInfo::exists(file))
        throw std::invalid_argument("file "+file.toStdString()+ " not exist");

    templateTestH = file;
}
