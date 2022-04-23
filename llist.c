#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

typedef struct node_s {
    int val;
    struct node_s *next;
} node_t;

typedef struct stack_node_s {
    void *ptr;
    struct stack_node_s* next;
} stack_node_t;

typedef unsigned char bool_t;


//STACK PROTOTYPES
bool_t stack_new_node(stack_node_t** n, void *ptr);
bool_t stack_push(stack_node_t** s, void *ptr);
bool_t stack_pop(stack_node_t** s, void **out_ptr);
bool_t stack_empty(stack_node_t** s);
void stack_destroy(stack_node_t **s);

//LL PROTOTYPES
bool_t ll_alloc_node(node_t **new_node, int val);
node_t* ll_create(int *input, int n);
void ll_destroy(node_t **in_head);
void ll_print(node_t *head);
int ll_get_size(node_t *head);
bool_t ll_insert_front(node_t **head, int val);
bool_t ll_insert_at_nth(node_t **head, int n, int val);
bool_t ll_insert_back(node_t **head, int val);
bool_t ll_pop_front(node_t **head, int *out_val);
bool_t ll_delete_nth(node_t **head, int n, int *outval);
bool_t ll_delete_last(node_t **head, int *out_val);
bool_t ll_reverse_data(node_t **head);
bool_t ll_reverse_list(node_t **head);
bool_t ll_search(node_t *head, int val);
bool_t ll_sorted_insert(node_t **head, int val);
void ll_delete_alternate(node_t *head);
node_t* ll_get_middle(node_t* head);
void ll_reverse_in_groups(node_t* head, int m);
void ll_reverse_n(node_t* head, int n);
node_t* ll_get_kth(node_t* head, int k);
bool_t ll_move_n_to_front(node_t** head, int n);
bool_t ll_check_palindrome(node_t* head);
void ll_fold(node_t* head);

// STACK DEFINITIONS 
bool_t 
stack_new_node
(
    stack_node_t** n, 
    void *ptr
)
{
    *n = (stack_node_t*)calloc(1, sizeof(stack_node_t));
    if (*n == NULL) {
        return FALSE;
    }
    (*n)->ptr = ptr;
    return TRUE;
}

bool_t 
stack_push
(
    stack_node_t** s, 
    void *ptr
) {
    stack_node_t* new_node;
    if (FALSE == stack_new_node(&new_node, ptr)) {
        return FALSE;
    }

    if (*s) {
        new_node->next = *s;
        *s = new_node;
    } else {
        *s = new_node;
    }
    return TRUE;
}

bool_t 
stack_pop
(
    stack_node_t** s, 
    void **out_ptr
)
{
    if (*s) {
        stack_node_t *del_node = *s;
        *out_ptr = (*s)->ptr;
        *s = (*s)->next;
        free(del_node);
        return TRUE;
    }
    return FALSE;
}

bool_t stack_empty(stack_node_t** s) {
    if (*s) {
        return TRUE;
    }
    return FALSE;
}

void 
stack_destroy
(
    stack_node_t **s
)
{
    stack_node_t *curr = *s;
    while(curr) {
        stack_node_t *del_node = curr;
        curr = curr->next;
        free(del_node);
    }
}

// LL DEFINITIONS
/*
* Allocates node and set the value to val
* and next to NULL.
* Returns FALSE failure else TRUE
*/
bool_t
ll_alloc_node
(
    node_t**new_node,
    int val
)
{
    *new_node = (node_t*)calloc(1, sizeof(node_t));
    if (!*new_node) {
        return FALSE;
    }
    (*new_node)->val = val;
    return TRUE;
}

node_t* 
ll_create
(
    int *input, 
    int n
)
{
    node_t *head = NULL, *curr, *prev = NULL;
    int i = 0;
    if (!input || n <= 0 || n > 1000) {
        return NULL;
    }
    
    while(i < n) {
        if(FALSE == ll_alloc_node(&curr, input[i])) {
            ll_destroy(&head);
            return NULL;
        }
        if (!head) {
            head = curr;
        } else {
            prev->next = curr;
        }
        prev = curr;
        i++;
    }
    
    return head;
}

void
ll_destroy
(
    node_t** in_head
)
{
    node_t* head = *in_head;
    while(head) {
        node_t* next = head->next;
        free(head);
        head = next;
    }
    *in_head = NULL;
}

void
ll_print
(
    node_t* head
)
{
    if (!head) {
        printf("Empty List\n");
    }
    printf("Node:[\t");
    while(head) {
        printf("%d (%p) -> ", head->val, head->next);
        head = head->next;
    }
    printf(" NULL ]\n");
}

int
ll_get_size
(
    node_t* head
)
{
    int n = 0;
    while(head) {
        head = head->next;
        n++;
    }
    return n;
}

bool_t
ll_insert_front
(
    node_t** head, 
    int val
)
{

    node_t* new_node;
    if(FALSE == ll_alloc_node(&new_node, val)) {
        return FALSE;
    }
    new_node->next = *head;
    *head = new_node;
    return TRUE;
}

/*
* Function to insert at nth position
* starting from 0 to n == size of list
* n == 0 -> head of list
* n == size -> last node in list
*/
bool_t 
ll_insert_at_nth
(
    node_t**head,
    int n,
    int val
)
{
    node_t* curr = *head, *prev = NULL, *new_node;
    if (n < 0) {
        return FALSE;
    }

    if (n == 0) {
        if (FALSE == ll_alloc_node(&new_node, val)) {
            return FALSE;
        }
        new_node->next = *head;
        *head = new_node;
        return TRUE;
    } else {
        int index = 0;
        //keep walking till we reach nth node
        //or end of list
        while(curr && (index < n)) {
            prev = curr;
            curr = curr->next;
            index++;
        }

        if (index == n) {
            if (FALSE == ll_alloc_node(&new_node, val)) {
                return FALSE;
            }
            prev->next = new_node;
            new_node->next = curr;
            return TRUE;            
        }
    }
    return FALSE;
}

bool_t
ll_insert_back
(
    node_t** head, 
    int val
)
{
    node_t *curr = *head, *new_node;
    if (FALSE == ll_alloc_node(&new_node, val)) {
        return FALSE;
    }

    if (!curr) {
        *head = new_node;
    } else {
        while(curr->next) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    return TRUE;
}

bool_t 
ll_pop_front
(
    node_t **head, 
    int *out_val
)
{
    if (*head) {
        node_t *del_node = *head;
        *head = (*head)->next;
        if (out_val) {
            *out_val = del_node->val;
        }
        free(del_node);
        return TRUE;
    }
    return FALSE;
}

bool_t 
ll_delete_nth
(
    node_t **head, 
    int n, 
    int *out_val
)
{
    node_t *del_node, *curr, *prev = NULL;
    if (n <=0) {
        return FALSE;
    }

    if (n == 1) {
        del_node = *head;
        *head = (*head)->next;
        if (out_val) {
            *out_val = del_node->val;
        }
        free(del_node);
        return TRUE;
    } else {
        curr = *head;
        while (curr && --n) {
            prev = curr;
            curr = curr->next;
        }

        if (!n && curr) {
            prev->next = curr->next;
            if (out_val) {
                *out_val = curr->val;
            }
            free(curr);
            return TRUE;
        }
    }
    return FALSE;
}

bool_t 
ll_delete_last
(
    node_t **head,
    int *out_val
)
{
    node_t *curr = *head, *prev = NULL;
    if (*head) {
        while(curr->next) {
            prev = curr;
            curr = curr->next;
        }

        if (!prev) {
            *head = NULL;
        } else {
            prev->next = NULL;
        }

        if (out_val) {
            *out_val = curr->val;
        }
        free(curr);
        return TRUE;
    }
    return FALSE;
}

bool_t 
ll_reverse_data
(
    node_t **head
)
{
    stack_node_t *st = NULL;
    node_t *curr = *head;
    int n = 0;

    if (curr) {
        while(curr) {
            if (FALSE == stack_push(&st, (void*)curr)) {
                stack_destroy(&st);
                return FALSE;
            }
            curr = curr->next;
            n++;
        }

        if (n == 1) {
            return TRUE;
        }

        n = n/2;
        curr = *head;
        while(n) {
            int val = curr->val;
            node_t *ptr;
            stack_pop(&st, (void**)&ptr);
            curr->val = ptr->val;
            ptr->val = val;
            curr = curr->next;
            n--;
        }

        stack_destroy(&st);
        return TRUE;
    }
    return FALSE;
}

bool_t 
ll_reverse_list
(
    node_t **head
)
{
    node_t *curr = *head, *prev = NULL;
    if (!curr) {
        return FALSE;
    }

    if (!curr->next) {
        return TRUE;
    }

    while(curr) {
        node_t* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
    return TRUE;
}

bool_t
ll_search
(
    node_t *head,
    int val
)
{
    node_t *curr = head;
    if (head == NULL) {
        return FALSE;
    }

    while(curr && (curr->val != val)) {
        curr = curr->next;
    }

    if (curr) {
        return TRUE;
    }
    return FALSE;
}

bool_t 
ll_sorted_insert
(
    node_t **head,
    int val
)
{
    node_t *new_node, *curr = *head, *prev = NULL;
    if (FALSE == ll_alloc_node(&new_node, val)) {
        return FALSE;
    }

    while (curr && (curr->val < val)) {
        prev = curr;
        curr = curr->next;
    }

    if (!prev) {
        *head = new_node;
    } else {
        prev->next = new_node;    
    }
    new_node->next = curr;
    return TRUE;
}

void 
ll_delete_alternate
(
    node_t *head
)
{
    node_t *curr = head;
    while(curr) {
        if (curr->next) {
            node_t *tmp = curr->next;
            if (tmp) {
                curr->next = tmp->next;
                free(tmp);
            }
            curr = curr->next;
            continue;
        }
        break;
    }
}

node_t* 
ll_get_middle
(
    node_t* head
) {
    node_t *sp = head, *fp = head;
    if (sp == NULL || sp->next == NULL) {
        return sp;
    }

    while (fp && fp->next) {
        fp = fp->next->next;
        if (fp) {
            sp = sp->next;
        }
    }

    return sp;
}

void 
ll_reverse_in_groups
(
    node_t* head, 
    int m
)
{
    node_t *curr = head;
    int cnt = m;
    printf("[%s] Begin\n", __func__);
    if (!curr || (curr->next == NULL) || (m <= 1)) {
        printf("[%s] Invalid input\n", __func__);
        return;
    }

    ll_reverse_n(curr, m);
    ll_print(head);
    while (curr) {
        if (!cnt) {
            cnt = 2;
            ll_reverse_n(curr, m);
            ll_print(head);
        }
        cnt--;
        curr = curr->next;
    }
    printf("[%s] End\n", __func__);
}

void 
ll_reverse_n
(
    node_t* head, 
    int n
)
{
    stack_node_t *st = NULL;
    node_t *curr = head;
    int cnt = n;

    if (!curr || !curr->next || (cnt <= 1)) {
        printf("[%s] Invalid input\n", __func__);
        return;
    }

    while(curr && (cnt > 0)) {
        stack_push(&st, curr);
        cnt--;
        curr = curr->next;
    }

    //if list is smaller than cnt
    if (!curr && (cnt != 0)) {
        printf("[%s] List smaller than n: %d\n", __func__, n);
        stack_destroy(&st);
        return;
    }

    cnt = n/2;
    curr = head;
    while(cnt) {
        int val = curr->val;
        node_t* ptr;
        stack_pop(&st, (void**)&ptr);
        curr->val = ptr->val;
        ptr->val = val;
        curr = curr->next;
        cnt--;
    }
    stack_destroy(&st);
}

node_t* 
ll_get_kth
(
    node_t* head, 
    int k
)
{
    node_t* curr = head;
    if (!curr || k < 1) {
        return NULL;
    }

    while (curr && (k > 1)) {
        curr = curr->next;
        k--;
    }

    if (!curr) {
        return NULL;
    }

    while(curr->next) {
        curr = curr->next;
        head = head->next;
    }

    return head;
}

bool_t
ll_move_n_to_front
(
    node_t** head, 
    int n
) {
    node_t *curr = *head, *tmp = *head, *prev = NULL;
    if (!curr || (n < 1)) {
        return FALSE;
    }

    while(curr && (n > 1)) {
        curr = curr->next;
        n--;
    }

    if (!curr) {
        return FALSE;
    }

    while (curr->next) {
        prev = tmp;
        tmp = tmp->next;
        curr = curr->next;
    }

    if (prev) {
        prev->next = NULL;
        curr->next = *head;
        *head = tmp;
    }
    return TRUE;
}

bool_t 
ll_check_palindrome
(
    node_t* head
)
{
    int size = ll_get_size(head), i = 0, *data;
    if (size <= 1) {
        return FALSE;
    }

    data = (int*)calloc(size, sizeof(int));
    while(head) {
        data[i++] = head->val;
        head = head->next;
    }

    for(i = 0; i < size/2; i++) {
        if (data[i] != data[size-i-1]) {
            free(data);
            return FALSE;
        }
    }

    free(data);
    return TRUE;
}

void 
ll_fold
(
    node_t* head
)
{
    node_t *f = head, *s, *t1, *t2;
    t1 = ll_get_middle(head);
    if (!t1 || (f == t1)) {
        printf("[%s] No second half. Cannot fold\n", __func__);
        return;
    }
    
    //Separate first and second halves.
    s = t1->next;
    t1->next = NULL;
    
    ll_reverse_list(&s);
    
    //ll_print(f);
    //ll_print(s);

    while(f && s) {
        t1 = f->next; t2 = s->next;
        f->next = s;
        s->next = t1;
        f = t1;
        s = t2;
    }
}

void test_ll(void) {
    int input[5] = {1,2,3,4,5}, n = 5, val;
    node_t* head, *tmp;

    head = ll_create(input, n);
    ll_print(head);
    printf("[%s] Size of list after create: %d\n", __func__, ll_get_size(head));
    ll_insert_front(&head, 0);
    ll_print(head);
    printf("[%s] Size of list after insert front: %d\n", __func__, ll_get_size(head));
    ll_insert_at_nth(&head, -1, 10);
    ll_print(head);

    n = 0;
    val = 10;
    if (TRUE == ll_insert_at_nth(&head, n, val)) {
        printf("[%s] Inserted at %d at %d\n", __func__, val, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to insert at %d at %d\n", __func__, val, n);
    }
    n = 4;
    val = 11;
    if (TRUE == ll_insert_at_nth(&head, n, val)) {
        printf("[%s] Inserted at %d at %d\n", __func__, val, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to insert at %d at %d\n", __func__, val, n);
    }
    n = ll_get_size(head);
    val = 12;
    if (TRUE == ll_insert_at_nth(&head, n, val)) {
        printf("[%s] Inserted at %d at %d\n", __func__, val, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to insert at %d at %d\n", __func__, val, n);
    }
    n = 100;
    val = 13;
    if (TRUE == ll_insert_at_nth(&head, n, val)) {
        printf("[%s] Inserted at %d at %d\n", __func__, val, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to insert at %d at %d\n", __func__, val, n);
    }

    val = 100;
    if (TRUE == ll_insert_back(&head, val)) {
        printf("[%s] Inserted at %d at end\n", __func__, val);
        ll_print(head);
    } else {
        printf("[%s] Failed to insert at %d at end\n", __func__, val);
    }

    tmp = NULL;
    val = 101;
    if (TRUE == ll_insert_back(&tmp, val)) {
        printf("[%s] Inserted at %d at end\n", __func__, val);
        ll_print(tmp);
        ll_destroy(&tmp);
    } else {
        printf("[%s] Failed to insert at %d at end\n", __func__, val);
    }


    n = -1;
    if (TRUE == ll_delete_nth(&head, n, NULL)) {
        printf("[%s] Deleted at %d\n", __func__, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to delete at %d\n", __func__, n);
    }

    n = 1;
    if (TRUE == ll_delete_nth(&head, n, NULL)) {
        printf("[%s] Deleted at %d\n", __func__, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to delete at %d\n", __func__, n);
    }

    n = ll_get_size(head);
    if (TRUE == ll_delete_nth(&head, n, NULL)) {
        printf("[%s] Deleted at %d\n", __func__, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to delete at %d\n", __func__, n);
    }

    n = ll_get_size(head)+1;
    if (TRUE == ll_delete_nth(&head, n, NULL)) {
        printf("[%s] Deleted at %d\n", __func__, n);
        ll_print(head);
    } else {
        printf("[%s] Failed to delete at %d\n", __func__, n);
    }

    if (TRUE == ll_reverse_data(&head)) {
        printf("[%s] Reversed data in list\n", __func__);
        ll_print(head);
    } else {
        printf("[%s] Failed to reverse list\n", __func__);
    }

    val = 11;
    if (TRUE == ll_search(head, val)) {
        printf("[%s] Found %d in list\n", __func__, val);
    } else { 
        printf("[%s] Did not find %d in list\n", __func__, val);
    }

    val = 102;
    if (TRUE == ll_search(head, val)) {
        printf("[%s] Found %d in list\n", __func__, val);
    } else { 
        printf("[%s] Did not find %d in list\n", __func__, val);
    }

    while(TRUE == ll_delete_last(&head, &val)) {
        printf("[%s] Deleted: %d\n", __func__, val);
    }

    while(TRUE == ll_pop_front(&head, &val)) {
        printf("[%s] Popped: %d\n", __func__, val);
    }

    ll_destroy(&head);
    ll_sorted_insert(&head, 5);
    ll_sorted_insert(&head, 9);
    ll_sorted_insert(&head, 1);
    ll_sorted_insert(&head, 4);
    ll_sorted_insert(&head, 15);
    ll_sorted_insert(&head, 16);
    ll_print(head);
    tmp = ll_get_middle(head);
    printf("[%s] Middle is : %p and %d\n", __func__, tmp, tmp ? tmp->val : -9999);
    ll_delete_alternate(head);
    ll_print(head);
    tmp = ll_get_middle(head);
    printf("[%s] Middle is : %p and %d\n", __func__, tmp, tmp ? tmp->val : -9999);
    ll_delete_alternate(head);
    ll_print(head);
    tmp = ll_get_middle(head);
    printf("[%s] Middle is : %p and %d\n", __func__, tmp, tmp ? tmp->val : -9999);
    ll_delete_alternate(head);
    ll_print(head);
    tmp = ll_get_middle(head);
    printf("[%s] Middle is : %p and %d\n", __func__, tmp, tmp ? tmp->val : -9999);
    ll_delete_alternate(head);
    ll_print(head);
    tmp = ll_get_middle(head);
    printf("[%s] Middle is : %p and %d\n", __func__, tmp, tmp ? tmp->val : -9999);
    ll_destroy(&head);
}

void test_ll_reverse_groups() {
    int input[5] = {1,2,3,4,5}, n = 5;
    int palinput[5] = {1,2,3,2,1};
    node_t* head, *tmp;

    head = ll_create(input, n);
    n = 6;
    ll_print(head);
    ll_reverse_in_groups(head, n);
    printf("[%s] After reverse in groups of %d \n", __func__, n);
    ll_print(head);

    for (n = 0;n <= 6; n++) {
        tmp = ll_get_kth(head, n);
        if (tmp) {
            printf("[%s] %dth node is : %d\n", __func__, n, tmp->val);
        } else {
            printf("[%s] %dth node is invalid\n", __func__, n);
        }
    }

    ll_print(head);
    ll_move_n_to_front(&head, 4);
    ll_print(head);
    if (TRUE == ll_check_palindrome(head)) {
        printf("[%s] list is palindrome\n", __func__);
    } else {
        printf("[%s] list is not palindrome\n", __func__);
    }
    ll_destroy(&head);
    
    n = 5;
    head = ll_create(palinput, n);
    ll_print(head);
    if (TRUE == ll_check_palindrome(head)) {
        printf("[%s] list is palindrome\n", __func__);
    } else {
        printf("[%s] list is not palindrome\n", __func__);
    }
    ll_destroy(&head);
    
    printf("[%s] fold_test\n", __func__);
    n = 5;
    head = ll_create(input, n);
    ll_print(head);
    ll_fold(head);
    ll_print(head);
    ll_destroy(&head);
}

void test_stack(void) {
    stack_node_t *head = NULL;
    node_t node_array[5];
    node_t *out_ptr;

    memset(node_array, 0, 5 * sizeof(node_t));
    node_array[0].val = 1;
    node_array[1].val = 2;
    node_array[2].val = 3;
    node_array[3].val = 4;
    node_array[4].val = 5;
    stack_push(&head, &node_array[0]);
    stack_push(&head, &node_array[1]);
    stack_push(&head, &node_array[2]);
    stack_push(&head, &node_array[3]);
    stack_push(&head, &node_array[4]);

    while(TRUE == stack_pop(&head, (void**)&out_ptr)) {
        printf("[%s] Popped node: %d\n", __func__, out_ptr->val);
    }
}

int 
main
(
    void
)
{
    printf("[%s] Begin\n", __func__);
    //test_ll();
    //test_stack();
    test_ll_reverse_groups();
    printf("[%s] End\n", __func__);
}

