#include<bits/stdc++.h>
using namespace std;
void scan(vector<int>vec,int head,int dir)
{
    vector<int>sequence;
    vector<int>left,right;
    int total=0;
    for(int i=0;i<vec.size();i++)
{
    if(vec[i]<head)left.push_back(vec[i]);
    else right.push_back(vec[i]);

}
   if(dir==1)
   {
    right.push_back(199);
    sort(right.begin(),right.end());
    int curr;
    for(int i=0;i<right.size();i++)
    {
        curr=right[i];
        total+=abs(head-curr);
        sequence.push_back(right[i]);
        head=curr;
    }
    sort(left.begin(),left.end(),greater<int>());
    head=199;
    for(int i=0;i<left.size();i++)
    {
        curr=left[i];
        total+=abs(curr-head);
        sequence.push_back(left[i]);
        head=curr;
    }
    cout<<"the total seek movement :"<<total<<endl;
    for(int i:sequence)cout<<i<<" ";
   }
   else {
    left.push_back(0);
     sort(left.begin(),left.end(),greater<int>());
    int curr;
    for(int i=0;i<left.size();i++)
    {
        curr=left[i];
        total+=abs(head-curr);
        sequence.push_back(left[i]);
        head=curr;
    }
    sort(right.begin(),right.end());
    head=0;
    for(int i=0;i<right.size();i++)
    {
        curr=right[i];
        total+=abs(curr-head);
        sequence.push_back(right[i]);
        head=curr;
    }
    cout<<"the total seek movement :"<<total<<endl;
    for(int i:sequence)cout<<i<<" ";
   }
}
int main()
{
    int n;
    cout<<"the total requests:"<<endl;
    cin>>n;
    vector<int>vec(n);
    cout<<"give request sequence :"<<endl;
    for(int i=0;i<n;i++)cin>>vec[i];
    int direction;
    cout<<"1 for right , 0 for left"<<endl;
    cin>>direction;
    int head;
    cout<<"the start"<<endl;
    cin>>head;
    scan(vec,head,direction);
}