// Assignment No 3(Coverage)

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define v 1 /* verbose flag, output if 1, no output if 0 */
#define tag 100 /* tag for sending a number */
int main ( int argc, char *argv[] )
{
int p,myid,i,f,*x;
double start, end;
MPI_Status status;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&p);
MPI_Comm_rank(MPI_COMM_WORLD,&myid);
if(myid == 0) /* the manager allocates and initializes x */
{
x = (int*)calloc(p,sizeof(int));
x[0] = 50;
for (i=1; i<p; i++) x[i] = 2*x[i-1];
if(v>0)
{
printf("The data to square : ");
for (i=0; i<p; i++)
 printf(" %d",x[i]);
 printf("\n");
}
}
if(myid == 0) /* the manager copies x[0] to f */
{             /* and sends the i-th element to the i-th processor */
f = x[0];
for(i=1; i<p; i++) 
MPI_Send(&x[i],1,MPI_INT,i,tag,MPI_COMM_WORLD);
}
else /* every worker receives its f from root */
{
MPI_Recv(&f,1,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
if(v>0) 
printf("Node %d will square %d\n",myid,f);
}
start = MPI_Wtime();
f *= f;       /* every node does the squaring */
if(myid == 0) /* the manager receives f in x[i] from processor i */
for(i=1; i<p; i++)
MPI_Recv(&x[i],1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
else     /* every worker sends f to the manager */
MPI_Send(&f,1,MPI_INT,0,tag,MPI_COMM_WORLD);
if(myid == 0) /* the manager prints results */
{
x[0] = f;
printf("The squared numbers : ");
for(i=0; i<p; i++) 
printf(" %d",x[i]);
 printf("\n");
end = MPI_Wtime();
printf("Runtime = %f\n", end-start);
}

MPI_Finalize();
return 0;
}


