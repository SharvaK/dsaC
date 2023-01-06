#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct _NODE
{
    int key;
    int degree;
    struct _NODE *left_sibling;
    struct _NODE *right_sibling;
    struct _NODE *parent;
    struct _NODE *child;
    bool mark;
    bool visited;
    } NODE;

typedef struct fibonacciheap{
        int n;
        NODE *min;
        int phi;
        int degree;
    } FIB_HEAP;


FIB_HEAP *make_fib_heap();
void insertion(FIB_HEAP *H, NODE *new, int val);
NODE *extract_min(FIB_HEAP *H);
void consolidate(FIB_HEAP *H);
void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x);
NODE *find_min_node(FIB_HEAP *H);
void decrease_key(FIB_HEAP *H, NODE *mode, int key);
void cut(FIB_HEAP *H, NODE *node_to_decrease, NODE *parent_node);
void cascading_cut(FIB_HEAP *H, NODE *parent_node);
void Delete_node(FIB_HEAP *H, int dec_key);

FIB_HEAP *make_fib_heap(){
    FIB_HEAP *H;
    H = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
    H->n = 0;
    H->min = NULL;
    H->phi = 0;
    H->degree = 0;
    return H;
}

//Printing the heap
void print_heap(NODE *n){
    NODE *x;
    for(x = n;; x = x->right_sibling){
        if(x->child == NULL){
            printf("node with no child");
        }else{
            printf("node(%d) with child (%d)\n",x->key,x->child->key);
            print_heap(x->child);
        }
        if(x->right_sibling == n){
            break;
        }
    }
    }

    //Inserting nodes
    void insertion(FIB_HEAP *H, NODE *new,int val){
        new = (NODE *)malloc(sizeof(NODE));
        new->key = val;
        new ->degree = 0;
        new->mark = false;
        new->parent = NULL;
        new->child = NULL;
        new->visited = NULL;
        new->left_sibling = new;
        new->right_sibling = new;
        if(H->min == NULL){
            H->min = new;
        }else{
            H->min->left_sibling->right_sibling = new;
            new->right_sibling = H->min;
            new->left_sibling = H->min->left_sibling;
            H->min->left_sibling = new;
            if(new->key < H->min->key){
                H->min = new;
            }
        }
        (H->n)++;
    }

    //Find min node
    NODE *find_min_node(FIB_HEAP *H){
        if(H == NULL){
            printf("\n Fibonacci heap not yet created\n");
            return NULL;
        }else
           return H->min;
    }

    //Union opeartion
    FIB_HEAP *unionHeap(FIB_HEAP *H1, FIB_HEAP *H2){
        FIB_HEAP *Hnew;
        Hnew = make_fib_heap();
        Hnew->min = H1->min;

        NODE *temp1, *temp2;
        temp1 = Hnew->min->right_sibling;
        temp2 = Hnew->min->left_sibling;

        Hnew->min->right_sibling->left_sibling = H2->min->left_sibling;
        Hnew->min->right_sibling = H2->min;
        H2->min->left_sibling = Hnew->min;
        temp2 -> right_sibling = temp1;

        if((H1->min == NULL) || (H2->min != NULL && H2->min->key < H1->min->key))
           Hnew->min = H2->min;
        Hnew->n = H1->n + H2->n;
        return Hnew;   
    }

    //Calculate the degree
    int cal_degree(int n){
        int count = 0;
        while (n > 0){
            n = n/2;
            count++;
        }
        return count;
    }

    //consolidate function
    void consolidate(FIB_HEAP *H){
        int degree,i,d;
        degree = cal_degree(H->n);
        NODE *A[degree], *x, *y, *z;
        for(i = 0; i<= degree ; i++){
            A[i] = NULL;
        }
        x = H->min;
        do{
            d = x->degree;
            while(A[d] != NULL){
                y = A[d];
                if(x->key > y->key){
                    NODE *exchange_help;
                    exchange_help = x;
                    z = y;
                    y = exchange_help;
                }
                if(y == H->min)
                   H->min = x;
                fib_heap_link(H, y, x);
                if(y->right_sibling == x)
                   H->min = x;
                A[d] = NULL;
                d++;      
            }
            A[d] = x;
            x = x->right_sibling;
        }while(x != H->min);

        H->min = NULL;
        for(i = 0; i<degree; i++){
            if(A[i] != NULL){
                A[i]->left_sibling = A[i];
                A[i]->right_sibling = A[i];
                if(H->min == NULL){
                    H->min = A[i];
                }else{
                    H->min->left_sibling->right_sibling = A[i];
                    A[i]->right_sibling = H->min;
                    A[i]->left_sibling = H->min->left_sibling;
                    H->min->left_sibling = A[i];
                    if(A[i]->key < H->min->key){
                        H->min = A[i];
                    } 
                }
                if(H->min == NULL){
                    H->min = A[i];
                }else if(A[i]->key < H->min->key){
                    H->min = A[i];
                }
            }
        }
    }

    //Linking
    void fib_heap_link(FIB_HEAP *H, NODE *y, NODE *x){
        y->right_sibling->left_sibling = y->left_sibling;
        y->left_sibling->right_sibling = y->right_sibling;

        if(x->right_sibling == x)
           H->min = x;

        y->left_sibling = y;
        y->right_sibling = y;
        y->parent = x;

        if(x->child == NULL){
            x->child = y;
        }   
        y->right_sibling = x->child;
        y->left_sibling = x->child->left_sibling;
        x->child->left_sibling->right_sibling = y;
        x->child->left_sibling = y;
        if((y->key) < (x->child->key))
           x->child = y;

        (x->degree)++;   
    }

    //Extract min
    NODE *extract_min(FIB_HEAP *H){
        if(H->min == NULL)
          printf("\n The heap is empty");
        else{
            NODE *temp = H->min;
            NODE *pntr;
            pntr = temp;
            NODE *x = NULL;
            if(temp ->child != NULL){
                x = temp->child;
                do{
                    pntr = x->right_sibling;
                    (H->min->left_sibling)->right_sibling = x;
                    x->right_sibling = H->min;
                    x->left_sibling = H->min->left_sibling;
                    H->min->left_sibling = x;
                    if(x->key < H->min->key)
                       H->min = x;
                    x->parent = NULL;
                    x = pntr;   
                }while ((pntr != temp->child));            
            }
            (temp->left_sibling)->right_sibling = temp->right_sibling;
            (temp->right_sibling)->left_sibling = temp->left_sibling;
            H->min = temp->right_sibling;

            if(temp == temp->right_sibling && temp->child == NULL)
              H->min = NULL;
            else{
                H->min = temp->right_sibling;
                consolidate(H);
            }  
            H->n = H->n-1;
            return temp;
        }  
        return H->min;
    }

    void cut(FIB_HEAP *H,NODE *node_to_decrease,NODE *parent_node ){
        NODE *temp_parent_check;

        if(node_to_decrease == node_to_decrease->right_sibling)
           parent_node->child = NULL;

        node_to_decrease->left_sibling->right_sibling = node_to_decrease->right_sibling;
        node_to_decrease->right_sibling->left_sibling = node_to_decrease->left_sibling;
        if(node_to_decrease == parent_node->child)
           parent_node->child = node_to_decrease->right_sibling;
        (parent_node->degree)--;

        node_to_decrease->left_sibling = node_to_decrease;
        node_to_decrease->right_sibling = node_to_decrease;
        H->min->left_sibling->right_sibling = node_to_decrease;
        node_to_decrease->right_sibling = H->min;
        node_to_decrease->left_sibling = H->min->left_sibling;
        H->min->left_sibling = node_to_decrease;

        node_to_decrease->parent = NULL;
        node_to_decrease->mark = false;  

    }

    void cascading_cut(FIB_HEAP *H, NODE *parent_node){
        NODE *aux;
        aux = parent_node->parent;
        if(aux != NULL){
            if(parent_node->mark == false){
                parent_node->mark = true;
            }else{
                cut(H, parent_node, aux);
                cascading_cut(H, aux);
            }
        }
    }

    void decrease_key(FIB_HEAP *H, NODE *node_to_be_decrease, int new_key){
        NODE *parent_node;
        if(H ==NULL){
            printf("\n Fibonacci heap is not created");
            return;
        }
        if(node_to_be_decrease == NULL){
            printf("Node is not in the heap");
        }

        else{
            if(node_to_be_decrease->key < new_key){
                printf("\n Invalid new key for decrease key operation \n");
            }else{
                node_to_be_decrease->key = new_key;
                parent_node = node_to_be_decrease->parent;
                if((parent_node != NULL) && (node_to_be_decrease->key <parent_node->key)){
                    printf("\n cut called");
                    cut(H, node_to_be_decrease, parent_node);
                    printf("Cascading cut called");
                    cascading_cut(H, parent_node);
                }
                if(node_to_be_decrease->key < H->min->key){
                    H->min = node_to_be_decrease;
                }
            }
        }
    }

    void *find_node(FIB_HEAP *H, NODE *n, int key, int new_key){
        NODE *find_use = n;
        NODE *f  = NULL;
        find_use->visited = true;
        if(find_use->key == key){
            find_use->visited = false;
            f = find_use;
            decrease_key(H, f , new_key);
        }
        if(find_use->child != NULL){
            find_node(H, find_use->child, key, new_key);
        }
        if((find_use->right_sibling->visited != true)){
            find_node(H, find_use->right_sibling, key, new_key);
        }

        find_use->visited = false;
    }

    FIB_HEAP *insertion_procedure(){
        FIB_HEAP *temp;
        int no_of_nodes,ele,i;
        NODE *new_node;
        temp = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
        temp = NULL;
        if(temp == NULL){
            temp = make_fib_heap();
        }
        printf("\n enter number of nodes to insert = ");
        scanf("%d", &no_of_nodes);
        for(i = 1;i <= no_of_nodes;i++){
            printf("\n node %d and its key value = ",i);
            scanf("%d", &ele);
            insertion(temp, new_node, ele);
        }
        return temp;
    }

    void Delete_node(FIB_HEAP *H, int dec_key){
        NODE *p = NULL;
        find_node(H,H->min, dec_key, -5000);
        p = extract_min(H);
        if(p != NULL)
           printf("\n Node deleted");
        else
           printf("\n Node not deleted:some error ");   
    }

    int main(int argc, char **argv){
        NODE *new_node, *min_node, *extracted_min, *node_to_decrease, *find_use;
        FIB_HEAP *heap, *h1, *h2;
        int operation_no, new_key, dec_key, ele, no_of_nodes;
        heap = (FIB_HEAP *)malloc(sizeof(FIB_HEAP));
        heap = NULL;
        while(1){
            printf("\n Operation \n 1 Create Fibonacci \n 2 Insert nodes \n 3 Find min \n 4 Union \n 5 Extract min \n 6 Decrease key \n 7 Delete node \n 8 Print heap \n 9 exit \n enter choice :");
            scanf("%d", &operation_no);

            switch (operation_no)
            {
             case 1: 
                heap = make_fib_heap();
                break;
             case 2:
                if(heap == NULL){
                    heap = make_fib_heap();
                }
                    printf("Enter number of nodes to insert = ");
                    scanf("%d", &no_of_nodes);
                    for(int i = 1;i <= no_of_nodes;i++){
                        printf("\n node %d and its key value = ",i);
                        scanf("%d",&ele);
                        insertion(heap, new_node, ele);
                    }
                break;
             case 3:
                min_node = find_min_node(heap);
                if(min_node == NULL)
                   printf("No minimum value");
                else
                   printf("\n min value = %d",min_node->key);
                break;


             case 4:
                if(heap == NULL){
                    printf(" no fibonacci heap created \n");
                    break;
                }  
                h1 = insertion_procedure();
                heap = unionHeap(heap, h1);
                printf("Unified Heap: \n");
                print_heap(heap->min);
                break;

             case 5:
                if(heap == NULL)
                   printf("Empty fibonacci heap");
                else{
                    extracted_min = extract_min(heap);
                    printf("\n min value = %d",extracted_min->key);
                    printf("\n updated heap: \n");
                    print_heap(heap->min);
                }                       
                break;

             case 6:
                if(heap == NULL)
                  printf("Fibonacci heap is empty");
                else{
                    printf("\n node to be decreased = ");
                    scanf("%d",&dec_key);
                    printf("\n Enter the new kwy = ");
                    scanf("%d", &new_key);
                    find_use = heap->min;
                    find_node(heap, find_use, dec_key, new_key);
                    printf("\n Key decreased - Corresponding heap :\n");
                    print_heap(heap->min);
                }
                break;       
            
             case 7:
                if(heap == NULL)
                printf("Fibonacci heap is empty");
                else{
                    printf("\n Enter node key to be deleted = ");
                    scanf("%d", &dec_key);
                    Delete_node(heap, dec_key);
                    printf("\n Node Deleted- Corresponding heap: \n");
                    print_heap(heap->min);
                    break;
                } 

             case 8:
                print_heap(heap->min);
                break;

             case 9:
                free(new_node);
                free(heap);
                exit(0);


             default:
                printf("invalid choice");
            }
        }
    }