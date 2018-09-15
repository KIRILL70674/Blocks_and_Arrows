#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsObject>
#include <QPainter>
#include <QBrush>
#include <qmath.h>
#include <QDebug>

#include "block.h"
#include "block_data.h"

class Arrow : public QGraphicsObject
{
    Q_OBJECT

public:
     enum { Type = UserType + 2 };
     int type() const;
     Arrow(void);
     Arrow(Block *startBlock_);

     QRectF boundingRect() const;
     QPainterPath shape() const;

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

     void changeGeometry(QPointF newEnd);//Change the end of the arrow
     void endArrow(Block *endBlock_);
     void setID(unsigned ID_);
     unsigned getID(void);

private:
    QList<QPointF> Path;
    QVector<QPointF> headPath;
    bool arrowEnded;
    unsigned ID;

    Block* startBlock;
    Block* endBlock;

    unsigned interval;

    QPointF findTopLeft(void) const;
    QPointF findBottomRight(void) const;

public slots:
    void receiveData(blockData Data);
    void deleteItself(void);
signals:
    void sendData(blockData);
};

#endif // ARROW_H
