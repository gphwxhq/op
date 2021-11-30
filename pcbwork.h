#ifndef PCBWORK_H
#define PCBWORK_H

#include<string>
using namespace std;
class pcb {

public:

    string name;      //进程名
    int id;           //进程标识数
    int arrive_time;  //到达时间
    int need_time;    //估计服务时间
    int prio;         //进程优先数，数字越大优先级越高
    int wait_time;    //等待时间
    int more_time = 0;    //剩余执行的时间
    int start_time;   //进程开始时间
    int finish_time;  //结束时间
    int state;        //进程状态：执行--0、就绪--1、阻塞--2、完成--3、预备--4
    int machine_state;
    int machine;      //申请打印机数量
    int size;         //申请内存大小
    int start;        //内存起始地址
    int status;       //内存占用状态, 0占用，1空闲
    pcb* next;        //队列链接指针

public:
    handle han;
    void init_Pcb(int id, string name, int arrive_time, int need_time, int size, int machine);  //初始化节点
    void init_Memory(int totalSize);                                                            //初始化主内存
    void insert_To(pcb*& target, string targetName);                                            //节点插入到目标队列
    void copy_Pcb(pcb*& object);                                                                //复制节点
    void put_To(pcb*& from, pcb*& target, string targetName);                                   //将节点从当前队列转移到目标队列队尾
    void print_Memory();                                                                        //输出内存状态
    void wait_Pcb();                                                                            //进程阻塞
    void destory_Pcb(pcb*& from, int now_time);                                                 //进程运行完成，删除进程，移进finish队列
    void destory_Memory();                                                                      //
};
class handle {
public:
    int num = 0, note_num = 0;
    int reserve_num = 0;    //预备队列进程数量
    pcb* ready = NULL, * finish = NULL;
    pcb* wait = NULL;//阻塞队列
    pcb* reserve = NULL;//预备队列
    int io;//打印机总量
    int block = 0;//必然阻塞的进程数目（申请打印机>总量）
    int note_block = 0;//srtf第一次遍历ready判断打印机阻塞
    pcb* Memory = new pcb;
public:

    void wakeup_Pcb(string check_Name);              // 唤醒阻塞进程
    int Alloc_Memory(string name, int size, pcb* p); // 分配内存：最佳适应算法
    void Free_Memory(string name, pcb* p);           // 释放内存
    void init();                                     // 初始换数据
    pcb* toReady(int now_time);                      // 遍历reserve队列，将此时间到达的进程加入ready队列
    pcb* SJF(int now_time, int* after);              // sjf  最短作业优先(shortest job first)
    pcb* SRTF(pcb* run, int now_time, int* after);   // srtf  最短剩余时间优先，从就绪队列取最佳到运行队列
    void print_Pcb(pcb* target, string name);        // 输出目标队列
    void output_result();                            // 所有进程结束，输出结果
    void output_run(struct pcb* p, int now_time);    // 输出当前运行进程
    void menu();                                     // 开始菜单
    void cmain();
};


#endif
