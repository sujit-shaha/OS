#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> a(1000);
    vector<int> b(1000);
    int n, f;
    int z,j,h,temp,pf;

    cout << "Enter the number of pages: ";
    cin>>  n;
    cout << "Enter the number of frames: ";
    cin>> f;
    cout << "Enter the pages: ";
    for(int i = 0; i < n; i++)
    {
        cin>>a[i];
    }

    for(int i = 0;i<f;i++)
    {
        b[i] = -1;
    }
    int i =0;
    pf=0;
    j=0;
    h=0;
    z=0;
    while(i<n){
        if(b[i] == -1 && i < f)
        {
            b[i] = a[i];
            pf++;
        }
        else{
            z=0;
            for(j=0 ;j < f;j++)
            {
                if(b[j] == a[i])
                {
                    h++;
                }
                else{
                    z++;
                }
            }
        }

        if(z == f)
        {
            for(int j=0;j<f-1;j++)
            {
                temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
            b[f-1] = a[i];
            pf++;
        }
        i++;
    }

    cout << "Page Faults: " << pf << endl;
    cout<< "Page Hits: " << n - pf << endl;
    cout << "Pages in memory: ";
    for(int i = 0; i < f; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl;
}