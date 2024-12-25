#include <stdio.h>
#include "handlelist.h"

 
// Function to allocate and initialize a new node 
node *createnode() { 
    node *newnode = (node *)malloc(sizeof(node));

    if (!newnode) { 
        perror("Memory allocation failed"); 
        return NULL; 
    }

    return newnode;
    
} 
 
// Function to append a node to the linked list 
void append_node(node **head) { 
    node *new_node; 
    if (!new_node){

        perror("Memory allocation failed"); 
        return NULL;
    }
 
    if (*head == NULL) { 
        *head = new_node; 
        return; 
    } 
 
    node *temp = *head; 
    while (temp->next != NULL) { 
        temp = temp->next; 
    } 
    temp->next = new_node; 
} 

