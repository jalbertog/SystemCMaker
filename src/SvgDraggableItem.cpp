#include "SvgDraggableItem.h"
#include <PolyLinesItem.h>
#include <GraphicsViewDrop.h>
#include <QScrollBar>

SvgDraggableItem::SvgDraggableItem(const QString &n,QSvgRenderer * renderer,const PropertyComponent &cmp
                                      , QGraphicsItem* parent): QGraphicsSvgItem(parent), m_dragged(false), name(n)
{
  setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
  setSharedRenderer(renderer);
  pComponent = cmp;
  text = "";
  pointFont = 28;

  middle = QPoint(size.width()/2,size.height()/2);
// TODO dinamyc calcute of ports
  qDebug() <<"In Ports" << pComponent.numberInPorts();
  switch(pComponent.numberInPorts())
  {
    PortItem *p;
    case 1:
      p = new PortItem(QPointF(0.0,size.height()/2.0-6.0),6.0,PortItem::IN,this);
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

/**
 * @brief SvgDraggableItem::setAnchorPoint
 * @param anchorPoint
 */
void SvgDraggableItem::setAnchorPoint(const QPointF &anchorPoint)
{
  this->anchorPoint = anchorPoint;
}

/**
 * @brief Move the item
 * @param event
 */
void SvgDraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  QGraphicsSvgItem::mouseMoveEvent(event);
  m_dragged = true;
  setCursor(Qt::ClosedHandCursor);
  adjustAll();
}

/**
 * @brief Mouse release
 * @param event
 */
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
  setCursor(Qt::ArrowCursor);
  QGraphicsSvgItem::mouseReleaseEvent(event);
}

/**
 * @brief mouse Press Event
 * @param event
 */
void SvgDraggableItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  setCursor(Qt::OpenHandCursor);
  qDebug() << event->scenePos();
  update();
  QGraphicsSvgItem::mousePressEvent(event);
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

/**
  * @brief Add wire to the list of wires
  * @param wire PolyLinesItem Line
  */
 void SvgDraggableItem::addWire(PolyLinesItem *wire)
 {
    wireLines << wire;
 }

 /**
  * @brief Remove de wire of the componente
  * @param wire PolyLinesItem wire to remove
  * @return bool true if wire exist
  */
 bool SvgDraggableItem::removeWire(PolyLinesItem *wire)
 {
    return wireLines.removeOne(wire);
 }

 /**
  * @brief Remove all wires of the component
  *         scene is used for remove the item from the Scene too.
  * @param scene The scene for current view
  */
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

 /**
 * @brief SvgDraggableItem::inPortsVector
 * @return vector of PortItem
 */
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

 /**
 * @brief reimplements setSharedRenderer
 * @param renderer
 */
void SvgDraggableItem::setSharedRenderer(QSvgRenderer * renderer)
{
  size = QSizeF(renderer->defaultSize());
  QGraphicsSvgItem::setSharedRenderer(renderer);
}

/**
 * @brief reimplents setScale
 * @param factor
 */
void SvgDraggableItem::setScale(qreal factor)
{
 size *= factor;
 QGraphicsSvgItem::setScale(factor);
}

/**
 * @brief get the current property of components
 * @return PropertyComponent
 */
const PropertyComponent & SvgDraggableItem::getPropertyComponent() const
{
  return pComponent;
}

/**
 * @brief Adjust all wires conected to this component
 */
void SvgDraggableItem::adjustAll()
{
  PolyLinesItem * curr;
  foreach (curr , wireLines)
  {
      curr->adjust();
  }
}


QVariant SvgDraggableItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if(change == QGraphicsItem::ItemPositionChange)
    adjustAll();
  return QGraphicsItem::itemChange(change,value);
}


void SvgDraggableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QGraphicsSvgItem::paint(painter,option,widget);
  if(text != "")
  {
    painter->setFont(QFont("Times", pointFont, QFont::Bold));
    painter->drawText(postext,text);
  }
}

void SvgDraggableItem::drawText(const QString &text,bool def, const QPoint &p)
{
  this->text = text;
  postext = def ? p : middle-QPoint(pointFont/2,-pointFont/2);
  qDebug() << "draw " << this->text << postext;
  update();
}


void SvgDraggableItem::deleteText()
{
  this->text = "";
  update();
}
