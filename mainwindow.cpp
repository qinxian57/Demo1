#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //托盘初始化
    initTrayIcon();

    this->setCentralWidget(ui->tableView);
    ui->dockWidget->setWidget(ui->treeWidget);

    //初始化tableView

    //设置大小
    objectModel = new QStandardItemModel(4, 3);//4行2列
    //选择这个model
    ui->tableView->setModel(objectModel);
    //隐藏左边那列
    ui->tableView->verticalHeader()->hide();
    //列宽
    ui->tableView->setColumnWidth(0,30);
    //整行选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置标题
    //objectModel->setHeaderData(0, Qt::Horizontal, tr("Label"));
    //objectModel->setHeaderData(1, Qt::Horizontal, tr("Quantity"));
    objectModel->setHorizontalHeaderLabels(QStringList() <<tr("姓名")<<tr("性别")<<tr("年龄"));


    //添加数据
    for(int j=0;j<2;j++)
    {
                //写id

        objectModel->setItem(j, 0, new QStandardItem("张三"));
        objectModel->setItem(j, 1, new QStandardItem("男"));
        objectModel->setItem(j, 2, new QStandardItem("18"));
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTrayIcon()
{
    //新建QSystemTrayIcon对象,
    mSysTrayIcon = new QSystemTrayIcon(this);

    //将icon设到QSystemTrayIcon对象中
    mSysTrayIcon->setIcon(QIcon(":/images/tray_icon.png"));
    //当鼠标移动到托盘上的图标时，会显示此处设置的内容
    mSysTrayIcon->setToolTip("Demo1");
    //设置父组件，否则程序退出时托盘图标不立即消失
    mSysTrayIcon->setParent(this);

    //给QSystemTrayIcon添加槽函数
    connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    //建立托盘操作的菜单
    createTrayActions();
}

void MainWindow::createTrayActions()
{
    mMenu = new QMenu(this);

    //新增菜单项---显示主界面
    mShowMainAction = new QAction("显示", this);
    connect(mShowMainAction,SIGNAL(triggered()),this,SLOT(on_showMainAction()));
    mMenu->addAction(mShowMainAction);

    //增加分隔符
    mMenu->addSeparator();

    //新增菜单项---退出程序
    mExitAppAction = new QAction("关闭", this);
    connect(mExitAppAction,SIGNAL(triggered()),this,SLOT(on_exitAppAction()));
    mExitAppAction->setIcon(QIcon(":/images/close.png"));
    mMenu->addAction(mExitAppAction);

//    //等宽字体12号
//    QFont font("consolas", 12, QFont::Normal);
//    mMenu->setFont(font);
//    mMenu->setStyle(QStyleFactory::create("fusion"));

    //把QMenu赋给QSystemTrayIcon对象
    mSysTrayIcon->setContextMenu(mMenu);
}

void MainWindow::closeEvent ( QCloseEvent * e )
{
    e->ignore();
    //隐藏窗口到托盘
    this->hide();
    mSysTrayIcon->show();
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()!=QEvent::WindowStateChange) return;
    //最小化事件
    if(this->windowState()==Qt::WindowMinimized)
    {
        //隐藏窗口到托盘
        event->ignore();
        this->hide();
        mSysTrayIcon->show();
    }
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标，显示主程序窗口
        this->activateWindow();
        this->show();
        break;
    default:
        break;
    }
}


/*
* 当在系统托盘点击菜单内的显示主界面操作
*/
void MainWindow::on_showMainAction()
{
    this->activateWindow();
    this->show();
}

/*
* 当在系统托盘点击菜单内的退出程序操作
*/
void MainWindow::on_exitAppAction()
{
    qApp->exit(0);
    //delete mSysTrayIcon;
}

void MainWindow::on_actionDock_triggered(bool checked)
{
    if(!checked)
    {
        ui->dockWidget->hide();
    }
    else{
        ui->dockWidget->show();
    }
}

void MainWindow::on_dockWidget_visibilityChanged(bool visible)
{
    ui->actionDock->setChecked(visible);
}

void MainWindow::on_pushButton_clicked()
{
    int row = objectModel->rowCount();
    objectModel->insertRow(row, QModelIndex());
    objectModel->setItem(row-1, 0, new QStandardItem("张三"));
    objectModel->setItem(row-1, 1, new QStandardItem("男"));
    objectModel->setItem(row-1, 2, new QStandardItem("18"));

    //x是指定删除哪一行
    //objectModel->removeRow(x);
    //删除所有行
    //objectModel->removeRows(0, objectModel->rowCount());


    //    for (int row = 0; row < 4; ++row) {
    //        for (int column = 0; column < 2; ++column) {
    //            QModelIndex index = objectModel->index(row, column, QModelIndex());
    //            objectModel->setData(index, QVariant((row+1) * (column+1)));
    //        }
    //    }
}
