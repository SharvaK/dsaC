#include <stdio.h>
int size = 0;


void swap(int *a, int *b){
    int temp = *b;
    *b = *a;
    *a = temp ;
}

//function to heapify the tree

void heapify(int array[], int size , int i ){
    if (size == 1){
        printf("Single element in heap");
    }else{
        // find the largest among root, left and right
        int largest = i;
        int l  = 2*i + 1;
        int r = 2*i + 2;
        if(l < size && array[l] > array[largest])
            largest = l;
        if(r < size && array[r] > array[largest])
            largest = r;

     // swap and continue heapifying if root is not largest

        if(largest != i){
            swap(&array[i] , &array[largest]);
            heapify(array , size, largest);
        }       
    }
}

// function to insert element 

void insert(int array[],int newNum){
    if(size == 0){
        array[0] = newNum;
        size += 1;
    }else{
        array[size] = newNum;
        size += 1;
        for( int i = size/2 -1 ; i>=0 ; i--){
            heapify(array , size , i);
        }
    }
}


// function to delete an element from the tree 

void deleteRoot( int array[], int num){
    int i;
    for(i=0 ; i<size ; i++){
        if(num == array[i])
           break;
    }

    swap(&array[i] , &array[size-1]);
    size -= 1;
    for(int i = size/2 -1 ; i >= 0; i--){
        heapify(array , size ,i);
    }
}

    //Print the array
    void printArrray(int array[] , int size){
        for(int i=0 ; i < size; ++i ){
            printf("%d", array[i]);
        printf("\n");    
        }
    }


// Driver code

int main(){
    int array[10];

    insert(array,2);
    insert(array,3);
    insert(array,5);
    insert(array,7);
    insert(array,9);

    printf("Max-heap array: ");
    printArrray(array,size);

    deleteRoot(array,5);

    printf("After deleting an element: ");
    printArrray(array, size);
}