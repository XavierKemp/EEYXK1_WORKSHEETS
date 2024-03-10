#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();
    struct ContextMenuData GetMenuData();
    void SetMenuData(ContextMenuData data);

public slots:

private:
    Ui::OptionDialog *ui;
};

struct ContextMenuData {
    unsigned int r, g, b;
    QString name;
    bool isVisible;
};
#endif // OPTIONDIALOG_H
