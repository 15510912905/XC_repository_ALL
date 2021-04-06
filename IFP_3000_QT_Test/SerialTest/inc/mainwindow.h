#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts>
#include <QColor>
#include <QFile>
#include <QTimer>

using namespace QtCharts;

namespace Ui {
class MainWindow;
}

typedef struct SYSDATA{
    double stdEvValue;
    double stdAveValue;
    double stdCvValue;
}NSYSDATA;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void ReadData();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void getPadIds();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    int uSearchSerial( QStringList* pTempList );
    void showValidPort();
    int iTestLineChartsA( void );
    int iTestLineChartsB( void );
    int iTestLineChartsC( void );
    QLineSeries* icreateSeries1( void );
    QLineSeries* icreateSeries2( void );
    QLineSeries* icreateSeries3( void );
//    QVector<qreal>* icreateQVecTValue( void );
    void findPeak(const QVector<int>& v, QVector<int>& peakPositions);
    QFile* icreateFileCsv( void );
    QFile* icreateCvFileCsv( void );
    double dAccumVaule( QVector<qreal> &VecTemp,NSYSDATA &ValueData );
    void CvFileClose( void );
    void CalTCValue( QString &qStrTemp,int iTempCount );
    int CalDensityResult( QString &qStrTemp,int iTempCount );
    void vEvAveCvClear(void);


private:
    Ui::MainWindow *ui;
    QSerialPort *serial;//全局的串口对象
    QLineSeries *pSeries;
    QLineSeries *pSeries2;
    QLineSeries *pSeries3;
    QChart *pChartAD = new QChart();
    QChart *pChartAD2 = new QChart();
    QChart *pChartAD3 = new QChart();
    QChartView *pView = new QChartView(pChartAD);
    QChartView *pView2 = new QChartView(pChartAD2);
    QChartView *pView3 = new QChartView(pChartAD3);
    QValueAxis *axisX1 = new QValueAxis(); //X 轴
    QValueAxis *axisX2 = new QValueAxis(); //X 轴
    QValueAxis *axisX3 = new QValueAxis(); //X 轴
    QValueAxis *axisY1 = new QValueAxis(); //Y 轴
    QValueAxis *axisY2 = new QValueAxis(); //Y 轴
    QValueAxis *axisY3 = new QValueAxis(); //Y 轴

    QTimer *pTimer = new QTimer();
    QStringList *pSeriesStrList = new QStringList();
    QString currentCOM;
    QFile *pDataFileCsv;
    QTextStream *pCsvOut;
    QFile *pCvDataFileCsv;
    QTextStream *pCvCsvOut;
//    QVector<qreal> *pVecTVale;
    QVector<qreal> VecTVale1;
    QVector<qreal> VecCVale1;
    QVector<qreal> VecTVale2;
    QVector<qreal> VecCVale2;
    QVector<qreal> VecTVale3;
    QVector<qreal> VecCVale3;

    QVector<qreal> VecTCVale1;
    QVector<qreal> VecDensity1;
    QVector<qreal> VecTCVale2;
    QVector<qreal> VecDensity2;
    QVector<qreal> VecTCVale3;
    QVector<qreal> VecDensity3;
    bool bFileStatus = true;

};

#endif // MAINWINDOW_H
