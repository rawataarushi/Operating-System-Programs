#include <bits/stdc++.h>
using namespace std;

int size = 8;
int disk_size = 200;

void CSCAN(int arr[], int head)
{
    int seek_count=0;
    vector<int>left,right;
    vector<int>seek_sequence;
    left.push_back(0);
    right.push_back(199);
    for(int i=0;i<size;i++)
    {
        if(arr[i]<head) left.push_back(arr[i]);
        if(arr[i]>head) right.push_back(arr[i]);
    }
    sort(left.begin(),left.end());
    sort(right.begin(),right.end());
    int curr;
    for(int i=0;i<right.size();i++)
    {
        curr=right[i];
        seek_sequence.push_back(curr);
        seek_count+=(curr-head);
        head=curr;
    }
    head=0;

    seek_count+=(disk_size-1);
     for(int i=0;i<left.size();i++)
    {
        curr=left[i];
        seek_sequence.push_back(curr);
        seek_count+=(curr-head);
        head=curr;
    }
    cout<<"the total distance is"<<seek_count<<endl;
    cout<<"the seek sequence is :"<<endl;
    for(int i : seek_sequence)cout<<i<<" ";
}

int main()
{
    int arr[size] = { 176, 79, 34, 60, 92, 11, 41, 114 };
    int head = 50;

    cout << "Initial position of head: " << head << endl;
    CSCAN(arr, head);

    return 0;
}
