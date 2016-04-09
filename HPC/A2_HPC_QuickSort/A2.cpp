#include<iostream>
#include<omp.h>
using namespace std;

void quicksort(int [], int, int);
int createPartition(int [], int, int);

int main() {
    int n;
	pthread_t thread;
    cout<<"Enter the size of the array = ";
    cin>>n;
    int elements[n];
    cout<<"Enter the elements in the array = "<<endl;
    for(int i = 1 ; i <= n ; i++) {
        cin>>elements[i];
    }
    int begin = 1, end = n;

    quicksort(elements, begin, end); 

	string delimator = ", ";

    cout<<"Quick Sort:"<<endl;
	cout<<"[";
	for(int i = 1 ; i <= n ; i++) {
		if (i == n)
			delimator = "";
		cout<<elements[i]<<delimator;
	}
	cout<<"]"<<endl;
    return 0;
}

void quicksort(int elements[], int begin, int end) {
	int middle;
    if(begin < end) {
		middle = createPartition(elements, begin, end);
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			quicksort(elements, begin, middle - 1);
			#pragma omp section
			quicksort(elements, middle + 1, end);
    	}
	}
}

int createPartition(int elements[], int begin, int end) {
        int temp, temp1;
        int x = elements[end];
        int i = begin - 1;
        for(int j = begin; j<= end - 1; j++) {
            if(elements[j] <= x) {
                i = i+1;
                temp = elements[i];
                elements[i] = elements[j];
                elements[j] = temp;
            }
        }
        temp1 = elements[i + 1];
        elements[i + 1] = elements[end];
        elements[end] = temp1;
        return i + 1;
    }
    
/** OUTPUT

student@CC:~/Downloads$ make Quick
g++     Quick.cpp   -o Quick
student@CC:~/Downloads$ ./Quick
Enter the size of the array = 4
Enter the elements in the array = 
4
3
2
1
Quick Sort:
[1, 2, 3, 4]
student@CC:~/Downloads$ 

**/    
