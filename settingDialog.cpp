#include<settingDialog.h>

SettingDialog::SettingDialog(QWidget *parent):QDialog(parent)
{
    initUi();
}
void SettingDialog::initUi(){
    // 设置窗口的位置和大小
    this->resize(500,280);

    // 设置标题栏
//    this->setWindowTitle("设置");
    //用户只有关闭弹窗后，才能关闭主界面
//    this->setWindowModality(Qt::ApplicationModal);
//    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    this->setWindowFlags(Qt::FramelessWindowHint);
     this->setFixedSize(this->width(),this->height());
    this->setObjectName("settingDialog");
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
    toolTitleBar=new ToolTitleBar(nullptr,"设置");

    //表单布局
    rB1=new QRadioButton("短进程优先");
    rB1->setChecked(true);
    rB2=new QRadioButton("最短剩余时间");

    hBox=new QHBoxLayout();
    hBox->addWidget(rB1);
    hBox->addWidget(rB2);

    bG=new QButtonGroup();
    bG->addButton(rB1,0);
    bG->addButton(rB2,1);
    bG->setExclusive(true);

    le1=new QLineEdit();
    le2=new QLineEdit();
    sbtn=new QPushButton("保存");
//    sbtn->setObjectName("setting_button");
    QObject::connect(sbtn,&QPushButton::clicked,this,&SettingDialog::sendSignal);

    fBox=new QFormLayout();
    fBox->setContentsMargins(5,5,5,5);
    fBox->setRowWrapPolicy(QFormLayout::WrapAllRows);
    fBox->addRow("模式:",hBox);
//    fBox->addRow("内存分块数:",le1);
    fBox->addRow("内存:(MB)",le1);
    fBox->addRow("打印机:(台)",le2);
    fBox->addRow(sbtn);

    //设置行间距和列间距为 10
    fBox->setSpacing(10);
    //将 layout 表单添加到 widget 窗口中
    vBox=new QVBoxLayout();
    vBox->addWidget(toolTitleBar);
    vBox->addStretch();
    vBox->addLayout(fBox);
    vBox->setContentsMargins(0,0,0,0);
    vBox->addStretch();

    this->setLayout(vBox);
}
void SettingDialog::sendSignal(){
    totalMem=atoi(le1->text().toLatin1());
    printerNum=atoi(le2->text().toLatin1());
    emit settingChanged(bG->checkedId(),totalMem,printerNum);
    this->hide();
}
//void SettingDialog::getValue(){
//    qDebug()<< atoi(le1->text().toLatin1())<<endl;
//}
SettingDialog::~SettingDialog(){
    delete le1;
    delete le2;
    delete sbtn;
    delete fBox;
}
