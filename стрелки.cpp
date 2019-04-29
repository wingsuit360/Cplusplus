#include <iostream>
#include <thread>
#include <condition_variable>
#include <ctime>
#include <chrono>

using namespace std;

class duel {
public:
    mutex Mutex;
    condition_variable v;
    int wait_time;
    time_t pli_time;
    bool pli;
    duel(int w) : wait_time(w), pli(false) {}
    void cornerman();
    void shooter(time_t * t, int shooter_id);
};

void duel::cornerman() {
    this_thread::sleep_for(chrono::seconds(wait_time));
    pli = true;
    pli_time = time(0);
    v.notify_all();
}

void duel::shooter(time_t * t, int shooter_id) {
    unique_lock<mutex> lock(Mutex);
    v.wait(lock, [this] {return this->pli;});
    *t = time(0);
    cout << "Shooter " << shooter_id << " Pif-paf" << endl;
}

void cornerman_pack(duel * d) {d->cornerman();}
void shooter_pack(duel * d, time_t * t, int shooter_id) {d->shooter(t, shooter_id);}

int main()
{
    int wt;
    cout << "Enter waiting time: ";
    cin >> wt;
    time_t sh1, sh2;
    duel d(wt);
    thread co_th(cornerman_pack, &d);
    thread sh_th1(shooter_pack, &d, &sh1, 1);
    thread sh_th2(shooter_pack, &d, &sh2, 2);
    cout << "Duel began!" << endl;
    co_th.join();
    sh_th1.join();
    sh_th2.join();
    cout << "First shooter delay: " << sh1-d.pli_time << endl;
    cout << "Second shooter delay: " << sh1-d.pli_time << endl;
    if (sh1 < sh2) cout << "Second shooter is dead" << endl;
    else cout << "First shooter is dead" << endl;
}
