#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void isSafe(vector<vector<int>>&maxx, vector<vector<int>>&allocation, vector<vector<int>>&need, vector<int>&available)
{
    int numProcess = maxx.size();
    int numResources = available.size();
    vector<bool>finish(numProcess, false);
    vector<int>work(numResources);
    work = available;
    vector<int>sequence;
    int count=0;
    while(count<numProcess)
    {
        bool found=false;
        for(int i=0; i<numProcess; i++)
        {
            if(!finish[i])
            {
                bool canAllocate=true;
                for(int j=0; j<numResources; j++)
                {
                    if(need[i][j]>work[j])
                    {
                        canAllocate=false;
                        break;
                    }
                }
                if(canAllocate)
                {
                    for(int j=0; j<numResources; j++)
                    {
                        work[j]+=allocation[i][j];
                    }
                    finish[i]=true;
                    sequence.push_back(i);
                    count++;
                    found=true;
                }
            }
        }
        if(!found)
        break;
    }

    for(int i=0; i<numProcess; i++)
    {
        if(!finish[i])
        {
            cout<<"Unsafe State"<<endl;
            return;
        }
    }
    cout<<"Safe State: "<<endl;
    for(auto x : sequence) cout<<"P"<<x<<" ";
    cout<<endl;
}
int main()
{
    freopen("bankers_input.txt", "r", stdin);
    int numProcess, numResources;
    cout<<"Enter the number of processes and resources: ";
    cin>>numProcess>>numResources;
    vector<vector<int>>maxx(numProcess, vector<int>(numResources)), allocation(numProcess, vector<int>(numResources)), need(numProcess, vector<int>(numResources));
    vector<int>available(numResources);
    cout<<"Enter maximum Needs: ";
    for(int i=0; i<numProcess; i++)
    {
        for(int j=0; j<numResources; j++)
        cin>>maxx[i][j];
    } 
    for(int i=0; i<numProcess; i++)
    {
        for(int j=0; j<numResources; j++)
        cin>>allocation[i][j];
    } 
    for(int i=0; i<numResources; i++)
    cin>>available[i];
    for(int i=0; i<numProcess; i++)
    {
        for(int j=0; j<numResources; j++)
        need[i][j] = maxx[i][j]-allocation[i][j];
    } 
    isSafe(maxx, allocation, need, available);
    return 0;
}
