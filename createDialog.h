#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include<QDialog>
#include<QFormLayout>
#include<QLineEdit>
#include<QDebug>
#include<QPushButton>
#include<QRadioButton>
#include<QVBoxLayout>
#include<QFile>

#include"toolTitleBar.h"

class CreateDialog :public QDialog
{
        Q_OBJECT
signals:
    void resultSignal(int,QString,int,int,int);

public:
    CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();
    void sendSignal();
    void initUi();
private:
//    int id, string name, int arrive_time, int need_time, int size, int machine
    ToolTitleBar *toolTitleBar;
    QVBoxLayout *vBox;
    QFormLayout *fBox;
    QLineEdit *idEdit,*nameEdit,*needTimeEdit,*sizeEdit,*machineEdit;
    QPushButton *sbtn;

    int id,need_time,size,machine;
    QString name;

};


#endif // CREATEDIALOG_H
