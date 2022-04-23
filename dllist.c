#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0

typedef unsigned char bool_t;

typedef struct node_dl_s {
    int val;
    struct node_dl_s *next;
    struct node_dl_s *prev;
} node_dl_t;

typedef struct dll_s {
    node_dl_t *head;
    node_dl_t *tail;
    int num;
} dll_t;

node_dl_t* dllist_add_front(node_dl_t* head, int val);
node_dl_t* dllist_add_back(node_dl_t* head, int val);
node_dl_t* dllist_del(node_dl_t*head, int val);
node_dl_t* dllist_find(node_dl_t* head, int val);
void dllist_destruct(node_dl_t* head);
void dllist_print(node_dl_t* head);


bool_t dll_construct(dll_t **dll);
void dll_destruct(dll_t **dll);
bool_t dll_insert_front(dll_t *dll, int val);
bool_t dll_insert_back(dll_t *dll, int val);
bool_t dll_insert_at_n(dll_t *dll, int val, int n);

bool_t
dll_alloc_node
(
    node_dl_t** new_node, 
    int data
)
{
    *new_node = (node_dl_t*)calloc(1, sizeof(node_dl_t));
    if (!*new_node) {printf("[%s] Failed to allocate node\n", __func__);return FALSE;}
    (*new_node)->val = data;
    return TRUE;
}

node_dl_t*
dllist_add_front
(
    node_dl_t* head, 
    int val
) 
{
    node_dl_t* new_node = (node_dl_t*)malloc(sizeof(node_dl_t));
    if (new_node == NULL) {
        return head;
    }

    new_node->val = val;
    new_node->next = head;
    if (head) {
        head->prev = new_node;
    }
    new_node->prev = NULL;

    return new_node;
}

void
dllist_destruct
(
    node_dl_t* head
)
{
    int num_free = 0;
    if (head) {
        node_dl_t* next;
        while(head) {
            next = head->next;
            num_free++;
            free(head);
            head = next;
        }
    }
    printf("[%s] Number of nodes freed: %d\n", __func__, num_free);
}

node_dl_t* 
dllist_add_back
(   
    node_dl_t* head, 
    int val
)
{
    node_dl_t *curr_node = head;
    node_dl_t *new_node = (node_dl_t*)malloc(sizeof(node_dl_t));
    if (new_node == NULL) {
        return head;
    }

    new_node->val = val;
    if (!curr_node) {
        new_node->next = NULL;
        new_node->prev = NULL;
        return new_node;
    }

    while(curr_node->next) {
        curr_node = curr_node->next;
    }

    curr_node->next = new_node;
    new_node->prev = curr_node;
    new_node->next = NULL;

    return head;
}

node_dl_t*
dllist_del
(
    node_dl_t* head, 
    int val
) 
{
    int num_free = 0;
    node_dl_t* del_node = dllist_find(head, val);
    while(del_node) {
        //If found node is head
        if (del_node->prev == NULL) {
            head = del_node->next;
            if (head) {
                head->prev = NULL;
            }
        } else {
            //Unlink node to be deleted
            del_node->prev->next = del_node->next;
            if (del_node->next) {
                del_node->next->prev = del_node->prev;
            }
        }
        free(del_node);
        num_free++;
        dllist_print(head);
        del_node = dllist_find(head, val);
    }
    printf("[%s] Number of nodes freed: %d\n", __func__, num_free);
    //Head might have changed
    return head;
}

node_dl_t*
dllist_find
(
    node_dl_t* head, 
    int val
)
{
    while (head) {
        if (head->val == val) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void
dllist_print
(
    node_dl_t* head
)
{
    if (!head) {
        printf("Empty List\n");
    }
    printf("Node:[\t");
    while(head) {
        //printf(" %d (%p, %p) -> <-", head->val, head->prev, head->next);
        printf(" %d <->", head->val);
        head = head->next;
    }
    printf("]\n");
}


bool_t 
dll_insert_front
(
    dll_t *dll,
    int val
)
{
    node_dl_t* new_node;
    if (!dll) {
        printf("[%s] Invalid input\n", __func__);
        return FALSE;
    }
    if (FALSE == dll_alloc_node(&new_node, val)) {
        return FALSE;
    }
    if (dll->head) {
        dll->head->prev = new_node;
    } else {
        dll->tail = new_node;
    }
    new_node->next = dll->head;
    dll->head = new_node;
    dll->num++;
    return TRUE;
}

bool_t 
dll_insert_back
(
    dll_t *dll,
    int val
)
{
    node_dl_t* new_node;
    if (!dll) {
        printf("[%s] Invalid input\n", __func__);
        return FALSE;
    }
    
    if (FALSE == dll_alloc_node(&new_node, val)) {
        return FALSE;
    }

    if (dll->tail) {
        dll->tail->next = new_node;
    } else {
        dll->head = new_node;
    }
    new_node->prev = dll->tail;
    dll->tail = new_node;
    dll->num++;
    return TRUE;
}

bool_t 
dll_construct
(
    dll_t **dll
)
{
    *dll = (dll_t *)calloc(1, sizeof(dll_t));
    if (*dll) {
        return FALSE;
    }
    return TRUE;
}

void
dll_destruct
(
    dll_t **dll
)
{
    if (*dll) {
        dllist_destruct((*dll)->head);
        free(*dll);
        *dll = NULL;
    }
}

void
dll_display
(
    dll_t *dll
)
{
    if (dll) {
        printf("[%s] Head: %p\tTail: %p\n", __func__, dll->head, dll->tail);
        dllist_print(dll->head);
        printf("[%s] Total number of nodes: %d\n", __func__, dll->num);
    }
}

bool_t 
dll_insert_at_n
(
    dll_t *dll, 
    int val, 
    int n
)
{
    node_dl_t *curr, *prev, *new_node;
    if (!dll || (n < 0)) {
        printf("[%s] Invalid input\n", __func__);
        return FALSE;
    }

    if (n == 0) {
        return dll_insert_front(dll, val);
    }
    
    curr = dll->head; prev = NULL;
    while (curr && (n > 0)) {
        prev = curr;
        curr = curr->next;
        n--;
    }

    if (!curr && (n != 0)) {
        printf("[%s] Input n is too large\n", __func__);
        return FALSE;
    }
    
    if (FALSE == dll_alloc_node(&new_node, val)) { return FALSE;}

    prev->next = new_node;
    new_node->prev = prev;
    new_node->next = curr;
    
    if (curr) {
        curr->prev = new_node;
    } else {
        dll->tail = new_node;
    }
    
    dll->num++;
    return TRUE;
}

int
dll_get_count
(
    dll_t* dll
)
{
    return dll ? dll->num : 0;
}

void test_dll() {
    node_dl_t* head;
    head = dllist_add_front(NULL, 5);
    head = dllist_add_front(head, 5);
    head = dllist_add_front(head, 6);
    head = dllist_add_front(head, 7);
    head = dllist_add_back(head, 5);
    dllist_print(head);
    printf("Delete node\n");
    head = dllist_del(head, 5);
    printf("Post delete node\n");
    dllist_print(head);
    dllist_destruct(head);
}

void test_dll_insert() {
    dll_t *dll;

    dll_construct(&dll);
    
    dll_insert_front(dll, 1);
    dll_insert_front(dll, 2);
    dll_insert_front(dll, 3);
    dll_insert_front(dll, 4);
    dll_insert_front(dll, 5);
    dll_insert_back(dll, 0);
    dll_insert_back(dll, -1);
    dll_insert_back(dll, -2);

    printf("[%s] Insert at n test start\n", __func__);

    dll_insert_at_n(dll, 20, -1);
    dll_display(dll);
    dll_insert_at_n(dll, 20, 0);
    dll_display(dll);
    dll_insert_at_n(dll, 21, 1);
    dll_display(dll);
    dll_insert_at_n(dll, 22, dll_get_count(dll));
    dll_display(dll);

    dll_insert_at_n(dll, 22, dll_get_count(dll)+1);
    dll_display(dll);

    dll_destruct(&dll);
}

int main(void) {
    printf("[%s] Begin\n", __func__);
    //test_dll();    
    test_dll_insert();
    printf("[%s] End\n", __func__);
    return 0;
}