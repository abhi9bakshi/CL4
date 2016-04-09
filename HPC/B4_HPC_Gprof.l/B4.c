/*
Author: Aditya Kamble
Class : BE C 323
*/

//test_gprof.c
#include<stdio.h>


static void func2(void)
{
    printf("\n Inside func2 \n");
    int i = 0;

    for(;i<0xffffffaa;i++);
    return;
}

int main(void)
{
    printf("\n Inside main()\n");
    int i = 0;

    for(;i<0xffffff;i++);
    func2();

    return 0;
}
