#include"toolTitleBar.h"

ToolTitleBar::ToolTitleBar(QWidget *parent,QString name):QWidget(parent)
{
    title=new QLabel(name);
    title->setStyleSheet("color: white;font-size: 25px;font-family:STKaiti;font-weight:bold;");
    titleBarLayout=new QHBoxLayout();
    titleBarLayout->addWidget(title);
    titleBarLayout->setContentsMargins(0,0,0,0);

    this->setLayout(titleBarLayout);
    this->setStyleSheet("background-color: #9999FF");
    this->setFixedHeight(50);
}

ToolTitleBar::~ToolTitleBar(){

}
