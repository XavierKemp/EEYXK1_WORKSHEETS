#include "mainwindow.h"
#include <QMessageBox>
#include "./ui_mainwindow.h"
#include "./ui_optiondialog.h"
#include <QFileDialog.h>
#include "optiondialog.h"
#include <EWIEGA46WW/moc_mainwindow.cpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui-> pushButton, &QPushButton::released, this, &MainWindow :: handleButton);
    connect(ui-> pushButton_2, &QPushButton::released, this, &MainWindow::handleButton2);
    connect(ui-> treeView , &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    ui->treeView->addAction(ui->actionItem_Options);

    rootItem = nullptr;

    // Create/allocate the ModelList
    this->partList = new ModelPartList("Parts List");

    // Link it to the tree view in the GUI
    ui->treeView->setModel(this->partList);

    // Manually create a model tree - there are much better and more flexible ways of doing this,
    // e.g., with nested functions. This is just a quick example as a starting point.
    ModelPart* rootItem = this->partList->getRootItem();

    // Add 3 top level items
    for (int i = 0; i < 3; i++) {
        // Create strings for both data columns
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        // Create child item
        ModelPart* childItem = new ModelPart({ name, visible });

        // Append to tree top-level
        rootItem->appendChild(childItem);

        // Add 5 sub-items
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });

            // Append to parent
            childItem->appendChild(childChildItem);
        }
    }
}





void MainWindow::handleButton() {
   QMessageBox msgBox;
   msgBox.setText("Add button was clicked");
   msgBox.exec();
   emit statusUpdateMessage(QString("Add button was clicked "), 0);
}

void MainWindow::handleButton2() {
    OptionDialog dialog(this); // Creating an instance of OptionDialog
    // Showing the dialog
    struct ContextMenuData menuData;

    menuData.name = rootItem->data(0).toString();
    menuData.isVisible = rootItem->data(1).toBool();

    dialog.SetMenuData(menuData);
    if (dialog.exec() == QDialog::Accepted) { // Checking if the dialog was accepted
        emit statusUpdateMessage(QString("Dialog accepted"), 0); // Emitting a signal with a message
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected"), 0); // Emitting a different signal with a message
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleTreeClicked()
{
    QModelIndex index = ui->treeView->currentIndex();


    emit statusUpdateMessage(QString("The selected item is: "), 0);
}

void MainWindow::on_actionOpen_File_triggered()
{
    emit statusUpdateMessage(QString("Open File action triggered" ), 0 );
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)"));
    emit statusUpdateMessage(QString(fileName), 0);
}

void MainWindow::on_actionItem_Options_triggered() {

    OptionDialog();
}


void MainWindow::OpenOptionDialog() {
    if (rootItem == nullptr) return;

    OptionDialog dialog(this);

    struct ContextMenuData menuData;

    menuData.name = rootItem->data(0).toString();
    menuData.isVisible = rootItem->data(1).toBool();

    dialog.SetMenuData(menuData);



    if (dialog.exec() == QDialog::Accepted) {
        struct ContextMenuData color = dialog.GetMenuData();


        rootItem ->set(0, color.name);
        rootItem->set(1, QVariant(color.isVisible).toString());
        rootItem->setVisible(color.isVisible);


        emit statusUpdateMessage(QString("Dialog accepted "), 0);
    }
    else {
        emit statusUpdateMessage(QString("Dialog rejected "), 0);
    }
}