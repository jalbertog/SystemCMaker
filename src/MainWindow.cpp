#include "MainWindow.h"
#include <QSvgRenderer>
#include <QKeyEvent>
#include <PortItem.h>

int n = 0;
/**
 * @brief Default constructor
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new MGraphicsScene();
    scene->setSceneRect(0,0,480,360);
    frame = new frameDrag();
    frame->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    //frame->resize(120,360);
    view = new GraphicsViewDrop(scene);
    setAcceptDrops(true);

    QScrollArea *sc = new QScrollArea;
    sc->setWidget(frame);
    sp = new QSplitter();
    sp->addWidget(sc);
    sp->addWidget(view);
    tb = new QTabWidget();
    tb->addTab(sp,QString("Circuit"));
    setCentralWidget(tb);
    QBrush myBrush(Qt::blue, Qt::CrossPattern);
    view->setBackgroundBrush(myBrush);

    resize(580,360);
    //Resources table for shared svg files
    rendererTable.insert(QString("AND_gate"),new QSvgRenderer(QLatin1String(":/SVG/AND_gate.svg")));
    rendererTable.insert(QString("OR_gate"),new QSvgRenderer(QLatin1String(":/SVG/OR_gate.svg")));
    rendererTable.insert(QString("XOR_gate"),new QSvgRenderer(QLatin1String(":/SVG/XOR_gate.svg")));
    rendererTable.insert(QString("NOT_gate"),new QSvgRenderer(QLatin1String(":/SVG/NOT_gate.svg")));
    rendererTable.insert(QString("input"),new QSvgRenderer(QLatin1String(":/SVG/input.svg")));
    rendererTable.insert(QString("output"),new QSvgRenderer(QLatin1String(":/SVG/output.svg")));

    view->setRedererTable(&rendererTable);

    SvgDraggableItem *svgItem = new SvgDraggableItem("AND_gate",rendererTable.value(QString("AND_gate")),
                                                                            PropertyComponent("AND_gate"));
    scene->addItem(svgItem);
    svgItem->setPos(30,120);
    svgItem->setScale(0.5);

}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
    QList<QGraphicsItem *> items = scene->selectedItems();
    if(!items.isEmpty())
    {

        qDebug() <<"SelectedItems : "<<scene->selectedItems().size();
        if(event->key() == Qt::Key_Delete)
        {
            while(!items.isEmpty())
            {
                QGraphicsItem *item = items.takeFirst();
                if(item)
                {
                    PolyLinesItem *wire = qgraphicsitem_cast<PolyLinesItem *>(item);
                    if(wire != 0)
                    {
                        qDebug() << "WIRE >>>";
                        wire->detach();
                        qDebug() << "Wire Delete";
                    }
                    else if(qgraphicsitem_cast<SvgDraggableItem*>(item))
                    {
                        qDebug() << "SvgDraggableItem";
                        qgraphicsitem_cast<SvgDraggableItem*>(item)->deleteAllWires(scene);
                    }
                    scene->removeItem(item);
                    delete item;
                }
            }
        }
    }

    if(event->matches(QKeySequence::AddTab))
      {
        tb->addTab(new QLabel(QString("Otro Tab")+QString::number(n)),QString("tab")+QString::number(n));
        n++;
      }
    switch(event->key())
    {
        case Qt::Key_Escape:
            close();
        break;
        case  Qt::Key_Plus:
            view->zoomIn();
        break;
        case Qt::Key_Minus:
            view->zoomOut();
        break;
        default:
            QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    QSize nSize = event->size();
    scene->setSceneRect(QRectF(QPointF(0.0,0.0),QSizeF(nSize)));
    //frame->resize(120,nSize.height()+20);
}
