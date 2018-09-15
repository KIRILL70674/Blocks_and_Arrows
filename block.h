#ifndef BLOCK_H
#define BLOCK_H

#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QWidget>

#include <connector.h>
#include <block_data.h>

class Block : public QGraphicsObject
{
    Q_OBJECT

public:

    enum { Type = UserType + 1 };
    int type() const;

    Block(QPointF Start, QString Name_ = "Hello World!!!");

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QPointF HLPoint(void);//Return highlighted point position or zeroPoint
    void setName(QString Text = "Hello World!!!");
    void setID(unsigned ID_);
    unsigned getID(void);
    qreal getHeight(void);
    qreal getWidth(void);
    static bool belong(QRectF Rec, QPointF pos);

    virtual void keyPressEvent(QKeyEvent *event);
    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
    void mouseRelesed(QGraphicsSceneMouseEvent *event);
    void mouseLeftClick(QGraphicsSceneMouseEvent *event);
    void mouseRightClick(QGraphicsSceneMouseEvent *event);
    void sendData(blockData);

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void deleteItself(void);
    void addConnector(void);
    void addInputConnector(void);
    void circleBlock(void);
    void receiveData(blockData Data_);
    blockData getData(void);


private:
    unsigned ID;
    QString Name;
    QString paintKey;
    bool wannaMove;
    bool inputAdded;//For input connector detection
    QList<Connector> Connectors;//If input exist -> it have a [0] position
    int HLConnector;//Highlighted connector
    qreal height, width;
    qreal FontSize,
        connectorLength,
        interval;// Distance between block's parts
    qreal differenceX ,differenceY;//Difference between topleft corner
                        //of bound_rect and current cursor
    QPointF currMousePos;//Highlighted connector
    unsigned HLRad;//Radious of highlighted circle
    blockData Data;
};

#endif // BLOCK_H
