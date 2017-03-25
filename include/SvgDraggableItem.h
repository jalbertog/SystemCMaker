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

    QString name;
  protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
  private:
    QPointF anchorPoint;
    QList<PolyLinesItem* > wireLines; 
    QVector<PortItem *> inPorts;
    QVector<PortItem *> outPorts;
    bool m_dragged;
    QSizeF size;
    PropertyComponent pComponent;
};

#endif
