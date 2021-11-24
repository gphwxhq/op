#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include<QDialog>
#include<QFormLayout>
#include<QLineEdit>
#include<QDebug>
#include<QPushButton>
#include<QRadioButton>
#include<QFile>

class SettingDialog :public QDialog
{
        Q_OBJECT
signals:
    void settingChanged(int,int);

public:
    SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    void sendSignal();
    void initUi();
private:
    QFormLayout *fBox;
    QLineEdit *le1;
    QLineEdit *le2;
    QPushButton *sbtn;
    QButtonGroup *qBG;
    QRadioButton *rB1,*rB2;
    int totalMem=0;
    int printerNum=0;

};

#endif // SETTINGDIALOG_H
