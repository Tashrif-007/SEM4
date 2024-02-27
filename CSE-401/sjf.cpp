#include<bits/stdc++.h>
using namespace std;

struct process {
    int burst_time;
    int priority;
    int arrival;
    int start;
    int end;
    int index;
};

bool compare(process p1, process p2)
{
    return p1.burst_time<p2.burst_time;
}

int main() {
    int num;
    cout << "Enter number of processes\n";
    cin >> num;
    process processes[num];

    cout << "Enter burst time and priority for each process\n";
    for(int i=0; i<num; i++) {
        cin >> processes[i].burst_time >> processes[i].priority;
        processes[i].arrival = 0;
        processes[i].start = 0;
        processes[i].end = processes[i].burst_time;
        processes[i].index = i+1;
    }
    
    sort(processes, processes+num, compare);

    
    for(int i = 1; i < num; i++) {
        processes[i].start = processes[i - 1].burst_time + processes[i - 1].start;
        processes[i].end = processes[i].start + processes[i].burst_time;
        cout<<processes[i].start<<" "<<processes[i].end<<endl;
    }

    cout<<"Gantt Chart\n";

    for(int i = 0; i < num; i++) {
        for(int j = processes[i].start; j < processes[i].end; j++) {
            if(j == processes[i].start)
                cout << "| ";
            else if(j == (processes[i].end - processes[i].start) / 2 + processes[i].start)
                cout << "P" << processes[i].index;
            else
                cout << "-";
        }
        if(processes[i].end - processes[i].start <= 1)
            cout << "P" << processes[i].index;
    }

    cout << "|";
    cout << endl;

    return 0;
}
