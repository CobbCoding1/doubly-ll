#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    char value;
} Node;

Node *node_init(char value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}
    
void list_push(Node **head, char value) {
    Node *new = node_init(value);
    if(*head != NULL) {
        new->next = *head;
    }
    (*head)->prev = new;
    *head = new;
}
   
void list_push_end(Node **head, char value) {
    Node *new = node_init(value);
    if(*head == NULL) {
        *head = new;
        return;
    }
    Node *cur = *head;
    while(cur->next != NULL) cur = cur->next;
    new->prev = cur;
    cur->next = new;
}

void list_insert_before(Node *node, char value) {
    Node *new = node_init(value);
    new->prev = node->prev;
    node->prev = new;
    new->next = node;
    if(new->prev != NULL) new->prev->next = new;
}
    
void list_insert_after(Node *node, char value) {
    Node *new = node_init(value);    
    new->next = node->next;
    node->next = new;
    new->prev = node;
    if(new->next != NULL) new->next->prev = new;
}
    
Node *list_get_index(Node **head, size_t n) {
    Node *cur = *head;
    while(cur != NULL && n > 0) {
        cur = cur->next;
        n--;
    }
    assert(cur != NULL && "List index out of bounds\n");
    return cur;
} 
    
void list_delete_index(Node **head, size_t n) {
    Node *del = list_get_index(head, n);
    if(*head == NULL || del == NULL) return;
    if(*head == del) *head = (*head)->next;
    if(del->next != NULL) del->next->prev = del->prev;
    if(del->prev != NULL) del->prev->next = del->next;
    free(del);
}
    
size_t list_size(Node *node) {
    size_t count = 0;
    while(node != NULL) {
        node = node->next;
        count++;
    }
    return count;
}
    
int list_largest(Node *node) {
    int largest = 0;
    while(node != NULL) {
        if(node->value > largest) largest = node->value;
        node = node->next;
    }
    return largest;
}

void list_print(Node *node) {
    printf("begin <-> ");
    while(node != NULL) {
        printf("%c <-> ", node->value);
        node = node->next;
    }
    printf("end\n");
}
    
void list_str_print(Node *node) {
    while(node != NULL) {
        printf("%c", node->value);
        node = node->next;
    }    
}
    
void list_reverse(Node **head) {
    Node *cur = *head;
    Node *temp = NULL;
    
    while(cur != NULL) {
        temp = cur->prev;
        cur->prev = cur->next;
        cur->next = temp;
        cur = cur->prev;
    }
    if(temp != NULL) *head = temp;
}
    
Node *node_str_init(char *str) {
    Node *root = node_init(str[0]);
    for(size_t i = 1; i < strlen(str); i++) {
        list_push_end(&root, str[i]);
    }
    return root;
}

int main() {
    Node *str = node_str_init("Hello, world!\n");
    list_str_print(str);
    printf("str: %zu, char*: %zu", list_size(str), strlen("Hello, world!\n"));
}