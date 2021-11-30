#include<progressMonitor.h>

ProgressMonitor::ProgressMonitor(QWidget *parent):QWidget(parent){

    //读取qss样式
    QFile file(QString(":/creator.qss"));
    if(!file.exists()){
        qDebug()<<"QSS file not found!"<<endl;
        return ;
    }
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();
    //第一行
//    startTable=new QTableWidget(0,6);
    // readyTable->resize(500,400);
    QStringList header;
    header<<"进程名"<<"提交时间"<<"预计执行时间"<<"完成时间"<<"内存请求大小"<<"打印机请求数目";
//    startTable->setHorizontalHeaderLabels(header);
    // readyTable->insertRow(1);
//    startTable->setItem(0,0,new QTableWidgetItem("1"));
//    startTable->setItem(0,1,new QTableWidgetItem("1"));
//    startTable->setItem(0,2,new QTableWidgetItem("1"));
//    startTable->setItem(0,3,new QTableWidgetItem("1"));
//    startTable->setItem(0,4,new QTableWidgetItem("1"));
//    startTable->setMinimumWidth(518);
//    startTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    startTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    startTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //第二行
    endTable=new QTableWidget(0,6);
    endTable->setHorizontalHeaderLabels(header);
    // readyTable->insertRow(1);
//    endTable->setItem(0,0,new QTableWidgetItem("1"));
//    endTable->setItem(0,1,new QTableWidgetItem("1"));
//    endTable->setItem(0,2,new QTableWidgetItem("1"));
//    endTable->setItem(0,3,new QTableWidgetItem("1"));
//    endTable->setItem(0,4,new QTableWidgetItem("1"));
    endTable->setMinimumWidth(518);
    endTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    endTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    endTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    hBox1=new QHBoxLayout();
    hBox1->addWidget(endTable);

    gBox1=new QGroupBox("完成队列");
    gBox1->setLayout(hBox1);

    resultLabel1=new QLabel();
    resultLabel1->setObjectName("resLabel");
    resultLabel1->setAlignment(Qt::AlignRight);
    resultLabel2=new QLabel();
    resultLabel2->setObjectName("resLabel");
    resultLabel2->setAlignment(Qt::AlignRight);

    vBox=new QVBoxLayout();
//    vBox->addWidget(startTable);
    vBox->addWidget(gBox1);
    vBox->addWidget(resultLabel1);
    vBox->addWidget(resultLabel2);
    vBox->setContentsMargins(30,30,30,30);

    this->setLayout(vBox);
}

void ProgressMonitor::refreshTable(){
    pcb* finish=work->finish;

    endTable->clearContents();
    endTable->setRowCount(0);
//    vector<QString[5]> tv;
    while(finish!=NULL){
        int r=endTable->rowCount();
        endTable->setRowCount(r+1);
        endTable->setItem(r,0,new QTableWidgetItem(QString::fromStdString(finish->name)));
        endTable->setItem(r,1,new QTableWidgetItem(QString("%1").arg(finish->arrive_time)));
        endTable->setItem(r,2,new QTableWidgetItem(QString("%1").arg(finish->need_time)));
        endTable->setItem(r,3,new QTableWidgetItem(QString("%1").arg(finish->finish_time)));
        endTable->setItem(r,4,new QTableWidgetItem(QString("%1").arg(finish->size)));
        endTable->setItem(r,5,new QTableWidgetItem(QString("%1").arg(finish->machine)));
//        tv.push_back({QString::fromStdString(reserve->name),QString("%1").arg(ntime),QString("%1").arg(reserve->need_time),QString("%1").arg(reserve->size)});
        finish=finish->next;
    }

    resultLabel1->setText(QString("平均周转时间：%1").arg(work->avg_turn_time()));
    resultLabel2->setText(QString("加权平均周转时间：%1").arg(work->avg_pow_turn_time()));

}

ProgressMonitor::~ProgressMonitor(){

}
