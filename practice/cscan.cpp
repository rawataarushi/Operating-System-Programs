#include <bits/stdc++.h>
using namespace std;

int size = 6;
int disk_size = 200;

void CSCAN(int arr[], int head,int distance)
{
    int seek_count=0;
    vector<int>left,right;
    vector<int>sequence;
    left.push_back(0);
    right.push_back(199);
    for(int i=0;i<size;i++)
    {
        if(arr[i]<head)left.push_back(arr[i]);
        else right.push_back(arr[i]);
    }
    if(distance==1)
    {
        sort(left.begin(),left.end());
        sort(right.begin(),right.end());
        int curr;
        for(int i=0;i<right.size();i++)
        {
            curr=right[i];
            seek_count+=(curr-head);
            sequence.push_back(right[i]);
            head=curr;
        }
        head=0;
        seek_count+=199;
        for(int i=0;i<left.size();i++)
        {
            curr=left[i];
            seek_count+=(curr-head);
            sequence.push_back(left[i]);
            head=curr;
        }
        cout<<"total seek movement"<<seek_count<<endl;
        for(int i : sequence)cout<<i<<" ";
    }
    else{
        sort(left.begin(),left.end(),greater<int>());
        sort(right.begin(),right.end(),greater<int>());
        int curr;
        for(int i=0;i<left.size();i++)
        {
            curr=left[i];
            seek_count+=(head-curr);
            sequence.push_back(curr);
            head=curr;
        }
        head=199;
        seek_count+=(199);
        for(int i=0;i<right.size();i++)
        {
            curr=right[i];
            seek_count+=(head-curr);
            sequence.push_back(curr);
            head=curr;
        }
        cout<<"the total seek count"<<seek_count<<endl;
        for(int i:sequence)cout<<i<<" ";

    }
}

int main()
{
    int arr[size] = { 23,89,132,42,187,14 };
    int head = 100;

    cout << "Initial position of head: " << head << endl;
    int distance;
    cout<<"1 for right , 0 for left"<<endl;
    cin>>distance;
    CSCAN(arr, head,distance);

    return 0;
}
