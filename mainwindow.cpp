#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //    , ui(new Ui::MainWindow)
{
    this->initUi();
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
    this->resize(1400,700);
    this->setMinimumSize(800,430);
    // 设置标题栏
    this->setWindowTitle("调度模拟系统");
    //设置菜单栏
    //名字
    appName = new QLabel();
    appName->setPixmap(QPixmap(":/title.png").scaled(QSize(300,50)));
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
    hBox1->setAlignment(Qt::AlignLeft);
    hBox1->addWidget(appName);
    hBox1->addSpacing(60);
    hBox1->addWidget(page1);
    hBox1->addStretch();
    hBox1->addWidget(page2);
    hBox1->addStretch();
    hBox1->addWidget(setBtn);

    mTitle=new QWidget();
    mTitle->setLayout(hBox1);
    mTitle->setStyleSheet("background-color: rgb(75, 75, 75)");
    this->setMenuWidget(mTitle);

    //初始化页面
    progressCreator=new ProgressCreator(this);
    progressMonitor=new ProgressMonitor(this);

    centralWidgetLayout=new QVBoxLayout();
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

void MainWindow::changeWidget(){
    QObject *sender=this->sender();
    if(sender==page1){
        progressMonitor->hide();
        //        this->setCentralWidget(progressCreator);
        progressCreator->show();
    }
    else{
        progressCreator->hide();
//        this->setCentralWidget(progressMonitor);
        progressMonitor->show();
    }
}
void MainWindow::showSettings(){
    settingDialog->show();
}
void MainWindow::getSettings(int mem,int num){
    qDebug()<<mem<<num<<endl;
}

MainWindow::~MainWindow()
{
    delete settingDialog;
    delete appName;
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

