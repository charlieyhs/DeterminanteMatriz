#ifndef DETERMINANTELINEEDITDIALOG_H
#define DETERMINANTELINEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class DeterminanteLineEditDialog;
}

class DeterminanteLineEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeterminanteLineEditDialog(const QString &valor, QWidget *parent = nullptr);
    ~DeterminanteLineEditDialog();

private:
    Ui::DeterminanteLineEditDialog *ui;
};

#endif // DETERMINANTELINEEDITDIALOG_H
