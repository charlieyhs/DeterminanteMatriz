#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
class QStandardItemModel;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_ordenSpinBox_valueChanged(int arg1);

    void on_determinantePushButton_clicked();

    void on_salirPushButton_clicked();

private:
    double getValueAt(int ix, int jx) const;
    double **convertToDoublePointer()const;
    double calculateDeterminant(double **a, int order);
    void deleteDoublePointer(double ***a) const;

    Ui::Widget *ui;
    QStandardItemModel *mModel;
};
#endif // WIDGET_H
