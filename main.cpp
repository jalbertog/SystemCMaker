#include <QApplication>
#include <MainWindow.h>
#include <template.h>
#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication app(argc,argv);

  Template t("templates/template.ht");
  QHash<QString,QString> dic;
  QString className("sum1bit");
  dic.insert(QString("CLASS_NAME"),className);
  dic.insert(QString("CLASSNAME_UPPERCAST"),className.toUpper());
  dic.insert(QString("INCLUDE_SECTION"),QString("#include<and.h>\n#include<or.h>\n"));
  dic.insert(QString("IN_PORTS_DECL"),"sc_in<bool> a_in;\n        sc_in<bool> b_in;\n");
  dic.insert(QString("OUT_PORTS_DECL"),"sc_out<bool> c_out;\n");
  dic.insert(QString("CREATE_COMPONENTS_SECTION"),"and_1 = new And(a_in);");
  dic.insert("PRIVATE_MEMBERS_SECCION","And *and1;");
  QString code = t.getFilledTemplate(dic);
  qDebug() <<"code : \n" << code;
  t.saveToFile("templates/sum1.h",dic);
  MainWindow m;
  m.show();

  return app.exec();
}
