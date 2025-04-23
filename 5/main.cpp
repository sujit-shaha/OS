#include<iostream>
using namespace std;

int main()
{
    cout<< "Enter the number of processes and resources: ";
    int n,m;
    cin>>n>>m;

    int alloc[n][m],max[n][m],avail[m],need[n][m],safeSeq[n],work[m],finish[n]={0};

    cout<< "Enter allocation matrix: ";
    for(int i = 0 ;i < n;i++)
    {
        for(int j = 0 ;j < m;j++)
        {
            cin>>alloc[i][j];
        }
    }

    cout<<"Enter maximum need matrix: ";
    for(int i = 0 ;i < n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            cin>>max[i][j];
        }
    }

    cout<<"Enter available resources";
    for(int i = 0;i<m;i++)
    {
        cin>>avail[i];
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }


    for(int i = 0 ;i < m;i++)
    {
        work[i] = avail[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for(int i = 0;i<n;i++)
        {
            if(!finish[i])
            {
                int j;
                for(j = 0;j<m;j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == m){
                    for(int k = 0 ; k < m;k++)
                    {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }

        if(!found)
        {
            cout<< "System is in unsafe state";
            return 0;
        }
        cout<< "Safe sequence: ";
        for(int i = 0;i<n;i++)
        {
            cout<< safeSeq[i]<< " ";
        }
        cout<<endl;
    }
    return 0;
}