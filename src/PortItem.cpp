#include <PortItem.h>
#include <QtDebug>
#include <SvgDraggableItem.h>

/**
* @brief Default constructor
* @param position The position of the port relative to the parent component
* @param rad radius of the port
* @param s Type of port (IN|OUT)
*/
PortItem::PortItem(const QPointF &position,const qreal &rad, Sig s,QGraphicsItem * parent) : 
                                               QGraphicsEllipseItem(position.x(),position.y(),2*rad,2*rad,parent)
{
  posi = QPointF(position.x(),position.y());
  radius = rad;
  sig = s;
  active = QColor(Qt::blue);
  pen = QPen(Qt::black);
  name = QString("port");
  setFlags(QGraphicsItem::ItemIsSelectable);
  setCursor(Qt::CrossCursor);
  setAcceptHoverEvents(true);
}

/**
* @brief get the name of the port
* @return QString name
*/
QString PortItem::getName() const
{
  return name;
}

void PortItem::setName(const QString &n)
{
  name = n;
}

void PortItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
  qDebug() << "***************__Press__********************";
  SvgDraggableItem *pp = qgraphicsitem_cast<SvgDraggableItem *>(parentItem());
  if(pp)
    qDebug() << "***Parent Pos" << pp->pos() << "******___";
}


void PortItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
  painter->setBrush(QBrush(active));
  painter->setPen(pen);
  painter->drawEllipse(posi.x(),posi.y(),2*radius+pen.width()/2.0,2*radius+pen.width()/2.0);
}

int PortItem::type() const
{
  return Type;
}
QPointF PortItem::Pos()
{
  QPointF sc = mapToScene(posi+QPointF(radius,radius));
  qDebug() << "Position Port"<<sc;
  return sc;
}

void PortItem::setState(int st)
{
  if(st == 1)
    active = QColor(Qt::red);
  else 
    active = QColor(Qt::blue);

  update();
}

void PortItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  if(active != Qt::red)
    active = Qt::magenta;
  pen.setColor(Qt::yellow);
  pen.setStyle(Qt::DotLine);
  pen.setWidth(3);
  radius *= 2.0;
  setRect(posi.x(),posi.y(),2*radius+1.5,2*radius+1.5);
  QGraphicsEllipseItem::hoverEnterEvent(event);
}


void PortItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  if(active != Qt::red)
    active = Qt::blue;
  pen.setColor(Qt::black);
  pen.setStyle(Qt::SolidLine);
  pen.setWidth(1);
  radius /= 2.0;
  setRect(posi.x(),posi.y(),2*radius,2*radius);
  QGraphicsEllipseItem::hoverLeaveEvent(event);
}


void PortItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
  if(active != Qt::red)
    active = Qt::magenta;
  pen.setColor(Qt::yellow);
  pen.setStyle(Qt::DotLine);
  QGraphicsEllipseItem::hoverMoveEvent(event);
}
