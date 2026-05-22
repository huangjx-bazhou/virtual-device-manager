#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DevicePanel.h"

class MainWindowPrivate
{
public:
    MainWindowPrivate();

    QScopedPointer<Ui::MainWindow> ui;
};

MainWindowPrivate::MainWindowPrivate() :
    ui(new Ui::MainWindow)
{
}

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    d(new MainWindowPrivate)
{
    d->ui->setupUi(this);
    d->ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    d->ui->listWidget->setSpacing(8);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_addBtn_clicked()
{ 
    int count = d->ui->listWidget->count();

    QListWidgetItem* item = new QListWidgetItem;
    d->ui->listWidget->insertItem(count, item);

    DevicePanel* devicePanel = new DevicePanel(this);
    d->ui->listWidget->setItemWidget(item, devicePanel);
}
