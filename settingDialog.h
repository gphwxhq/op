#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include<QDialog>
#include<QFormLayout>
#include<QLineEdit>
#include<QDebug>
#include<QPushButton>
#include<QButtonGroup>
#include<QRadioButton>
#include<QFile>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>

#include"toolTitleBar.h"

class SettingDialog :public QDialog
{
        Q_OBJECT
signals:
    void settingChanged(int,int,int);

public:
    SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    void sendSignal();
    void initUi();
private:
    ToolTitleBar *toolTitleBar;

    QFormLayout *fBox;
    QLineEdit *le1;
    QLineEdit *le2;
    QLineEdit *le3;
    QPushButton *sbtn;
    QButtonGroup *bG;
    QRadioButton *rB1,*rB2;
    QHBoxLayout *hBox;
    QVBoxLayout *vBox;
    int totalMem=0;
    int printerNum=0;
    int blockNum=0;

};

#endif // SETTINGDIALOG_H
