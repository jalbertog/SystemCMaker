#ifndef SVGDRAGGABLEITEM_H
#define SVGDRAGGABLEITEM_H
#include <QtGui>
#include <QGraphicsSvgItem>
#include <QGraphicsSceneMouseEvent>
#include <QPair>
#include <QVector>
#include <QGraphicsLineItem>
#include <PortItem.h>
#include <PropertyComponent.h>

class PolyLinesItem;
/**
* @brief Class for represent a item in with icon in format .svg
*/
class SvgDraggableItem : public QGraphicsSvgItem
{
  public:
    enum { Type = UserType + 1 };

    SvgDraggableItem(const QString &n,QSvgRenderer * renderer,const PropertyComponent &cmp
                                                        , QGraphicsItem* parent = 0);
    void setAnchorPoint(const QPointF& anchorPoint);
    int type() const;
    void setPosToItem(const QPointF &);
    void addWire(PolyLinesItem *wire);
    bool removeWire(PolyLinesItem *wire);
    void deleteAllWires(QGraphicsScene *scene);
    void setScale(qreal factor);
    void setSharedRenderer(QSvgRenderer * renderer);
    void adjustAll();

    void drawText(const QString &text,bool def, const QPoint &p = QPoint());
    void deleteText();
    const PropertyComponent &getPropertyComponent() const;
    const QVector<PortItem *> &inPortsVector() const;
    const QVector<PortItem *> &outPortsVector() const;

    QString name;
  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  private:
    QPointF anchorPoint;
    QList<PolyLinesItem* > wireLines; 
    QVector<PortItem *> inPorts;
    QVector<PortItem *> outPorts;
    QString text;
    QPoint postext;
    int pointFont;

    QPoint middle;

    bool m_dragged;
    QSizeF size;
    PropertyComponent pComponent;
};

#endif
