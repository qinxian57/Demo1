#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPointer>
#include <QtEvents>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>

#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QPointer<QSystemTrayIcon> mSysTrayIcon;
    QPointer<QMenu> mMenu;
    QPointer<QAction> mShowMainAction;
    QPointer<QAction> mExitAppAction;

    QStandardItemModel * objectModel;

    void initTrayIcon();
    void createTrayActions();
    void closeEvent ( QCloseEvent * e );
    void changeEvent(QEvent * event);

private slots:
    void on_showMainAction();
    void on_exitAppAction();
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

    void on_actionDock_triggered(bool checked);

    void on_dockWidget_visibilityChanged(bool visible);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
