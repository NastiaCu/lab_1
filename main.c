#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};


void append(struct node **head, int data){
    
    struct node *new = (struct node*)malloc(sizeof(struct node));
    
    struct node *last = *head;
    
    new->data = data;
    new->next = NULL;
    
    if (*head == NULL){
        *head = new;
        return;
    }
    
        while (last->next != NULL){
            last = last->next;
        }
        
        last->next = new;
        return;
    
}


void prepend(struct node **head, int data){
    
    struct node *new = (struct node*)malloc(sizeof(struct node));
    
    new->data = data;
    
    new->next = (*head);
    
    (*head) = new;
}


void reverse(struct node **head){
    
    struct node *current = *head;
    struct node *prev = NULL;
    struct node *next = NULL;
    
    while (current != NULL){
        next = current -> next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    *head = prev;
}


int size(struct node *head){
    int count = 0;
    
    while (head != NULL){
        count++;
        head = head->next;
    }
    
    return count;
}


void insertAt(struct node **head, int pos, int data){
    struct node *new = (struct node*)malloc(sizeof(struct node));
    struct node *current = *head;
    struct node *prev = NULL;
    new->data = data;
    
    if ((pos < 1) || (pos > size(*head))){
        printf("Position doesn't exist\n");
        return;
    }
    
    if (pos == 1){
        prepend(head, data);
        return;
    }
    
    if (pos > 1 && pos<=size(*head)){
        for(int i=1; i<pos;i++){
            prev = current;
            current = current->next;
        }
        new->data = data;
        prev->next = new;
        new->next = current;
        
    }
    
    if ((*head == NULL) || (pos = size(*head)+1)){
        append(head, data);
        return;
    }
}


void remoreFrom(struct node **head, int pos){
    struct node *current = *head;
    struct node *prev = NULL;
    struct node *next = NULL;
    
    if (*head == NULL){
        printf("The linked list is empty. Nothing to delete.\n");
        return;
    }
    
    if ((pos < 1) || (pos > size(*head))){
        printf("Position doesn't exist\n");
        return;
    }
    
    if (pos == 1){
        next = current->next;
        free(*head);
        *head = next;
        return;
    }
    
    for(int i=1; i<pos; i++){
        prev = current;
        current = current->next;
        next = current->next;
    }
    
    prev->next = next;
    free(current);
}


void sort(struct node **head){
    struct node *current = *head;
    struct node *next = NULL;
    struct node *sorted = NULL;
    struct node *node = NULL;
    
    if (*head == NULL){
        printf("The linked list is empty. Nothing to sort.\n");
        return;
    }
    
    while (current != NULL){
        next = current->next;
        
        if (sorted == NULL || sorted->data >= current->data){
            current->next = sorted;
            sorted = current;
        }
        
        else {
            node = sorted;
            while (node->next != NULL && node->next->data < current->data){
                node = node->next;
            }
            
            current->next = node->next;
            node->next = current;
        }
        
        current = next;
    }
    *head = sorted;
}


void print(struct node *node){
    while (node != NULL){
        printf(" %d ->", node->data);
        node = node->next;
    }
        printf(" NULL\n");
}


int main(){
    struct node *head = NULL;
    
    int option = 0, val = 0;
    int pos = 0;
    
    while(1){
        
        printf("Select the option:\n");
        printf("1 - Append\n");
        printf("2 - Prepend\n");
        printf("3 - Reverse\n");
        printf("4 - Add a value to the specific index\n");
        printf("5 - Remove a value the from index\n");
        printf("6 - Sort the linked list, with re-arranging the cells, not just copying values\n");
        printf("7 - Search for a value\n");
        printf("8 - Join two linked lists\n");
        printf("9 - Backwards traversal, use double-linked-list\n");
        printf("10 - load the data in a new file\n");
        printf("11 - read from a file\n");
        printf("0 - end of execution\n");
        scanf("%d", &option);
    
    switch(option){
            
        case 1:{
            printf("Enter the value you want to append: ");
            scanf("%d", &val);
            append(&head, val);
            print(head);
            
            break;
        }
            
        case 2:{
            printf("Enter the value you want to prepend: ");
            scanf("%d", &val);
            prepend(&head, val);
            print(head);
          
            break;
        }
            
        case 3:{
            reverse(&head);
            print(head);
            
            break;
        }
            
        case 4:{
            printf("Enter the value you want to insert: ");
            scanf("%d", &val);
            printf("Enter the position: ");
            scanf("%d", &pos);
            insertAt(&head, pos, val);
            print(head);
            
            break;
        }
            
        case 5:{
            printf("Enter the position: ");
            scanf("%d", &pos);
            remoreFrom(&head, pos);
            print(head);
            break;
        }
            
        case 6:{
            sort(&head);
            print(head);
         
            break;
        }
            
        case 7:{
          
            break;
        }
        
        case 8:{
            
            break;
        }
            
        case 9:{
            
            break;
        }
        
        case 10:{
            
            break;
        }
            
        case 11:{
            
            break;
            
        }
            
        case 0:{
            return 0;
        }
            
        default:{
            break;
        }
    }
}
    return 0;
}
