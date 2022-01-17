#include "widget.h"
#include "ui_widget.h"
#include "doublespinboxdelegate.h"
#include "determinantelineeditdialog.h"
#include <QtMath>
#include <QStandardItemModel>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mModel = new QStandardItemModel(this);
    ui->tableView->setModel(mModel);
    ui->tableView->setItemDelegate(new DoubleSpinBoxDelegate(this));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_ordenSpinBox_valueChanged(int arg1)
{
    mModel->setRowCount(arg1);
    mModel->setColumnCount(arg1);

}

void Widget::on_determinantePushButton_clicked()
{
    double **a = convertToDoublePointer();
    const int orden = mModel->rowCount();
    const double determinante = calculateDeterminant(a,orden);
    deleteDoublePointer(&a);
    DeterminanteLineEditDialog d(QString::number(determinante),this);
    d.exec();
}

void Widget::on_salirPushButton_clicked()
{
    close();
}

double Widget::getValueAt(int ix, int jx) const
{
    if(!mModel->item(ix,jx)){
        return 0.0;
    }
    return mModel->item(ix,jx)->text().toDouble();
}

double **Widget::convertToDoublePointer() const
{
    const int rowCount = mModel->rowCount();
    const int colCount = mModel->columnCount();

    double **matrix = new double*[rowCount];

    for(int ix=0;ix<rowCount;ix++){
        matrix[ix] = new double[colCount];
        for(int jx=0;jx<colCount;jx++){
            matrix[ix][jx] = getValueAt(ix,jx);
        }
    }
    return matrix;
}

double Widget::calculateDeterminant(double **a, int order)
{
    double det = 0.0;
    double **m = nullptr;
    if(order<1){
        return 0.0;
    }else if(order == 1){
        det = a[0][0];
    }else if(order == 2){
        det = a[0][0]*a[1][1]-a[1][0]*a[0][1];
    }else{
        for(int jx=0;jx<order;jx++){
            m = new double*[order-1];
            for(int hx =0;hx<order-1;hx++){
                m[hx] = new double[order-1];
            }
            for(int hx = 1;hx<order;hx++){
                int kx = 0;
                for(int ix = 0;ix<order;ix++){
                   if(ix == jx) {
                       continue;
                   }
                   m[hx-1][kx] = a[hx][ix];
                   kx++;
                }
            }
            det += pow(-1.0, 1.0+jx+1.0)*a[0][jx]*calculateDeterminant(m,order-1);
            for(int hx=0;hx<order-1;hx++){
                delete[] m[hx];
            }
            delete[]m;
        }
    }
    return det;
}

void Widget::deleteDoublePointer(double ***a) const
{
    const int rowCount = mModel->rowCount();
    for(int ix=0;ix<rowCount;ix++){
        delete [] (*a)[ix];
    }
    delete[] *a;
    *a = nullptr;
}
