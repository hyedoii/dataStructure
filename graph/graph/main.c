#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS 100
#define MAX_QUEUE_SIZE 100

typedef struct GrapeNode {
    int id;
    struct GrapeNode* link;
}GNode;
typedef char VtxData;
typedef int Element;

int visited[MAX_VTXS];
int adj[MAX_VTXS][MAX_VTXS];
int vsize;
int vdataSize = 0;
VtxData vdata[MAX_VTXS];
GNode* GNodeAdj[MAX_VTXS];


Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void init_queue() {
    front = rear = 0;
}

int is_empty() {
    return front == rear;
}

int is_full() {
    return (rear + 1) % MAX_QUEUE_SIZE == front;
}

int size() {
    return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void enqueue(Element val) {
    if (is_full())
        printf("큐 포화 에러\n");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    //printf("\n");
    data[rear] = val;
}

Element dequeue() {
    if (is_empty())
        printf("큐 에러");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}


void init_graph(){
    vsize = 0;
    for( int i = 0 ; i < MAX_VTXS ; i++){
        GNodeAdj[i] = 0;
        for( int j = 0 ; j < MAX_VTXS ; j++){
            GNodeAdj[i] = NULL;
        }
    }
}

void reset_graph() {
    GNode* n;
    for ( int i = 0 ; i < vsize ; i++ ){
        while(GNodeAdj[i] != NULL ){
            n = GNodeAdj[i];
            GNodeAdj[i] = n->link;
            free(n);
        }
    }
    vsize = 0;
}

int is_empty_graph(){
    return (vsize == 0);
}

int is_full_graph(){
    return (vsize >= MAX_VTXS);
}

void insert_vertex(char name){
    if(is_full_graph()){
        printf("ERROR : 정점 개수 초과\n");
        exit(1);
    }
    else{
        vdata[vsize++] = name;
    }
}

void insert_edge(int u , int v, int val){
    adj[u][v] = val;
}

void insert_edge2(int u , int v, int val){
    adj[u][v] = adj[v][u] = val;
}

void insert_edge3( int u , int v ){
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->id = v;
    n->link = GNodeAdj[u];
    GNodeAdj[u] = n;
}

void print_graph(char* msg){
    GNode* v;
    printf("%s%d\n", msg, vsize);
    for( int i = 0 ; i < vsize ; i++ ){
        printf("%c\t" , vdata[i]);
        for(v = GNodeAdj[i] ; v != NULL ; v = v->link){
            printf("%c ",vdata[v->id]);
        }
        printf("\n");
    }
}

void load_graph( char *filename){
    int val, n;
    char str[80];
    FILE * fp = fopen(filename, "r");
    if(fp != NULL ){
        fscanf(fp, "%d", &n);
        for(int i = 0 ; i < n ; i++){
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for( int j = 0 ; j < n+1 ; j++){
                fscanf(fp, "%d", &val);
                if(val !=0){
                    insert_edge3(i , j);
                }
            }
        }
        fclose(fp);
    }
}

void reset_visited(){
    for( int i = 0 ; i < vsize ; i++){
        visited[i] = 0;
    }
}

void DFS( int v) {
    visited[v] = 1;
    printf("%c ", vdata[v]);
    for ( int i = 0 ; i < vsize ; i++ ){
        if( adj[v][i] != 0 && visited[i] == 0 ){
            DFS(i);
        }
    }
}

void BFS ( int v ) {
    GNode* w;
    init_queue();
    visited[v] = 1;
    printf("%c ", vdata[v]);
    enqueue(v);
    while( !is_empty()){
        v = dequeue();
        for( w = GNodeAdj[v] ; w!= NULL ; w= w->link){
            if(!visited[w->id]){
                visited[w->id] = 1;
                printf("%c ", vdata[w->id]);
                enqueue(w->id);
            }
        }
    }
}

int main() {
    init_graph();
    /*
    for( int i = 0 ; i < 4 ; i++) {
        insert_vertex( 'A'+ i);
    }
    insert_edge2(0,1,1);
    insert_edge2(0,3,1);
    insert_edge2(1,2,1);
    insert_edge2(1,3,1);
    insert_edge2(2,3,1);
    */
    load_graph("DFS.txt");
    reset_visited();
    printf("BFS ==> ");
    BFS(0);
    printf("\n");
    //print_graph("그래프(인접행렬)\n");
    //printf("DFS == >");
    //DFS(0);
}
