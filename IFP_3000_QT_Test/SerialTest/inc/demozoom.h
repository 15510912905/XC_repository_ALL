#ifndef DEMOZOOM_H
#define DEMOZOOM_H

#include <QtCharts/QChartView>
using namespace QtCharts;

class DemoZoom : public QChartView
{
public:
    DemoZoom(QWidget* pParent = nullptr);
    ~DemoZoom();
protected:
    virtual void mouseMoveEvent(QMouseEvent *pEvent) override;
    virtual void mousePressEvent(QMouseEvent *pEvent) override;
    virtual void mouseReleaseEvent(QMouseEvent *pEvent) override;
    virtual void wheelEvent(QWheelEvent *pEvent) override;
private:
    bool m_bMiddleButtonPressed;
    QPoint m_oPrePos;
};

#endif // DEMOZOOM_H
