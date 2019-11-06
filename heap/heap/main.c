#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_NODE 100

typedef int HNode;
#define Key(n) (n)

HNode heap[MAX_HEAP_NODE];
int heap_size;

#define Parent(i) (heap[i/2])
#define Left(i) (heap[i*2])
#define Right(i) (heap[i*2+1])

void init_heap() { heap_size = 0;}
int is_empty_heap() { return heap_size == 0;}
int is_full_heap() { return (heap_size == MAX_HEAP_NODE-1);}
HNode find_heap() { return heap[1]; }

void insert_heap( HNode n ){
    int i;
    if( is_full_heap() ) return;
    i = ++(heap_size);
    while (i != 1 && Key(n) > Key(Parent(i))) {
        heap[i]= Parent(i);
        i = i/2;
    }
    heap[i] = n;
}

HNode delete_heap() {
    HNode hroot = 0, last;
    int parent = 1, child = 2;
    if( !is_empty_heap()) {
        hroot = heap[1];
        last = heap[heap_size--];
        while( child <= heap_size ){
            if( child < heap_size && Key(Left(parent)) < Key(Right(parent))){ child++; }
            if( Key(last) >= Key(heap[child]) ){ break; }
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = last;
    }
    return hroot;
}

void print_heap(){
    int i = 1, degree = 1;
    while( i <= heap_size){
        //printf("degree %d\n",degree);
        for(int j = 0 ; j < degree ; j++) {
            printf("%d ",heap[i]);
            i++;
            if( i == heap_size + 1){
                break;
            }
        }
        //printf("\n");
        degree = degree*2;
    }
    //printf("-----------\n");
}

int main() {
    int num[10];
    init_heap();
    insert_heap(41);
    
    insert_heap(67);
    insert_heap(34);
    insert_heap(0);
    insert_heap(69);
    insert_heap(24);
    insert_heap(78);
    insert_heap(58);
    insert_heap(62);
    insert_heap(64);
    //print_heap();
    printf("정렬 전: 41 67 34 0 69 24 78 58 62 64 \n");
    
    for (int i = 0; i < 10; ++i) {
        num[i] = delete_heap();
    }
    init_heap();
    for (int i = 9; i >= 0; i--) {
        printf("%d ",num[i]);
    }
    print_heap();
    
    

    return 0;
}

