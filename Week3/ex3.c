#include <stdio.h>
#include "stdlib.h"

typedef struct node{
    int val;
    struct node* next;
}node;

void insert_node(node *head_node, int value, int index){
    int counter = 0;
    if (index == 0){
        printf("Cannot change head node");
        return;
    }
    node* current = head_node;
    node* prev = NULL;
    while (counter != index){
        counter += 1;
        if (current == NULL && counter < index + 2){
            printf("Index out range");
            return;
        }
        prev = current;
        current = current->next;

    }
    node * new = NULL;
    new = (node *) malloc(sizeof(node));
    new->val = value;
    prev->next = new;
    new->next = current;
}

void print_list(node* head_node){
    printf("%d", head_node->val);
    node* next = head_node->next;

    while (next != NULL){
        printf("%d", next->val);
        next = next->next;
    }
    printf("\n");
}

void delete_node(node* head_node, int index){
    int counter = 0;
    node* current = head_node;
    node* prev = NULL;
    while (counter != index){
        counter += 1;
        if (current == NULL && counter < index + 2){
            printf("Index out range");
            return;
        }
        prev = current;
        current = current->next;
    }
    if (current == NULL){
        printf("Index out of range");
    } else{
        prev->next=current->next;
    }
    free(current);
}

void free_memory(node* head_node){
    node* prev = NULL;
    node* next = head_node->next;
    while (next != NULL){
        prev = next;
        free(prev);
        next = next->next;
    }
}
int main() {
    node * head;
    head = (node *) malloc(sizeof(node));
    head->val = 0;
    head->next = NULL;
    insert_node(head, 1, 1);
    insert_node(head, 2, 2);
    insert_node(head, 3, 3);
    printf("Initial list:\n");
    print_list(head);
    printf("Delete node at index 3\n");
    delete_node(head ,3);
    print_list(head);
    printf("Insert node at index 2\n");
    insert_node(head, 3, 2);
    print_list(head);
    printf("Delete node at index 2\n");
    delete_node(head ,2);
    print_list(head);
    free_memory(head);
    return 0;
}




