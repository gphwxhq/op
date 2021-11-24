#ifndef PROGRESSCREATOR_H
#define PROGRESSCREATOR_H

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

class ProgressCreator:public QWidget{
    Q_OBJECT
public:
    ProgressCreator(QWidget *parent = nullptr);
    ~ProgressCreator();

private:
    QLabel *t;
    QTableWidget *readyTable;
    QTableWidget *blockTable;
    QTableWidget *runTable;
    QVBoxLayout *vBox,*btnVBox;
    QHBoxLayout *hBox1,*hBox2,*hBox3,*fHBox;
    QGroupBox *gBox1,*gBox2,*gBox3;
    QPushButton *blockBtn,*wakeBtn,*newBtn,*runBtn;
};


#endif // PROGRESSCREATOR_H
