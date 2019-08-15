#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

enum status { NOT_ARRIVED, ARRIVED, EXECUTING, FINISHED };

struct Process {

    int id;
    status stat;
    float arrivalTime;
    float burstTime;
    float finishTime;
    float turnAroundTime;
    float waitingTime;

    //void queueProcess();
    void scheduleProcess(int);

};

void Process :: scheduleProcess(int prevFinishTime) {
    
    finishTime = burstTime + prevFinishTime;
    turnAroundTime = finishTime - arrivalTime;
    waitingTime = turnAroundTime - burstTime;
}

// check if time occurs in p vector and return pid //
bool arrivalTimeOf(int t, std::vector<Process>& P) {
    bool flag = false; int i = 0;
    for(i = 0; i < P.size(); i++) {
        flag = false;
        if(P[i].arrivalTime == t and P[i].stat == NOT_ARRIVED) {
            flag = true;
            P[i].stat = ARRIVED;
            break;
        }
    }
    return (flag)? i : -1;
}

int maxArrivalTime(const std::vector<Process>& P) {

    int max = P[0].arrivalTime;
    for(int i = 0; i < P.size(); i++) {
        if(P[i].arrivalTime > max) max = P[i].arrivalTime;
    }
    return max;
}

void displayTable(const std::vector<Process> P) {
    for(int i = 0; i < P.size(); i++) {
        std::cout << "\n PID:" << P[i].id;
        std::cout << "\n AT :" << P[i].arrivalTime;
        std::cout << "\n BT :" << P[i].burstTime;
        std::cout << "\n FT :" << P[i].finishTime;
        std::cout << "\n TAT:" << P[i].turnAroundTime;
        std::cout << "\n WT :" << P[i].waitingTime;
        std::cout << "\n\n\n";
    }
}

int main() {

    int n, id;
    float at, bt, ft, wt, tt;
    
    std::cout << "\n Enter the number of processes:";
    std::cin >> n;

    std::vector<Process> process(n);
    
    for(int i = 0; i < n; i++) {
        std::cout << "\n Enter Process ID:";
        std::cin >> id;
        process[i].id = id;

        std::cout << "\n Enter Process Arrival Time:";
        std::cin >> at;
        process[i].arrivalTime = at;
        
        std::cout << "\n Enter Process Burst Time:";
        std::cin >> bt;
        process[i].burstTime = bt;
    }

    for(int clockTime = 0; clockTime <= maxArrivalTime(process); clockTime++) {
        // If clockTime occurs in arrivalTime, return pid of that process
        int pid = arrivalTimeOf(clockTime, process);
        if(pid >= 0) {     
            if(pid == 0) process[pid].scheduleProcess(0);
            else process[pid].scheduleProcess(process[pid-1].finishTime);            
        } else continue;
    }
    
    displayTable(process);


    return 0;
}

//TODO: Check if any process is executing before scheduling the next one
// check if any of the arrival time < current process arrival time status is not executing