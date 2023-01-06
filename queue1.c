#include<stdio.h>

#define SIZE 5

void enQueue(int);
void deQueue();
void display();

int items[SIZE],front = -1 , rear = -1;    

void enQueue(int value) {
  if (rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (front == -1)
      front = 0;
    rear++;
    items[rear] = value;
    printf("\nInserted -> %d", value);
  }
}
void deQueue() {
    if(rear == -1)
       printf("nQueue is empty");
    else{
       int i ;
       printf("\n Deleted : %d ,items[front]");
       front++ ;
       if (front > rear)
          front = rear = -1 ;
    }
}
void  display () {
    if(rear == -1)
       printf("\nQuery is empty");
    else{
        int i;
        printf("\nNoueue elements are: \n");
        for (i = front; i <=rear ; i++)
           printf("%d",items[i]);
    }              

printf("\n");
       }


int main(){
    deQueue();

    enQueue(1);
    enQueue(2);
    enQueue(3);
    enQueue(4);
    enQueue(5);

    display();
    deQueue();
    
    return 0 ;
}
