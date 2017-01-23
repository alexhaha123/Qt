#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QMouseEvent;
class QKeyEvent;
class QTimerEvent;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *keyEvent);
    void timerEvent(QTimerEvent *timerEvent);

private slots:
    void timerUpdate();
private:
    Ui::Widget *ui;
    int id1, id2, id3;
    int count;
};

#endif // WIDGET_H
