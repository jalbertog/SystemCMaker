#ifndef POLYLINESITEM_H
#define POLYLINESITEM_H
#include <QtGui>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <SvgDraggableItem.h>
#include <PortItem.h>

/**
* @brief Class for implement PolyLines in the scene
* @param event The event
*/
class PolyLinesItem : public QGraphicsPathItem
{
  public:
    enum { Type = UserType + 2 };

    PolyLinesItem(PortItem *pIn, PortItem *pOut,QGraphicsItem* parent = 0);
    PolyLinesItem(PortItem *pIn, PortItem *pOut,

    const QPointF &start, const QPointF &end,QGraphicsItem* parent = 0);
    int type() const;
    QPointF firstPoint() const;
    QPointF lastPoint() const;

    inline PortItem * inPort() { return portIn;}
    inline PortItem * outPort() {return portOut;}

    void adjust(const QPointF &start, const QPointF &end);
    void adjust();
    bool detach();
  protected:
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
   void mousePressEvent(QGraphicsSceneMouseEvent *event);

   void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
   void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
  private:
    QVector<QPointF> breakPoints;
    int penWidth;
    QPainterPath path;
    QColor color;
    PortItem *portIn;
    PortItem *portOut;
    QPen polPen;
  private:
    void CalculatePoints(const QPointF &start, const QPointF &end);
};

#endif
