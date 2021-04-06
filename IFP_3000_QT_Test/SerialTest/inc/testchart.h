#ifndef TESTCHART_H
#define TESTCHART_H

#include "mainwindow.h"

class TestChart : public MainWindow
{
    Q_OBJECT
public:
    TestChart(QWidget *parent = 0);
    ~TestChart();
};

#endif // TESTCHART_H
