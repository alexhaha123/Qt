#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QPixmap>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{

  QPainter painter(this);
  QPixmap pix;
  //pix.load("/Users/zhouzhan/Qt/painter_1/logo.png");      //绝对路径
  pix.load(":/image/logo.png");         //在资源管理下的相对路径
  painter.drawPixmap(0,0,110,110,pix);

  painter.translate(100,100);
  painter.rotate(90);
  painter.drawPixmap(0,0,110,110,pix);

//  qreal width = pix.width();
//  qreal height = pix.height();
//  pix = pix.scaled(width*2, height*2, Qt::KeepAspectRatio);
//  painter.drawPixmap(70,70,pix);

//  pix = pix.scaled(width,height);
//  painter.translate(64,60);
//  painter.rotate(90);
//  painter.translate(-64, -60);
//  painter.drawPixmap(0,0,pix);

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    ui->pushButton->setText(tr("%1,%2").arg(e->x()).arg(e->y()));
}
