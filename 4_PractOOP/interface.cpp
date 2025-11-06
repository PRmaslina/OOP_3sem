#include "interface.h"
#include "polynom.h"
#include "complex.h"
#include <QString>
#include "./ui_interface.h"

interface::interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::interface)
{
    ui->setupUi(this);
}

interface::~interface()
{
    delete ui;
}

void interface::on_OutputType1Button_clicked()
{
    p.setPrintType(1);
    ui->PolynomOut->setText(outputString(p));
}


void interface::on_OutputType2Button_clicked()
{
    p.setPrintType(2);
    ui->PolynomOut->setText(outputString(p));
}


void interface::on_PolynomInputButton_clicked()
{
    inputString(ui->PolynomInputA->text(),ui->PolynomInputRoots->text(),&p);
    ui->PolynomOut->setText(outputString(p));
}


void interface::on_PointButton_clicked()
{
    number a = p.solve(toComplex(ui->PointInput->text()));
    ui->OutputSolve->setText("значение в точке " + ui->PointInput->text() + "  равно: " + complexOut(a));
}

