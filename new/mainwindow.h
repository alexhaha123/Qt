#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QLineEdit;
class QDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void newFile();
    bool maySave();
    bool save();
    bool saveAs();
    bool saveFile(const QString& fileName);
    bool loadFile(const QString& fileName);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_file_triggered();

    void on_action_store_triggered();

    void on_action_OtherStock_triggered();

    void on_action_Open_triggered();

    void on_action_Close_triggered();

    void on_action_Exit_triggered();

    void on_action_chexiao_triggered();

    void on_action_jiantie_triggered();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void showFindText();

    void on_action_find_triggered();

private:
    Ui::MainWindow *ui;

    bool isUnStocked; //文件是否被保存
    QString curFile;    //保存当前文件的路径

    QLineEdit* findLineEdit;
    QDialog* findDialog;
};

#endif // MAINWINDOW_H
