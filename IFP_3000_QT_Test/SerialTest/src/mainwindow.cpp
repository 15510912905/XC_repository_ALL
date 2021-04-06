#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts>
#include <QDebug>
#include <QVBoxLayout>
#include <QtCore>
#include <QFile>
#include <QTextStream>
#include <QTimer>

#define QT_NO_DEBUG_OUTPUT
//#define QT_CHARTS_USE_NAMESPACE
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
                       QMainWindow(parent), ui(new Ui::MainWindow),
                       pSeries(icreateSeries1()),pSeries2(icreateSeries2()),                       
                       pSeries3(icreateSeries3()),currentCOM(""),
                       pDataFileCsv(icreateFileCsv()),pCvDataFileCsv(icreateCvFileCsv()),
                       VecTVale1(QVector<qreal>()),VecCVale1(QVector<qreal>()),
                       VecTVale2(QVector<qreal>()),VecCVale2(QVector<qreal>()),
                       VecTVale3(QVector<qreal>()),VecCVale3(QVector<qreal>()),
                       VecTCVale1(QVector<qreal>()),VecDensity1(QVector<qreal>()),
                       VecTCVale2(QVector<qreal>()),VecDensity2(QVector<qreal>()),
                       VecTCVale3(QVector<qreal>()),VecDensity3(QVector<qreal>())

{
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(clicked()), this, SLOT(getPadIds()));
    connect(pTimer,&QTimer::timeout,this,&MainWindow::showValidPort);//实时更新端口号
    pTimer->start(1000); //每1000ms定时检测串口状态

//    uSearchSerial( pSeriesStrList );
    getPadIds();
    ui->tabWidget->setEnabled(false);
//    QVector<qreal> qVecTVale;

}

MainWindow::~MainWindow()
{
    if( false==bFileStatus ){
        pDataFileCsv->close();
    }
    if( false==bFileStatus ){
        CvFileClose();
    }

    delete ui;
}

int MainWindow::uSearchSerial( QStringList * pTempList )
{
    pTempList->clear();
    //查找可用的串口
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        QSerialPort serial;
        serial.setPort(info);
        ui->comboBox->addItem(serial.portName());
        *pTempList += serial.portName();
    }

    return 0;
}

//更新并检测串口函数实现
void MainWindow::showValidPort()
{
    QStringList newPortStringList;
    uSearchSerial( &newPortStringList );

    if(newPortStringList.size() != pSeriesStrList->size()){
        qDebug()<<"ListNum "<<newPortStringList.size()<<pSeriesStrList->size();

        ui->comboBox->clear();   
        uSearchSerial(pSeriesStrList);
    }
//    qDebug()<<"currentCOM:"<<currentCOM;
    if(currentCOM != ui->comboBox->currentText()) //串口突然断开连接了
    {
        currentCOM = ui->comboBox->currentText();
        if("关闭" == ui->pushButton->text())
        {
            on_pushButton_clicked();
        }
    }
}

void MainWindow::getPadIds()
{
    ui->comboBox->clear(); //清除列表
    uSearchSerial( pSeriesStrList );
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButton->text()==tr("打开"))
    {
        serial=new QSerialPort;
        //设置串口名
        currentCOM = ui->comboBox->currentText();
        serial->setPortName(currentCOM);

        //打开串口
        if(serial->open(QIODevice::ReadWrite)){
            //设置波特率
            serial->setBaudRate(QSerialPort::Baud115200);
            //设置数据为
            serial->setDataBits(QSerialPort::Data8);
            //设置校验位
            serial->setParity(QSerialPort::NoParity);
            //设置停止为
            serial->setStopBits(QSerialPort::OneStop);
            //设置流控制
            serial->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制

            //关闭设置菜单使能
            ui->comboBox->setEnabled(false);
            ui->tabWidget->setEnabled(true);
            ui->pushButton->setText("关闭");

            if(pDataFileCsv->open(QFile::WriteOnly | QFile::Append)){
                *pCsvOut<<"File Open"<<'\n';
            }else{
                pDataFileCsv = icreateFileCsv();
            }

            if(pCvDataFileCsv->open(QFile::WriteOnly | QFile::Append)){
                *pCvCsvOut<<"Cv Open"<<','
                          <<"T1:"<<','<<"C1:"<<','<<"T/C 1:"<<','<<"Density1:"<<','
                          <<"T2:"<<','<<"C2:"<<','<<"T/C 2:"<<','<<"Density2:"<<','
                          <<"T3:"<<','<<"C3:"<<','<<"T/C 3:"<<','<<"Density3:"<<','
                          <<'\n';
            }else{
                pCvDataFileCsv = icreateFileCsv();
            }
            bFileStatus = false;

            QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);
        }else{
            ui->plainTextEdit->appendPlainText("File Open error");
            QSerialPort::SerialPortError uTempErr = serial->error();
            QString qTempStr(uTempErr);
            ui->plainTextEdit->appendPlainText( qTempStr );
        }
    }
    else
    {
        //关闭串口
        serial->clear();
        serial->close();
        serial->deleteLater();

        *pCsvOut<<"File Close"<<'\n';
        pDataFileCsv->close();

        CvFileClose();
        bFileStatus = true;

        //恢复使能
        ui->comboBox->setEnabled(true);
        ui->tabWidget->setEnabled(false);
        ui->pushButton->setText("打开");
    }
}

void MainWindow::CvFileClose( void )
{
    QVector<qreal> uArrTempValue[12] = { VecTVale1,VecCVale1,VecTCVale1,VecDensity1,
                                         VecTVale2,VecCVale2,VecTCVale2,VecDensity2,
                                         VecTVale3,VecCVale3,VecTCVale3,VecDensity3 };
    NSYSDATA stdev[12] = {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                          {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

    for( int i=0;i<((int)sizeof(uArrTempValue)/(int)sizeof(QVector<qreal>));i++ ){
        dAccumVaule( uArrTempValue[i],stdev[i] );
    }

    vEvAveCvClear();

    for( int j=0;j<3;j++ ){
        if( 0==j ){
            *pCvCsvOut<<"Ev Close "<<j<<',';
        }else if( 1==j ){
            *pCvCsvOut<<"Ave Close "<<j<<',';
        }else if( 2==j ){
            *pCvCsvOut<<"Cv Close "<<j<<',';
        }
        for( int i=0;i<((int)sizeof(stdev)/(int)sizeof(NSYSDATA));i++ ){
            if(0==j){
                if( stdev[i].stdEvValue>=0 ){
                    *pCvCsvOut<<stdev[i].stdEvValue<<',';
                }else{
                    *pCvCsvOut<<' '<<',';
                }
            }else if(1==j){
                if( stdev[i].stdAveValue>=0 ){
                    *pCvCsvOut<<stdev[i].stdAveValue<<',';
                }else{
                    *pCvCsvOut<<' '<<',';
                }
            }else if(2==j){
                if( stdev[i].stdCvValue>=0 ){
                    *pCvCsvOut<<stdev[i].stdCvValue<<',';
                }else{
                    *pCvCsvOut<<' '<<',';
                }
            }
        }
        *pCvCsvOut<<'\n';
    }

    pCvDataFileCsv->close();
}

void MainWindow::vEvAveCvClear(void)
{
    VecTVale1.clear();
    VecCVale1.clear();
    VecTCVale1.clear();
    VecDensity1.clear();
    VecTVale2.clear();
    VecCVale2.clear();
    VecTCVale2.clear();
    VecDensity2.clear();
    VecTVale3.clear();
    VecCVale3.clear();
    VecTCVale3.clear();
    VecDensity3.clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    serial->write(ui->textEdit->toPlainText().toLatin1());
}

//读取接收到的消息
void MainWindow::ReadData()
{
    static bool qbStaA = false;
    static bool qbStaB = false;
    static bool qbStaC = false;
    static bool qbStaD = false;
    static QString tmpADStr;
    static QString tmpBarStr;
    static QByteArray gBuf;
    static int iRecNum = 0;
    static int iRecCountNum = 0;
    static int iRecTC = 0;
    static int iRecTCCount = 0;
//    static int iRecTest = 0;

    gBuf += serial->readAll();
//    qDebug()<<"<"<<gBuf<<">";

    if((gBuf.endsWith("\n")))
    {
//        qDebug()<<"iRecTest:"<<iRecTest++;
//        qDebug()<<"("<<gBuf<<")";
        QString str(gBuf);
        str = str.fromLocal8Bit(gBuf);
        gBuf.clear();
//        str = str.toUtf8();

//        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->appendPlainText(str);
        ui->plainTextEdit->moveCursor(QTextCursor::End);//
        ui->plainTextEdit->textCursor().deletePreviousChar();

        if((true==str.contains("QUICK_RESULT_PAGE\r\n"))||(true==str.contains("STANDARD_RESULT_PAGE\r\n"))||
           (true==str.contains("g_uAutoTestTimes:") )){
            qbStaA = true;
            iRecCountNum++;
        }

        if(iRecCountNum!=iRecTC){
            ui->label_8->clear();
            ui->label_10->clear();
            ui->label_12->clear();
            iRecTC = iRecCountNum;
            iRecTCCount = 0;
            *pCvCsvOut<<iRecTC<<',';
        }

        if(true==qbStaA){
            tmpADStr += str;
            if(true==tmpADStr.contains("\r\n\r\n",Qt::CaseSensitive)){
               qbStaA = false;

               qint32 qTempDataA = tmpADStr.indexOf("line_smoth_slid:\r\n");
               tmpADStr = tmpADStr.remove(0, qTempDataA);
               qTempDataA = tmpADStr.indexOf("\r\n\r\n");
               tmpADStr = tmpADStr.remove(qTempDataA+2, (tmpADStr.size()-(qTempDataA+2)));
               tmpADStr.remove(0, 18);

               static bool bRecSeries1 = false;
               if( false==bRecSeries1 ){
                   bRecSeries1 = true;
               }else{
                   pChartAD->removeSeries(pSeries);
                   pChartAD3->removeSeries(pSeries3);
               }               

               QStringList listA = tmpADStr.split("\r\n");
               QVector<QPointF> qPointA;
               QVector<QPointF> qPointC;
               QVector<qreal> qPointAdit;
               *pCsvOut<<iRecCountNum<<',';
               for( int i=0;i<listA.count()-1;i++){
                   QString qStrC = listA.at(i);
                   int qTempintC = qStrC.toInt();
                   qPointC.append(QPointF(i,qTempintC));

                   QString qStrA = listA.at((listA.count()-2)-i);
                   int qTempintA = qStrA.toInt();
                   qPointA.append(QPointF(i,qTempintA));

                   qPointAdit.append(qTempintA);

                   *pCsvOut<<qTempintA<<',';
               }
               *pCsvOut<<'\n';
               pCsvOut->flush();
               auto qTempmax1 = std::max_element(std::begin(qPointAdit), std::end(qPointAdit));
               auto qTempmin1 = std::min_element(std::begin(qPointAdit), std::end(qPointAdit));
               auto positionmax1 = std::distance(std::begin(qPointAdit),qTempmax1);
               QString qStrTemp1;
               qStrTemp1 = qStrTemp1.sprintf("%d",positionmax1);
    //           qDebug()<<"positionmax1:"<<positionmax1<<"-"<<qStrTemp1;
               ui->label_3->setText(qStrTemp1);
               qStrTemp1 = qStrTemp1.sprintf("%d",(int)(*qTempmax1));
               ui->label_5->setText(qStrTemp1);
               ui->label_17->setText(qStrTemp1);

               qStrTemp1 = qStrTemp1.sprintf("%d",(311-positionmax1));
               ui->label_15->setText(qStrTemp1);

               axisY1->setRange( (*qTempmin1)-100,(*qTempmax1)+100 );
               axisY3->setRange( (*qTempmin1)-100,(*qTempmax1)+100 );
               pSeries->replace(qPointA);
               pSeries3->replace(qPointC);

               qint32 qTempDataB = str.indexOf("\r\n\r\n");//buf.indexOf("\r\n\r\n");
               str = str.remove(0, qTempDataB+4);//buf.remove(0, qTempDataB+4);
               qbStaB = true;

               iTestLineChartsA();
               iTestLineChartsC();
               tmpADStr.clear();
            }else if((true==tmpADStr.contains("BarCode:\r\n",Qt::CaseSensitive))){
                qbStaA = false;
                qint32 qTempDataD = str.indexOf("BarCode:\r\n");
                str = str.remove(0, qTempDataD);
                qbStaB = true;
            }
        }

        if( true==qbStaB ){
            tmpBarStr += str;
            if((false==qbStaC)&&(true==tmpBarStr.contains("BarCode:\r\n",Qt::CaseSensitive))){
                qint32 qTempDataC = tmpBarStr.indexOf("BarCode:\r\n");
                tmpBarStr = tmpBarStr.remove(0, qTempDataC);
                qbStaC = true;
                qbStaD = false;
            }else{
                if( (false==qbStaC) ){
                    iRecNum++;
                    qbStaD = true;
                    if( iRecNum>3 ){
                        qbStaB = false;
                        iRecNum = 0;
                    }
                }
            }

            if((true==qbStaC)&&(true==tmpBarStr.contains("\r\n\r\n",Qt::CaseSensitive))){
                qbStaB = false;
                qbStaC = false;
                qbStaD = true;
                iRecNum = 0;

                tmpBarStr.remove(0, 10);
                qint32 qTempDataB = tmpBarStr.indexOf("\r\n\r\n");
                tmpBarStr.remove(qTempDataB+2,tmpBarStr.size()-(qTempDataB+2));

                static bool bRecSeries2 = false;
                if( false==bRecSeries2 ){
                    bRecSeries2 = true;
                }else{
                    pChartAD2->removeSeries(pSeries2);
                }

                QStringList listB = tmpBarStr.split("\r\n");
                pSeries2->clear();
                *pCsvOut<<iRecCountNum<<',';
                QVector<qreal> qPointBdit;
                for( int i=0;i<listB.count()-1;i++){
                    QString qStrB = listB.at(i);
                    int qTempintB = qStrB.toInt();
                    *pSeries2<<QPointF(i,qTempintB);
                    *pCsvOut<<qTempintB<<',';
                    qPointBdit.append(qTempintB);
                }
                *pCsvOut<<'\n';
                pCsvOut->flush();
                auto qTempmax2 = std::max_element(std::begin(qPointBdit), std::end(qPointBdit));
                auto qTempmin2 = std::min_element(std::begin(qPointBdit), std::end(qPointBdit));
                axisY2->setRange( (*qTempmin2)-10,(*qTempmax2)+10 );

                iTestLineChartsB();
                tmpBarStr.clear();
            }
        }

        if(true==qbStaD){
            QString qStrTempA(str);

            do{
                if( true==qStrTempA.contains("T:") ){
        //                    qDebug()<<listA.at(i);
                    CalTCValue( qStrTempA,iRecTCCount);
                }
                if( 1==CalDensityResult(qStrTempA,iRecTCCount) ){
                    iRecTCCount++;
                }

                qint32 qTempNumA = qStrTempA.indexOf("result:");
                qStrTempA = qStrTempA.remove(0,qTempNumA+7);
            }while( true==qStrTempA.contains("T:") );
        }

        if( true==str.contains("QuickTest:") ){
           *pCvCsvOut<<'\n';
           qbStaD = false;
        }
    }
}

void MainWindow::CalTCValue( QString &qStrTemp,int iTempCount )
{
    QString qStrTempA = qStrTemp;
    qint32 iRecTCCount = iTempCount;

    qint32 qTempNumA = qStrTempA.indexOf("T:");
    qStrTempA = qStrTempA.remove(0,qTempNumA);
    qTempNumA = qStrTempA.indexOf("\r\n");
    qStrTempA = qStrTempA.remove(qTempNumA,(qStrTempA.size()-1));

    QStringList listA = qStrTempA.split(" ");

    for( int i=0;i<listA.count();i++ ){
    //                    qDebug()<<listA.at(i);
        if(0==i){
            qStrTempA = listA.at(i);
            qStrTempA.remove(0,2);

            QString qStrTempB = ui->label_8->text();
            qStrTempB += (qStrTempA + ' ');
            ui->label_8->setText(qStrTempB);

            *pCvCsvOut<<qStrTempA<<',';

            if( 0==(iRecTCCount%3) ){
                VecTVale1.append(qStrTempA.toFloat());
            }else if( 1==(iRecTCCount%3) ){
                VecTVale2.append(qStrTempA.toFloat());
            }else if( 2==(iRecTCCount%3) ){
                VecTVale3.append(qStrTempA.toFloat());
            }
        }else if(1==i){
            qStrTempA = listA.at(i);
            qStrTempA.remove(0,2);

            QString qStrTempB = ui->label_10->text();
             qStrTempB += (qStrTempA + ' ');
            ui->label_10->setText(qStrTempB);

            *pCvCsvOut<<qStrTempA<<',';

            if( 0==(iRecTCCount%3) ){
                VecCVale1.append(qStrTempA.toFloat());
            }else if( 1==(iRecTCCount%3) ){
                VecCVale2.append(qStrTempA.toFloat());
            }else if( 2==(iRecTCCount%3) ){
                VecCVale3.append(qStrTempA.toFloat());
            }
        }
        else if(2==i){
            qStrTempA = listA.at(i);
            qStrTempA.remove(0,8);

            QString qStrTempB = ui->label_12->text();
            qStrTempB += (qStrTempA + ' ');
            ui->label_12->setText(qStrTempB);

            *pCvCsvOut<<qStrTempA<<',';

            if( 0==(iRecTCCount%3) ){
                VecTCVale1.append(qStrTempA.toFloat());
            }else if( 1==(iRecTCCount%3) ){
                VecTCVale2.append(qStrTempA.toFloat());
            }else if( 2==(iRecTCCount%3) ){
                VecTCVale3.append(qStrTempA.toFloat());
            }
        }
    }
}

int MainWindow::CalDensityResult( QString &qStrTemp,int iTempCount )
{
    QString qStrTempA = qStrTemp;
    qint32 iRecTCCount = iTempCount;

    if( true==qStrTempA.contains("result:") ){

        qint32 qTempNumA = qStrTempA.indexOf("result:");
        qStrTempA = qStrTempA.remove(0,qTempNumA+7);
        qTempNumA = qStrTempA.indexOf("\r\n");
        qStrTempA = qStrTempA.remove(qTempNumA,(qStrTempA.size()));

        *pCvCsvOut<<qStrTempA<<',';

        if( 0==(iRecTCCount%3) ){
            VecDensity1.append(qStrTempA.toFloat());
        }else if( 1==(iRecTCCount%3) ){
            VecDensity2.append(qStrTempA.toFloat());
        }else if( 2==(iRecTCCount%3) ){
            VecDensity3.append(qStrTempA.toFloat());
        }

        return 1;
    }
    return 0;
}

int MainWindow::iTestLineChartsA( void )
{
    axisX1->setRange(0, 311);
    axisX1->setTitleText("Tick");
    axisX1->setLabelFormat("%d"); //标签格式
    axisX1->setTickCount(39);
    axisX1->setMinorTickCount(1);
    axisX1->setGridLineColor( QColor( 100,149,237 ) );
    axisX1->setMinorGridLineColor( QColor( 130,149,237 ) );

    axisY1->setGridLineColor( QColor( 100,149,237 ) );
    axisY1->setMinorGridLineColor( QColor( 130,149,237 ) );

    ui->verticalLayout_9->addWidget(pView);

    pSeries->setUseOpenGL(true);

    pChartAD->legend()->hide();
    pChartAD->addSeries(pSeries);
//    pChartAD->createDefaultAxes();
    pChartAD->setAxisX(axisX1,pSeries);
    pChartAD->setAxisY(axisY1,pSeries);
    pChartAD->setTitle(QStringLiteral("AD"));

    pView->setRubberBand(QChartView::HorizontalRubberBand);       //设置橡皮筋（放大缩小）
    pView->setRenderHint(QPainter::Antialiasing);
    pView->show();    

    return 0;
}

int MainWindow::iTestLineChartsB( void )
{
    axisX2->setRange(0, 499);
    axisX2->setTitleText("Tick");
    axisX2->setLabelFormat("%d"); //标签格式
    axisX2->setTickCount(50);
    axisX2->setMinorTickCount(1);
    axisX2->setGridLineColor( QColor( 100,149,237 ) );
    axisX2->setMinorGridLineColor( QColor( 130,149,237 ) );

    axisY2->setGridLineColor( QColor( 100,149,237 ) );
    axisY2->setMinorGridLineColor( QColor( 130,149,237 ) );

//qDebug()<<"Start \r\n";
//qDebug()<<"End \r\n";

    ui->verticalLayout_15->addWidget(pView2);

    pSeries2->setUseOpenGL(true);

    pChartAD2->legend()->hide();
    pChartAD2->addSeries(pSeries2);
//    pChartAD2->createDefaultAxes();
    pChartAD2->setAxisX(axisX2,pSeries2);
    pChartAD2->setAxisY(axisY2,pSeries2);
    pChartAD2->setTitle(QStringLiteral("Bar"));

    pView2->setRubberBand(QChartView::HorizontalRubberBand);       //设置橡皮筋（放大缩小）
    pView2->setRenderHint(QPainter::Antialiasing);
    pView2->show();

    return 0;
}

int MainWindow::iTestLineChartsC( void )
{
    axisX3->setRange(0, 311);
    axisX3->setTitleText("Tick");
    axisX3->setLabelFormat("%d"); //标签格式
    axisX3->setTickCount(39);
    axisX3->setMinorTickCount(1);
    axisX3->setGridLineColor( QColor( 100,149,237 ) );
    axisX3->setMinorGridLineColor( QColor( 130,149,237 ) );

    axisY3->setGridLineColor( QColor( 100,149,237 ) );
    axisY3->setMinorGridLineColor( QColor( 130,149,237 ) );

    ui->verticalLayout_16->addWidget(pView3);

    pSeries3->setUseOpenGL(true);

    pChartAD3->legend()->hide();
    pChartAD3->addSeries(pSeries3);
//    pChartAD->createDefaultAxes();
    pChartAD3->setAxisX(axisX3,pSeries3);
    pChartAD3->setAxisY(axisY3,pSeries3);
    pChartAD3->setTitle(QStringLiteral("AD2"));

    pView3->setRubberBand(QChartView::HorizontalRubberBand);       //设置橡皮筋（放大缩小）
    pView3->setRenderHint(QPainter::Antialiasing);
    pView3->show();

    return 0;
}

QLineSeries* MainWindow::icreateSeries1( void )
{
    QLineSeries *p_mSeries1 = new QLineSeries();

    *p_mSeries1<<QPointF(0,0);

    return p_mSeries1;
}

QLineSeries* MainWindow::icreateSeries2( void )
{
    QLineSeries *p_mSeries2 = new QLineSeries();

    *p_mSeries2<<QPointF(0,0);

    return p_mSeries2;
}

QLineSeries* MainWindow::icreateSeries3( void )
{
    QLineSeries *p_mSeries3 = new QLineSeries();

    *p_mSeries3<<QPointF(0,0);

    return p_mSeries3;
}

//QVector<qreal>* MainWindow::icreateQVecTValue( void )
//{
//   QVector<qreal>* pTempQvec = new QVector(QVector<qreal>);

//    return pTempQvec;
//}

QFile* MainWindow::icreateFileCsv( void )
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString timestr = datetime.toString("ddHHmmzzz");
    QFile* ptempfiledata = new QFile("ADBarValue" + timestr + ".csv");
    timestr = datetime.toString("HHmmzzz")+"\n";
    if(ptempfiledata->open(QFile::WriteOnly | QFile::Truncate))        // 打开文件
    {
        QTextStream* pout = new QTextStream(ptempfiledata);    // 输入流
        pCsvOut = pout;
        *pCsvOut<<timestr;
    }

    ptempfiledata->close();

    return ptempfiledata;
}

QFile* MainWindow::icreateCvFileCsv( void )
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString timestr = datetime.toString("ddHHmmzzz");
    QFile* ptempfiledata = new QFile("CvValue" + timestr + ".csv");
    timestr = datetime.toString("HHmmzzz")+"\n";
    if(ptempfiledata->open(QFile::WriteOnly | QFile::Truncate))        // 打开文件
    {
        QTextStream* pout = new QTextStream(ptempfiledata);    // 输入流
        pCvCsvOut = pout;
        *pCvCsvOut<<timestr;
    }

    ptempfiledata->close();

    return ptempfiledata;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    pSeries->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    pSeries2->clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    pSeries3->clear();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString qStrTempA = ui->label_3->text();
    int iTempA = qStrTempA.toInt();
//    qDebug()<<"iTempA1:"<<iTempA;
    QString qStrTempB = ui->lineEdit->text();
    int iTempB = qStrTempB.toInt();
//    qDebug()<<"iTempB1:"<<iTempB;
    iTempB = (int)((qreal)iTempB*(qreal)((qreal)312/(qreal)272));
    iTempA -= iTempB;
//    qDebug()<<"iTempA1iTempB1:"<<iTempB<<iTempA;
    QString qStrTempC;
    qStrTempC = qStrTempC.sprintf("%d",iTempA);
    ui->label_7->setText(qStrTempC);
}

void MainWindow::on_pushButton_8_clicked()
{
    QString qStrTempA = ui->label_15->text();
    int iTempA = qStrTempA.toInt();
    QString qStrTempB = ui->lineEdit_2->text();
    int iTempB = qStrTempB.toInt();
    iTempB = (int)((qreal)iTempB*(qreal)((qreal)312/(qreal)272));
    iTempA -= iTempB;

    QString qStrTempC;
    qStrTempC = qStrTempC.sprintf("%d",iTempA);
    ui->label_16->setText(qStrTempC);
}

void MainWindow::findPeak(const QVector<int>& v, QVector<int>& peakPositions)
{
    QVector<int> diff_v(v.size() - 1, 0);
    // 计算V的一阶差分和符号函数trend
    for (QVector<int>::size_type i = 0; i != diff_v.size(); i++)
    {
        if (v[i + 1] - v[i]>0)
            diff_v[i] = 1;
        else if (v[i + 1] - v[i] < 0)
            diff_v[i] = -1;
        else
            diff_v[i] = 0;
    }
    // 对Trend作了一个遍历
    for (int i = diff_v.size() - 1; i >= 0; i--)
    {
        if (diff_v[i] == 0 && i == diff_v.size() - 1)
        {
            diff_v[i] = 1;
        }
        else if (diff_v[i] == 0)
        {
            if (diff_v[i + 1] >= 0)
                diff_v[i] = 1;
            else
                diff_v[i] = -1;
        }
    }

    for (QVector<int>::size_type i = 0; i != diff_v.size() - 1; i++)
    {
        if (diff_v[i + 1] - diff_v[i] == -2)
            peakPositions.push_back(i + 1);
    }
}

double MainWindow::dAccumVaule( QVector<qreal> &VecTemp,NSYSDATA &ValueData )
{
    auto iSizeNum = VecTemp.size();
    if(iSizeNum<2){
        ValueData.stdAveValue = -1;
        ValueData.stdEvValue = -1;
        ValueData.stdCvValue = -1;
        qDebug() << "ErrAcc:"<<iSizeNum;
        return -1;
    }

    double sum = std::accumulate(std::begin(VecTemp), std::end(VecTemp), 0.0);
    double mean =  sum / VecTemp.size(); //均值
    double accum  = 0.0;
    std::for_each(std::begin(VecTemp), std::end(VecTemp), [&](const double d){accum += (d-mean)*(d-mean);});

    double stdev = sqrt(accum/(VecTemp.size()-1)); //样本方差
    VecTemp.clear();

    ValueData.stdAveValue = mean;
    ValueData.stdEvValue = stdev;
//    qDebug() << "mean:"<<mean<<"stdev:"<<stdev;
    stdev = stdev/mean;

    ValueData.stdCvValue = stdev;

    return stdev;
}

///* 求平均值 */
//double average(double *x, int len)
//{
//    double sum = 0;
//    for (int i = 0; i < len; i++) // 求和
//        sum += x[i];
//    return sum/len; // 得到平均值
//}

///* 求方差 */
//double variance(double *x, int len)
//{
//    double average = average(x, len);
//    for (int i = 0; i < len; i++) // 求和
//        sum += pow(x[i] - average, 2);
//    return sum/len; // 得到平均值
//}

///* 求标准差 */
//double average(double *x, int len)
//{
//    double variance = variance(x, len);
//    return sqrt(variance); // 得到标准差
//}

//{
//    double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
//    double mean =  sum / resultSet.size(); //均值

//    double accum  = 0.0;
//    std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
//        accum  += (d-mean)*(d-mean);
//    });

//    double stdev = sqrt(accum/(resultSet.size()-1)); //方差
//}
//VecTVale
//double sum = std::accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
//double mean =  sum / resultSet.size(); //均值

//double accum  = 0.0;
//std::for_each (std::begin(resultSet), std::end(resultSet), [&](const double d) {
//    accum  += (d-mean)*(d-mean);
//});

//double stdev = sqrt(accum/(resultSet.size()-1)); //方差

