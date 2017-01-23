/* QT里的事件  */

#include "widget.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
