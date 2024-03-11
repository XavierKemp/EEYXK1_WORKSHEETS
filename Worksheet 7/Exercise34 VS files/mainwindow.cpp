#include "mainwindow.h"
#include <QMessageBox>
#include "mainwindow.ui"
#include "optiondialog.ui"
#include <QFileDialog.h>
#include "optiondialog.h"
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include "./ui_mainwindow.h"
#include <vtkCylinderSource.h>
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "QVTKOpenGLNativeWidget.h"






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

    // Create a render window
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    ui->QWidget->setRenderWindow(renderWindow);

    // Add a renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // Create an object and add to renderer (this will change later to display a CAD model)
    // Will just copy and paste cylinder example from before
    // This creates a polygonal cylinder model with eight circumferential facets
    // (i.e., in practice an octagonal prism).
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1., 0., 0.35);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    renderer->AddActor(cylinderActor);

    // Reset Camera (probably needs to go in its own function that is called whenever
    // model is changed)
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();


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
/*

void MainWindow::updateRender() {
    renderer->RemoveAllViewProps();
    updateRenderFromTree(partList->index(0, 0, QModelIndex()));
    renderer->Render();
}

void MainWindow::updateRenderer() {
    renderer->RemoveAllViewProps();
    int rows = partList->rowCount(QModelIndex());
    for (int i = 0; i < rows; ++i) {
        updateRenderFromTree(partList->index(i, 0, QModelIndex()));
    }

    renderer->Render();
    ui->treeView->expandAll();
    ui->treeView->update();

    UpdateCamera();
    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) {
        return;
    }


    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
} 
*/


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