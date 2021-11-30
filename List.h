#ifndef LIST_H
#define LIST_H
#include<string>
using namespace std;
class memory {
public:
    string pcbName;   //占用内存名
    int size;         //内存块大小
    int start;        //内存起始地址
    int status;       //内存占用状态, 0占用，1空闲
    memory* next;     //队列链接指针
public:
    memory(int size);
    ~memory() {}
    void destory_Memory();
    void print_Memory();            //输出内存状态
};
class pcb {

public:
    string name;      //进程名
    int id;           //进程标识数
    int arrive_time;  //到达时间  
    int need_time;    //估计服务时间 
    int wait_time;    //等待时间 
    int more_time;    //剩余执行的时间
    int start_time;   //进程开始时间 
    int finish_time;  //结束时间
    int state;        //进程状态：执行--0、就绪--1、阻塞--2、完成--3、预备--4
    int machine_state;
    int machine;      //申请打印机数量
    int size;         //申请内存大小

    int turn_time;
    int pow_turn_time;

    //int status;       //内存占用状态, 0占用，1空闲
    pcb* next;        //队列链接指针

public:
    void init_Pcb(int id, string name, int arrive_time, int need_time, int size, int machine);  //初始化节点       
    void insert_To(pcb*& target, string targetName);                                            //节点插入到目标队列
    void copy_Pcb(pcb*& object);                                                                //复制节点
    void put_To(pcb*& from, pcb*& target, string targetName);                                   //将节点从当前队列转移到目标队列队尾

};


class handle {
public:
    int num;
    int reserve_num;    //预备队列进程数量
    pcb* run;
    pcb* ready;
    pcb* finish;
    pcb* wait;//阻塞队列
    pcb* reserve;//预备队列
    int io;//打印机总量
    int block;//必然阻塞的进程数目（申请打印机>总量）
    int note_me;
    int note_io;//srtf第一次遍历ready判断打印机阻塞
    memory* Memory;
public:
    
    handle();
    ~handle() {}
    pcb* toReady(int now_time);                      // 遍历reserve队列，将此时间到达的进程加入ready队列
    void print_Pcb(pcb* target, string name);        // 输出目标队列
    void output_result();                            // 所有进程结束，输出结果
    void output_run(struct pcb* p, int now_time);    // 输出当前运行进程

    int Alloc_Memory(string name, int size, memory* p); // 分配内存：最佳适应算法
    void Free_Memory(string name, memory* p);           // 释放内存
    pcb* SJF(int now_time);              // sjf  最短作业优先(shortest job first)
    pcb* SRTF(int now_time);   // srtf  最短剩余时间优先，从就绪队列取最佳到运行队列


    /*
    * 调用以下函数
    */
    string destory_Pcb(pcb*& from, pcb*& finish, int now_time); //进程结束，加入完成队列，the：运行完成进程；from：运行队列；now_time：当前时间
    string initValues(int total, int io); //创建主存，total：内存空间，io：打印机数量
    string createPcb(int id, string name, int arrive_time, int need_time, int size, int machine); //创建进程，id：进程id；name：进程名；arrive_time：到达时间；need_time：服务时间；size：申请内存大小；machine：申请打印机数量
    string createPcb_new(int id, string name, int arrive_time, int need_time, int size, int machine); //创建进程，内存或打印机不足就不创建
    string wait_Pcb(pcb*& p); //进程阻塞，p：需要被阻塞进程
    string wakeup_Pcb(string check_Name); //唤醒阻塞进程，check_Name：被唤醒进程名
    string deletePcb(pcb*& from, string target);    //删除进程，from：删除进程所在队列；target：删除进程名

    void run_SJF(int& now_time); //以为短进程优先运行，now_time：当前时间
    void run_SRTF(int& now_time); //以最短剩余时间优先运行，now_time：当前时间

    float avg_turn_time(); //平均周转时间
    float avg_pow_turn_time(); //加权平均周转时间
};

#endif
