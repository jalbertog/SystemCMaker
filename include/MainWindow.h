#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <MGraphicsScene.h>
#include <SvgDraggableItem.h>
#include <PolyLinesItem.h>
#include <QHash>
#include <frameDrag.h>
#include <GraphicsViewDrop.h>
#include <QSplitter>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
  private:
    MGraphicsScene *scene;
    GraphicsViewDrop *view;
    QSplitter *sp;
    QHash<QString,QSvgRenderer *> rendererTable;
    frameDrag *frame;
    QTabWidget *tb;
  protected:
    void keyPressEvent(QKeyEvent * event);
    void resizeEvent(QResizeEvent * event);
        
};

#endif
