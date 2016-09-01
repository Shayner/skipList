#include <stdlib.h>

typedef struct  nodeStruct{
    double key;
    struct nodeStruct* forward[1];
}Node;
typedef struct testNode{
    int *a;
    char b;
}test;
int main(){
    int total_size = sizeof(Node) + 10*sizeof(Node*);
    test* tem;
    printf("test:%d,%d\n",sizeof(test),sizeof(tem));
    printf("%d\n",sizeof(int));
    printf("Node:%d,Node*:%d,size::%d\n",sizeof(Node),sizeof(Node*),total_size);
    Node* temp = (Node*)malloc(total_size);
    temp->key = 1;
    int i;
    for(i = 0; i < 9; i++){
        printf("i:::%d\n",temp->key);
        temp->key++;
        temp->forward[i] = temp;
        temp = temp->forward[i];
    }
}
