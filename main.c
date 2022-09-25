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
    
    if ((*head == NULL) || (pos >= size(*head))){
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


void search(struct node *head, int data){
    
    if (head == NULL){
        printf("The linked list is empty. Nothing to serch.\n");
        return;
    }
    
    int pos = 1;
    
    while (head->next != NULL && head->data != data){
        pos++;
        head = head->next;
    }
    if (head->data != data){
        printf("The value doesn't exist.\n");
        return;
    }
        
    if (head->data == data){
        printf("The value is at %d position.\n", pos);
        return;
    }
}


struct node *join(struct node *list1, struct node *list2){
    struct node *joined = NULL;
    
    
    if (list1 == NULL || list2 == NULL){
        printf("Nothing to join.\n");
        return 0;
    }
    
    while (list1 != NULL){
        append(&joined, list1->data);
        list1 = list1->next;
    }
    
    while (list2 != NULL){
        append(&joined, list2->data);
        list2 = list2->next;
    }

    return joined;
}


void print(struct node *node){
    while (node != NULL){
        printf(" %d ->", node->data);
        node = node->next;
    }
    printf(" NULL\n");
}


void serialize(struct node *head, char name[]){
    FILE* file = fopen(name, "w");

    if(file == NULL){
        printf("Can't open the file\n");
        exit(1);
    }
    

    while(head != NULL){
        fprintf(file, " %d ->", head->data);
        head = head->next;
    }

    fprintf(file, " NULL");
    fclose(file);
}


void deserialize(struct node *head, char name[]){
    FILE* file = fopen(name, "r");
    struct node *node = NULL;

    if(file == NULL){
        printf("Can't read the file\n");
        exit(2);
    }
    
    int val = 0;
    while((fscanf(file, " %d ->", &val)) > 0){
        append(&node, val);
    }

    fclose(file);
    
}


int main(){
    struct node *arr[4] = {NULL};
    
    int head = 1;
    int option = 0, val = 0;
    int pos = 0;
    int list1 = 0, list2 = 0;
    
    char file_name[101] = {0};
    
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
        printf("10 - Load the data in a new file\n");
        printf("11 - Read from a file\n");
        printf("12 - Choose the list\n");
        printf("0 - End of execution\n");
        scanf("%d", &option);
    
    switch(option){
            
        case 1:{
            printf("Enter the value you want to append: ");
            scanf("%d", &val);
            append(&arr[head], val);
            print(arr[head]);
            
            break;
        }
            
        case 2:{
            printf("Enter the value you want to prepend: ");
            scanf("%d", &val);
            prepend(&arr[head], val);
            print(arr[head]);
          
            break;
        }
            
        case 3:{
            reverse(&arr[head]);
            print(arr[head]);
            
            break;
        }
            
        case 4:{
            printf("Enter the value you want to insert: ");
            scanf("%d", &val);
            printf("Enter the position: ");
            scanf("%d", &pos);
            insertAt(&arr[head], pos, val);
            print(arr[head]);
            
            break;
        }
            
        case 5:{
            printf("Enter the position: ");
            scanf("%d", &pos);
            remoreFrom(&arr[head], pos);
            print(arr[head]);
            
            break;
        }
            
        case 6:{
            sort(&arr[head]);
            print(arr[head]);
         
            break;
        }
            
        case 7:{
            printf("Enter the value you want to find: ");
            scanf("%d", &val);
            search(arr[head], val);
          
            break;
        }
        
        case 8:{
            printf("What two lists should be joined?: ");
            scanf("%d %d", &list1, &list2);
            
            arr[head] = join(arr[list1], arr[list2]);
            print(arr[head]);
           
            break;
        }
            
        case 9:{
            
            break;
        }
        
        case 10:{
            printf("Type the name of a file: \n");
            scanf("%s", file_name);
            serialize(arr[head], file_name);
            
            break;
        }
            
        case 11:{
            deserialize(arr[head], file_name);
            print(arr[head]);
            
            break;
            
        }
        
        case 12:{
            for(int i=1;i<4;i++){
                print(arr[i]);
            }

            printf("Choose the list: \n");
            scanf("%d", &head);
            break;
        }   

        case 0:{
            return 0;
        }
            
        default:{
            printf("Try again\n");
            break;
        }
    }
}
    return 0;
}
