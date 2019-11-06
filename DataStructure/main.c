#include <stdio.h>
#include <stdlib.h>

typedef int TElement;
typedef struct BinTrNode{
    TElement data;
    struct BinTrNode* left;
    struct BinTrNode* right;
}TNode;

typedef struct LinkedNode {
    TNode* data;
    struct LinkedNode *link;
}Node;
Node *front;
Node *rear;

TNode * root = NULL;

void init_queue() {
    front = NULL;
    rear = NULL;
}

int is_empty() {
    return front == NULL && rear == NULL;
}

int size() {
    Node *p;
    int count = 0;
    
    for (p = front; p != NULL; p = p->link)
        count++;
    
    return count;
}

void enqueue(TNode* e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->link = NULL;
    
    if (is_empty()) {
        front = p;
        rear = p;
    }
    else {
        rear->link = p;
        rear = p;
    }
}

TNode* dequeue() {
    Node *p = (Node*)malloc(sizeof(Node));
    
    if (size() >= 2) {
        p = front;
        front = front->link;
    }
    else if (size() == 1) {
        p = front;
        front = NULL;
        rear = NULL;
    }
    else
        printf("에러");
    return p->data;
}

TNode* create_tree(TElement Bval, TNode* l , TNode* r) {
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = Bval;
    n->left = l;
    n->right = r;
    return n;
}


TNode* search(TNode*n, int key){
    if( n == NULL){
        return NULL;
    }
    else if ( key == n->data){
        return n;
    }
    else if (key < n->data){
        return search(n->left, key);
    }
    else return search(n->right, key);
}

TNode* search_iter( TNode *n, int key ) {
    while(n != NULL){
        if( key == n->data ) return n;
        else if( key < n->data ) n = n->left;
        else n = n->right;
    }
    return NULL;
}

void search_BST(int key){
    TNode* n = search(root, key);
    if(n!= NULL){
        printf("[탐색 연산] : 성공 [%d] = %p\n", n->data, n);
    }
    else{
        printf("[탐색 연산] : 실패 : No %d!\n", key);
    }
}

int insert( TNode* r, TNode* n )
{
    if( n->data == r->data ) return 0;
    else if( n->data < r->data ) {
        if( r->left == NULL ) r->left = n;
        else insert( r->left, n );
    }
    else {
        if( r->right== NULL ) r->right = n;
        else insert( r->right, n );
    }
    return 1;
}

void insert_BST(int key){
    TNode* n = create_tree(key, NULL, NULL);
    if(root==NULL){
        root = n;
    }
    else if (insert(root, n) == 0){
        free(n);
    }
}
void delete(TNode* parent , TNode* node){
    TNode *child, *succ, *succp;
    
    //case 1
    if( node->left == NULL && node->right == NULL) {
        if(parent == NULL) root = NULL;
        else {
            if(parent->left == node){
                parent->left = NULL;
            }
            else parent->right = NULL;
        }
    }
    //case2
    else if ( node->left == NULL || node-> right == NULL ){
        child = (node->left != NULL) ? node->left : node->right;
        if(node == root) root = child;
        else{
            if(parent->left == node){
                parent->left = child;
            }
            else{
                parent->right = child;
            }
        }
    }
    
    //case3
    else {
        succp = node;
        succ = node->right;
        while(node->left != NULL){
            succp = succ;
            succ = succ->left;
        }
        if(succp->left == succ){
            succp->left = succ->right;
        }
        else succp->right = succ->right;
        
        node->data = succ->data;
        node = succ;
    }
    free(node);
}

void delete_BST(int key){
    TNode* parent = NULL;
    TNode* node = root;
    
    if(node == NULL) return;
    while(node != NULL && node->data != key){
        parent = node;
        node = (key < node->data)? node->left : node->right;
    }
    if(node == NULL){
        printf(" Error: key is not in the tree!\n");
    }
    else{
        delete(parent, node);
    }
}

void init_tree(){ root = NULL;}


TNode* get_root(){
    return root;
}

int count_node(TNode* n){
    if( n == NULL){
        return 0;
    }
    return 1+ count_node(n->left)+count_node(n->right);
    
}

int count_leaf(TNode* n){
    if( n == NULL){
        return 0;
    }
    if(n->left == NULL && n->right == NULL) {
        return 1;
    }
    else return count_leaf(n->left) + count_leaf(n->right);
    
}

int calc_height(TNode* n){
    int hLeft , hRight;
    if( n == NULL){
        return 0;
    }
    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);
    return (hLeft>hRight)? hLeft+1 : hRight+1;
}

int calc_size(TNode *n)
{
    if( n == NULL ) return 0;
    return n->data + calc_size(n->left) + calc_size(n->right);
}

void preOrder(TNode * n){
    if(n != NULL) {
        printf("[%d] ",n->data);
        preOrder(n->left);
        preOrder(n->right);
    }
}

void inOrder(TNode* n){
    if( n != NULL ) {
        inOrder(n->left);
        printf("[%d] ",n->data);
        inOrder(n->right);
    }
}

void postOrder(TNode*n){
    if(n != NULL){
        postOrder(n->left);
        postOrder(n->right);
        printf("[%d] ", n->data);
    }
}

void levelOrder(){
    init_queue();
    if(root == NULL){
        return;
    }
    enqueue(root);
    while(is_empty() == 0){
        TNode* x= dequeue();
        if( x != NULL){
            printf("[%d] ",x->data);
            enqueue(x->left);
            enqueue(x->right);
        }
    }
}

int evaluate(TNode* n){
    int result = 0;
    int x, y;
    if (n->left->left == NULL) {
        x = n->left->data - 48;
        y = n->right->data - 48;
    }
    else {
        x = evaluate(n->left);
        y = evaluate(n->right);
    }
    char op = n->data;
    
    if (op == '+') result = x + y;
    if (op == '/') result = x / y;
    if (op == '*') result = x * y;
    if (op == '-') result = x - y;
    return result;
}

int calc_height_diff(TNode* n){
    int hLeft, hRight;
    if( n == NULL) return 0;
    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);
    return hLeft - hRight;
}

TNode* rotateLL(TNode* A){
    TNode* B = A->left;
    A->left = B-> right;
    B->right = A;
    return B;
}
TNode* rotateRR(TNode* A){
    TNode* B = A->right;
    A->right = B->left;
    B->left =A;
    return B;
}
TNode* rotateRL(TNode* A){
    TNode* B = A->right;
    A->right = rotateLL(B);
    return rotateRR(A);
}
TNode* rotateLR(TNode* A){
    TNode* B = A->left;
    A->left = rotateRR(B);
    return rotateLL(A);
}

TNode* reBalance(TNode* parent){
    int hDiff = calc_height_diff(parent);
    
    if(hDiff>1){
        if(calc_height_diff(parent->left)>0){
            parent = rotateLL(parent);
        }
        else{
            parent = rotateLR(parent);
        }
    }
    else if(hDiff<-1){
        if(calc_height_diff(parent->right)<0){
            parent = rotateRR(parent);
        }
        else{
            parent = rotateRL(parent);
        }
    }
    return parent;
}

TNode* insert_node_AVL(TNode* parent, int key){
    if(key < parent->data){
        if(parent->left != NULL){
            parent->left = insert_node_AVL(parent->left, key);
        }
        else {
            parent->left = create_tree(key, NULL, NULL);
        }
        return reBalance(parent);
    }
    else if ( key > parent->data){
        if(parent->right != NULL){
            parent->right = insert_node_AVL(parent->right, key);
        }
        else {
            parent->left = create_tree(key, NULL, NULL);
        }
        return reBalance(parent);
    }
    else {
        printf("중복된 키 에러\n");
        return NULL;
    }
}



int main() {
    /*init_tree();
    printf("[삽입 연산] : 35 18 7 26 12 3 68 22 30 99");
    
    insert_BST(35);
    insert_BST(18);
    insert_BST(7);
    insert_BST(26);
    insert_BST(12);
    insert_BST(3);
    insert_BST(68);
    insert_BST(22);
    insert_BST(30);
    insert_BST(99);
    
    printf("In-Order : ");
    inOrder(root);
    printf("\nPre-Order : ");
    preOrder(root);
    printf("\nPost-Order : ");
    postOrder(root);
    printf("\nLevel-Order : ");
    levelOrder();
    printf("\n노드의 개수 : %d", count_node(root));
    printf("\n단말의 개수 : %d", count_leaf(root));
    printf("\n트리의 높이 : %d \n", calc_height(root));
    
    search_BST(26);
    search_BST(25);
    
    printf("original bintree : LevelOrder: ");
    levelOrder();
    delete_BST(3);
    printf("\ncase1 < 3> 삭제 : LevelOrder: ");
    levelOrder();
    delete_BST(68);
    printf("\ncase2 <68> 삭제 : LevelOrder: ");
    levelOrder();
    delete_BST(18);
    printf("\ncase3 <18> 삭제 : LevelOrder: ");
    levelOrder();
    delete_BST(35);
    printf("\ncase3 <35> root : LevelOrder: ");
    levelOrder();
    printf("\n노드의 개수 : %d", count_node(root));
    printf("\n단말의 개수 : %d", count_leaf(root));
    printf("\n트리의 높이 : %d \n", calc_height(root));
     */
    init_tree();
    //TNode* root;
    
    root = create_tree(7, NULL, NULL); printf("\nAVL(7) : "); levelOrder();
    root = insert_node_AVL(root, 8); printf("\nAVL(8) : "); levelOrder();
    root = insert_node_AVL(root, 9); printf("\nAVL(9) : "); levelOrder();
    root = insert_node_AVL(root, 2); printf("\nAVL(2) : "); levelOrder();
    root = insert_node_AVL(root, 1); printf("\nAVL(1) : "); levelOrder();
    root = insert_node_AVL(root, 5); printf("\nAVL(5) : "); levelOrder();
    root = insert_node_AVL(root, 3); printf("\nAVL(3) : "); levelOrder();
    root = insert_node_AVL(root, 6); printf("\nAVL(6) : "); levelOrder();
    root = insert_node_AVL(root, 4); printf("\nAVL(4) : "); levelOrder();
   
    printf("\n노드의 개수 : %d", count_node(root));
    printf("\n단말의 개수 : %d", count_leaf(root));
    printf("\n트리의 높이 : %d \n", calc_height(root));
    
    return 0;
}
