// C++ implementation of Best-Fit algorithm
#include <iostream>
#include <vector>
using namespace std;

// Function to allocate memory to blocks as per Best-Fit algorithm
void bestFit(vector<int>& blockSize, int m, vector<int>& processSize, int n)
{
    vector<int> allocation(n, -1); 

    for(int i = 0 ;i < n;i++)
    {
        int bestindex = -1;
        for(int j = 0 ;j <m;j++)
        {
            if(blockSize[j]>=processSize[i])
            {
                if(bestindex == -1)
                {
                    bestindex = j;
                
                }
                else if(blockSize[j] < blockSize[bestindex])
                {
                    bestindex = j;
                }
            }
        }

        if(bestindex != -1)
        {
            allocation[i] = bestindex;
            blockSize[bestindex] -= processSize[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// Driver code
int main()
{
    int m; // number of blocks in the memory
    int n; // number of processes in the input queue

    cout << "Enter the number of blocks: ";
    cin >> m;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> blockSize(m);
    vector<int> processSize(n);
    
    cout << "Enter the size of each block: ";
    for (int i = 0; i < m; i++)
    {
        cin >> blockSize[i];
    }

    cout << "Enter the size of each process: ";
    for (int i = 0; i < n; i++)
    {
        cin >> processSize[i];
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}