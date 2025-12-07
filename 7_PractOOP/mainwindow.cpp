#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "complex.h"
#include "si.h"
#include "sin.h"
#include "cos.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculateButton_clicked()
{
    Sin<TComplex>* s;
    Si<TComplex>* si;
    Cos<TComplex>* cos;
    QString answer;
    switch(ui->FuncChoose->currentIndex()){
    case 0:
        s = new Sin<TComplex>((ui->AccuracyEdit->value()));
        answer = complexOut(s->solve(toComplex(ui->ComplexEdit->text())));
        delete s;
        break;
    case 1:
        si = new Si<TComplex>((ui->AccuracyEdit->value()));
        answer = complexOut(si->solve(toComplex(ui->ComplexEdit->text())));
        delete si;
        break;
    case 2:
        cos = new Cos<TComplex>((ui->AccuracyEdit->value()));
        answer = complexOut(cos->solve(toComplex(ui->ComplexEdit->text())));
        delete cos;
        break;
    }
    ui->Answer->setText(answer);
}

