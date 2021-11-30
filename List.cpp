#include <iostream>
#include<string>
#include "List.h"
using namespace std;

handle::handle() {
    num = 0;
    reserve_num = 0;    //预备队列进程数量
    run = NULL;
    ready = NULL;
    finish = NULL;
    wait = NULL;//阻塞队列
    reserve = NULL;//预备队列
    io = 0;//当前打印机数量
    block = 0;//必然阻塞的进程数目（申请打印机>总量）
    note_io = 0;//打印机绝对数量
    note_me = 0;

}
void pcb::insert_To(pcb*& target, string targetName) {
    pcb* p = target;
    pcb* t = NULL;   //用于target链表的添加

   //将进程添加到target队列
    if (target == NULL)
    {
        target = this;    //target指向完成链表的表头
        this->next = NULL;
    }
    else {
        t = target;
        while (t->next != NULL){
            t = t->next;
        }
        t->next = this;
        this->next = NULL;
    }

    cout << "\n将进程 " << this->name << " 置于" << targetName << "队列中!" << endl;
}

void pcb::copy_Pcb(pcb*& object) {
    pcb* p = object;

    id = p->id;
    name = p->name;
    arrive_time = p->arrive_time;
    need_time = p->need_time;
    size = p->size;
    machine = p->machine;

    wait_time = p->wait_time;    //等待时间 
    more_time = p->more_time;    //剩余执行的时间
    start_time = p->start_time;   //进程开始时间 
    finish_time = p->finish_time;  //结束时间
    state = p->state;

    more_time = p->more_time;  //剩余服务时间=服务时间
    next = NULL;
}

void pcb::put_To(pcb*& from, pcb*& target, string targetName) {

    if (targetName == "运行") this->state = 0;
    else if (targetName == "就绪") this->state = 1;
    else if (targetName == "阻塞") this->state = 2;
    else if (targetName == "完成")this->state = 3;
    else if (targetName == "预备") this->state = 4;

    if (this->name == from->name) {  //若在原链表头
        from = from->next;
    }
    
    else {                           //若原链表中间或最后
        pcb* q = from;
        while (q->next->name != this->name && q->next != NULL)
        {
            q = q->next;
        }
        q->next = this->next;
    }

    if (target == NULL) {
        target = this;    //target指向目标链表的表头
        this->next = NULL;
    }
    else
    {
        pcb* t = target;
        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = this;
        this->next = NULL;
    }
}

void pcb::init_Pcb(int id, string name, int arrive_time, int need_time, int size, int machine) {
    this->id = id;
    this->name = name;
    this->arrive_time = arrive_time;
    this->need_time = need_time;
    this->size = size;
    this->machine = machine;
    //this->state = 1;   //状态1：就绪
    //this->status = 1;  //未分配状态
    this->more_time = this->need_time;  //剩余服务时间=服务时间
    this->next = NULL;
    this->machine_state = 0;//未占有打印机
}
memory::memory(int size) {
    this->pcbName = "";
    this->start = 0;
    this->size = size;
    this->status = 1;         //1. 空闲
    this->next = NULL;

}


void memory::print_Memory() {
    cout << "\t内存状态\n";
    cout << "*************************************************************************\n";
    cout << "|Start_Add\tEnd_Add\t\tSize\t\tStatus\t\tJob_id  |\n";
    memory* out = NULL;
    out = this;
    while (out != NULL) {
        if (out->status == 1) {
            cout << "|" << out->start << "\t\t" << out->start + out->size - 1 << "\t\t" << out->size << "\t\tFree_Memory\t\tNone\t|" << endl;
        }
        else {
            cout << "|" << out->start << "\t\t" << out->start + out->size - 1 << "\t\t" << out->size << "\t\tBusy\t\t" << out->pcbName << "\t|" << endl;
        }
        out = out->next;
    }
    delete(out);
    cout << "*************************************************************************\n" << endl;
}

string handle::wait_Pcb(pcb*& target) {
    pcb* t = target;

    if (t->state == 2) {
        cout << "进程已被阻塞！" << endl;
        return "错误：进程已被阻塞！";
    }
    else {
        cout << "wait pcb!\n";
        t->state = 2;
        //io += t->machine;
        t->put_To(run, wait, "阻塞");
        return "进程 " + t->name + " 被阻塞！";
    }
}
string handle::wakeup_Pcb(string check_Name) {
    pcb* m = wait;
    int check = 0;
    //pcb* r = ready;
    while (m != NULL) {   //循环，若有进程在wait队列中，重新加入
        if (m->name == check_Name) {
            check = 1;
            m->state = 1;
            m->put_To(wait, ready, "就绪");
            cout << "重新唤醒进程 " << m->name << endl;
            return "重新唤醒进程 " + m->name;
            /*if (m->machine <= io) {
                m->state = 1;
                m->put_To(wait, ready, "就绪");
                cout << "重新唤醒进程 " << m->name << endl;
                return "重新唤醒进程 " + m->name;
            }
            else {
                cout << "打印机数量不足，无法唤醒！" << endl;
                return "打印机数量不足，无法唤醒！";
            }
            break;*/
        }
        m = m->next;
    }
    if (check == 0) cout << "阻塞队列中没有该进程！" << endl;
}

// 最佳适应算法
int handle::Alloc_Memory(string name, int size, memory* p)
{
    memory* q = NULL;

    // 找到空闲模块
    while (p != NULL)
    {
        if (p->status == 1 && p->size >= size)
        {
            q = p;
            break;
        }
        if (p->next == NULL)
        {
            cout << "无足够空间，分配失败！" << endl;
            return 0;
            //break;
        }
        else p = p->next;
    }

    // 最佳空闲模块
    while (p != NULL)
    {
        if (p->status == 1 && p->size >= size && p->size < q->size) {
            q = p;
        }
        p = p->next;
    }
    if (q->size > size) {
        memory* t = new memory(0);
        t->start = q->start + size;
        t->size = q->size - size;
        t->status = 1;
        t->pcbName = "";
        // 分配空间
        q->pcbName = name;
        q->size = size;
        q->status = 0;
        // 
        t->next = q->next;
        q->next = t;
        //delete t;
    }
    else if (q->size == size) {
        q->pcbName = name;
        q->size = size;
        q->status = 0;
    }
    return 1;
}

// 释放内存
void handle::Free_Memory(string name, memory* target) {
    memory* p = target;
    if (p->next == NULL && p->pcbName == "") {
        cout << "还未分配任务！" << endl;
    }
    while (p != NULL) {
        if (p->status == 1 && p->next->status == 0 && p->next->pcbName == name) {
            p->size = p->size + p->next->size;
            memory* q = p->next;
            p->next = p->next->next;
            delete(q);
            if (p->next->status == 1) {
                p->size = p->size + p->next->size;
                memory* q = p->next;
                p->next = p->next->next;
                delete(q);
            }
            break;
        }
        else if (p->status == 0 && p->pcbName == name) {
            p->status = 1;
            p->pcbName = "";
            if (p->next != NULL && p->next->status == 1) {
                p->size 
                    = p->size + p->next->size;
                memory* q = p->next;
                p->next = p->next->next;
                delete(q);
            }
            break;
        }
        else if (p->next == NULL) {
            cout << "没有此任务！" << endl;
            break;
        }
        p = p->next;
    }
}

void memory::destory_Memory()
{
    memory* p = this;
    memory* q = p;
    while (p != NULL) {
        p = p->next;
        delete(q);
        q = p;
    }
}

string handle::destory_Pcb(pcb*& from, pcb*& finish, int now_time) {
    cout << "destory pcb!\n";
    pcb* p = from;
    pcb* f = NULL;   //用于finish链表的添加

    p->finish_time = now_time;    //结束时间
    p->start_time = now_time - p->need_time;  //开始时间
    p->turn_time = p->finish_time - p->arrive_time;//周转时间
    p->pow_turn_time = p->turn_time / p->need_time;//加权周转时间
    p->state = 3;   //状态3：完成

    Free_Memory(p->name, Memory);
    p->put_To(from, finish, "完成");
    num--;   //进程数减一
    io += p->machine;//归还打印机
    cout << "\ndestory success!" << endl;
    return "进程结束，移入完成队列！";
}

void handle::print_Pcb(pcb* target, string name) {
    //int i;
    pcb* p = target;
    if (p == NULL) {
        cout << "\n------------------------------" << name << "队列------------------------------- \n";
        cout << "当前暂无" << name << "进程！" << endl;
    }
    else {
        cout << "\n------------------------------" << name << "队列------------------------------- \n";
        cout << "进程号\t进程名\t进程到达时间\t\t进程服务时间\t\t申请内存大小\t\t申请打印机大小" << endl;
        while (p != NULL) {
            cout << p->id << "\t" << p->name << "\t" << p->arrive_time << "\t\t" << p->need_time << "\t\t" << p->size << "\t\t" << p->machine << endl;
            p = p->next;
        }
    }

}

string handle::initValues(int total, int theio) {
    memory* m = NULL;//内存指针
    Memory = new memory(total);
    m = Memory;
    io = theio;
    note_me = total;
    note_io = theio;
    return "内存、打印机创建";
}

string handle::createPcb_new(int id, string name, int arrive_time, int need_time, int size, int machine) {

    if (machine > io) { //申请打印机数大于当前打印机数量
        cout << "打印机不足，创建失败！";
        return "打印机不足，创建失败！";
    }
    else {
        memory* m = Memory;
        if (Alloc_Memory(name, size, m)) {
            pcb* p = new pcb;
            num++;
            p->init_Pcb(id, name, arrive_time, need_time, size, machine);
            p->state = 1;
            io -= p->machine;
            p->insert_To(ready, "就绪");
            cout << "creat success" << endl;
            return"进程创建成功，加入就绪队列";
        }
        else {
            cout << "当前内存不足，创建失败！" << endl;
            return "当前内存不足，创建失败！";
        }
    }
}

string handle::createPcb(int id, string name, int arrive_time, int need_time, int size, int machine) { 
    if (machine > note_io || size > note_me) {  //申请打印机数量大于系统打印机总量||申请内存大小大于系统内存
        return "创建失败";
    }

    pcb* p = new pcb;
    num++;
    p->init_Pcb(id, name, arrive_time, need_time, size, machine);
    
    if (p->machine > io) { //申请打印机数大于当前打印机数量
        p->insert_To(reserve, "预备");
        return "打印机不足，加入预备队列！";
        //p->insert_To(wait, "阻塞");
        //block++;
    }
    else {
        memory* m = Memory;
        if (Alloc_Memory(p->name, p->size, m)) {
            p->state = 1;
            io -= p->machine;
            //p->put_To(reserve, ready, "就绪");
            p->insert_To(ready, "就绪");
            cout << "creat success" << endl;
            return"进程创建成功，加入就绪队列";
        }
        else {
            p->state = 4;   //状态4：预备
            cout << "当前内存不足！加入预备队列" << endl;
            p->insert_To(reserve, "预备");
            reserve_num++;
            return "当前内存不足！加入预备队列";
        }
    }
}

string handle::deletePcb(pcb*& from, string target) {
    pcb* p = from, * q = from;
    if (from ==NULL) {
        cout << "空" << endl;
        return "空，没法删";
    }
    if (from->name == target) {
        p = from;
        from = from->next;
        delete p;
        cout << target << "删除成功" << endl;
        //print_Pcb(from, "预备");
        return "删除成功";
    }
    while (p->name != target && p->next != NULL) {
        q = p;
        p = p->next;
    }
    if (p->name == target) {
        q->next = p->next;
        delete p;//删除节点
        cout << target << "删除成功" << endl;
        //print_Pcb(from, "预备");
        return "删除成功";
    }
    else {
        cout << "没有指定的节点";
        return "没有指定的节点";
    }

}
pcb* handle::toReady(int now_time) {
    pcb* p = reserve;
    memory* m = Memory;
    if (reserve != NULL) {
        while (p != NULL) {
            if (now_time >= p->arrive_time) {   //若进程已经到达，进入就绪队列
                if (Alloc_Memory(p->name, p->size, m)) {
                    p->state = 1;
                    p->put_To(reserve, ready, "就绪");

                }
                else {
                    p->state = 4;   //状态4：预备
                    //p->insert_To(reserve, "预备");
                    reserve_num++;
                }
            }
            p = p->next;
        }
    }
    return ready;
}

//sjf  最短作业优先(shortest job first)
pcb* handle::SJF(int now_time) {
    int min_time = 0;   //最短时间，即优先运行的进程的时间
    if (run != NULL && run->more_time > 0) return run;
    pcb* r = NULL;  //遍历链表，查找出运行时间最短的进程
    pcb* p = ready;
    //pcb* p = toReady(now_time);
    if (ready != NULL) {
        while (p != NULL) {
            if (now_time >= p->arrive_time && p->state != 2) {   //若进程已经到达，注意：时间单位为1 && p->machine <= io
                if (min_time == 0) {  //给最短时间赋初值
                    r = p;
                    min_time = p->need_time;
                    //io -= p->machine;
                }
                else {
                    if (p->need_time < min_time) {
                        r = p;
                        min_time = p->need_time;
                        //io -= p->machine;
                    }
                }
            }
            /*else if (now_time >= p->arrive_time && p->state != 2 && p->machine > io) {
                wait_Pcb(p);
            }*/
            p = p->next;
        }
    }
    //cout << "\nSJF:a shortest progress pning!\n";
    if (ready != NULL) {
        r->put_To(ready, run, "运行");
        return run;   //返回指向正在运行进程的指针

    }
    else return NULL;
    
}

//srtf  最短剩余时间优先，从就绪队列取最佳到运行队列
pcb* handle::SRTF(int now_time) {

    int min_time = 0;   //最短时间，即优先运行的进程的时间
    pcb* r = NULL;  //遍历链表，查找出运行时间最短的进程

    pcb* p = ready;
    //pcb* p = toReady(now_time);
    if (run != NULL) {
        r = run;
        r->put_To(run, ready, "运行");
    }

    if (ready != NULL) {
        while (p != NULL) {
            if (now_time >= p->arrive_time && p->state != 2 && p->more_time > 0) {   //若进程已经到达，注意：时间单位为1 && p->machine <= io
                if (min_time == 0) {  //给最短时间赋初值
                    //p->state = 0;  //状态0：执行
                    r = p;
                    min_time = p->more_time;
                    if (p->machine_state == 0) {
                        //io -= p->machine;
                        //p->machine_state = 1;
                    }

                }
                else {
                    if (p->more_time < min_time) {
                        //p->state = 0;  //状态0：执行
                        r = p;
                        min_time = p->more_time;
                        if (p->machine_state == 0) {
                            //io -= p->machine;
                            //p->machine_state = 1;
                        }
                    }
                }
            }
            /*else if (now_time >= p->arrive_time && p->state != 2 && p->more_time > 0 && p->machine > io) {
                wait_Pcb(p);
            }*/
            p = p->next;
        }
    }
    if (r != NULL) r->state = 0;
    cout << "\nSRTF:a shortest more_time progress pning!\n";

    if (ready != NULL) {
        r->put_To(ready, run, "运行");
        return run;   //返回指向正在运行进程的指针

    }
    else return NULL;
    //return r;   //返回指向正在运行进程的指针
}

float handle::avg_turn_time() {
    pcb* p = finish;
    if (finish != NULL) {
        int ave_turtime = 0,sum = 0;
        while (p != NULL) {
            sum++;
            ave_turtime += p->turn_time;
            p = p->next;
        }
        cout << "平均周转时间\t" << ave_turtime / sum << endl;
        return (float)ave_turtime / (float)sum;
    }
    else {
        cout << "平均周转时间\t" << 0 << endl;
        return 0;
    }
}
float handle::avg_pow_turn_time() {
    pcb* p = finish;
    if (finish != NULL) {
        int pow_ave_turtime = 0, sum = 0;
        while (p != NULL) {
            sum++;
            pow_ave_turtime += p->pow_turn_time;
            p = p->next;
        }
        cout << "平均带权周转时间\t" << (float)pow_ave_turtime / (float)sum << endl;
        return (float)pow_ave_turtime / (float)sum;
    }
    else {
        cout << "平均带权周转时间\t" << 0 << endl;
        return 0;
    }
}
void handle::output_result()
{
    pcb* p = finish;
    if (finish != NULL) {
        int ave_turtime = 0, pow_ave_turtime = 0, sum = 0;
        cout << "\n---------------统计结果----------------\n";
        cout << "进程\t" << "到达时间\t" << "服务时间\t" << "开始时间\t" << "结束时间\t" << "周转时间\t" << "带权周转时间" << endl;
        while (p != NULL) {
            sum++;
            cout << p->name << "\t" << p->arrive_time << "\t\t" << p->need_time << "\t\t" << p->start_time << "\t\t" << p->finish_time << "\t\t"
                << p->turn_time << "\t\t" << p->pow_turn_time << endl;
            ave_turtime += p->turn_time;
            pow_ave_turtime += p->pow_turn_time;
            p = p->next;
        }
        cout << "平均周转时间\t" << ave_turtime / sum << endl
            << "平均带权周转时间\t" << pow_ave_turtime / sum << endl;
    }
    else {
        cout << "\n---------------统计结果----------------\n";
        cout << "当前暂无进程运行完成！" << endl;
    }
}

void handle::output_run(pcb* p, int now_time) {
    if (NULL == p) {
        cout << "当前时刻: " << now_time << "， 暂无进程运行!\n";
    }
    else {
        cout << "进程 " << p->name << "\t到达时间: " << p->arrive_time << "\t运行需要时间: " << p->need_time << "\t剩余运行时间：" << p->more_time << endl;
    }
}


void handle::run_SJF(int& now_time) {
    pcb* re = reserve;
    while (re != NULL) {
        if (re->machine <= io && Alloc_Memory(re->name, re->size, Memory)) {
            re->put_To(reserve, ready, "就绪");
        }
        re = re->next;
    }

    run = SJF(now_time);  //调用SJF函数，遍历链表

    if (run != NULL)
    {
        /*进程执行，每循环一次，当前时间加一同时要判断当前时间是否有进程刚好到达正在在等待 */
        run->more_time--;
        now_time++;

        //output_ready(run, now_time);
        /*pcb* rr = toReady(now_time);*/
            
    }
    else {   //没有进程在运行
        now_time++;
    }
    if (run != NULL && run->more_time == 0) {
        destory_Pcb(run, finish, now_time);
    }
}
void handle::run_SRTF(int &now_time) {
    pcb* re = reserve;
    while (re != NULL) {
        if (re->machine <= io && Alloc_Memory(re->name, re->size, Memory)) {
            re->put_To(reserve, ready, "就绪");
        }
        re = re->next;
    }

    run = SRTF(now_time);  //调用SRTF函数，遍历链表

    if (run != NULL) {
        //剩余时间为0，调用destory函数
        
        run->more_time--;
        now_time++;
    }
    else {   //没有进程在运行
        now_time++;
    }
    if (run != NULL && run->more_time == 0) {
        destory_Pcb(run, finish, now_time);
    }
}
