#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
struct pagetable
{
    int frame;
    int last_time;
    bool valid;
};
bool ispagepresent(struct pagetable pt[], int page)
{
    return pt[page].valid;
}
void print(int frame[],int nof)
{
    for(int i=0;i<nof;i++)
    {
        printf("%d ",frame[i]);
    }
    printf("\n");
}
void update(struct pagetable pt[], int page , int status,int frame,int time)
{
    pt[page].valid=status;
    if(status==1)
    {
        pt[page].frame=frame;
        pt[page].last_time=time;
    }
}
int findlru(struct pagetable pt[],int frame[],int nof)
{
    int mn=INT_MAX;
    int index=0;
   for(int i=0;i<nof;i++)
   {
       int page=frame[i];
      
       if(pt[page].last_time<mn)
       {
        mn=pt[page].last_time;
        index=i;
       }
   }
   return index;
}
int main()
{
    int n;
    printf("the number of pages :");
    scanf("%d",&n);
    int nof;
    int ref[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&ref[i]);
    }
    printf("the no of frame:");
    scanf("%d",&nof);
    int frame[nof];
    memset(frame,-1,nof*sizeof(int));
    struct pagetable pt[50];
    for(int i=0;i<50;i++) pt[i].valid=0;
    int filled=0;
    for(int time=0;time<n;time++)
    {
        int page=ref[time];
        if(!ispagepresent(pt,page))
        {
           if(filled<nof)
           {
              frame[filled]=page;
              update(pt,page,1,filled,time);
              filled++;
           }
           else{
              int lru=findlru(pt,frame,nof);
             int old_page=frame[lru];
             update(pt,old_page,0,-1,time);
             frame[lru]=page;
             update(pt,page,1,lru,time);

           }
        }
        else{
          pt[page].last_time=time;
        }
        print(frame,nof);
    }
}