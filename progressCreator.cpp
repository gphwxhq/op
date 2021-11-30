#include<progressCreator.h>

ProgressCreator::ProgressCreator(QWidget *parent):QWidget(parent){
    ntime=0;
    initUi();
}
void ProgressCreator::initUi(){
    //读取qss样式
    QFile file(QString(":/creator.qss"));
    if(!file.exists()){
        qDebug()<<"QSS file not found!"<<endl;
        return ;
    }
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();

    //初始化新建对话框
    createDialog=new CreateDialog();
    connect(createDialog,&CreateDialog::resultSignal,this,&ProgressCreator::addNewProcess);

    //第一行 图表部分
    series1 = new QPieSeries();

    chart1 = new QChart();
    chart1->addSeries(series1);
    chart1->setTitle("内存");
    chart1->legend()->hide();									//是否显示图例
    chart1->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing); //抗锯齿处理
    chartView1->chart()->setTheme(QChart::ChartThemeLight);

    series2 = new QPieSeries();

    chart2= new QChart();
    chart2->addSeries(series2);
    chart2->setTitle("打印机");
    chart2->legend()->hide();									//是否显示图例
    chart2->setAnimationOptions(QChart::AllAnimations); // 设置显示时的动画效果
    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing); //抗锯齿处理
    chartView2->chart()->setTheme(QChart::ChartThemeLight);

    clock=new QLabel(QString("当前时间:\n%1").arg(ntime));
    clock->setWordWrap(true);
    clock->setAlignment(Qt::AlignCenter);
//    clock->setFixedWidth(50);
    clock->setObjectName("clock");
    newBtn=new QPushButton();
    newBtn->setObjectName("new_btn");
    connect(newBtn,&QPushButton::clicked,this,&ProgressCreator::showCreate);
    runBtn=new QPushButton();
    runBtn->setObjectName("run_btn");
    connect(runBtn,&QPushButton::clicked,this,&ProgressCreator::goNext);

    gLayout2=new QGridLayout();
    gLayout2->addWidget(clock,0,0,2,1);
    gLayout2->addWidget(newBtn,0,1);
    gLayout2->addWidget(runBtn,1,1);
    gLayout2->setHorizontalSpacing(20);
    gLayout2->setVerticalSpacing(10);
    gLayout2->setContentsMargins(0,0,0,0);

    hBox1=new QHBoxLayout();
    hBox1->addWidget(chartView1);
    hBox1->addWidget(chartView2);
//    hBox1->addSpacing(10);
    hBox1->addLayout(gLayout2);

    //第二行
    createTable=new QTableWidget(0,6);
    QStringList header;
    header<<"进程名"<<"提交时间"<<"预计执行时间"<<"剩余时间"<<"内存请求大小"<<"打印机请求数目";
    createTable->setHorizontalHeaderLabels(header);
    createTable->setMinimumWidth(518);
    createTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    createTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    createTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    createTable->setFocusPolicy(Qt::NoFocus);

//    createTable->setRowCount(createTable->rowCount()+1);
//    createTable->setItem(0,0,new QTableWidgetItem("1"));
    createDelBtn=new QPushButton("删除");
    connect(createDelBtn,&QPushButton::clicked,this,&ProgressCreator::delProcess);

    hBox5=new QHBoxLayout();
    hBox5->addWidget(createTable);
    hBox5->addWidget(createDelBtn,0,Qt::AlignTop);
    gBox4=new QGroupBox("创建队列");
    gBox4->setLayout(hBox5);


    readyTable=new QTableWidget(0,6);
    readyTable->setHorizontalHeaderLabels(header);
    // readyTable->insertRow(1);
//    readyTable->setItem(0,0,new QTableWidgetItem("1"));
//    readyTable->setItem(0,1,new QTableWidgetItem("1"));
//    readyTable->setItem(0,2,new QTableWidgetItem("1"));
//    readyTable->setItem(0,3,new QTableWidgetItem("1"));
//    readyTable->setItem(0,4,new QTableWidgetItem("1"));
    readyTable->setMinimumWidth(518);
    readyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    readyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    readyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    readyTable->setFocusPolicy(Qt::NoFocus);

    readyDelBtn=new QPushButton("删除");
    connect(readyDelBtn,&QPushButton::clicked,this,&ProgressCreator::delProcess);

    hBox2=new QHBoxLayout();
    hBox2->addWidget(readyTable);
    hBox2->addWidget(readyDelBtn,0,Qt::AlignTop);
    gBox1=new QGroupBox("就绪队列");
    gBox1->setLayout(hBox2);
    //    fHBox=new QHBoxLayout();
    //    fHBox->addWidget(gBox1);

    //    gBox1->setMaximumWidth(540);
    //第三行
    blockTable=new QTableWidget(0,6);
    blockTable->setHorizontalHeaderLabels(header);
//    blockTable->setItem(0,0,new QTableWidgetItem("1"));
//    blockTable->setItem(0,1,new QTableWidgetItem("1"));
//    blockTable->setItem(0,2,new QTableWidgetItem("1"));
//    blockTable->setItem(0,3,new QTableWidgetItem("1"));
//    blockTable->setItem(0,4,new QTableWidgetItem("1"));
//    blockTable->setItem(1,0,new QTableWidgetItem("2"));
//    blockTable->setItem(1,1,new QTableWidgetItem("2"));
//    blockTable->setItem(1,2,new QTableWidgetItem("2"));
//    blockTable->setItem(1,3,new QTableWidgetItem("2"));
//    blockTable->setItem(1,4,new QTableWidgetItem("2"));
    blockTable->setMinimumWidth(518);
    blockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    blockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    blockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    blockTable->setFocusPolicy(Qt::NoFocus);

    wakeBtn=new QPushButton("唤醒");
    connect(wakeBtn,&QPushButton::clicked,this,&ProgressCreator::wakeUpProcess);

    hBox3=new QHBoxLayout();
    hBox3->addWidget(blockTable);
    hBox3->addSpacing(10);
    hBox3->addWidget(wakeBtn,0,Qt::AlignTop);
    gBox2=new QGroupBox("阻塞队列");
    gBox2->setLayout(hBox3);

    //第四行
    runTable=new QTableWidget(0,6);
    runTable->setHorizontalHeaderLabels(header);
//    runTable->setItem(0,0,new QTableWidgetItem("1"));
//    runTable->setItem(0,1,new QTableWidgetItem("1"));
//    runTable->setItem(0,2,new QTableWidgetItem("1"));
//    runTable->setItem(0,3,new QTableWidgetItem("1"));
//    runTable->setItem(0,4,new QTableWidgetItem("1"));
    runTable->setMinimumWidth(518);
    runTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    runTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    runTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    runTable->setFocusPolicy(Qt::NoFocus);

    blockBtn=new QPushButton("阻塞");
    connect(blockBtn,&QPushButton::clicked,this,&ProgressCreator::blockProcess);

    hBox4=new QHBoxLayout();
    hBox4->addWidget(runTable);
    hBox4->addSpacing(10);
    hBox4->addWidget(blockBtn,0,Qt::AlignTop);
    gBox3=new QGroupBox("运行队列");
    gBox3->setLayout(hBox4);

    gLayout=new QGridLayout();
    gLayout->setHorizontalSpacing(10);
    gLayout->setVerticalSpacing(10);
    gLayout->setContentsMargins(10,10,10,10);
    gLayout->addLayout(hBox1,0,0,1,2);
    gLayout->addWidget(gBox4,1,0);
    gLayout->addWidget(gBox1,1,1);
    gLayout->addWidget(gBox2,2,0);
    gLayout->addWidget(gBox3,2,1);

    //    vBox->addSpacing(10);
    //    vBox->addLayout(fHBox);

    //    vBox->addSpacing(10);
    //    vBox->addWidget(gBox2);

    //    vBox->addSpacing(10);
    //    vBox->addWidget(gBox3);

    //    vBox->setStretchFactor(hBox1,3);
    //    vBox->setStretchFactor(fHBox,2);
    //    vBox->setStretchFactor(gBox2,2);
    //    vBox->setStretchFactor(gBox3,2);

    this->setLayout(gLayout);
}
void ProgressCreator::delProcess(){
    auto *sender=this->sender();
    if(sender==createDelBtn){
        int r=createTable->currentRow();
        if(r==-1)
            return;
        QString name=createTable->item(r,0)->text();
        QString tmsg=QString::fromStdString(work->deletePcb(work->reserve,name.toStdString()));
        QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示
    }
    else{
        int r=readyTable->currentRow();
        if(r==-1)
            return;
        QString name=readyTable->item(r,0)->text();
        QString tmsg=QString::fromStdString(work->deletePcb(work->ready,name.toStdString()));
        QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示
    }
    refreshTable();

}
void ProgressCreator::addNewProcess(int id,QString name,int need_time,int size,int machine){
    qDebug()<<id<<name<<need_time<<size<<machine<<endl;

    QString tmsg=QString::fromStdString(work->createPcb(id,name.toStdString(),ntime,need_time,size,machine));
    QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示
    
    refreshTable();

//    int r=createTable->rowCount();
//    createTable->setRowCount(r+1);

//    createTable->setItem(r,0,new QTableWidgetItem(name));
//    createTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(ntime)));
//    createTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(need_time)));
//    createTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(size)));
//    createTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(machine)));

//    series1->append(QString("%1 %2").arg(name).arg(size), 10);

}
void ProgressCreator::refreshTable(){
    pcb* run=work->run;
    pcb* ready=work->ready;
    pcb* finish=work->finish;
    pcb* wait=work->wait;//阻塞队列
    pcb* reserve=work->reserve;//预备队列

    int memRemain=mem;
    int printerRemain=printerNum;

    series1->clear();
    series2->clear();

    createTable->clearContents();
    createTable->setRowCount(0);
//    vector<QString[5]> tv;
    while(reserve!=NULL){
        int r=createTable->rowCount();
        createTable->setRowCount(r+1);
        createTable->setItem(r,0,new QTableWidgetItem(QString::fromStdString(reserve->name)));
        createTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(reserve->arrive_time)));
        createTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(reserve->need_time)));
        createTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(reserve->more_time)));
        createTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(reserve->size)));
        createTable->setItem(r,5,new QTableWidgetItem(QString("%1").arg(reserve->machine)));
//        tv.push_back({QString::fromStdString(reserve->name),QString("%1").arg(ntime),QString("%1").arg(reserve->need_time),QString("%1").arg(reserve->size)});
        reserve=reserve->next;
    }

    readyTable->clearContents();
    readyTable->setRowCount(0);
    while(ready!=NULL){
        int r=readyTable->rowCount();
        readyTable->setRowCount(r+1);
        readyTable->setItem(r,0,new QTableWidgetItem(QString::fromStdString(ready->name)));
        readyTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(ready->arrive_time)));
        readyTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(ready->need_time)));
        readyTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(ready->more_time)));
        readyTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(ready->size)));
        readyTable->setItem(r,5,new QTableWidgetItem(QString("%1").arg(ready->machine)));

        memRemain-=ready->size;
//        qDebug()<<float(ready->size)/mem<<endl;
        series1->append(QString("%1 %2").arg(QString::fromStdString(ready->name)).arg(ready->size), float(ready->size)/mem);
        printerRemain-=ready->machine;
        series2->append(QString("%1 %2").arg(QString::fromStdString(ready->name)).arg(ready->machine), float(ready->machine)/printerNum);

        ready=ready->next;
    }

    runTable->clearContents();
    runTable->setRowCount(0);
    while(run!=NULL){
        int r=runTable->rowCount();
        runTable->setRowCount(r+1);
        runTable->setItem(r,0,new QTableWidgetItem(QString::fromStdString(run->name)));
        runTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(run->arrive_time)));
        runTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(run->need_time)));
        runTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(run->more_time)));
        runTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(run->size)));
        runTable->setItem(r,5,new QTableWidgetItem(QString("%1").arg(run->machine)));

        memRemain-=run->size;
        series1->append(QString("%1 %2").arg(QString::fromStdString(run->name)).arg(run->size), float(run->size)/mem);
        printerRemain-=run->machine;
        series2->append(QString("%1 %2").arg(QString::fromStdString(run->name)).arg(run->machine), float(run->machine)/printerNum);

        run=run->next;
    }

    blockTable->clearContents();
    blockTable->setRowCount(0);
    while(wait!=NULL){
        int r=blockTable->rowCount();
        blockTable->setRowCount(r+1);
        blockTable->setItem(r,0,new QTableWidgetItem(QString::fromStdString(wait->name)));
        blockTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(wait->arrive_time)));
        blockTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(wait->need_time)));
        blockTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(wait->more_time)));
        blockTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(wait->size)));
        blockTable->setItem(r,5,new QTableWidgetItem(QString("%1").arg(wait->machine)));

        memRemain-=wait->size;
        series1->append(QString("%1 %2").arg(QString::fromStdString(wait->name)).arg(wait->size), float(wait->size)/mem);
        printerRemain-=wait->machine;
        series2->append(QString("%1 %2").arg(QString::fromStdString(wait->name)).arg(wait->machine), float(wait->machine)/printerNum);

        wait=wait->next;
    }
    qDebug()<<float(memRemain)/mem<<endl;
    if(memRemain>0){
        series1->append(QString("空闲 %1").arg(memRemain),float(memRemain)/mem)->setColor(QColor(30,144,255));
    }
    if(printerRemain>0){
        series2->append(QString("空闲 %1").arg(printerRemain),float(printerRemain)/printerNum)->setColor(QColor(30,144,255));
    }
    series1->setLabelsVisible();
    series2->setLabelsVisible();

}
void ProgressCreator::init(int mode,int mem,int num){
    this->mode=mode;
    this->mem=mem;
    printerNum=num;
    ntime=0;

    clock->setText(QString("当前时间为:\n%1").arg(ntime));

    series1->clear();
    series2->clear();
    createTable->clearContents();
    createTable->setRowCount(0);
    runTable->clearContents();
    runTable->setRowCount(0);
    readyTable->clearContents();
    readyTable->setRowCount(0);
    blockTable->clearContents();
    blockTable->setRowCount(0);

    series1->append(QString("空闲%1").arg(mem), 1)->setColor(QColor(30,144,255));
//    remain1->setColor(QColor(0, 200, 200));
    series2->append(QString("空闲%1").arg(num), 1)->setColor(QColor(30,144,255));
//    remain2->setColor(QColor(0, 200, 200));
    series1->setLabelsVisible();
    series2->setLabelsVisible();
    qDebug()<<mem<<num<<endl;
}
void ProgressCreator::showCreate(){
    createDialog->exec();
}
void ProgressCreator::goNext(){
    if(mode==0)
        work->run_SJF(ntime);
    else
        work->run_SRTF(ntime);
    refreshTable();
    clock->setText(QString("当前时间为:\n%1").arg(ntime));
}
void ProgressCreator::blockProcess(){
    if(work->run){
        QString tmsg=QString::fromStdString(work->wait_Pcb(work->run));
        QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示

        refreshTable();
    }
}
void ProgressCreator::wakeUpProcess(){
    int r=blockTable->currentRow();
    if(r==-1)
        return;
    QString name=blockTable->item(r,0)->text();

    QString tmsg=QString::fromStdString(work->wakeup_Pcb(name.toStdString()));
    QMessageBox::warning(NULL,QStringLiteral("警告"),tmsg, QMessageBox::Ok,QMessageBox::Ok);// 添加提示


    refreshTable();
}
ProgressCreator::~ProgressCreator(){

}
