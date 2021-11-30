#ifndef PROGRESSMONITOR_H
#define PROGRESSMONITOR_H

#include<QWidget>
#include<QLabel>
#include<QTableWidget>
#include<QHeaderView>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGroupBox>
#include<QPushButton>
#include<QFile>
#include<QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

#include"List.h"

class ProgressMonitor:public QWidget{
    Q_OBJECT
public:
    ProgressMonitor(QWidget *parent = nullptr);
    ~ProgressMonitor();
    void refreshTable();

    handle *work;
private:
    QVBoxLayout *vBox;
    QHBoxLayout *hBox1;
//    QTableWidget *startTable;
    QGroupBox *gBox1;
    QTableWidget *endTable;
    QLabel *resultLabel1,*resultLabel2;



};

#endif // PROGRESSMONITOR_H
