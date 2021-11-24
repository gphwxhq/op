#ifndef PROGRESSMONITOR_H
#define PROGRESSMONITOR_H

#include<QWidget>
#include<QLabel>

class ProgressMonitor:public QWidget{
    Q_OBJECT
public:
    ProgressMonitor(QWidget *parent = nullptr);
    ~ProgressMonitor();

private:
    QLabel *t;
};

#endif // PROGRESSMONITOR_H
