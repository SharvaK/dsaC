#include<stdio.h>

#define MAX 10

void addfront(int *,int,int *,int *);
void addrear(int *, int,int *, int *);
int delfront(int *,int *, int *);
int delrear(int *,int *,int *);
void display(int *);
int count(int *);

void addfront(int *arr,int item,int *pfront,int *prear){
    int i,k,c;

    if(*pfront == 0 && *prear == MAX -1){
        printf("\n deque is full \n");
        return;     
    }
    if(*pfront == -1){
        *pfront = *prear = 0;
        arr[*pfront] = item;
        return;
    }
    if(*prear != MAX - 1){
        c = count(arr);
        k = *prear + 1;
        for(i = 1;i <= c ;i++){
            arr[k] = arr[k-1];
            k--;
        }
       arr[k] = item;
       *pfront = k;
       (*prear)++ ; 
    } else{
        (*pfront)--;
        arr[*pfront] = item;
    } 
}

void addrear(int *arr,int item , int *pfront, int *prear){
    int i,k;

    if(*pfront == 0 && *prear == MAX - 1){
        printf("\nIs full\n");
    }
     if(*pfront == -1){
        *pfront = *prear = 0;
        arr[*prear] = item;
        return;
    }
    if(*prear != MAX - 1){
        k = *pfront - 1;
        for(i = *pfront -1 ; i < *prear ;i++){
            k= i;
            if(k == MAX -1){
               arr[k] = 0;
            }else
               arr[k] = arr[i+1]; 
        }
        (*prear)--;
        (*pfront)--;
    }
       (*prear)++;
       arr[*prear] = item ;
}

int delfront(int *arr, int *pfront,int *prear){
    int item;
    
    if(*pfront == -1){
        printf("\n Deque is empty \n");
        return 0;
    }
    item = arr[*pfront];
    arr[*pfront] = 0;

    if(*pfront == *prear)
        *pfront = *prear = -1;
    else 
       (*pfront)++;

    return item;   
}

int delrear(int *arr,int *pfront,int *prear){
    int item;

    if(*pfront == -1){
        printf("\nDeque is empty\n");
        return 0;
    }

    item = arr[*prear];
    arr[*prear] = 0;
    (*prear)--;
    if (*prear == -1)
        *pfront = -1;
    return item;     
}

void display(int *arr){
    int i;

    printf("\n Front: ");
    for(i =0; i<MAX ;i++)
       printf("%d",arr[i]);
    printf(" : Rear");   
}

int count(int *arr){
    int c=0 ,i;

    for(i =0;i<MAX;i++){
       if(arr[i] != 0)
          c++;
    }
    return c;     
}

int main(){
    int arr[MAX];
    int front,rear,i,n;

    front =  rear = -1;
    for(i=0 ; i<MAX ; i++)
       arr[i] = 0;

    addrear(arr,5,&front,&rear);   
    addfront(arr,12,&front,&rear);
    addrear(arr,11,&front,&rear);
    addfront(arr,5,&front,&rear);
    addrear(arr,6,&front,&rear);
    addfront(arr,8,&front,&rear);
    
    printf("\nelements in deque");
    display(arr);

    i = delfront(arr,&front, &rear);
    printf("\nremoved item: %d",i);

    printf("\nelements in deque after deletion");
    display(arr);

    addrear(arr,16,&front,&rear);
    addrear(arr,7,&front,&rear);

    printf("\ndeque after adding elements");
    display(arr);

    n = count(arr);
    printf("\ntotal elements %d",n);

}

