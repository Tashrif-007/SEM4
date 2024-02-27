#include<bits/stdc++.h>
using namespace std;

struct process {
    int burst_time;
    int priority;
    int arrival;
    int start;
    int end;
};

int main() {
    int num;
    cout << "Enter number of processes\n";
    cin >> num;
    process processes[num];

    cout << "Enter burst time and priority for each process\n";
    for(auto &x : processes) {
        cin >> x.burst_time >> x.priority;
        x.arrival = 0;
        x.start = 0;
        x.end = x.burst_time;
    }
    
    for(int i = 1; i < num; i++) {
        processes[i].start = processes[i - 1].burst_time + processes[i - 1].start;
        processes[i].end = processes[i].start + processes[i].burst_time;
    }

    cout<<"Gantt Chart\n";

    for(int i = 0; i < num; i++) {
        for(int j = processes[i].start; j < processes[i].end; j++) {
            if(j == processes[i].start)
                cout << "| ";
            else if(j == (processes[i].end - processes[i].start) / 2 + processes[i].start)
                cout << "P" << i + 1;
            else
                cout << "-";
        }
        if(processes[i].end - processes[i].start <= 1)
            cout << "P" << i + 1;
    }

    cout << "|";
    cout << endl;

    return 0;
}
