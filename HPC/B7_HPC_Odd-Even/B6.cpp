#include<iostream>
#include<omp.h>

using namespace std;

//function for swap
void swap(int *a,int* b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

//print array
void printArr(int *arr,int size,int val)
{
	cout<<"\n after iteration "<<val<<" \n";
	for(int i=0;i<size;i++)
	cout<<arr[i]<<"\t";
	cout<<endl;
}


//odd_even sort function
void odd_even(int * arr,int size)
{
	int tid;
	int k=0;

	omp_set_num_threads(size/2);
	while(k<size)
	{
		if(k%2 == 0)
		{	
			#pragma omp parallel for	
			//for even iteration
			for(int i=0;i<size;i+=2)
			{
			   tid = omp_get_thread_num();
			  cout <<"\ncurrent thread no :"<<tid;
			  if(i!=size-1)
			  if(arr[i] > arr[i+1])	
			  swap( (arr+i), (arr+i+1));
			}
		}
		else
		{
			#pragma omp parallel for
			//for odd iteration
			for(int j=1;j<size;j+=2)
			{
			 	 tid = omp_get_thread_num();
				 cout <<"\ncurrent thread no :"<<tid;
				//skip for last iteration
			 	if(j!=size-1)
				 if(arr[j] > arr[j+1])
				
				 swap((arr+j),(arr+j+1));
			}
		}
		//print array
		printArr(arr,size,k);
		k++;
	}
}

int main()
{
	int size=0;
	cout<<"enter the array size";
	cin>>size;
	
	int *arr = new int[size];
	
	cout<<"\nenter array elements";
	for(int i=0;i<size;i++)
	cin>>arr[i];
 	
	odd_even(arr,size);
	
return 0;
}
