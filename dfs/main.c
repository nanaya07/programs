#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Node{
    int numValue;
    struct Node *leftNode;
    struct Node *rightNode;
};

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
                    switch(order){
                        case 1:
                            generateTree(&tree, firstNumber);
                            pre_order_travers(tree);
                            break;
                        case 2:
                            generateTree(&tree, firstNumber);
                            inorder_travers(tree);
                            break;
                        case 3:
                            generateTree(&tree, firstNumber);
                            post_order_travers(tree);
                            break;
                    }
        }
    }
    return 0;
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
