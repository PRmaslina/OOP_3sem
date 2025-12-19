#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


    class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked();
    void on_plotButton_clicked();

private:
    Ui::MainWindow *ui;
    QChart *chart;
    QChartView *chartView;
    QList<QLineSeries*> seriesList;

    void setupChart();
    void clearChart();
    void plotFunction(int funcIndex, double xMin, double xMax, int points);
    double evaluateRealFunction(int funcIndex, double x);
};

#endif // MAINWINDOW_H
