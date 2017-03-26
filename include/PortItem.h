#ifndef PORTITEM_H
#define PORTITEM_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QRectF>
class PortItem : public QGraphicsEllipseItem
{
    public:
      enum Sig{IN,OUT};
      enum { Type = UserType + 3 };
      PortItem(const QPointF &position,const qreal &rad,Sig  t,QGraphicsItem * parent= 0);
      int type() const;
      inline Sig getType() const { return sig;}
      void setState(int st);
      inline qreal getRadius()const {return radius;}
      QPointF Pos() ;
    protected:
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
    private:
        qreal radius;
        QPointF posi;
        Sig  sig;
        QColor active;
};
#endif