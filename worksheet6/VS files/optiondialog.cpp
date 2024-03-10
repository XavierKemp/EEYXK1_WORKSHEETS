#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
    show();


}

OptionDialog::~OptionDialog()
{
    delete ui;
}

struct ContextMenuData OptionDialog::GetMenuData() {
    struct ContextMenuData menuData;

    menuData.isVisible = ui->checkBox->isChecked();
    menuData.name = ui->textEdit->toPlainText();

    return menuData;
}
void OptionDialog::SetMenuData(ContextMenuData data) {

    ui->textEdit->setText(data.name);
    ui->checkBox->setChecked(data.isVisible);

}