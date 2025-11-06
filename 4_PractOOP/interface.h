#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include "polynom.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class interface;
}
QT_END_NAMESPACE

class interface : public QWidget
{
    Q_OBJECT
    Polynom p;

public:
    interface(QWidget *parent = nullptr);
    ~interface();

private slots:
    void on_OutputType1Button_clicked();

    void on_OutputType2Button_clicked();

    void on_PolynomInputButton_clicked();

    void on_PointButton_clicked();

private:
    Ui::interface *ui;
};
#endif // INTERFACE_H
