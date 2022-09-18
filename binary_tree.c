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


struct node *min(struct node *node){
    
    struct node *temp = node;
    while (temp != NULL  && temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}


struct node *delete(struct node *node, int data){
    
    if (node == NULL){
        return node;
    }
    
    if (data < node->data){
        node->left = delete(node->left, data);
    }
    
    if (data > node->data){
        node->right = delete(node->right, data);
    }
    
    if (node->left == NULL){
        struct node *temp = node->right;
        free(node);
        return temp;
    }
    
    if (node->right == NULL){
        struct node *temp = node->left;
        free(node);
        return temp;
    }
    
    struct node *temp = min(node->right);
    node->data = temp->data;
    node->right = delete(node->right, temp->data);
   
    return node;
}


struct node *search(struct node *node, int data){
    
    if (node == NULL || node->data == data){
        return node;
    }
    
    if (node->data < data){
        node = search(node->right, data);
    }
   
    else if (node-> data > data){
        node = search(node->left, data);
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
        printf("2 - delete an element\n");
        printf("3 - inorder traversal\n");
        printf("4 - postorder traversal\n");
        printf("5 - preorder traversal\n");
        printf("6 - search a node\n");
        printf("7 - end of execution\n");
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
            printf("What element do you want to delete? : ");
            scanf("%d", &val);
            if (root == NULL){
                return 0;
            }
            else {
                delete(root, val);
            }
            break;
        }
            
        case 3:{
            Inorder(root);
            break;
        }
            
        case 4:{
            Postorder(root);
            break;
        }
            
        case 5:{
            Preorder(root);
            break;
        }
        
        case 6:{
            printf("Which node do you want to find? : ");
            scanf("%d", &val);
            
            if (search(root, val)) {
                printf("The node exists\n");
            }
            
            else {
                printf("The node was not found in the tree\n");
            }
            
            break;
        }
        
        case 7:{
            return 0;
        }
    }
    }
    
    
    return 0;
}
