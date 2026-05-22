#ifndef DEVICEPANEL_H
#define DEVICEPANEL_H

#include <QWidget>

QT_USE_NAMESPACE

class DevicePanelPrivate;

/**
 * @brief 设备面板
 */
class DevicePanel : public QWidget
{
    Q_OBJECT
public:
    explicit DevicePanel(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~DevicePanel();

public Q_SLOTS:
    /**
     * @brief 开始发布
     */
    void startPublish();

    /**
     * @brief 停止发布
     */
    void stopPublish();

private:
    Q_DISABLE_COPY(DevicePanel)
    QScopedPointer<DevicePanelPrivate> d;
};

#endif // DEVICEPANEL_H
