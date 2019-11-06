#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS 100
#define MAX_HEAP_NODE 100
#define INF 9999

#define Key(n) (n.key)

#define Parent(i) (heap[i/2])
#define Left(i) (heap[i*2])
#define Right(i) (heap[i*2+1])
typedef char VtxData;

typedef struct HeapNode{
    int key;
    int v1;
    int v2;
}HNode;

VtxData vdata[MAX_VTXS];
HNode heap[MAX_HEAP_NODE];
int adj[MAX_VTXS][MAX_VTXS];
int parent[MAX_VTXS];
int heap_size;
int set_size;
int vsize;
int path[MAX_VTXS];
int dist[MAX_VTXS];
int found[MAX_VTXS];


void init_heap() { heap_size = 0;}
int is_empty_heap() { return heap_size == 0;}
int is_full_heap() { return (heap_size == MAX_HEAP_NODE-1);}
HNode find_heap() { return heap[1]; }

void insert_heap( HNode n ){
    int i;
    if( is_full_heap() ) return;
    i = ++(heap_size);
    while (i != 1 && Key(n) < Key(Parent(i))) {
        heap[i]= Parent(i);
        i = i/2;
    }
    heap[i] = n;
}

HNode delete_heap() {
    HNode hroot, last;
    int parent = 1, child = 2;
    if( !is_empty_heap()) {
        hroot = heap[1];
        last = heap[heap_size--];
        while( child <= heap_size ){
            if( child < heap_size && Key(Left(parent)) > Key(Right(parent))){ child++; }
            if( Key(last) <= Key(heap[child]) ){ break; }
            heap[parent] = heap[child];
            parent = child;
            child *= 2;
        }
        heap[parent] = last;
    }
    return hroot;
}

void init_set(int nSets){
    set_size = nSets;
    for( int i = 0 ; i < nSets ; i++) {
        parent[i] = -1;
    }
}

int find_set(int id){
    while(parent[id]>=0){
        id = parent[id];
    }
    return id;
}

void union_set(int s1, int s2){
    parent[s1] = s2;
    set_size--;
}

void Kruskal() {
    int edgeAccepted = 0 , uset, vset;
    HNode e;
    init_heap();
    init_set(vsize);
    for ( int i = 0 ; i < vsize ; i++ ) {
        for( int j = i+1 ; j < vsize ; j++ ){
            if(adj[i][j] < INF ) {
                e.key = adj[i][j];
                e.v1 = i;
                e.v2 = j;
                if(e.key != 0){
                    insert_heap(e);
                }
            }
        }
    }
    while( edgeAccepted < vsize -1 ){
        e = delete_heap();
        uset = find_set(e.v1);
        vset = find_set(e.v2);
        if( uset != vset) {
            printf("간선추가 : %c - %c ( 비용 : %d)\n", vdata[e.v1], vdata[e.v2] , e.key);
            union_set(uset, vset);
            edgeAccepted++;
        }
    }
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

void insert_edge( int u , int v , int keyValue){
    adj[u][v] = keyValue;
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
                    insert_edge(i , j, val);
                }
            }
        }
        fclose(fp);
    }
}

int choose_vertex(){
    int min = INF, minpos = -1;
    for( int i = 0 ; i < vsize ; i++ ){
        if(dist[i]< min && !found[i]){
            min = dist[i];
            minpos=i;
        }
    }
    return minpos;
}

void shortest_path_dijkstra( int start ){
    int u;
    for( int i = 0 ; i<vsize ; i++){
        dist[i] = adj[start][i];
        path[i] = start;
        found[i] = 0;
    }
    found[start] = 1;
    dist[start] = 0;
    
    for( int i = 0 ; i < vsize ; i++ ){
        printf("Step%d :\t", i+1);
        for( int i = 0 ; i < vsize ; i++) {
            if( dist[i] != 9999){
                printf("%d\t",dist[i]);
            }
            else{
                printf("INF\t");
            }
        }
        printf("\n");
        u = choose_vertex();
        found[u] = 1;
        for( int w = 0 ; w < vsize ; w++) {
            if( found[w] == 0 ) {
                if(dist[u]+adj[u][w] < dist[w]){
                    dist[w] = dist[u] + adj[u][w];
                    path[w] = u;
                }
            }
        }
    }
}

void print_graph(char * msg){
    printf("%s", msg);
}

void print_shortest_path( int u , int v ){
    printf("[최단경로 : %c---%c ]", vdata[v] , vdata[u]);
    
    printf("%c", vdata[v]);
    for( int i = v; i >= u; --i) {
        printf("-%c",vdata[path[i]]);
        if (vdata[u] == vdata[path[i]]) break;
    }
    printf("\n");
}

int main() {
    load_graph( "wgraph_sp.txt" );
    print_graph( "최단거리(wgraph.txt)\n");
    printf("Shortest Path By Dijkstra Algorithm\n");
    shortest_path_dijkstra( 0 );
    for (int i = 1; i<vsize; i++) {
        print_shortest_path(0, i);
    }
    return 0;
}
