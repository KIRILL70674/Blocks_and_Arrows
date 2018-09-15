#include "block.h"

bool Block::belong(QRectF Rec, QPointF pos)
{
    qreal topLeftX, topLeftY, bottomRightX, bottomRightY;
    Rec.getCoords(&topLeftX, &topLeftY, &bottomRightX, &bottomRightY);
        if(pos.rx()>=topLeftX&&pos.rx()<=bottomRightX)
            if(pos.ry()>=topLeftY&&pos.ry()<=bottomRightY)
                return true;
        return false;
}

int Block::type() const
{
    return Type;
}

Block::Block(QPointF Start, QString Name_) : QGraphicsObject()
{
    setPos(Start);
    Name = Name_;
    HLRad = 2;
    FontSize = 20;
    connectorLength = 10;
    interval = 5;
    width = interval*2 + Name.length()*FontSize/1.3;
    height = connectorLength*6+FontSize;
    setFlag(ItemIsMovable,true);
    setFlag(ItemIsSelectable,true);
    wannaMove = false;
    inputAdded = false;
    HLConnector = -1;//It mean that no connectors have been highlighted
}

QRectF Block::boundingRect() const
{
    return QRectF(0,0,width,height);
}
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);
    QPointF Beginning, End, textBeginning, inputPointEnd;
    QFont font("Arial", FontSize);
    qreal partLength,//It need for connectors and its bounding rect-s
        LineLength;

    //wannaArrow_ = false;
    LineLength = width;

        painter->setPen(QPen(brush, 3));
        Beginning.setX(rec.topLeft().rx());
        Beginning.setY(rec.topLeft().ry()+connectorLength*4+FontSize);
        End.setX(LineLength);
        End.setY(Beginning.ry());
        textBeginning.setX(LineLength/2 - Name.length()*FontSize/3.5);//Set text in the middle
        textBeginning.setY(FontSize*2+interval);//The position of the text depends on the position of the line

        painter->drawLine(Beginning,End);
        painter->setFont(font);
        painter->drawText(textBeginning,Name);
/*Draw and Add connectors*/
        if(paintKey == "addConnect" || paintKey == "addInputConnector")
        {
            Connector EndCon;
            //QPointF EndCon;
            if(inputAdded)
            {
                EndCon.setAsInput();
                connect(EndCon,SIGNAL(sendData()),this,SLOT(receiveData(blockData)))
            }
            Connectors.push_back(EndCon);
            paintKey.clear();
        }
            QPointF BegCon;//Beginning of connector
            if(inputAdded)
                partLength = LineLength/(Connectors.length());
            else
                partLength = LineLength/(Connectors.length()+1);//"1" cause input
                                                //connector out of count
            for(int i = 0; i<Connectors.length(); i++)
            {
                /*Draw input connector*/
                if(i == 0 && inputAdded == true)
                {
                    inputPointEnd.setX(LineLength/2);
                    inputPointEnd.setY(FontSize-interval);
                    Connectors[i].setX(inputPointEnd.rx());
                    Connectors[i].setY(inputPointEnd.ry()-connectorLength);
                    painter->drawLine(Connectors[i],inputPointEnd);
                    continue;
                }
                if(inputAdded)
                    BegCon.setX(partLength*i);
                else
                    BegCon.setX(partLength*(i+1));
                BegCon.setY(Beginning.ry());
                Connectors[i].setX(BegCon.rx());
                Connectors[i].setY(Beginning.ry()+connectorLength);//length of connector
                painter->setPen(QPen(brush, 3));
                painter->drawLine(BegCon,Connectors.at(i));
            }
/*Highlight connector with black circle*/
            if(paintKey == "highlight")
            {
                painter->setPen(QPen(brush, 3));
                painter->setBrush(brush);
                QPointF CMP = mapFromScene(currMousePos);
                partLength = partLength/2;
                qreal partLengthDEV2 = partLength/2;//For making "boundingConnRect"
                QRectF boundingConnRect;
                for(int i = 0; i<Connectors.length(); i++)
                {
                    QPointF topLeft;
                        topLeft.setX(Connectors[i].rx()-partLengthDEV2);//Set Rect's centert
                        topLeft.setY(Connectors[i].ry()-partLengthDEV2);//in Connector's point
                        boundingConnRect.setRect(topLeft.rx(),topLeft.ry()
                                          ,partLength,partLength);//Bounding connectors
                        if(belong(boundingConnRect, CMP))
                        {
                            QPointF HLPoint;
                            painter->drawEllipse(Connectors[i],HLRad,HLRad);
                            HLPoint.setX(Connectors[i].rx());
                            HLPoint.setY(Connectors[i].ry());
                            HLConnector = i;
                            break;
                        }
                        else
                            HLConnector = -1;
                }
                paintKey.clear();
            }
/*Circle boundingRec with DashLine*/
            if(paintKey == "addContour" || this->isSelected())
            {
                painter->setBrush(Qt::NoBrush);
                painter->setPen(QPen(brush, 1, Qt::DashLine));
                painter->drawRect(rec);
                paintKey.clear();
            }
    //paintKey.clear();
}

QPointF Block::HLPoint(void)
{
    QPointF zeroPoint;
    paintKey = "highlight";
    update();
    if(HLConnector != -1)
    {
        if(Connectors[HLConnector].isConnected())
            return zeroPoint;
        else
        {
            QPointF P;
            P.setX(Connectors[HLConnector].rx());
            P.setY(Connectors[HLConnector].ry());
            return mapToScene(P);
        }
    }
    else
        return zeroPoint;
}

void Block::setName(QString Text)
{
    Name = Text;
}

void Block::setID(unsigned ID_)
{
    ID = ID_;
}

unsigned Block::getID(void)
{
    return ID;
}

qreal Block::getHeight()
{
    return height;
}

qreal Block::getWidth()
{
    return width;
}

void Block::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    /* Create an object context menu */
    QMenu *menu = new QMenu();
    /* Create actions to the context menu */
    QAction *deleteItem = new QAction(trUtf8("Удалить"), menu);
    QAction *addInputConnector = new QAction(trUtf8("Добавить вход"), menu);
    QAction *addConnector = new QAction(trUtf8("Добавить выход"), menu);
    /* Connect slot handlers for Action pop-up menu */
    connect(deleteItem,SIGNAL(triggered()),this,SLOT(deleteItself()));
    connect(addConnector,SIGNAL(triggered()),this,SLOT(addConnector()));
    connect(addInputConnector,SIGNAL(triggered()),this,SLOT(addInputConnector()));
    /* Set the actions to the menu */
    menu->addAction(deleteItem);
    menu->addAction(addConnector);
    menu->addAction(addInputConnector);
    /* Call the context menu */
    QAction *a = menu->exec(event->screenPos());
    Q_UNUSED(a);
    delete menu;
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && HLConnector == -1)//If we wanna make the
    {                                       //arrow we can't move Item
        differenceX = event->scenePos().rx() - scenePos().rx();
        differenceY = event->scenePos().ry() - scenePos().ry();
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        wannaMove = true;
    }
}

void Block::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
     /*Set the position of the graphical element in the graphic scene,
     * translate coordinates of the cursor within the graphic element
     * in the coordinate system of the graphic scenes
     * */
    currMousePos = event->scenePos();
    if(wannaMove && HLConnector == -1)
        setPos(event->scenePos().rx()-differenceX,event->scenePos().ry()-differenceY);
}

void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && wannaMove) {
            this->setCursor(QCursor(Qt::ArrowCursor));
            wannaMove = false;
        }
    Q_UNUSED(event);
    //emit mouseRelesed(event);
}

void Block::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Right:
        moveBy(10,0);
        break;
    case Qt::Key_Left:
        moveBy(-10,0);
        break;
    case Qt::Key_Up:
        moveBy(0,-10);
        break;
    case Qt::Key_Down:
        moveBy(0,10);
        break;
    case Qt::Key_Delete:
        deleteItself();
        break;
    case Qt::Key_F1:
        addConnector();
        break;
    case Qt::Key_F2:
        addInputConnector();
        break;
    default:
        break;
    }
    update();
}

/*QVariant block::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)
        {
            // do stuff if selected
            //paintKey = "addContour";
            //update();
            //emit needToUpdate();
            //paintKey.clear();
        }
        else
        {
            // do stuff if not selected
        }
    }

    return QGraphicsItem::itemChange(change, value);
}*/

void Block::deleteItself(void)
{
    delete this;
}

void Block::addConnector(void)
{
    paintKey = "addConnect";
    update();
}

void Block::addInputConnector(void)
{
    if(!inputAdded)
    {
        paintKey = "addInputConnector";
        inputAdded = true;
        update();
    }
}

void Block::circleBlock(void)
{
    paintKey = "addContour";
    update();
}

void Block::receiveData(blockData Data_)
{
    Data = Data_;
}

blockData Block::getData()
{
    return Data;
}
