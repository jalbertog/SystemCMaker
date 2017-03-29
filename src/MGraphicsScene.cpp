#include <MGraphicsScene.h>

MGraphicsScene::MGraphicsScene(QObject *parent) : QGraphicsScene(parent), press(false)
{}

void MGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() <<"Pos double: "<< mouseEvent->scenePos();
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

void MGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Press event";
    initSelection = event->scenePos();
    press = true;
    //clearSelection();
    QGraphicsScene::mousePressEvent(event);
}

void MGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if(press)
  {
    qDebug() << "MOve";
    QPointF current = event->scenePos();
    QSizeF siz(qAbs(initSelection.x()-current.x()),qAbs(initSelection.y()-current.y()));
    QRectF rect(initSelection,siz);
    QPainterPath p;
    p.addRect(rect.normalized());
    qDebug() << rect;
    //setSelectionArea(p);
    update();
  }

  QGraphicsScene::mouseMoveEvent(event);
}

void MGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    press = false;
    QGraphicsScene::mouseReleaseEvent(event);
}
