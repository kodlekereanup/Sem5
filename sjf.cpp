#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>

enum status { NOT_ARRIVED, IN_QUEUE, EXECUTING, SUSPENDED, SCHEDULED };

struct Process {

	int id;
	float arrivalTime;
	float burstTime;
	float finishTime;
	float turnAroundTime;
	float waitingTime;
	status stat;
	bool estat = false;

	float scheduleProcess(int);

};

void sort(std::vector<Process>& proc) {
	int n = proc.size();
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (proc[j].finishTime > proc[j + 1].finishTime)
				std::swap(proc[j], proc[j + 1]);

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
std::vector<int> arrivedProccesses(int t, std::vector<Process>& P) {
	bool flag = false; int i = 0;   std::vector<int> queue;
	for (i = 0; i < P.size(); i++) {
		flag = false;
		if (P[i].arrivalTime <= t && (P[i].stat == NOT_ARRIVED || P[i].stat == IN_QUEUE)) {
			flag = true;
			P[i].stat = IN_QUEUE;
			queue.push_back(i);
		}
	}

	return queue;
}

int maxArrivalTime(const std::vector<Process>& P) {
	int max = P[0].arrivalTime;
	for (int i = 0; i < P.size(); i++) if (P[i].arrivalTime > max) max = P[i].arrivalTime;
	return max;
}

int findInProcess(const std::vector<Process>& proc, int k){  
   for (int i = 0; i < proc.size(); i++){  
      if (proc[i].burstTime == k)
         return i;
   }
   return -1;
}

// find the occurrences of all shortestburtesttime 
std::vector<int> findNextShortest(const std::vector<Process>& proc, std::vector<int> arrivedProc) {
	std::vector<int> temp, temp2;	
	float btShort = proc[arrivedProc.at(0)].burstTime;
	
    for(int i = 0; i < arrivedProc.size(); i++) {
        temp.push_back(proc[arrivedProc.at(i)].burstTime);
    }

    // find the shortest value in temp and return its index  
    int min = temp.at(0); int index = 0;
    for(int i = 0; i < temp.size(); i++) {
        if(temp[i] < min) min = temp.at(i);         
    }
    
    index = findInProcess(proc, min);    
    temp2.push_back(index);

	return temp2;
}

void displayTable(const std::vector<Process>& P) {
	std::cout << "\n\nPID" << "\tAT" << "\tBT" << "\tFT" << "\tTAT" << "\tWT\n\n";
	for (int i = 0; i < P.size(); i++) {
		std::cout << P[i].id << "\t" << P[i].arrivalTime << "\t" << P[i].burstTime
			<< "\t" << P[i].finishTime << "\t" << P[i].turnAroundTime << "\t" << P[i].waitingTime << "\n";
	}
	std::cout << "\n\n";
}

void displayGanttChart(const std::vector<Process>& proc) {

	// print top bar
	std::cout << " ";
	for (int i = 0; i < proc.size(); i++) {
		for (int j = 0; j < proc[i].burstTime; j++) std::cout << "--";
		std::cout << " ";
	}
	std::cout << "\n|";

	//print process
	for (int i = 0; i < proc.size(); i++) {
		for (int j = 0; j < proc[i].burstTime - 1; j++) std::cout << " ";
		std::cout << "P" << proc[i].id;
		for (int j = 0; j < proc[i].burstTime - 1; j++) std::cout << " ";
		std::cout << "|";
	}

	std::cout << "\n ";

	// printing bottom bar
	for (int i = 0; i < proc.size(); i++) {
		for (int j = 0; j < proc[i].burstTime; j++) std::cout << "--";
		std::cout << " ";
	}
	std::cout << "\n";

	// printing the finish time
	std::cout << "0";
	for (int i = 0; i < proc.size(); i++) {
		for (int j = 0; j < proc[i].burstTime; j++) std::cout << "  ";
		if (proc[i].finishTime > 9) std::cout << "\b";
		std::cout << proc[i].finishTime;

	}
	std::cout << "\n\n";

}

void displayStats(const std::vector<Process>& proc) {

	float tsum = 0, wsum = 0;

	for (int i = 0; i < proc.size(); i++) {
		tsum += proc[i].turnAroundTime;
		wsum += proc[i].waitingTime;
	}

	std::cout << "\n Average Turn Around Time: " << tsum / proc.size() << "ms";
	std::cout << "\n Average Waiting Time:     " << wsum / proc.size() << "ms";

}

bool complete(const std::vector<Process>& proc) {
    bool check = true;

    for(int i = 0; i < proc.size(); i++) {
        if(proc[i].stat != SCHEDULED) {
            check = false;
            break;
        }
    }

    return check;
}

int main() {

    bool completed = true;
	int n, id, currentTime = 0;
	float at, bt, ft, wt, tt, prevFinishTime;

	std::cout << "\n Enter the number of processes:";
	std::cin >> n;

	std::vector<Process> process(n);
	
	for (int i = 0; i < n; i++) {
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
	
    currentTime = 0;
    while(!complete(process)) {
        std::vector<int> pid = arrivedProccesses(currentTime, process);
        std::vector<int> schedulable = findNextShortest(process, pid);

        for(int i = 0; i < schedulable.size(); i++) {            
            if(i == 0 && currentTime == 0) {               
                prevFinishTime = process[schedulable.at(i)].scheduleProcess(0);
                currentTime = prevFinishTime;
            } else {               
                prevFinishTime = process[schedulable.at(i)].scheduleProcess(prevFinishTime);               
                currentTime = prevFinishTime;
            }
        }
    }
	
	displayTable(process);
	sort(process);
	displayGanttChart(process);
	displayStats(process);

	return 0;
}
