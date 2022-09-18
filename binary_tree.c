#include <stdio.h>
#include <stdlib.h>


struct node{
    int data;
    struct node *left;
    struct node *right;
};


struct node *newNode(int data){
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}


struct node *insert(struct node *node, int data){
    
    int option;
 
    if (node == NULL){
        return newNode(data);
    }
    
    else{
        printf("Current element: %d\n", node->data);
        
        if (node->left != NULL){
            printf("Left element: %d\n", node->left->data);
        }
        
        else{
            printf("Left side is empty\n");
        }
        
        if (node->right != NULL){
            printf("Right element: %d\n", node->right->data);
        }
        
        else{
            printf("Right side is empty\n");
        }
        
        printf("Add: 1 - left, 2 - right\n");
        scanf("%d", &option);
        
        switch(option){
            
            case 1:{
                node->left = insert(node->left, data);
                break;
            }
                
            case 2:{
                node->right = insert(node->right, data);
                break;
            }
        }
    }
        
    return node;
}


void Inorder(struct node *node){
    if (node != NULL){
        Inorder(node->left);
        printf("%d -> ", node->data);
        Inorder(node->right);
    }
}


void Postorder(struct node *node){
    if (node != NULL){
        Postorder(node->left);
        Postorder(node->right);
        printf("%d -> ", node->data);
    }
}


void Preorder(struct node *node){
    if (node != NULL){
        printf("%d -> ", node->data);
        Preorder(node->left);
        Preorder(node->right);
    }
}


int main(){
    
    struct node *root = NULL;
    int option = 0, val;
    
    while(1){
        
        printf("Select the option:\n");
        printf("1 - insert new node\n");
        printf("2 - inorder traversal\n");
        printf("3 - postorder traversal\n");
        printf("4 - preorder traversal\n");
        printf("5 - end of execution\n");
        scanf("%d", &option);
    
    switch(option){
            
        case 1:{
            printf("What you want to add? : ");
            scanf("%d", &val);
            if (root == NULL){
                root = insert(root, val);
            }
            else {
                insert(root, val);
            }
            break;
        }
            
        case 2:{
            Inorder(root);
            break;
        }
            
        case 3:{
            Postorder(root);
            break;
        }
            
        case 4:{
            Preorder(root);
            break;
        }
            
        case 5:{
            return 0;
        }
    }
    }
    
    
    return 0;
}
