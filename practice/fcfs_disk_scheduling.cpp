#include<bits/stdc++.h>
using namespace std;
void fcfs(vector<int>requests,int head)
{
    vector<int>sequence;
    int total=0;
    int curr;
    for(int i=0;i<requests.size();i++)
    {
       curr=requests[i];
       total+=abs(head-curr);
       sequence.push_back(requests[i]);
       head=curr;
    }
    cout<<"the total number of seek operations :"<<total<<endl;
    for(int i:sequence)cout<<i<<" ";
}
int main()
{
    int num;
    cout<<"the number of requests"<<endl;
    cin>>num;
    vector<int>requests(num);
    cout<<"input the requests:";
    for(int i=0;i<num;i++)cin>>requests[i];
    int head;
    cout<<"the initial position :"<<endl;
    cin>>head;
    fcfs(requests,head);
}