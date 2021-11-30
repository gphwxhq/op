#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //    , ui(new Ui::MainWindow)
{
    this->initUi();
    QTimer::singleShot(1000, this,SLOT(showSettings()));
//    work=new handle();
    //    ui->setupUi(this);
    //    btn1=new QPushButton("111",this);
    //    btn1->setGeometry(10,10,100,50);
    //    btn1->setObjectName("btn");
    //    QObject::connect(btn1,&QPushButton::clicked,this,&QWidget::close);
}
void MainWindow::initUi(){
    //读取qss样式
    QFile file(QString(":/style.qss"));
    if(!file.exists()){
        qDebug()<<"QSS file not found!"<<endl;
        return ;
    }
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();

    // 设置窗口的位置和大小
    this->resize(1400,900);
    this->setMinimumSize(800,430);
    // 去除原生标题栏
    //    this->setWindowTitle("调度模拟系统");
    this->setWindowFlags(Qt::FramelessWindowHint);
    //自定义标题栏
    TitleBar *pTitleBar = new TitleBar(this);
    this->installEventFilter(pTitleBar);

    //自定义工具栏
    //初始化设置对话框
    settingDialog=new SettingDialog();

    //初始化标签页按钮
    page1=new QPushButton("进程创建");
    page1->setObjectName("app");
    page1->setCheckable(true);
    page1->setChecked(true);
    page1->setAutoExclusive(true);
    QObject::connect(page1,&QPushButton::clicked,this,&MainWindow::changeWidget);

    page2 =new QPushButton("结果预览");
    page2->setObjectName("app");
    page2->setCheckable(true);
    page2->setAutoExclusive(true);
    QObject::connect(page2,&QPushButton::clicked,this,&MainWindow::changeWidget);

    //初始化设置按钮
    setBtn =new QPushButton();
    setBtn->setObjectName("set_btn");
    QObject::connect(setBtn,&QPushButton::clicked,this,&MainWindow::showSettings);
    QObject::connect(settingDialog,&SettingDialog::settingChanged,this,&MainWindow::getSettings);

    //初始化布局
    hBox1=new QHBoxLayout();
    hBox1->addWidget(page1);
    hBox1->addStretch();
    hBox1->addWidget(page2);
    hBox1->addStretch();
    hBox1->addWidget(setBtn);

    vBox1=new QVBoxLayout();
    vBox1->addWidget(pTitleBar);
    vBox1->addLayout(hBox1);

    //整个上部
    mTitle=new QWidget();
    mTitle->setLayout(vBox1);
    mTitle->setStyleSheet("background-color: #9999FF");
    mTitle->setFixedHeight(60);
    //    this->setMenuWidget(mTitle);

    //初始化页面
    progressCreator=new ProgressCreator(this);
    connect(this,&MainWindow::init,progressCreator,&ProgressCreator::init);
    progressMonitor=new ProgressMonitor(this);
    connect(page2,&QPushButton::clicked,progressMonitor,&ProgressMonitor::refreshTable);


    //初始化遮罩
    MaskWidget::Instance()->setMainWidget(this);
    MaskWidget::Instance()->setDialogNames(QStringList() << "settingDialog"<<"createDialog");

    //初始化动画
    initAnimation();

    centralWidgetLayout=new QVBoxLayout();
    centralWidgetLayout->setSpacing(0);
    centralWidgetLayout->setMargin(0);
    centralWidgetLayout->addWidget(pTitleBar);
    centralWidgetLayout->addWidget(mTitle);
    centralWidgetLayout->addWidget(progressCreator);
    centralWidgetLayout->addWidget(progressMonitor);
    //    centralWidgetLayout->setContentsMargins(0, 0, 0, 0);

    centralWidget=new QWidget();
    centralWidget->setLayout(centralWidgetLayout);
    //    centralWidget->setStyleSheet("background-color: red");

    progressMonitor->hide();
    this->setCentralWidget(centralWidget);

    //    settingDialog->show();
}
void MainWindow::initAnimation(){
    //切换动画
    //    widgetOpacity1= new QGraphicsOpacityEffect(progressCreator);
    //    widgetOpacity1->setOpacity(1);
    //    progressCreator->setGraphicsEffect(widgetOpacity1);
    progressMonitorEnterAnimation=new QPropertyAnimation(progressMonitor, "pos");
    progressMonitorEnterAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    progressMonitorEnterAnimation->setDuration(500);
    connect(progressMonitorEnterAnimation, &QPropertyAnimation::finished, [=] {
        progressMonitor->setMinimumSize(0, 0);
        progressMonitor->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    });

    progressCreatorLeaveAnimation= new QPropertyAnimation(progressCreator, "pos");
    progressCreatorLeaveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    progressCreatorLeaveAnimation->setDuration(500);
    connect(progressCreatorLeaveAnimation, &QPropertyAnimation::finished, [=] {
        progressCreator->setMinimumSize(0, 0);
        progressCreator->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
        progressCreator->hide();
    });

    progressMonitorLeaveAnimation=new QPropertyAnimation(progressMonitor, "pos");
    progressMonitorLeaveAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    progressMonitorLeaveAnimation->setDuration(500);
    connect(progressMonitorLeaveAnimation, &QPropertyAnimation::finished, [=] {
        progressMonitor->setMinimumSize(0, 0);
        progressMonitor->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
        progressMonitor->hide();
    });

    progressCreatorEnterAnimation=new QPropertyAnimation(progressCreator, "pos");
    progressCreatorEnterAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    progressCreatorEnterAnimation->setDuration(500);
    connect(progressCreatorEnterAnimation, &QPropertyAnimation::finished, [=] {
        progressCreator->setMinimumSize(0, 0);
        progressCreator->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
//        progressCreator->show();
    });
}
void MainWindow::changeWidget(){
    QObject *sender=this->sender();
    if(sender==page1){
        if(progressCreator->isVisible())
            return;
        QPoint t= progressMonitor->pos();
        progressMonitor->setFixedSize(progressMonitor->width(),progressMonitor->height());
        progressCreator->setFixedSize(progressMonitor->width(),progressMonitor->height());
        progressCreator->show();
        progressCreatorEnterAnimation->setStartValue(QPoint(-progressMonitor->width(), t.y()));
        progressCreatorEnterAnimation->setEndValue(t);
        progressCreatorEnterAnimation->start();
        progressMonitorLeaveAnimation->setStartValue(t);
        progressMonitorLeaveAnimation->setEndValue(QPoint(progressMonitor->width(), t.y()));
        progressMonitorLeaveAnimation->start();

    }
    else{
        if(progressMonitor->isVisible())
            return;
        QPoint t=progressCreator->pos();
        progressCreator->setFixedSize(progressCreator->width(),progressCreator->height());
        progressMonitor->setFixedSize(progressCreator->width(),progressCreator->height());
        progressCreatorLeaveAnimation->setStartValue(t);
        progressCreatorLeaveAnimation->setEndValue(QPoint(-progressCreator->width(), t.y()));
        progressCreatorLeaveAnimation->start();
        progressMonitor->show();
        progressMonitorEnterAnimation->setStartValue(QPoint(progressMonitor->width(), t.y()));
        progressMonitorEnterAnimation->setEndValue(t);
        progressMonitorEnterAnimation->start();

        //        this->setCentralWidget(progressMonitor);
        progressMonitor->show();
    }
}
void MainWindow::showSettings(){
    settingDialog->exec();
}
void MainWindow::getSettings(int mode,int mem,int printerNum){
    qDebug()<<mode<<mem<<printerNum<<endl;
//    work->initValues(printerNum,mem);
    //mode:0、短进程 1、最短剩余时间
    if(work){
        delete work;
        work=new handle();
    }
    else
        work=new handle();
    QString tmsg=QString::fromStdString(work->initValues(mem,printerNum));
    //QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示
    progressCreator->work=work;
    progressMonitor->work=work;
    emit init(mode,mem,printerNum);
}

MainWindow::~MainWindow()
{
    delete work;
    delete settingDialog;
    //    delete appName;
    delete page1;
    delete page2;
    delete setBtn;
    delete hBox1;
    delete mTitle;

    delete progressMonitor;
    delete progressCreator;
    delete centralWidgetLayout;
    delete centralWidget;
}

