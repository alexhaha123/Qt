#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QLineEdit>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUnStocked = true;
    curFile = tr("未命名.txt");
    setWindowTitle(curFile);

    //findDialog
    findDialog = new QDialog(this);
    findDialog->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDialog);
    QPushButton* nextButton = new QPushButton(tr("查找下一个"), findDialog);
    QVBoxLayout* layout = new QVBoxLayout(findDialog);
    layout->addWidget(findLineEdit);
    layout->addWidget(nextButton);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(showFindText()));

    //状态栏
    ui->statusBar->showMessage(tr("欢迎来到alex的记事本"), 5000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile()
{
    if(maySave())
    {
       isUnStocked = true;
       curFile = tr("未命名.txt");
       setWindowTitle(curFile);
       ui->textEdit->clear();
       ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maySave()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(tr("警告!"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + tr("尚未保存,是否保存?"));
        QPushButton* yesButton = box.addButton(tr("是&Y"), QMessageBox::YesRole);
        box.addButton(tr("否&N"), QMessageBox::NoRole);
        QPushButton* cancelButton = box.addButton(tr("取消"),QMessageBox::RejectRole);
        box.exec();

        if(box.clickedButton() == yesButton)
        {
            return save();
        }else if(box.clickedButton() == cancelButton)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::save()
{
    if(isUnStocked)
    {
        return saveAs();
    }else
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), curFile);
    if(filename.isEmpty()) return false;
    return saveFile(curFile);
}

bool MainWindow::saveFile(const QString& fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("多文档编辑器"), tr("无法写入文件 %1 /n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUnStocked = false;
    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);

    return true;
}

//加载文件
bool MainWindow::loadFile(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("多文档编辑器"),tr("无法读取文件!"));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlaceholderText(in.readAll());
    QApplication::restoreOverrideCursor();

    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);

    return true;
}

void MainWindow::on_actionNew_file_triggered()
{
    newFile();
}

void MainWindow::on_action_store_triggered()
{
    save();
}

void MainWindow::on_action_OtherStock_triggered()
{
    saveAs();
}

void MainWindow::on_action_Open_triggered()
{
    if(maySave())
    {
       QString fileName = QFileDialog::getOpenFileName(this);
       if(!fileName.isEmpty())
       {
           loadFile(fileName);
           ui->textEdit->setVisible(true);
       }
    }
}

//关闭
void MainWindow::on_action_Close_triggered()
{
    if(maySave())
    {
       ui->textEdit->setVisible(false);
    }
}

//退出
void MainWindow::on_action_Exit_triggered()
{
    on_action_Close_triggered();
    qApp->quit();
}

//撤销
void MainWindow::on_action_chexiao_triggered()
{
    ui->textEdit->undo();
}

//剪切
void MainWindow::on_action_jiantie_triggered()
{
    ui->textEdit->cut();
}

//复制
void MainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
}

//黏贴
void MainWindow::on_action_paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if(!ui->textEdit->find(str, QTextDocument::FindBackward))
    {
        QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
    }
}

void MainWindow::on_action_find_triggered()
{
    findDialog->show();
}
