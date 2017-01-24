#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPen>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    resize(600,500);
    pix = QPixmap(600,500);
    pix.fill(Qt::white);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *paintEvent)
{
    QPen pen;  // creates a default pen
    pen.setWidth(3);
    pen.setBrush(Qt::red);
    QPainter pp(&pix);
    pp.setPen(pen);

    pp.drawLine(lastPoint, endPoint);
    lastPoint = endPoint;



    QPainter painter(this);
    painter.drawPixmap(0,0,pix);
}

void Dialog::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton){
        lastPoint = event->pos();
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons()&Qt::LeftButton){
        qDebug() << event->pos();
        endPoint = event->pos();
        update();
    }

}

void Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        endPoint = event->pos();
        update();
    }
}
