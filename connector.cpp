#include "connector.h"

Connector::Connector() : QPointF()
{
    arrowID = -1;
    input = false;
    output = false;
    Connected = false;
}

void Connector::setArrowID(int arrowID_)
{
    arrowID = arrowID_;
}

void Connector::setAsInput()
{
    input = true;
    output = false;
    Connected = true;
}

void Connector::setAsOutput()
{
    input = false;
    output = true;
    Connected = true;
}

bool Connector::isOutput()
{
    return output;
}

bool Connector::isInput()
{
    return input;
}

bool Connector::isConnected()
{
    return Connected;
}

void Connector::receiveData(blockData Data)
{
    sendData(Data);
}
