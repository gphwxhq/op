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
#include"settingDialog.h"
#include"progressCreator.h"
#include"progressMonitor.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeWidget();
    void initUi();
    void showSettings();
    void getSettings(int,int);

private:
//    Ui::MainWindow *ui;
    QWidget *centralWidget;
    QVBoxLayout *centralWidgetLayout;
    ProgressCreator *progressCreator;
    ProgressMonitor *progressMonitor;
    SettingDialog *settingDialog;
    QLabel *appName;
    QWidget *mTitle;
    QHBoxLayout *hBox1;
    QPushButton *page1;
    QPushButton *page2;
    QPushButton *setBtn;
};
#endif // MAINWINDOW_H
