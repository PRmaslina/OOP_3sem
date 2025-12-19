#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "complex.h"
#include "si.h"
#include "sin.h"
#include "cos.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QPainter>
#include <QStatusBar>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chart(nullptr)
    , chartView(nullptr)
{
    ui->setupUi(this);

    // Инициализация графика
    setupChart();

    // Подключите сигналы и слоты кнопок
    connect(ui->plotButton, &QPushButton::clicked, this, &MainWindow::on_plotButton_clicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::on_calculateButton_clicked);

    // Подключите действия меню (actions из UI)
    connect(ui->actionSavePlot, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Plot", "",
                                                        "PNG Image (*.png);;JPEG Image (*.jpg)");
        if (!fileName.isEmpty() && chartView) {
            QPixmap pixmap = chartView->grab();
            if (pixmap.save(fileName)) {
                statusBar()->showMessage("Plot saved to " + fileName, 3000);
            } else {
                QMessageBox::warning(this, "Save Error", "Failed to save plot image.");
            }
        }
    });

    connect(ui->actionClearPlot, &QAction::triggered, this, [this]() {
        clearChart();
        statusBar()->showMessage("Plot cleared", 2000);
    });

    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
}

MainWindow::~MainWindow()
{
    clearChart();
    delete ui;
}

void MainWindow::setupChart()
{
    // Очистите предыдущий график
    clearChart();

    // Создайте новый график
    chart = new QChart();
    chart->setTitle("Function Plot");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTheme(QChart::ChartThemeLight);

    // Создайте оси
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("x");
    axisX->setLabelFormat("%.2f");
    axisX->setTickCount(10);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("f(x)");
    axisY->setLabelFormat("%.2f");
    axisY->setTickCount(10);

    // Добавьте оси к графику
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Создайте представление графика
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand); // Добавьте возможность выделения области

    // Установите представление графика в graphicsView
    QVBoxLayout *layout = new QVBoxLayout(ui->graphicsView);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);

    ui->graphicsView->setLayout(layout);
}

void MainWindow::clearChart()
{
    // Удалите все серии
    for (auto series : seriesList) {
        if (chart) {
            chart->removeSeries(series);
        }
        delete series;
    }
    seriesList.clear();

    // Сбросьте заголовок графика
    if (chart) {
        chart->setTitle("Function Plot");
        chart->legend()->setVisible(false);
    }
}

void MainWindow::on_calculateButton_clicked()
{
    Sin<TComplex>* s = nullptr;
    Si<TComplex>* si = nullptr;
    Cos<TComplex>* cos = nullptr;
    QString answer;

    try {
        QString inputText = ui->ComplexEdit->text().trimmed();
        if (inputText.isEmpty()) {
            ui->Answer->setText("Error: Please enter a complex number");
            return;
        }

        TComplex complexValue = toComplex(inputText);

        switch(ui->FuncChoose->currentIndex()){
        case 0:
            s = new Sin<TComplex>((ui->AccuracyEdit->value()));
            answer = complexOut(s->solve(complexValue));
            delete s;
            break;
        case 1:
            si = new Si<TComplex>((ui->AccuracyEdit->value()));
            answer = complexOut(si->solve(complexValue));
            delete si;
            break;
        case 2:
            cos = new Cos<TComplex>((ui->AccuracyEdit->value()));
            answer = complexOut(cos->solve(complexValue));
            delete cos;
            break;
        default:
            ui->Answer->setText("Error: Unknown function selected");
            return;
        }
        ui->Answer->setText("Result: " + answer);
        statusBar()->showMessage("Calculation completed", 2000);
    } catch (const std::exception& e) {
        ui->Answer->setText("Error: " + QString(e.what()));
        statusBar()->showMessage("Calculation failed: " + QString(e.what()), 3000);
        if (s) delete s;
        if (si) delete si;
        if (cos) delete cos;
    } catch (...) {
        ui->Answer->setText("Error: Unknown error occurred");
        statusBar()->showMessage("Calculation failed: Unknown error", 3000);
        if (s) delete s;
        if (si) delete si;
        if (cos) delete cos;
    }
}

void MainWindow::on_plotButton_clicked()
{
    bool ok1, ok2;
    double xMin = ui->xMinEdit->text().toDouble(&ok1);
    double xMax = ui->xMaxEdit->text().toDouble(&ok2);
    int points = ui->pointsSpinBox->value();

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Invalid Input",
                             "Please enter valid numeric values for X range");
        return;
    }

    if (xMin >= xMax) {
        QMessageBox::warning(this, "Invalid Range",
                             "xMin must be less than xMax");
        return;
    }

    if (points < 2) {
        QMessageBox::warning(this, "Invalid Points",
                             "Number of points must be at least 2");
        return;
    }

    if (points > 10000) {
        QMessageBox::warning(this, "Too Many Points",
                             "Number of points is too high. Please use 10000 or less.");
        return;
    }

    plotFunction(ui->FuncChoose->currentIndex(), xMin, xMax, points);
}

double MainWindow::evaluateRealFunction(int funcIndex, double x)
{
    // Создайте комплексное число с нулевой мнимой частью
    TComplex input(x, 0);
    TComplex result;

    try {
        switch(funcIndex){
        case 0: { // sin(x)
            Sin<TComplex> s(ui->AccuracyEdit->value());
            result = s.solve(input);
            break;
        }
        case 1: { // Si(x)
            Si<TComplex> si(ui->AccuracyEdit->value());
            result = si.solve(input);
            break;
        }
        case 2: { // cos(x)
            Cos<TComplex> cos(ui->AccuracyEdit->value());
            result = cos.solve(input);
            break;
        }
        default:
            return 0.0;
        }
    } catch (const std::exception& e) {
        qWarning() << "Error evaluating function at x =" << x << ":" << e.what();
        return 0.0;
    }

    return result.getReal();
}



void MainWindow::plotFunction(int funcIndex, double xMin, double xMax, int points)
{
    if (!chart || !chartView) {
        setupChart();
    }

    // Очистите предыдущие графики
    clearChart();

    // Создайте новую серию
    QLineSeries *series = new QLineSeries();

    // Установите имя функции
    QString functionNames[] = {"sin(x)", "Si(x)", "cos(x)"};
    QString functionName = functionNames[funcIndex];
    series->setName(functionName);

    // Установите цвет линии в зависимости от функции
    QColor colors[] = {Qt::blue, Qt::red, Qt::green};
    QPen pen(colors[funcIndex]);
    pen.setWidth(2);
    series->setPen(pen);

    // Вычислите шаг
    double step = (xMax - xMin) / (points - 1);

    // Сгенерируйте точки
    double maxY = -1e10;
    double minY = 1e10;
    int validPoints = 0;

    Sin<TComplex> sin(ui->AccuracyEdit->value());
    Si<TComplex> si(ui->AccuracyEdit->value());
    Cos<TComplex> cos(ui->AccuracyEdit->value());

    // Добавьте первую точку
    double firstX = xMin;
    double firstY;
    switch(funcIndex){
        case 0: { // sin(x)
            firstY = sin.solve(firstX).getReal();
            break;
        }
        case 1: { // Si(x)
            firstY = si.solve(firstX).getReal();
            break;
        }
        case 2: { // cos(x)
            firstY = cos.solve(firstX).getReal();
            break;
        }
    }
    if (std::isfinite(firstY)) {
        series->append(firstX, firstY);
        validPoints++;
        maxY = firstY;
        minY = firstY;
    }

    // Добавьте остальные точки
    for (int i = 1; i < points; ++i) {
        double x = xMin + i * step;
        double y;
        switch(funcIndex){
            case 0: { // sin(x)
                y = sin.solve(x).getReal();
                break;
            }
            case 1: { // Si(x)
                y = si.solve(x).getReal();
                break;
            }
            case 2: { // cos(x)
                y = cos.solve(x).getReal();
                break;
            }
        }
        // Проверка на специальные значения
        if (!std::isfinite(y)) {
            qWarning() << "Non-finite value at x =" << x << ", y =" << y;
            continue;
        }

        series->append(x, y);
        validPoints++;

        if (y > maxY) maxY = y;
        if (y < minY) minY = y;
    }

    // Проверка на валидные данные
    if (validPoints == 0) {
        delete series;
        QMessageBox::warning(this, "Plot Error",
                             "No valid data points to plot. Check function evaluation.");
        return;
    }

    // Добавьте серию на график
    chart->addSeries(series);
    seriesList.append(series);

    // Получите оси
    QList<QAbstractAxis*> xAxes = chart->axes(Qt::Horizontal);
    QList<QAbstractAxis*> yAxes = chart->axes(Qt::Vertical);

    if (!xAxes.isEmpty() && !yAxes.isEmpty()) {
        QValueAxis *axisX = qobject_cast<QValueAxis*>(xAxes.first());
        QValueAxis *axisY = qobject_cast<QValueAxis*>(yAxes.first());

        if (axisX && axisY) {
            // Установите диапазоны осей
            axisX->setRange(xMin, xMax);

            // Добавьте отступы для оси Y
            double yRange = maxY - minY;
            if (std::abs(yRange) < 1e-10) {
                // Если все значения примерно одинаковые, установите разумный диапазон
                axisY->setRange(minY - 1.0, maxY + 1.0);
            } else {
                double padding = yRange * 0.1;
                axisY->setRange(minY - padding, maxY + padding);
            }

            // Присоедините серию к осям
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
    } else {
        // Если оси не созданы, создайте их заново
        chart->createDefaultAxes();
    }

    // Обновите заголовок графика
    chart->setTitle(functionName + " on [" +
                    QString::number(xMin, 'f', 2) + ", " +
                    QString::number(xMax, 'f', 2) + "]");

    // Покажите легенду
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    statusBar()->showMessage(QString("Plot created with %1 points").arg(validPoints), 3000);
}
