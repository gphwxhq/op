#ifndef PROGRESSCREATOR_H
#define PROGRESSCREATOR_H

#include<QWidget>
#include<QLabel>
#include<QTableWidget>
#include<QHeaderView>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QGroupBox>
#include<QPushButton>
#include<QFile>
#include<QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include<QMessageBox>

#include "settingDialog.h"
#include "createDialog.h"
#include "List.h"

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class ProgressCreator:public QWidget{
    Q_OBJECT
public:
    ProgressCreator(QWidget *parent = nullptr);
    ~ProgressCreator();
    void addNewProcess(int,QString,int,int,int);
    void initUi();
    void init(int,int ,int);
    void refreshTable();
    void goNext();
    void wakeUpProcess();
    void blockProcess();
    void delProcess();

    int mem=0,printerNum=0,mode=-1;
    int ntime;
    handle *work;

private slots:
    void showCreate();

private:
    CreateDialog *createDialog;
    QLabel *clock;

    QTableWidget *readyTable;
    QTableWidget *blockTable;
    QTableWidget *runTable;
    QTableWidget *createTable;
    QGridLayout *gLayout,*gLayout2;
    QVBoxLayout *vBox,*btnVBox;
    QHBoxLayout *hBox1,*hBox2,*hBox3,*fHBox,*hBox4,*hBox5;
    QGroupBox *gBox1,*gBox2,*gBox3,*gBox4;
    QPushButton *blockBtn,*wakeBtn,*newBtn,*runBtn,*createDelBtn,*readyDelBtn;

    QPieSeries *series1,*series2;
    QChart *chart1,*chart2;
    QChartView *chartView1,*chartView2;


};


#endif // PROGRESSCREATOR_H
