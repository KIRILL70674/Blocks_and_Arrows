#include "arrow.h"

int Arrow::type() const
{
    return Type;
}

Arrow::Arrow(void) : QGraphicsObject()
{}

Arrow::Arrow(Block* startBlock_)
{
    interval = 20;
    arrowEnded = false;
    startBlock = startBlock_;
    Path.push_back(startBlock_->HLPoint());
}

QRectF Arrow::boundingRect() const
{
    return QRectF(findTopLeft(),findBottomRight());
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsItem::shape();
    path.addRect(boundingRect());
    return path;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
        QBrush brush(Qt::black);
        painter->setPen(QPen(brush, 3));
        if(Path.length()>1)
        for(int i = 0; i<Path.length()-1; i++)
            painter->drawLine(Path.at(i),Path.at(i+1));
   /*Draw the Arrow Head*/
        if(arrowEnded)
        {
            painter->setBrush(brush);
            painter->setPen(QPen(brush, 1));
            brush.setStyle(Qt::SolidPattern);
            QPolygonF poly(headPath);
            painter->drawPolygon(poly);
        }
//qDebug()<<Path.length();
}

void Arrow::changeGeometry(QPointF newEnd)
{
    prepareGeometryChange();
    if(Path.length()==1)
    {
        Path.push_back(mapFromScene(newEnd));
        return;
    }
    Path.last() = mapFromScene(newEnd);
}

void Arrow::endArrow(Block* endBlock_)
{
/*There is two types of arrow
 first - start Y < end Y
 second - start X > end Y*/
    prepareGeometryChange();
    QPointF startPoint = Path.first(), endPoint, P;
        endPoint = Path.last();
        Path.clear();
        endPoint.setX(endBlock_->HLPoint().rx());
        endPoint.setY(endBlock_->HLPoint().ry());
    if(startPoint.ry() <= endPoint.ry())
    {
        Path.push_back(startPoint);
            P.setX(startPoint.rx());
            P.setY(startPoint.ry()+fabs(endPoint.ry()-startPoint.ry())/2);
        Path.push_back(P);
            P.setX(endPoint.rx());
        Path.push_back(P);
        Path.push_back(endPoint);
    }
    else
    {
        Path.push_back(startPoint);
            P.setX(startPoint.rx());
            P.setY(startPoint.ry()+interval);
        Path.push_back(P);
            P.setX(startPoint.rx()+fabs(endPoint.rx()-startPoint.rx())/2);
        Path.push_back(P);
            P.setY(endPoint.ry()-interval);
        Path.push_back(P);
            P.setX(endPoint.rx());
        Path.push_back(P);
        Path.push_back(endPoint);
    }
    headPath.push_back(Path.last());
    headPath.push_back(QPointF(Path.last().rx()+interval/4, Path.last().ry()-interval/2));
    headPath.push_back(QPointF(Path.last().rx()-interval/4, Path.last().ry()-interval/2));
    arrowEnded = true;
}

void Arrow::setID(unsigned ID_)
{
    ID = ID_;
}

unsigned Arrow::getID()
{
    return ID;
}

QPointF Arrow::findTopLeft(void) const
{
    qreal minX = 0, minY = 0;
    foreach (QPointF P, Path)
    {
        if(P.rx()<=minX) minX = P.rx();
        if(P.ry()<=minY) minY = P.ry();
    }
    foreach (QPointF P, headPath)
    {
        if(P.rx()<=minX) minX = P.rx();
        if(P.ry()<=minY) minY = P.ry();
    }
    return QPointF(minX,minY);
}

QPointF Arrow::findBottomRight(void) const
{
    qreal maxX = 0, maxY = 0;
    foreach (QPointF P, Path)
    {
        if(P.rx()>=maxX) maxX = P.rx();
        if(P.ry()>=maxY) maxY = P.ry();
    }
    foreach (QPointF P, headPath)
    {
        if(P.rx()>=maxX) maxX = P.rx();
        if(P.ry()>=maxY) maxY = P.ry();
    }
    return QPointF(maxX,maxY);
}

void Arrow::receiveData(blockData Data)
{
    emit sendData(Data);
}

void Arrow::deleteItself()
{
    delete this;
}
