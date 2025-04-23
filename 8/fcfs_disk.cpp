#include <bits/stdc++.h>
using namespace std;

void fcfs_disk(int arr[],int n,int head)
{
    int seek_time = 0;
    int distance ,crrent_track;

    for(int i = 0;i<n;i++)
    {
        crrent_track = arr[i];
        distance = abs(crrent_track - head);
        seek_time += distance;
        head = crrent_track;
        cout << "Seeked to track: " << crrent_track << " | Total seek time: " << seek_time << endl;
    }
    cout << "Total seek time: " << seek_time << endl;
}

int main()
{
    int n;
    cout<<"Enter number for array size:"<<endl;
    cin>>n;
    int head;
    int arr[n];
    cout<<"Enter the head:"<<endl;
    cin>>head;

    cout<<"Enter the elements of the array:"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    fcfs_disk(arr,n,head);
    return 0;
}