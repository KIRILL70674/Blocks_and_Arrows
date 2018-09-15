#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QRectF>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <block.h>
#include <myscene.h>
#include <arrow.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    //void mouseDoubleClickEvent(QMouseEvent *);

public slots:

private slots:
    void on_pushButton_clicked();

    //void changeLable(int x);

signals:
    void wannaBlock(void);
private:
    Ui::Dialog *ui;
    MyScene *scene;
};

#endif // DIALOG_H
