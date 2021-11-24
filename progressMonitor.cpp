#include<progressMonitor.h>

ProgressMonitor::ProgressMonitor(QWidget *parent):QWidget(parent){
t=new QLabel("progressMonitor",this);
//this->setStyleSheet("background-color: red");
}
ProgressMonitor::~ProgressMonitor(){

}
