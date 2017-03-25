#include <MGraphicsScene.h>

MGraphicsScene::MGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{}

void MGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    qDebug() <<"Pos double: "<< mouseEvent->scenePos();
    //QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}