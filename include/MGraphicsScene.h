#ifndef MGRAPHICSSCENE
#define MGRAPHICSSCENE
#include <QtWidgets>
#include <QGraphicsScene>

class MGraphicsScene : public QGraphicsScene
{
  public:
    MGraphicsScene(QObject *parent = 0);
  protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
  private:
    QPointF initSelection;
    bool press;
};

#endif
