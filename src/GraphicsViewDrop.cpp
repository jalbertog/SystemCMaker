#include "GraphicsViewDrop.h"
#include <PolyLinesItem.h>
#include <QScrollBar>

/**
* @brief Default constructor
*/
GraphicsViewDrop::GraphicsViewDrop(QWidget *parent) : QGraphicsView(parent)
{
  click = 0;
  first = NULL;
  setAcceptDrops(true);
}

/**
* @brief Constructor with scene
* @param scene The current scene
*/
GraphicsViewDrop::GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent) : 
                        QGraphicsView(scene,parent)
{
  click = 0;
  setAcceptDrops(true);
  first = NULL;
}

/**
* @brief Set Table of shared resources for render the icons
* @param render Pointer to the table 
*/
void GraphicsViewDrop::setRedererTable(QHash<QString,QSvgRenderer *> *render)
{
  if(render)
    rendererTable = render;
}

/**
* @brief Drop event when the item is drop in the scene
* @param event The event
*/
void GraphicsViewDrop::dropEvent(QDropEvent * event)
{
  if (event->mimeData()->hasText()) 
  {
    QString name = event->mimeData()->text();
    PropertyComponent cp(name);
    if(name == QString("NOT_gate"))
      cp = cp.getNotGate();
    SvgDraggableItem *svgItem = new SvgDraggableItem(name,rendererTable->value(name),cp);
    scene()->addItem(svgItem);
    svgItem->setScale(0.5);
    qDebug() << "Pos in View Coordinates : " << event->pos();
    qDebug() << "Pos in Scene Coordinate: " << mapToScene(event->pos());
    svgItem->setPosToItem(mapToScene(event->pos()));                                        //!!!
    event->accept();
    setCursor(Qt::ArrowCursor);
  } 
  else 
      event->ignore();
}

/**
* @brief Event when the drop enter in the graphics
* @param event the DragEnterEvent
*/
void GraphicsViewDrop::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();
    setCursor(Qt::ClosedHandCursor);
  } 
  else
    event->ignore();
}

/**
* @brief Event when the drop is moved in the graphics
* @param event the DragMoveEvent
*/
void GraphicsViewDrop::dragMoveEvent(QDragMoveEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();
    setCursor(Qt::ClosedHandCursor);
  } 
  else 
    event->ignore();
}

/**
* @brief Function to handle  double click
* @param event The event
*/
void GraphicsViewDrop::mouseDoubleClickEvent(QMouseEvent * event)
{
  QPoint p = event->pos();
  qDebug() <<"Point" <<p;
  qDebug()  <<"CLicks = " << click;
  PortItem * port = qgraphicsitem_cast<PortItem *>(itemAt(p));

  if(port)
  {
    qDebug() << "port";
    click++;
    if( click == 2 and (port->getType() == PortItem::IN))
    {
      qDebug() << "=================ADD WIre==========";
      port->setState(1);
      PolyLinesItem *wire = new PolyLinesItem(first,port);
      scene()->addItem(wire);
      qgraphicsitem_cast<SvgDraggableItem *>(first->parentItem())->addWire(wire);
      qgraphicsitem_cast<SvgDraggableItem *>(port->parentItem())->addWire(wire);
      first->setState(0);
      port->setState(0);
      click = 0;
      first = NULL;
    }
    else if( click == 1 and (port->getType() == PortItem::OUT))
    {
      init = p;
      first = port;
      first->setState(1);
    }
    else
    {
      if(first)
        first->setState(0);
      click = 0;
    }
  }
  else
  {
    if(first)
      first->setState(0);
    click = 0;
    first = 0;
  }
  
  qDebug() << "Pos in View Coordinates : " << event->pos();
  qDebug() << "Pos in Scene Coordinate: " << mapToScene(event->pos());
  qDebug() << "Clicks " << click;
  QGraphicsView::mouseDoubleClickEvent(event);

}

/**
* @brief Scale the view in a factor
* @param scaleFactor Factor to scale the view between 0.07 and 100
*/
void GraphicsViewDrop::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
    return;

  scale(scaleFactor, scaleFactor);
}

/**
* @brief ZoomIn the view
*/
void GraphicsViewDrop::zoomIn()
{
  scaleView(qreal(1.2));
}

/**
* @brief Zoom out the view
*/
void GraphicsViewDrop::zoomOut()
{
  scaleView(1 / qreal(1.2));
}

/**
* @brief Zoom relative to the wheel of mouse
* @param event WheelEvent 
*/
void GraphicsViewDrop::wheelEvent(QWheelEvent *event)
{
  scaleView(pow((double)2, event->delta() / 240.0));
}


/**
* @brief Get the property of all components( gates) in the scene
* @return QVector<PropertyComponent> 
**/
QVector<PropertyComponent> GraphicsViewDrop::getAllPropertyOfComponent() const
{
  QVector<PropertyComponent> vectorOfComponents;
  QList<QGraphicsItem *> components = items();
  foreach(QGraphicsItem *it, components)
  {
    SvgDraggableItem * item = qgraphicsitem_cast<SvgDraggableItem *>(it);
    if(item)
        vectorOfComponents.append(item->getPropertyComponent());
  }

  return vectorOfComponents;
}

/**
 * @brief Adjust the scene dynamically
 * @param dx scrolled x
 * @param dy scrooled y
 */
void GraphicsViewDrop::scrollContentsBy(int dx, int dy)
{
    QScrollBar * h = horizontalScrollBar();
    QScrollBar * v = verticalScrollBar();
    QRectF r = sceneRect();
    if(h->value() == h->maximum())
        r.setWidth(r.width()+h->singleStep());

    if(v->value() == v->maximum())
        r.setHeight(r.height()+v->singleStep());

    setSceneRect(r);
    QGraphicsView::scrollContentsBy(dx,dy);
}
