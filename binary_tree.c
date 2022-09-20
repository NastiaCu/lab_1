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
    
    if (node->data > data){
        node = search(node->right, data);
    }
   
    else if (node-> data < data){
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


void store(struct node *node, int inorder[], int *index){
   
    if (node == NULL){
        return;
    }
    else{
        store(node->left, inorder, index);
        inorder[*index] = node->data;
        (*index)++;
        store(node->right, inorder, index);
    }
}


int count(struct node *node){
    
    int n = 0;
    
    if (node == NULL){
        return 0;
    }
    
    else {
        n = count(node->left) + count(node->right) + 1;
        return n;
    }
}


void arrToBT(struct node *node, int *arr, int *index){
    
    if (node == NULL){
        return;
    }
    
    else {
        arrToBT(node->left, arr, index);
        node->data = arr[*index];
        (*index)++;
        arrToBT(node->right, arr, index);
    }
}


//function to swap the position of two elements
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//function to find the largest element among the nodes

void heapify(int arr[], int n, int i){
    
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 1;
    
    if (left < n && arr[left] > arr[largest]){
        largest = left;
    }
    
    else if (right < n && arr[right] > arr[largest]){
        largest = right;
    }
    
    if (largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n , largest);
    }
}


void HeapSort(int arr[], int n){
//    build max heap
    int i;
    for (i = n/2; i >= 0; i--){
        heapify(arr, n , i);
    }
    
//    heap sort
    for (i = n-1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


void BTtoBST(struct node *node){
    
    if (node == NULL){
        return;
    }
    
    else {
        int n = count(node);
        int *arr = malloc(n * sizeof(*arr));
        int i = 0;
        store(node, arr, &i);
        HeapSort(arr, n);
        i = 0;
        arrToBT(node, arr, &i);
        free(arr);
    }
        
}


//write the binary tree to a file
void serialize(struct node *node, char name[]){
    FILE* file = fopen(name, "w");

    if(file == NULL){
        printf("Can't open the file\n");
        exit(1);
    }
    
    while(node != NULL)
    {
        fprintf(file, " %d ->", node->data);
        if (node->right != NULL){
            fprintf(file, " %d ->", node->right->data);
        }
        if (node->left != NULL){
            fprintf(file, " %d ->", node->left->data);
        }
        node = node->left;
    }
    fprintf(file, " NULL");
    fclose(file);
}


//read the binary tree from a file
void deserialize(struct node **node, char name[]){
    FILE* file = fopen(name, "r");

    if(file == NULL){
        printf("Can't read the file\n");
        exit(2);
    }
    
    int val = 0;
    while(fscanf(file, " %d ->", &val) > 0)
    {
        insert(*node, val);
    }
    fclose(file);
}


int main(){
    
    struct node *root = NULL;
    int option = 0, val = 0;
    
    while(1){
        
        printf("Select the option:\n");
        printf("1 - insert new node\n");
        printf("2 - delete an element\n");
        printf("3 - search a node\n");
        printf("4 - inorder traversal\n");
        printf("5 - postorder traversal\n");
        printf("6 - preorder traversal\n");
        printf("7 - sort, transform in BST\n");
        printf("8 - balance, transform in a balanced BT\n");
        printf("9 - load the data in a new file\n");
        printf("10 - read from a file\n");
        printf("11 - end of execution\n");
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
            
        case 4:{
            Inorder(root);
            break;
        }
            
        case 5:{
            Postorder(root);
            break;
        }
            
        case 6:{
            Preorder(root);
            break;
        }
            
        case 7:{
            BTtoBST(root);
            Inorder(root);
            break;
        }
        
        case 8:{
            break;
        }
            
        case 9:{
            serialize(root, "file.txt");
            break;
        }
        
        case 10:{
            deserialize(&root, "file.txt");
            break;
        }
            
        case 11:{
            return 0;
        }
            
        default:{
            break;
        }
    }
    }
    
    
    return 0;
}
