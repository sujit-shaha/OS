#include <bits/stdc++.h>

using namespace std;
int lastindex=0;

void nextfit(int block[],int process[],int m,int n,int allocation[])
{
    for(int i = 0;i<n;i++)
    {
        bool allocated = false;
        for(int j =lastindex;j<n;j++)
        {
            if(block[i] >= process[j])
            {
                allocation[i]=j;
                block[i] -=process[j];
                lastindex = (j+1)%m;
                allocated = true;
                break;
            }
        }

        if(!allocated)
        {
            for(int j = 0 ; j < lastindex;j++)
            {
                if(block[i] >= process[j])
                {
                    allocation[i]=j;
                    block[j] -= process[i];
                    lastindex = (j+1)%m;
                    allocated = true;
                    break;
                }
            }
        }

    }
    for(int i = 0; i < n; i++)
    {
        if(allocation[i] != -1)
            cout << "Process " << i << " is allocated to block " << allocation[i] << endl;
        else
            cout << "Process " << i << " could not be allocated" << endl;
    }
}

int main()
{
    int m , n;

    cout<<"Enter the number of blocks: ";
    cin>>m;
    cout<<"Enter the number of processes: ";
    cin>>n;

    int block[m],process[n],allocation[n];
    cout<<"Enter the size of block";
    for(int i =  0 ;i < m;i++)
    {
        cin>>block[i];
    }

    for(int i = 0;i<n;i++)
    {
        cin>>process[i];
    }

    for(int i = 0;i<n;i++)
    {
        allocation[i]= -1;
    }

    nextfit(block,process,m,n,allocation);
}