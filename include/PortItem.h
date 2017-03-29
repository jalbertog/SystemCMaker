#ifndef PORTITEM_H
#define PORTITEM_H
#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QRectF>

/**
* @brief Class for paint and hadled the pins of components
*/
class PortItem : public QGraphicsEllipseItem
{
    public:
      enum Sig{IN,OUT};
      enum { Type = UserType + 3 };
      PortItem(const QPointF &position,const qreal &rad,Sig  t,QGraphicsItem * parent= 0);
      int type() const;
      QString getName() const;
      void setName(const QString &n);
      inline Sig getType() const { return sig;}
      void setState(int st);
      inline qreal getRadius()const {return radius;}
      QPointF Pos() ;
    protected:
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
        void mousePressEvent(QGraphicsSceneMouseEvent * event);

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    private:
        qreal radius;
        const qreal org;
        QPointF posi;
        Sig  sig;
        QColor active;
        QPen pen;
        QString name;
};
#endif
