#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPointF>
#include "block_data.h"

class Connector : public QPointF
{
public:
    Connector();
    void setArrowID(int arrowID_);
    void setAsInput(void);
    void setAsOutput(void);
    bool isOutput(void);
    bool isInput(void);
    bool isConnected(void);
private:
    int arrowID;
    bool output;
    bool input;
    bool Connected;
public slots:
    void receiveData(blockData Data);
signals:
    void sendData(blockData);
};

#endif // CONNECTOR_H
