#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


struct Node{
    int numValue;
    struct Node *leftNode;
    struct Node *rightNode;
};


void traverseBFS();
void generateTree(struct Node **tree, int input);
void traverseDFS();
void deleteTree(struct Node **tree);
void pre_order_travers(struct Node *tree);
void inorder_travers(struct Node *tree);
void post_order_travers(struct Node *tree);

int main()
{
    int firstNumber = INT_MAX;
    int order = 0;
    struct Node *tree = NULL;

    printf("Please choose which order.");
    printf("1 - Pre-Order ");
    printf("2 - In-Order ");
    printf("3 - Post-Order ");
    scanf("%d", &order);
    while(firstNumber !=0){
        printf("Please enter one number (0 to exit): ");
        scanf("%d", &firstNumber);
        switch(firstNumber){
                case 0:
                    deleteTree(&tree);
                    break;
                default:
                    generateTree(&tree, firstNumber);
                    switch(order){
                        case 1:
                            traverseBFS(tree);
                            break;
                        case 2:
                            inorder_travers(tree);
                            break;
                        case 3:
                            post_order_travers(tree);
                            break;
                    }
        }
    }
    return 0;
}

/*void insertBFS(struct Node *new , struct Node *head)
{
    if (new->numValue > head->numValue)
    {
        if (head->rightNode == NULL)
            head->rightNode = new;
        else
            insertBFS(new, head->rightNode);
    }
    if (new->numValue < head->numValue)
    {
        if (head->leftNode  ==  NULL)
            head->leftNode = new;
        else
            insertBFS(new, head->leftNode);
    }
}*/

void traverseBFS(struct Node *tree){
    //declare empty queue
    struct Node *array[100];
    int index1 = 0;
    int index2 = 0;

    array[index2] = tree;
    index2++;

    while (index2 - index1 != 0){
        struct Node *dequeue = array[index1];
        index1++;
        printf("%d ", dequeue->numValue);
        if (dequeue->leftNode != NULL){
            array[index2] = dequeue->leftNode;
            index2++;
        }
        if (dequeue ->rightNode != NULL){
            array[index2] = dequeue->rightNode;
            index2++;
        }
     }
}

void traverseIDFS(struct Node *tree){
    //for all possible nodes/levels
        //Use DFS
        //if there is another node/level
            //return node/level
        //else if there are no more levels
            //return
}










































void generateTree(struct Node **tree, int input){

    struct Node *current = *tree;
    struct Node *previous = *tree;
    bool bigger = true; // if input bigger, true

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    (temp)->numValue = input;
    (temp)->leftNode = NULL;
    (temp)->rightNode = NULL;

    if(*tree == NULL){
        *tree = temp;
    }else{
        while(current !=NULL){
            if(current->numValue > input){
                previous = current;
                current = current->leftNode;
                bigger = false;
            }else{
                previous = current;
                current = current->rightNode;
                bigger = true;
            }
        }
        if(!bigger){
            previous->leftNode = temp;
        }
        else{
            previous->rightNode = temp;
        }
    }

}

void pre_order_travers(struct Node *tree) {
   if(tree != NULL) {
      printf("%d ",tree->numValue);
      pre_order_travers(tree->leftNode);
      pre_order_travers(tree->rightNode);
   }
}

void inorder_travers(struct Node *tree) {
   if(tree != NULL) {
      inorder_travers(tree->leftNode);
      printf("%d ",tree->numValue);
      inorder_travers(tree->rightNode);
   }
}

void post_order_travers(struct Node *tree) {
   if(tree != NULL) {
      post_order_travers(tree->leftNode);
      post_order_travers(tree->rightNode);
      printf("%d ", tree->numValue);
   }
}

void traverseDFS(){

}

void deleteTree(struct Node **tree){
    if (tree == NULL){
        return;
    }else{
        deleteTree(&(*tree)->leftNode);
        deleteTree(&(*tree)->rightNode);
        free(*tree);
    }
}
