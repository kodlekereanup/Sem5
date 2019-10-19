#include <iostream>
#include <vector>
#include <queue>
#include <conio.h>
#include <cmath>

enum status { NOT_ARRIVED, IN_QUEUE, EXECUTING, SUSPENDED, SCHEDULED };

struct Process {

	int id;
	float arrivalTime;
	float burstTime;
	float finishTime;
	float turnAroundTime;
	float waitingTime;
	status state;

	float scheduleProcess(std::vector<int>&, std::vector<float>&, int, int, int);

};

float Process :: scheduleProcess(std::vector<int>& orderOfExec, std::vector<float>& intermediateFinishTime, int prevFinishTime, int tempBT, int i) {
	state = EXECUTING;
	finishTime = tempBT + prevFinishTime;
	intermediateFinishTime.push_back(finishTime);
	burstTime -= tempBT;
	turnAroundTime = finishTime - arrivalTime;

	orderOfExec.push_back(i);

	if (burstTime == 0) state = SCHEDULED;
	else state = IN_QUEUE;

	return finishTime;
}

void arrivedProccesses(std::vector<Process>& P, std::queue<int>& scheduleQueue, int currentTime) {
	bool flag = false; int i = 0;
	for (i = 0; i < P.size(); i++) {
		flag = false;
		if (P.at(i).arrivalTime <= currentTime && P.at(i).state == NOT_ARRIVED) {
			flag = true;
			P.at(i).state = IN_QUEUE;
			scheduleQueue.push(i);
		}
	}
}

void displayTable(const std::vector<Process>& P) {
	std::cout << "\n\nPID" << "\tAT" << "\tBT" << "\tFT" << "\tTAT" << "\tWT\n\n";
	for (int i = 0; i < P.size(); i++) {
		std::cout << P.at(i).id << "\t" << P.at(i).arrivalTime << "\t" << P.at(i).burstTime
			<< "\t" << P.at(i).finishTime << "\t" << P.at(i).turnAroundTime << "\t" << P.at(i).waitingTime << "\n";
	}
	std::cout << "\n\n";
}

void displayGanttChart(const std::vector<Process>& proc, const std::vector<int>& orderOfExec,
	const std::vector<float>& intermediateFinishTime) {

	std::cout << " ";
	for (int i = 0; i < intermediateFinishTime.size(); i++) {
		for (int j = 0; j < intermediateFinishTime.at(i); j++) std::cout << "--";
		std::cout << " ";
	}
	std::cout << "\n|";

	for (int i = 0; i < orderOfExec.size(); i++) {
		for (int j = 0; j < intermediateFinishTime.at(i) / 2; j++) std::cout << " ";
		std::cout << "P" << orderOfExec.at(i);
		for (int j = 0; j < intermediateFinishTime.at(i) / 2; j++) std::cout << " ";
		std::cout << "|";
	}
	std::cout << "\n ";

	for (int i = 0; i < intermediateFinishTime.size(); i++) {
		for (int j = 0; j < intermediateFinishTime.at(i); j++) std::cout << "--";
		std::cout << " ";
	}
	std::cout << "\n";

	std::cout << "0";
	for (int i = 0; i < intermediateFinishTime.size(); i++) {
		for (int j = 0; j < intermediateFinishTime.at(i); j++) std::cout << " ";
		if (intermediateFinishTime.at(i) > 9) std::cout << "\b";
		std::cout << intermediateFinishTime.at(i);
	}
	std::cout << "\n\n";
}

void displayStats(const std::vector<Process>& proc) {
	float tsum = 0, wsum = 0;
	for (int i = 0; i < proc.size(); i++) {
		tsum += proc.at(i).turnAroundTime;
		wsum += proc.at(i).waitingTime;
	}

	std::cout << "\n Average Turn Around Time: " << tsum / proc.size() << "ms";
	std::cout << "\n Average Waiting Time:     " << wsum / proc.size() << "ms";
	std::cout << "\n";
}

bool complete(const std::vector<Process>& proc) {
	bool check = true;
	for (int i = 0; i < proc.size(); i++) if (proc.at(i).state != SCHEDULED) { check = false; break; }	
	return check;
}

int main() {

	int n, id, s, currentTime;
	float at, bt, ft, wt, tt, prevFinishTime, timeQuantum;
	bool flag = false;

	std::cout << "\n Enter the number of processes:";
	std::cin >> n;

	std::vector<Process> process(n);
	std::queue<int> scheduleQueue;
	std::vector<int> orderOfExec;
	std::vector<float> intermediateFinishTime;

	for (int i = 0; i < n; i++) {
		std::cout << "\n Enter Process ID:";
		std::cin >> id;
		process.at(i).id = id;
		process.at(i).state = NOT_ARRIVED;

		std::cout << "\n Enter Process Arrival Time:";
		std::cin >> at;
		process.at(i).arrivalTime = at;

		std::cout << "\n Enter Process Burst Time:";
		std::cin >> bt;
		process.at(i).burstTime = bt;
	}

	std::cout << "\n Enter the Time Quantum: ";
	std::cin >> timeQuantum;

	std::vector<Process> copy = process;
		
	currentTime = 0, prevFinishTime = 0;
	while (!complete(process)) {

		arrivedProccesses(process, scheduleQueue, currentTime);

		if (flag) scheduleQueue.push(s);

		if (process.at(scheduleQueue.front()).burstTime < timeQuantum)
			prevFinishTime = process.at(scheduleQueue.front()).scheduleProcess(orderOfExec, intermediateFinishTime,
				prevFinishTime, process.at(scheduleQueue.front()).burstTime, process.at(scheduleQueue.front()).id);
		else prevFinishTime = process.at(scheduleQueue.front()).scheduleProcess(orderOfExec, intermediateFinishTime,
			prevFinishTime, timeQuantum, process.at(scheduleQueue.front()).id);

		if (process.at(scheduleQueue.front()).burstTime != 0) {
			flag = true;
			s = scheduleQueue.front();
			scheduleQueue.pop();
		} else {
			flag = false;
			scheduleQueue.pop();
		}
		currentTime = prevFinishTime;

	}

	for (int i = 0; i < process.size(); i++) {
		copy.at(i).finishTime = process.at(i).finishTime;
		copy.at(i).turnAroundTime = process.at(i).turnAroundTime;
		copy.at(i).waitingTime = copy.at(i).turnAroundTime - copy.at(i).burstTime;
	}

	process = copy;
	displayTable(process);
	displayGanttChart(process, orderOfExec, intermediateFinishTime);
	displayStats(process);

	return 0;
}

// TODO:
// Draw Gantt chart 
/*
Round Robin Algorithm:

1. Find the process that arrives first
2. If it's burst time is less than the time quantum, schedule using
it's burst time. Else use time quantum.
3. If scheduled using quantum, update process bursttime = bursttime - timequantum
NOTE: Make sure it doesn't go negative
4. Check for the processes that have arrived (FCFS)
5. Schedule the next one in the same way
6. Stop when all process burst times = 0


*/