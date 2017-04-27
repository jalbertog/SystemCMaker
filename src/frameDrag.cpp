#include "frameDrag.h"

frameDrag::frameDrag(QWidget *parent)
    : QFrame(parent)
{
  setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
  setAcceptDrops(true);
  QLabel *andGate = new QLabel(this);
  andGate->setPixmap(QIcon(":/SVG/AND_gate.svg").pixmap(QSize(80,80)));
  andGate->move(10, 10);
  andGate->show();
  andGate->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(andGate,QString("AND_gate"));

  QLabel *orGate = new QLabel(this);
  orGate->setPixmap(QIcon(":/SVG/OR_gate.svg").pixmap(QSize(80,80)));
  orGate->move(10, 90);
  orGate->show();
  orGate->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(orGate,QString("OR_gate"));

  QLabel *xorGate = new QLabel(this);
  xorGate->setPixmap(QIcon(":/SVG/XOR_gate.svg").pixmap(QSize(80,80)));
  xorGate->move(10, 170);
  xorGate->show();
  xorGate->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(xorGate,QString("XOR_gate"));

  QLabel *notGate = new QLabel(this);
  notGate->setPixmap(QIcon(":/SVG/NOT_gate.svg").pixmap(QSize(80,80)));
  notGate->move(10, 250);
  notGate->show();
  notGate->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(notGate,QString("NOT_gate"));

  QLabel *input = new QLabel(this);
  input->setPixmap(QIcon(":/SVG/input.svg").pixmap(QSize(80,80)));
  input->move(10, 320);
  input->show();
  input->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(input,QString("input"));

  QLabel *output = new QLabel(this);
  output->setPixmap(QIcon(":/SVG/output.svg").pixmap(QSize(80,80)));
  output->move(10, 380);
  output->show();
  output->setAttribute(Qt::WA_DeleteOnClose);
  mapNameGate.insert(output,QString("output"));

  resize(120,460);
}

// Event when the drag enter in the widget
void frameDrag::dragEnterEvent(QDragEnterEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();                                            
  } 
  else 
    event->ignore();
}

void frameDrag::dragMoveEvent(QDragMoveEvent *event)
{
  if (event->mimeData()->hasText()) 
  {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  } 
  else
    event->ignore();
}


void frameDrag::mousePressEvent(QMouseEvent *event)
{
  QLabel *child = static_cast<QLabel*>(childAt(event->pos()));    //check if click on the icon gate
  if (!child)
    return;

  QPixmap pixmap = *child->pixmap();

  QMimeData *mimeData = new QMimeData;
  mimeData->setText(mapNameGate.value(child));    // Set MimeData (name of gate selected)

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
  drag->setPixmap(pixmap);
  drag->setHotSpot(event->pos() - child->pos());

  // pain opaque pixmap
  QPixmap tempPixmap = pixmap;
  QPainter painter;
  painter.begin(&tempPixmap);
  painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
  painter.end();

  child->setPixmap(tempPixmap);

  if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) 
    child->close();
  else 
  {
    child->show();
    child->setPixmap(pixmap);
  }
}
