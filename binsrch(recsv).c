#include<stdio.h>

// create function
int binary_search(int array[],int x, int low, int high){
    if(high >= low){
        int mid = low + (high-low) /2 ;

        // if found at middle
        if (array[mid] == x)
           return mid ;

        // search left half
        if(array[mid] > x)
           return(binary_search(array,x,low,mid-1));

        //right half
        if(array[mid] < x)
           return(binary_search(array,x,mid +1 ,high));             
    }
    return -1;    
}

// main method
int main(void){
    int array[] = {3,4,5,6,7,8,9};
    int n = sizeof(array) / sizeof(array[0]);
    int x = 7;
    int result = binary_search(array,x,0,n-1);
    if (result == -1)
       printf("not found");
    else
       printf("Element found at index %d",result);
}