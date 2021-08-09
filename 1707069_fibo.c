#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int array[500],upper;

void *runner(void *param);

int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,argv[1]);
    pthread_join(tid,NULL);

    for(int i=0;i<upper;i++) printf("%d ",array[i]);printf("\n");
}

void *runner(void *param)
{
    int i ; upper = atoi(param);
    array[0] = 0 ; array[1] = 1;
    
       for(int i=1;i<=upper-2;i++)
       {
          array[i+1] = array[i] + array[i-1];
       }
    pthread_exit(0);
       
}
