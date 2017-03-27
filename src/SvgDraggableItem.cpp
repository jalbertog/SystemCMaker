#include "SvgDraggableItem.h"
#include <PolyLinesItem.h>
#include <GraphicsViewDrop.h>

SvgDraggableItem::SvgDraggableItem(const QString &n,QSvgRenderer * renderer,const PropertyComponent &cmp
                                      , QGraphicsItem* parent): QGraphicsSvgItem(parent), m_dragged(false), name(n)
{
  setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
  setSharedRenderer(renderer);
  pComponent = cmp;

// TODO dinamyc calcute of ports
  qDebug() <<"In Ports" << pComponent.numberInPorts();
  switch(pComponent.numberInPorts())
  {
    PortItem *p;
    case 1:
      p = new PortItem(QPointF(0.0,size. height()/2.0-6.0),6.0,PortItem::IN,this);
      p->setName(pComponent.inPortsList().at(0));
      inPorts << p;
    break;
    case 2:
      p = new PortItem(QPointF(0.0,4.0),6.0,PortItem::IN,this);
      p->setName(pComponent.inPortsList().at(0));
      inPorts << p;
      p = new PortItem(QPointF(0.0,size.height()-16.0),6.0,PortItem::IN,this);
      p->setName(pComponent.inPortsList().at(1));
      inPorts << p;
    break;
  }

qDebug() <<"Out Ports" << pComponent.numberOutPorts();
  switch(pComponent.numberOutPorts())
  {
    PortItem * p;
    case 1:
      p = new PortItem(QPointF(size.width()-6.0,size.height()/2.0 - 6.0),6.0,PortItem::OUT,this);
      p->setName(pComponent.outPortsList().at(0));
      inPorts << p;
    break;
    case 2:
      p = new PortItem(QPointF(size.width(),4.0),6.0,PortItem::OUT,this);
      p->setName(pComponent.outPortsList().at(0));
      inPorts << p;
      p = new PortItem(QPointF(size.width(),size.height()-4.0),6.0,PortItem::OUT,this);
      p->setName(pComponent.outPortsList().at(1));
      inPorts << p;
    break;
  }

}

void SvgDraggableItem::setAnchorPoint(const QPointF &anchorPoint)
{
  this->anchorPoint = anchorPoint;
}
void SvgDraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsSvgItem::mouseMoveEvent(event);
  qDebug() << "Move: " << event->scenePos() ;
  m_dragged = true;
  PolyLinesItem * curr;
  qDebug() << wireLines.size();
  foreach (curr , wireLines)
  {
      curr->adjust();
  }
}

void SvgDraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  QRectF b = boundingRect();
  QPointF d = mapFromScene(event->scenePos());
  if(m_dragged)
  {
    this->setPos(event->scenePos()-d*scale());
    m_dragged = false;
  }

  update();
  QGraphicsSvgItem::mouseReleaseEvent(event);
}

void SvgDraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  qDebug() <<"Cantidad de Lineas:  " << wireLines.size();
  qDebug() << "Point <<" << mapFromItem(this,event->scenePos());
  update();
  QGraphicsSvgItem::mouseReleaseEvent(event);  
}

/**
* @brief Set item in the point with center in the middle of the Item.
* @param p Point in Scene coordinates
*/
void SvgDraggableItem::setPosToItem(const QPointF &p)
{
  QRectF b = boundingRect();
  QPointF middlePoint = (QPointF(b.width(),b.height())/2.0)*scale();
  this->setPos(p-middlePoint);
}

 void SvgDraggableItem::addWire(PolyLinesItem *wire)
 {
    wireLines << wire;
 }

 bool SvgDraggableItem::removeWire(PolyLinesItem *wire)
 {
    return wireLines.removeOne(wire);
 }

 void SvgDraggableItem::deleteAllWires(QGraphicsScene *scene)
 {
    while(!wireLines.isEmpty())
    {
      PolyLinesItem *removedWire = wireLines.takeFirst();
      qDebug() << "detach() ";
      removedWire->detach();
      scene->removeItem(removedWire);
      delete removedWire;
    }
 }

const QVector<PortItem *> & SvgDraggableItem::inPortsVector() const
{ 
  return inPorts;
}

const QVector<PortItem *> & SvgDraggableItem::outPortsVector() const
{
  return outPorts;
}

 int SvgDraggableItem::type() const
 {
    return Type;
 }

void SvgDraggableItem::setSharedRenderer(QSvgRenderer * renderer)
{
  size = QSizeF(renderer->defaultSize());
  QGraphicsSvgItem::setSharedRenderer(renderer);
}
  void SvgDraggableItem::setScale(qreal factor)
  {
    size *= factor;
    QGraphicsSvgItem::setScale(factor);
  }

  const PropertyComponent & SvgDraggableItem::getPropertyComponent() const
  {
    return pComponent;
  }