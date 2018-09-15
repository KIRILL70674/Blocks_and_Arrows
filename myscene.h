#ifndef MYSCENE_H
#define MYSCENE_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QTransform>
#include <QtDebug>
#include <qmath.h>

#include <arrow.h>
#include <block.h>

class MyScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit MyScene(QObject *parent = 0);
    virtual ~MyScene() {}

    static bool belong(QRectF Rec, QPoint pos);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void createBlock(void);
    //void createArrow(QPointF startPoint, QPointF endPoint);
    void createArrow(Block* currentBlockItem_);

signals:
    void wannaArrow(void);
    //void arrowAdded(int);
private:
    const QPointF zeroPoint;
    bool arrowCreation;
    QGraphicsItem *currentQItem;//QItem that has been selected at the current moment
    Arrow *currentArrowItem;//For Arrow creation
    Block *currentBlockItem, *previousBlockItem;
    QPointF currentHighlightedPoint;
    int previousItemID;
};

#endif // MYSCENE_H
