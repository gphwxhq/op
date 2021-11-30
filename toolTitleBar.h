#ifndef TOOLTITLEBAR_H
#define TOOLTITLEBAR_H

#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>

class ToolTitleBar : public QWidget
{
    Q_OBJECT

public:
    ToolTitleBar(QWidget *parent = nullptr,QString name="");
    ~ToolTitleBar();
private:
    QHBoxLayout *hBox,*titleBarLayout;
    QLabel *title;
};

#endif // TOOLTITLEBAR_H
