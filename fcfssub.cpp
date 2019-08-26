#include <iostream>
#include <vector>
#include <utility>

enum status { NOT_ARRIVED, IN_QUEUE, EXECUTING, SUSPENDED, SCHEDULED };

struct Process {

    int id;    
    float arrivalTime;
    float burstTime;
    float finishTime;
    float turnAroundTime;
    float waitingTime;
    status stat;

    float scheduleProcess(int);

};

void sort(std::vector<Process>& proc) {
    int n = proc.size() ;
    for(int i = 0; i < n - 1 ; i++) 
        for(int j = 0; j < n - i - 1; j++) 
            if(proc[j].arrivalTime > proc[j+1].arrivalTime) 
                std::swap(proc[j], proc[j+1]);           
    
}

float Process :: scheduleProcess(int prevFinishTime) {
    stat = EXECUTING;
    finishTime = burstTime + prevFinishTime;
    turnAroundTime = finishTime - arrivalTime;
    waitingTime = turnAroundTime - burstTime;
    stat = SCHEDULED;
    return finishTime;
}

// check if time occurs in p vector and return pid //
std::vector<int> arrivalTimeOf(int t, std::vector<Process>& P) {
    bool flag = false; int i = 0;   std::vector<int> temp; 
    for(i = 0; i < P.size(); i++) {        
        flag = false;
        if(P[i].arrivalTime == t && P[i].stat == NOT_ARRIVED) {            
            flag = true;            
            P[i].stat = IN_QUEUE;
            temp.push_back(i);
        }
    }    
   
    return temp;
}

int maxArrivalTime(const std::vector<Process>& P) {
    int max = P[0].arrivalTime;
    for(int i = 0; i < P.size(); i++) if(P[i].arrivalTime > max) max = P[i].arrivalTime;    
    return max;
}

void displayTable(const std::vector<Process>& P) {
    std::cout << "\n\nPID" << "\tAT" << "\tBT" << "\tFT" << "\tTAT" << "\tWT\n\n";
    for(int i = 0; i < P.size(); i++) {      
        std::cout << P[i].id << "\t" << P[i].arrivalTime << "\t" << P[i].burstTime 
        << "\t" << P[i].finishTime << "\t" << P[i].turnAroundTime << "\t" << P[i].waitingTime << "\n";
    }
    std::cout << "\n\n";
}

void displayGanttChart(const std::vector<Process>& proc) {

    // print top bar
    std::cout << " ";
    for(int i = 0; i < proc.size(); i++) {
        for(int j = 0; j < proc[i].burstTime; j++) std::cout << "--";
        std::cout << " ";
    }
    std::cout << "\n|";

    //print process
    for(int i = 0; i < proc.size(); i++) {
        for(int j = 0; j < proc[i].burstTime - 1; j++) std::cout << " ";
        std::cout << "P" << proc[i].id;
        for(int j = 0; j < proc[i].burstTime - 1; j++) std::cout << " ";
        std::cout << "|";
    }

    std::cout << "\n ";

    // printing bottom bar
    for(int i = 0; i < proc.size(); i++) {
        for(int j = 0; j < proc[i].burstTime; j++) std::cout << "--";
        std::cout << " ";
    }
    std::cout << "\n";

    // printing the finish time
    std::cout << "0";
    for(int i = 0; i < proc.size(); i++) {
        for(int j = 0; j < proc[i].burstTime; j++) std::cout << "  ";
        if(proc[i].finishTime > 9) std::cout << "\b"; 
        std::cout << proc[i].finishTime;

    }
    std::cout << "\n";

}

void displayStats(const std::vector<Process>& proc) {

    float tsum = 0, wsum = 0;

    for(int i = 0; i < proc.size(); i++) {
        tsum += proc[i].turnAroundTime;
        wsum += proc[i].waitingTime;
    }

    std::cout << "\n Average Turn Around Time: "     << tsum / proc.size() << "ms";
    std::cout << "\n Average Waiting Time:     "     << wsum / proc.size() << "ms";

}

int main() {

    int n, id;
    float at, bt, ft, wt, tt, prevFinishTime;
    
    std::cout << "\n Enter the number of processes:";
    std::cin >> n;

    std::vector<Process> process(n);
    
    for(int i = 0; i < n; i++) {
        std::cout << "\n Enter Process ID:";
        std::cin >> id;
        process[i].id = id;
        process[i].stat = NOT_ARRIVED;

        std::cout << "\n Enter Process Arrival Time:";
        std::cin >> at;
        process[i].arrivalTime = at;
        
        std::cout << "\n Enter Process Burst Time:";
        std::cin >> bt;
        process[i].burstTime = bt;
    }
        
    for(int clockTime = 0; clockTime <= maxArrivalTime(process); clockTime++) {
        // If clockTime occurs in arrivalTime, return pid of that process        
        std::vector<int> pid = arrivalTimeOf(clockTime, process);        
        for(int i = 0; i < pid.size(); i++) {  
            if(i == 0 && clockTime == 0) prevFinishTime = process[pid.at(i)].scheduleProcess(0);                        
            else prevFinishTime = process[pid.at(i)].scheduleProcess(prevFinishTime);            
        }     
    }

    displayTable(process);
    sort(process);    
    displayGanttChart(process);
    displayStats(process);    

    return 0;
}
