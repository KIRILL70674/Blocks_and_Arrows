#include "myscene.h"
#include "block.h"

bool MyScene::belong(QRectF Rec, QPoint pos)
{
    qreal topLeftX, topLeftY, bottomRightX, bottomRightY;
    Rec.getCoords(&topLeftX, &topLeftY, &bottomRightX, &bottomRightY);
        if(pos.rx()>=topLeftX&&pos.rx()<=bottomRightX)
            if(pos.ry()>=topLeftY&&pos.ry()<=bottomRightY)
                return true;
        return false;
}

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent)
{
    arrowCreation = false;
    currentQItem = 0;
    currentArrowItem = 0;
    currentBlockItem = 0;
    previousBlockItem = 0;
    previousItemID = -1;
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
        currentQItem = itemAt(event->scenePos(), QTransform());
        if(currentQItem!=0 && currentQItem->type() == Block::Type)
        {
            currentBlockItem = qgraphicsitem_cast<Block *>(currentQItem);
            currentBlockItem->mouseMoveEvent(event);
            currentHighlightedPoint = currentBlockItem->HLPoint();
        }
        else
        {
            currentHighlightedPoint = zeroPoint;//If no points had been highlighted
            foreach(QGraphicsItem *item, items())//reset all of highlighted connectors
            {
                if(item->type() == Block::Type)
                {
                    currentBlockItem = qgraphicsitem_cast<Block *>(item);
                    currentBlockItem->update(currentBlockItem->boundingRect());
                }
            }
        }
        if(arrowCreation && currentArrowItem != 0)//Control the arrow
        {
            currentArrowItem->changeGeometry(event->scenePos());
            if(previousItemID == -1) previousItemID = currentBlockItem->getID();
        }
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
/*Decision 'bout Arrow creation*/
    if(currentHighlightedPoint != zeroPoint)
        arrowCreation = true;
    else
        arrowCreation = false;
/*If we want to make the Arrow...*/
if(arrowCreation)
    //createArrow(currentHighlightedPoint,event->scenePos());
    createArrow(currentBlockItem);
else
{
    currentQItem = itemAt(event->scenePos(), QTransform());
    if(currentQItem!=0 && currentQItem->type() == Block::Type)
    {
        if(QApplication::keyboardModifiers() != Qt::ControlModifier)//If Ctrl isn't pushed
            foreach(QGraphicsItem *item, items())//reset Selected Rect of all items
        if(item->type() == Block::Type)
        {
            currentBlockItem = qgraphicsitem_cast<Block *>(item);
            currentBlockItem->setSelected(false);
            currentBlockItem = 0;
        }
        currentBlockItem = qgraphicsitem_cast<Block *>(currentQItem);
        currentBlockItem->setSelected(true);
        currentBlockItem->mousePressEvent(event);
    }
    else/*Reset all selected Items if empty space chosen*/
         foreach(QGraphicsItem *item, items())
             if(item->type() == Block::Type)
             {
                currentBlockItem = qgraphicsitem_cast<Block *>(item);
                currentBlockItem->setSelected(false);
             }
}
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(arrowCreation)
    {
        //qDebug()<<"CurID "<<currentBlockItem->getID()<<"PrevID "<<previousItemID;
        if(!currentHighlightedPoint.isNull() && currentBlockItem->getID() != previousItemID)
        {
            //currentArrowItem->changeGeometry(currentHighlightedPoint);
            currentArrowItem->endArrow(currentBlockItem);
            currentArrowItem = 0;
            previousItemID = -1;
        }
        else
        {
            currentArrowItem->deleteItself();
            currentArrowItem = 0;
        }
        arrowCreation = false;
    }
    else
        if(currentBlockItem!=0)
            currentBlockItem->mouseReleaseEvent(event);
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    foreach(QGraphicsItem *item, selectedItems())
    {
        if(item->type() == Block::Type)
        {
            Block *b_ = qgraphicsitem_cast<Block *>(item);
            b_->keyPressEvent(event);
        }
    }
}

void MyScene::createBlock()
{
    currentBlockItem = new Block(sceneRect().center());
    addItem(currentBlockItem);
    currentBlockItem->setID(items().length()-1);//Set ID in items stack order
    //qDebug()<<"curB_ID"<<currentBlockItem->getID();
    currentBlockItem = 0;
}

void MyScene::createArrow(Block* currentBlockItem_)
{
    //currentArrowItem = new Arrow(startPoint,endPoint);
    currentArrowItem = new Arrow(currentBlockItem_);
    addItem(currentArrowItem);
    currentArrowItem->setID(items().length()-1);//Set ID in items stack order
    //qDebug()<<"curA_ID"<<currentArrowItem->getID();
}
