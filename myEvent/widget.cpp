#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    count = 0;
    id1 = startTimer(2000);
    id2 = startTimer(4000);
    id3 = startTimer(10000);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ui->pushButton->setText(tr("%1,%2").arg(event->x()).arg(event->y()));
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    ui->pushButton->setText(tr("%1,%2").arg(event->x()).arg(event->y()));
}

void Widget::keyPressEvent(QKeyEvent *keyEvent)
{
    int x = ui->pushButton->x();
    int y = ui->pushButton->y();
    switch (keyEvent->key())
    {
    case Qt::Key_W: ui->pushButton->move(x, y-10);  break;
    case Qt::Key_S: ui->pushButton->move(x, y+10);  break;
    case Qt::Key_A: ui->pushButton->move(x-10, y);  break;
    case Qt::Key_D: ui->pushButton->move(x+10, y);  break;
    default: break;
    }
}

void Widget::timerEvent(QTimerEvent *timerEvent)
{
    if(timerEvent->timerId() == id1)
    {
        ui->label_1->setText(tr("%1").arg(qrand()%10));
    }
    else if(timerEvent->timerId() == id2)
    {
        ui->label_2->setText(tr("%1").arg(count));
        count++;
    }
    else if(timerEvent->timerId() == id3)
    {
        qApp->quit();

    }
}

void Widget::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-mm-dd hh:mm:ss dddd");
    ui->lineEdit->setText(str);
}
