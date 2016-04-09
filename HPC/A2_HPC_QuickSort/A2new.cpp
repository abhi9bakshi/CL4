#include <iostream>
#include<stdlib.h>
//#include <process>

using namespace std;

class SortList
{
private :
int *list;
int size;
public :
SortList(int size)
{
list=new int[size];
this->size=size;
}
void Swap(int i,int j)
{
int tmp;
tmp=list[i];
list[i]=list[j];
list[j]=tmp;
}
void QuickSort(int,int);
void StoreNum(int);
void Display();
};

void SortList::StoreNum(int x)
{
static int i=0;
*(list+i)=x;
i++;
}


void SortList::Display()
{
int i=0;
for(;i<size;i++)
cout<<*(list+i)<<" ";
}
void SortList::QuickSort(int X,int I)
{
int L,R,V;
if (I>X)
{
V=list[I];
L=X-1;
R=I;
for(;;)
{
while(list[++L]>V);
while(list[--R]<V);
if (L==R) break;
Swap(L,R);
}
Swap(L,I);
QuickSort(X,L-1);
QuickSort(L+1,I);
}
}

int main()
{
int i,x,n;
SortList *S;
cout<<endl<<"\t"<<"Program for Quick Sort"<<endl;
cout<<endl<<"How many numbers to be sorted : ";
cin>>n;
S=new SortList(n);
for(i=0;i<n;i++)
{
cout<<endl<<"Enter number : ";
cin>>x;
S->StoreNum(x);
}
cout<<endl<<"Numbers entered are "<<endl;
S->Display();
S->QuickSort(1,n-1);
cout<<endl<<"Numbers After QuickSort are "<<endl;
S->Display();

return 0;
}