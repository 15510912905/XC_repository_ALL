#include "demozoom.h"
#include <QLineSeries>
#include <QMouseEvent>

DemoZoom::DemoZoom(QWidget* pParent):QChartView(pParent),m_bMiddleButtonPressed(false),m_oPrePos(0, 0)
{
    QLineSeries *pLineServies = new QLineSeries();
    for (int i = 0; i < 100; ++i){
        pLineServies->append(i, qrand() % 10);
    }
    this->chart()->addSeries(pLineServies);
    this->chart()->createDefaultAxes();
}

DemoZoom::~DemoZoom()
{
}

void DemoZoom::mouseMoveEvent(QMouseEvent *pEvent)
{
    if (m_bMiddleButtonPressed){
        QPoint oDeltaPos = pEvent->pos() - m_oPrePos;
        this->chart()->scroll(-oDeltaPos.x(), oDeltaPos.y());
        m_oPrePos = pEvent->pos();
    }
////    __super::mouseMoveEvent(pEvent);
//    mouseMoveEvent(pEvent);
}

void DemoZoom::mousePressEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::MiddleButton){
        m_bMiddleButtonPressed = true;
        m_oPrePos = pEvent->pos();
        this->setCursor(Qt::OpenHandCursor);
    }
//    QMouseEvent::mousePressEvent(pEvent);
}

void DemoZoom::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() == Qt::MiddleButton){
        m_bMiddleButtonPressed = false;
        this->setCursor(Qt::ArrowCursor);
    }
//    QMouseEvent::mouseReleaseEvent(pEvent);
}

void DemoZoom::wheelEvent(QWheelEvent *pEvent)
{
    qreal rVal = std::pow(0.999, pEvent->delta()); // 设置比例
    // 1. 读取视图基本信息
    QRectF oPlotAreaRect = this->chart()->plotArea();
    QPointF oCenterPoint = oPlotAreaRect.center();
    // 2. 水平调整
    oPlotAreaRect.setWidth(oPlotAreaRect.width() * rVal);
    // 3. 竖直调整
    oPlotAreaRect.setHeight(oPlotAreaRect.height() * rVal);
    // 4.1 计算视点，视点不变，围绕中心缩放
    //QPointF oNewCenterPoint(oCenterPoint);
    // 4.2 计算视点，让鼠标点击的位置移动到窗口中心
    //QPointF oNewCenterPoint(pEvent->pos());
    // 4.3 计算视点，让鼠标点击的位置尽量保持不动(等比换算，存在一点误差)
    QPointF oNewCenterPoint(2 * oCenterPoint - pEvent->pos() - (oCenterPoint - pEvent->pos()) / rVal);

    // 5. 设置视点
    oPlotAreaRect.moveCenter(oNewCenterPoint);
    // 6. 提交缩放调整
    this->chart()->zoomIn(oPlotAreaRect);

//    QMouseEvent::wheelEvent(pEvent);
}

