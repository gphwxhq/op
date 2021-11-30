#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <QHBoxLayout>
#include<QVBoxLayout>
#include<QFile>
#include<QDebug>
#include<QLabel>
#include<QPixmap>
#include<QGraphicsOpacityEffect>
#include<QPropertyAnimation>
#include<QTimer>
#include<QMessageBox>

#include"settingDialog.h"
#include"progressCreator.h"
#include"progressMonitor.h"
#include"title_bar.h"
#include "maskwidget.h"
#include "List.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


signals:
    void init(int mode,int mem,int num);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeWidget();
    void initUi();
    void initAnimation();
    void getSettings(int,int,int);

private slots:
    void showSettings();

private:
//    Ui::MainWindow *ui;
    handle *work=nullptr;
    QWidget *centralWidget;
    QVBoxLayout *centralWidgetLayout;
    ProgressCreator *progressCreator;
    ProgressMonitor *progressMonitor;

    SettingDialog *settingDialog;
    QLabel *appName;
    QWidget *mTitle;
    QHBoxLayout *hBox1,*hBox2;
    QVBoxLayout *vBox1;
    QPushButton *page1;
    QPushButton *page2;
    QPushButton *setBtn;
//    QGraphicsOpacityEffect *widgetOpacity1,*widgetOpacity2;
    QPropertyAnimation *progressCreatorEnterAnimation,*progressCreatorLeaveAnimation,*progressMonitorEnterAnimation,*progressMonitorLeaveAnimation;
};
#endif // MAINWINDOW_H
