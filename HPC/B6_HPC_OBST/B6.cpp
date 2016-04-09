//Assignment No. 10(OBST)


#include <iostream>
#define num 20
#include <omp.h>
#include <stdlib.h>
using namespace std;

typedef struct obst
{
	int key;
	obst *left,*right;
}obst;

int weight[num][num];
int cost[num][num];
int R[num][num];
int p[num];
int q[num];
int No_of_keys;
int keys[num];
obst *ROOT;
void Display();
void compute()
{
	int x,min;
	int i,j,k,h,m;

#pragma omp for
	for(i = 0; i <= No_of_keys; i++)
	{
		weight[i][i] = q[i];
		for(j = i + 1; j <= No_of_keys; j++)
			weight[i][j] = weight[i][j-1] + p[j] + q[j];
	}

#pragma omp for
	for(i = 0; i <= No_of_keys; i++)
		cost[i][i] = weight[i][i];
#pragma omp for
	for(i = 0; i <= No_of_keys - 1; i++)
	{
		j = i + 1;
		cost[i][j] = cost[i][i] + cost[j][j] + weight[i][j];
		R[i][j] = j;
	}
#pragma omp for
	for(h = 2; h <= No_of_keys; h++)
		for(i = 0; i <= No_of_keys - h; i++)
		{
			j = i + h;
			m = R[i][j-1];
			min = cost[i][m-1] + cost[m][j];
			for(k = m+1; k <= R[i+1][j]; k++)
			{
				x = cost[i][k-1] + cost[k][j];
				if(x < min)
				{
					m = k;
					min = x;
				}
			}
			cost[i][j] = weight[i][j] + min;
			R[i][j] = m;
		}
	Display();
}
void Display()
{
	cout<<"The weight matrix "<<endl;
	for(int i=0;i<=No_of_keys;i++)
	{
		for(int j=i;j<=No_of_keys;j++)
			cout<<"\t"<<weight[i][j];
		cout<<endl;
	}
	cout<<"The cost matrix "<<endl;
	for(int i=0;i<=No_of_keys;i++)
	{
        for(int j=i;j<=No_of_keys;j++)
			cout<<"\t"<<cost[i][j];
		cout<<endl;
	}
	cout<<"The root matrix "<<endl;
	for(int i=0;i<=No_of_keys;i++)
	{
        for(int j=i;j<=No_of_keys;j++)
			cout<<"\t"<<R[i][j];
		cout<<endl;
	}
}

void DISPLAY(obst *ROOT)
{
	int i;
	if(ROOT != 0)
	{
        DISPLAY(ROOT->left);
        cout<<ROOT->key<<endl;
        DISPLAY(ROOT->right);
	}
}

obst *CONSTRUCT_OBST(int i, int j)
{
	obst *p;
	if(i == j)
		p = NULL;
	else
	{
		p = new obst;
		p->key = keys[R[i][j]];
		p->left = CONSTRUCT_OBST(i, R[i][j] - 1); //left subtree
		p->right = CONSTRUCT_OBST(R[i][j], j); //right subtree
	}
	return p;
}

void OPTIMAL_BINARY_SEARCH_TREE()
{
	float average_cost_per_weight;
	compute();
	cout<<"Cost[0] = "<<cost[0][No_of_keys]<<" Weight[0] = " <<weight[0][No_of_keys];
	average_cost_per_weight = cost[0][No_of_keys]/(float)weight[0][No_of_keys];
	cout<<"The cost per weight ratio is: "<< average_cost_per_weight;
	ROOT = CONSTRUCT_OBST(0, No_of_keys);
}

int main()
{
	int i, k;
	cout<<"Input number of keys: ";
	cin>>No_of_keys;
	for(i = 1; i <= No_of_keys; i++)
	{
		cout<<"key["<<i<<"] = ";
		cin>>keys[i];
		cout<<" frequency = ";
		cin>>p[i];
	}
	for(i = 0; i <= No_of_keys; i++)
	{
		cout<<"Q["<<i<<"] = ";
		cin>>q[i];
	}
	while(1)
	{
		cout<<"1.Construct tree\n2.Display tree\n3.Exit\n";
		cin>>k;
		switch(k)
		{
		case 1:
			OPTIMAL_BINARY_SEARCH_TREE();
			break;
		case 2:
			DISPLAY(ROOT);
			break;
		case 3:
			exit(0);
			break;
		}
	}
	system("PAUSE");
	return 0;
}


/*
///////////////////////////OUTPUT//////////////////////////
rahul@rahul-Inspiron-5521:~/Downloads$ g++ -fopenmp OBST.cpp
rahul@rahul-Inspiron-5521:~/Downloads$ ./a.out
Input number of keys: 6
key[1] = 3
 frequency = 10
key[2] = 7
 frequency = 3
key[3] = 10
 frequency = 9
key[4] = 15
 frequency = 2
key[5] = 20
 frequency = 0
key[6] = 25
 frequency = 10
Q[0] = 5
Q[1] = 6
Q[2] = 4
Q[3] = 4
Q[4] = 3
Q[5] = 8
Q[6] = 0
1.Construct tree
2.Display tree
3.Exit
1
The weight matrix 
	5	21	28	41	46	54	64
	6	13	26	31	39	49
	4	17	22	30	40
	4	9	17	27
	3	11	21
	8	18
	0
The cost matrix 
	5	32	56	98	118	151	188
	6	23	53	70	103	140
	4	25	42	75	108
	4	16	41	68
	3	22	43
	8	26
	0
The root matrix 
	0	1	1	2	3	3	3
	0	2	3	3	3	3
	0	3	3	3	4
	0	4	5	6
	0	5	6
	0	6
	0
Cost[0] = 188 Weight[0] = 64The cost per weight ratio is: 2.93751.Construct tree
2.Display tree
3.Exit
2
3
7
10
15
20
25
1.Construct tree
2.Display tree
3.Exit
3

///////////////////////////////////////////////////////////////////////////////////////////*/
