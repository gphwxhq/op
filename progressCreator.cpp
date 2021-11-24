#include<progressCreator.h>

ProgressCreator::ProgressCreator(QWidget *parent):QWidget(parent){
    //读取qss样式
    QFile file(QString(":/creator.qss"));
    if(!file.exists()){
        qDebug()<<"QSS file not found!"<<endl;
        return ;
    }
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();
    // t=new QLabel("progressCreator",this);
    // this->setStyleSheet("background-color: rgb(75, 75, 75)");
    readyTable=new QTableWidget(1,5);
    // readyTable->resize(500,400);
    QStringList header;
    header<<"进程名"<<"提交时间"<<"预计执行时间"<<"内存请求大小"<<"打印机请求数目";
    readyTable->setHorizontalHeaderLabels(header);
    // readyTable->insertRow(1);
    readyTable->setItem(0,0,new QTableWidgetItem("1"));
    readyTable->setItem(0,1,new QTableWidgetItem("1"));
    readyTable->setItem(0,2,new QTableWidgetItem("1"));
    readyTable->setItem(0,3,new QTableWidgetItem("1"));
    readyTable->setItem(0,4,new QTableWidgetItem("1"));
    readyTable->setMinimumWidth(518);
    readyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    readyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    readyTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    newBtn=new QPushButton();
    newBtn->setObjectName("new_btn");
    runBtn=new QPushButton();
    runBtn->setObjectName("run_btn");

    hBox1=new QHBoxLayout();
    hBox1->addWidget(readyTable);
    gBox1=new QGroupBox("就绪队列");
    gBox1->setLayout(hBox1);
    fHBox=new QHBoxLayout();
    fHBox->addWidget(gBox1);
    fHBox->addSpacing(10);
    fHBox->addWidget(newBtn);
    fHBox->addWidget(runBtn);

//    gBox1->setMaximumWidth(540);

    blockTable=new QTableWidget(2,5);
    blockTable->setHorizontalHeaderLabels(header);
    blockTable->setItem(0,0,new QTableWidgetItem("1"));
    blockTable->setItem(0,1,new QTableWidgetItem("1"));
    blockTable->setItem(0,2,new QTableWidgetItem("1"));
    blockTable->setItem(0,3,new QTableWidgetItem("1"));
    blockTable->setItem(0,4,new QTableWidgetItem("1"));
    blockTable->setItem(1,0,new QTableWidgetItem("2"));
    blockTable->setItem(1,1,new QTableWidgetItem("2"));
    blockTable->setItem(1,2,new QTableWidgetItem("2"));
    blockTable->setItem(1,3,new QTableWidgetItem("2"));
    blockTable->setItem(1,4,new QTableWidgetItem("2"));
    blockTable->setMinimumWidth(518);
    blockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    blockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    blockTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    wakeBtn=new QPushButton("唤醒");

    hBox2=new QHBoxLayout();
    hBox2->addWidget(blockTable);
    hBox2->addSpacing(10);
    hBox2->addWidget(wakeBtn,0,Qt::AlignTop);
    gBox2=new QGroupBox("阻塞队列");
    gBox2->setLayout(hBox2);

    runTable=new QTableWidget(1,5);
    runTable->setHorizontalHeaderLabels(header);
    runTable->setItem(0,0,new QTableWidgetItem("1"));
    runTable->setItem(0,1,new QTableWidgetItem("1"));
    runTable->setItem(0,2,new QTableWidgetItem("1"));
    runTable->setItem(0,3,new QTableWidgetItem("1"));
    runTable->setItem(0,4,new QTableWidgetItem("1"));
    runTable->setMinimumWidth(518);
    runTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    runTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    runTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    blockBtn=new QPushButton("阻塞");

    hBox3=new QHBoxLayout();
    hBox3->addWidget(runTable);
    hBox3->addSpacing(10);
    hBox3->addWidget(blockBtn,0,Qt::AlignTop);
    gBox3=new QGroupBox("运行队列");
    gBox3->setLayout(hBox3);

    vBox=new QVBoxLayout();
    vBox->addLayout(fHBox);

    vBox->addSpacing(10);
    vBox->addWidget(gBox2);

    vBox->addSpacing(10);
    vBox->addWidget(gBox3);
    this->setLayout(vBox);
}
ProgressCreator::~ProgressCreator(){

}
