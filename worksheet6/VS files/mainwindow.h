#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QFileDialog.h>
#include "optiondialog.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;
    ModelPart* rootItem;
    QModelIndex selectedIndex;
    ModelPart* index;
    void OpenOptionDialog();

public slots:
    void handleButton();
    void handleButton2();
    void handleTreeClicked();
    signals:
        void statusUpdateMessage(const QString & message, int timeout);


    private slots:
        void on_actionOpen_File_triggered();
        void on_actionItem_Options_triggered();


};
#endif // MAINWINDOW_H
