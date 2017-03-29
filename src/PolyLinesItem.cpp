#include <PolyLinesItem.h>

/**
* @brief Default constructor 
*/
PolyLinesItem::PolyLinesItem(PortItem *pIn, PortItem *pOut,QGraphicsItem *parent) : 
                                                QGraphicsPathItem(parent) 
{
  setFlags(QGraphicsItem::ItemIsSelectable);
  penWidth = 2;
  color = Qt::black;
  polPen.setColor(color);
  polPen.setWidth(penWidth);
  setPen(polPen);
  setAcceptHoverEvents(true);
  portIn = pIn;
  portOut = pOut;
  adjust();
  qDebug() << "Points in PolyLInes " << breakPoints ;
}

/**
* @brief Constructor with points
* @param start Start Point in Scene coordinates
* @param end  End Point in Scene coordinates
*/
PolyLinesItem::PolyLinesItem(PortItem *pIn, PortItem *pOut
                  ,const QPointF &start, const QPointF &end ,
                    QGraphicsItem* parent ) : QGraphicsPathItem(parent) 
{
  setFlags(QGraphicsItem::ItemIsSelectable| QGraphicsItem::ItemIsMovable);
  penWidth = 2;
  color = Qt::black;
  portIn = pIn;
  portOut = pOut;
  adjust(start,end);
}

/**
* @brief Calculate de intermediate points for the polyLine
* @param start Start Point in Scene coordinates
* @param end  End Point in Scene coordinates
*/
void PolyLinesItem::CalculatePoints(const QPointF &start, const QPointF &end)
{
  breakPoints.clear();
  if(start.x() < end.x())
  {
    breakPoints.push_back(start);
    int midX =  (end.x()+start.x())/2.0;
    breakPoints.push_back(QPointF(midX,start.y()));
    breakPoints.push_back(QPointF(midX,end.y()));
    breakPoints.push_back(end);
  }
  else
  {
    breakPoints.push_back(start);
    int midY = (end.y()+start.y())/2.0;
    breakPoints.push_back(QPointF(start.x(),midY));
    breakPoints.push_back(QPointF(end.x(),midY));
    breakPoints.push_back(end);
  }
}

void PolyLinesItem::adjust(const QPointF &start, const QPointF &end)
{
  CalculatePoints(start,end);
  prepareGeometryChange();
  QPainterPath mpath(start);
  mpath.lineTo(QPointF(breakPoints.at(1)));
  mpath.lineTo(QPointF(breakPoints.at(2)));
  mpath.lineTo(QPointF(breakPoints.at(3)));
  path = mpath;
  setPath(path);
}

void PolyLinesItem::adjust()
{
  QPointF offSet(portIn->getRadius()*0.9,0);
  CalculatePoints(portIn->Pos()+offSet,portOut->Pos()-offSet);
  prepareGeometryChange();
  QPainterPath mpath(breakPoints.at(0));
  mpath.lineTo(QPointF(breakPoints.at(1)));
  mpath.lineTo(QPointF(breakPoints.at(2)));
  mpath.lineTo(QPointF(breakPoints.at(3)));
  path = mpath;
  setPath(path);
}

QPointF PolyLinesItem::firstPoint() const
{
  return breakPoints.at(0);
}

QPointF PolyLinesItem::lastPoint() const
{
  return breakPoints.at(3);
}

/**
*  @brief Detach line of ports
*/
bool PolyLinesItem::detach()
{
  qgraphicsitem_cast<SvgDraggableItem *>(portIn->parentItem())->removeWire(this);
  qgraphicsitem_cast<SvgDraggableItem *>(portOut->parentItem())->removeWire(this);
  return true;
}
/**
* @brief Changue the color to item selected
* @param event The Event
*/
void PolyLinesItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  color = Qt::red;
  update();
  //QGraphicsPathItem::mousePressEvent(event);
}

/**
* @brief Paint the polyLines in the Scene
* @param painter Painter
*/
void PolyLinesItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
  painter->setPen(QPen(color, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
  painter->drawPath(path);
}

/**
 * @brief PolyLinesItem::type
 * @return type of QGraphicsItem
 */
int PolyLinesItem::type() const
{
  return Type;
}

void PolyLinesItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  color = QColor("gold");
  penWidth = 4;
  polPen.setColor(color);
  polPen.setWidth(penWidth);
  setPen(polPen);
  update();
}

void PolyLinesItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  color = Qt::black;
  penWidth = 2;
  polPen.setColor(color);
  polPen.setWidth(penWidth);
  setPen(polPen);
  update();
}
