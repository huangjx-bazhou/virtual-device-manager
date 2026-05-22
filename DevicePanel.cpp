#include "DevicePanel.h"
#include "ui_DevicePanel.h"
#include <qzeroconf.h>

class DevicePanelPrivate
{
public:
    DevicePanelPrivate();

    QScopedPointer<Ui::DevicePanel> ui;
    QScopedPointer<QZeroConf> zeroConf;
    QString name;
    QString service;
    QString domain;
    bool publishing;
    static quint32 i;
};

quint32 DevicePanelPrivate::i = 0;

DevicePanelPrivate::DevicePanelPrivate() :
    ui(new Ui::DevicePanel),
    zeroConf(new QZeroConf),
    name(),
    service("_nirs._tcp"),
    domain(),
    publishing(false)
{
     zeroConf->clearServiceTxtRecords();
     DevicePanelPrivate::i++;
     name = QString("device.") + QString::number(i);
     domain = /*name + */"local";
}

DevicePanel::DevicePanel(QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent),
    d(new DevicePanelPrivate)
{
    d->ui->setupUi(this);
    d->ui->labelName->setText(d->name);
    d->ui->labelServiceType->setText(d->service);
    d->ui->labelDomain->setText(d->domain);
    d->ui->labelIsPublished->setText(u8"未发布");
    connect(d->ui->btnPublish, &QPushButton::clicked, this, &DevicePanel::startPublish);
    connect(d->ui->btnCancelPublish, &QPushButton::clicked, this, &DevicePanel::stopPublish);

    connect(d->zeroConf.data(), &QZeroConf::servicePublished, this, [=] ()
    {
        d->ui->labelIsPublished->setText(u8"已发布");
    });

    connect(d->zeroConf.data(), &QZeroConf::error, this, [=] (QZeroConf::error_t error)
            {
                qDebug() << "error:" << error;

            if (error != QZeroConf::noError && true == d->publishing)
            {
                d->publishing = false;
                d->ui->labelIsPublished->setText(u8"发布失败");
            }
            });
}

DevicePanel::~DevicePanel()
{
    this->stopPublish();
}

void DevicePanel::startPublish()
{
    // 如果正在发布，则什么都不做
    if (d->publishing)
    {
        return;
    }


    d->publishing = true;
    d->zeroConf->startServicePublish(d->name.toStdString().c_str(), d->service.toStdString().c_str(), d->domain.toStdString().c_str(), 12345);

}

void DevicePanel::stopPublish()
{
    if (!d->publishing)
    {
        return;
    }

    d->ui->labelIsPublished->setText(u8"未发布");
    d->zeroConf->stopServicePublish();
    d->publishing = false;
}
