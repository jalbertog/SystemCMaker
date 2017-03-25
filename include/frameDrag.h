#ifndef FRAMEDRAG_H
#define FRAMEDRAG_H
#include <QFrame>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#else
#include <QtGui>
#endif

// class for implement own version of QFrame for contain the icons draggables
class frameDrag : public QFrame
{
  public:
    frameDrag(QWidget *parent = 0);
  private:
    QHash<QLabel *,QString> mapNameGate;        // Map Name for the type of the gate
  protected:
    void dragEnterEvent(QDragEnterEvent *event) ;
    void dragMoveEvent(QDragMoveEvent *event) ;
    void mousePressEvent(QMouseEvent *event) ;

};

#endif