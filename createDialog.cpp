#include "createDialog.h"

CreateDialog::CreateDialog(QWidget *parent):QDialog(parent){
    id=need_time=size=machine=0;
    name="";
    initUi();
}
void CreateDialog::initUi(){
    // 设置窗口的位置和大小
    this->resize(500,420);
    // 设置标题栏
    this->setWindowTitle("新建进程");
    //用户只有关闭弹窗后，才能关闭主界面
    //    this->setWindowModality(Qt::ApplicationModal);
    //    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    this->setObjectName("createDialog");
    //读取qss样式
    QFile file(QString(":/setting.qss"));
    if(!file.exists()){
        qDebug()<<"QSS file not found!"<<endl;
        return ;
    }
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
    file.close();

    //标题栏
    toolTitleBar=new ToolTitleBar(nullptr,"新建进程");

    idEdit=new QLineEdit();
    nameEdit=new QLineEdit();
    needTimeEdit=new QLineEdit();
    sizeEdit=new QLineEdit();
    machineEdit=new QLineEdit();

    sbtn=new QPushButton("保存");
    //    sbtn->setObjectName("setting_button");
    QObject::connect(sbtn,&QPushButton::clicked,this,&CreateDialog::sendSignal);

    fBox=new QFormLayout();
    fBox->setContentsMargins(5,5,5,5);
    fBox->setRowWrapPolicy(QFormLayout::WrapAllRows);
    fBox->addRow("进程号:",idEdit);
    fBox->addRow("进程名:",nameEdit);
    fBox->addRow("运行所需时间:",needTimeEdit);
    fBox->addRow("所需内存(MB):",sizeEdit);
    fBox->addRow("所需设备数:",machineEdit);
    fBox->addRow(sbtn);

    //设置行间距和列间距为 10
    fBox->setSpacing(10);
    //将 layout 表单添加到 widget 窗口中
    vBox=new QVBoxLayout();
    vBox->addWidget(toolTitleBar);
    vBox->addStretch();
    vBox->addLayout(fBox);
    vBox->addStretch();
    vBox->setContentsMargins(0,0,0,0);

    this->setLayout(vBox);
}
void CreateDialog::sendSignal(){
    id=atoi(idEdit->text().toLatin1());
    name=nameEdit->text();
    need_time=atoi(needTimeEdit->text().toLatin1());
    size=atoi(sizeEdit->text().toLatin1());
    machine=atoi(machineEdit->text().toLatin1());
    this->hide();
    emit resultSignal(id,name,need_time,size,machine);
}
CreateDialog::~CreateDialog(){

}
