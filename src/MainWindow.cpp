#include "MainWindow.h"
#include <QSvgRenderer>
#include <QKeyEvent>
#include <PortItem.h>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new MGraphicsScene();
    scene->setSceneRect(0,0,480,360);
    frame = new frameDrag();
    frame->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    frame->resize(100,360);
    view = new GraphicsViewDrop(scene);
    setAcceptDrops(true);

    sp = new QSplitter();
    sp->addWidget(frame);
    sp->addWidget(view);
    setCentralWidget(sp);
    QBrush myBrush(Qt::blue, Qt::CrossPattern);
    view->setBackgroundBrush(myBrush);

    resize(580,360);
    //Resources table for shared svg files
    rendererTable.insert(QString("AND_gate"),new QSvgRenderer(QLatin1String(":/SVG/AND_gate.svg")));
    rendererTable.insert(QString("OR_gate"),new QSvgRenderer(QLatin1String(":/SVG/OR_gate.svg")));
    rendererTable.insert(QString("XOR_gate"),new QSvgRenderer(QLatin1String(":/SVG/XOR_gate.svg")));
    rendererTable.insert(QString("NOT_gate"),new QSvgRenderer(QLatin1String(":/SVG/NOT_gate.svg")));

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
}