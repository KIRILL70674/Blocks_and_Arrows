#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new MyScene (this);
    scene->setSceneRect(ui->graphicsView->geometry());
    ui->graphicsView->setScene(scene);

    connect(this,SIGNAL(wannaBlock()),scene,SLOT(createBlock()));
    //connect(scene,SIGNAL(arrowAdded(int)),this,SLOT(changeLable(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    emit wannaBlock();
}

/*void Dialog::changeLable(int x)
{
    QString text = "Arrows: " + QString::number(x);
    ui->label->setText(text);
}*/
