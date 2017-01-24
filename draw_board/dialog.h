#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
class QPaintEvent;
class QMouseEvent;
class QPixmap;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void paintEvent(QPaintEvent* paintEvent);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    Ui::Dialog *ui;

    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;
};

#endif // DIALOG_H
