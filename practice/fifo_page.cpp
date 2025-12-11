#include<stdio.h>
#include<string.h>
struct pagetable
{
    int frame;
    bool valid;
};
bool ispresent(struct pagetable pt[],int page) {return pt[page].valid;}
void update(struct pagetable pt[],int page,int status ,int frame3)
{
    pt[page].frame=frame3;
    pt[page].valid=status;
}
void printd(struct pagetable pt[],int frame[],int nof)
{
   for(int i=0;i<nof;i++)
   {
    printf("%d ",frame[i]);
   }
   printf("\n");
}
int main()
{
   int n;
   printf("the total pages : ");
   scanf("%d",&n);
   int ref[n];
   printf("give the reference string :");
   for(int i=0;i<n;i++)
   {
    scanf("%d",&ref[i]);
   }
   struct pagetable pt[50];
   for(int i=0;i<50;i++)pt[i].valid=0;
   int nof;
   printf("number of frame : ");
   scanf("%d",&nof);
   int frame[nof];
   memset(frame,-1,nof*sizeof(int));
   int curr=0,filled=0,flag=0;
   for(int time=0;time<n;time++)
   {
    int page=ref[time];
    if(!ispresent(pt,page))
    {
        if(!flag & filled<nof)
        {
            update(pt,page,1,filled);
            frame[filled]=page;
            filled++;
            if(filled==nof)
            {
                flag=1;
                curr=0;
            }
        }
        else{
            update(pt,frame[curr],0,-1);
            update(pt,page,1,curr);
            frame[curr]=page;
            curr=(curr+1)%nof;

        }
    }
    printd(pt,frame,nof);
   }
}