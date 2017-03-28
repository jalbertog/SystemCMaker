#ifndef GRAPHICSVIEWDROP_H
#define GRAPHICSVIEWDROP_H
#include <QSvgRenderer>
#include <QGraphicsView>
#include <QHash>
#include <SvgDraggableItem.h>
#include <PortItem.h>
#include <QVector>
#include <PropertyComponent.h>

/**
* @brief Class for reimplement methods for the class view
*/
 class GraphicsViewDrop : public QGraphicsView
 {
   public:
    GraphicsViewDrop(QWidget *parent = 0);
    GraphicsViewDrop(QGraphicsScene * scene, QWidget * parent = 0);
    void setRedererTable(QHash<QString,QSvgRenderer *> *render);
    QVector<PropertyComponent> getAllPropertyOfComponent() const ;
    void zoomIn();
    void zoomOut();
  private:
    QHash<QString,QSvgRenderer *> *rendererTable;
    QPoint init;
    int click;
    PortItem  *first;
  protected:
    void dropEvent(QDropEvent * event) ;
    void dragEnterEvent(QDragEnterEvent *event) ;
    void dragMoveEvent(QDragMoveEvent *event) ;
    void mouseDoubleClickEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent *event);
    void scrollContentsBy(int dx, int dy);
  private:
    void scaleView(qreal scaleFactor);
};

#endif
