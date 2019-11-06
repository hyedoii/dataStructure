# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define TABLE_SIZE 13

typedef struct RecordNode {
    char key[128];
    char value[128];
    struct RecordNode* link;
} Node ;
Node* ht[TABLE_SIZE];

int transform(char *key){
    int val = 0 ;
    while( *key != '\0'){
        val = val + (*key++);
    }
    return val;
}

int hash_function(char *key){
    return transform(key) % TABLE_SIZE;
}

typedef struct Record {
    char key[128];
    char value[128];
}Record;


void init_map( ) {
    for( int i = 0 ; i < TABLE_SIZE ; i++ ){
        ht[i] = NULL;
    }
}

void print_map( ) {
    Node* p = (Node*)malloc(sizeof(Node));
    for( int i = 0 ; i < TABLE_SIZE ; i++ ){
        printf("[%2d]\t", i);
        if( ht[i] == NULL){ printf("\n"); continue; }
        else{
            for( p = ht[i] ; p != NULL; p = p->link){
                printf("%s\t",p->key);
            }
        }
        printf("\n");
    }
}
void add_record(char* key, char* value){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->key, key);
    strcpy(p->value, value);
    p->link = NULL;
    
    int hash = hash_function(key);
    if( ht[hash] != NULL ){
        p->link = ht[hash];
        ht[hash] = p;
    }
    else{
        ht[hash] = p;
    }
}

Node* search_record( char *key ) {
    Node * p = (Node*)malloc(sizeof(Node));
    int hash = hash_function(key);
    if( ht[hash] == NULL ){
        printf("[%s] 탐색 실패 : 찾는 값이 테이블에 없음\n" , key);
        return 0;
    }
    else{
        for( p = ht[hash] ; p->link != NULL ; p = p->link){
            if( !strcmp(ht[hash]->key,key)){
                printf("[%s] 탐색 성공[%2d]\t%s = %s \n", key , hash, ht[hash]->key , ht[hash]->value);
                return p;
            }
        }
    }
    return 0;
}

int main(){
    init_map();
    add_record( "do", "반복" );
    add_record( "for", "반복" );
    add_record( "if", "분기" );
    add_record( "case", "분기" );
    add_record( "else", "분기" );
    add_record( "return", "반환" );
    add_record( "function", "함수" );
    print_map( );
    search_record( "return" );
    search_record( "function" );
    search_record( "class" );
    
    return 0;
}
