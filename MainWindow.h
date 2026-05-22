#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_USE_NAMESPACE

class MainWindowPrivate;

/**
 * @brief 主窗口
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
    virtual ~MainWindow();

private Q_SLOTS:
    void on_addBtn_clicked();

private:
    Q_DISABLE_COPY(MainWindow)
    QScopedPointer<MainWindowPrivate> d;
};

#endif // MAINWINDOW_H
