#include <stdio.h>
#include <stdlib.h>

/* declare a linked list node */
typedef struct node {
  int val;
  struct node * next;
} node_t;

void print_list(node_t * head) {
  node_t * current = head;

  while (current != NULL) {
    printf("%d\n", current->val);
    current = current->next;
  }
}

int pop(node_t ** head) {
  int retval = -1;
  node_t * next_node = NULL;

  if (*head == NULL) {
    return -1;
  }

  next_node = (*head)->next;
  retval = (*head)->val;
  free(*head);
  *head = next_node;

  return retval;
}

int remove_by_value(node_t ** head, int val) {
  node_t *previous, *current;

  if (*head == NULL) {
    return -1;
  }

  if ((*head)->val == val) {
    return pop(head);
  }

  previous = current = (*head)->next;
  while (current) {
    if (current->val == val) {
      previous->next = current->next;
      free(current);
      return val;
    }

    previous = current;
    current  = current->next;
  }
  return -1;
}

void delete_list(node_t *head) {
  node_t  *current = head,
    *next = head;

  while (current) {
    next = current->next;
    free(current);
    current = next;
  }
}

void push2end(node_t * head, int val) {
  node_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = malloc(sizeof(node_t));
  current->next->val = val;
  current->next->next = NULL;
}

void push2head(node_t ** head, int val) {
  node_t * new_node;
  new_node = malloc(sizeof(node_t));

  new_node->val = val;
  new_node->next = *head;
  *head = new_node;
}

int main(void) {
  /* create a pointer variable which points to the first item of the list (called head). */
  node_t * test_list = NULL;	/* make sure list is empty so set first pointer or head to NULL */
  test_list = malloc(sizeof(node_t));
  /* check if malloc returned a NULL value or not */
  if (test_list == NULL) {
	 return 1;
  }
  /* set the value, and the next item to be empty. note that we should always check if
     malloc returned a NULL value or not. */
  test_list->val = 1;
  test_list->next = malloc(sizeof(node_t));
  /* to add a variable to the end of the list, we can just continue advancing to the next
     pointer. advance to the last item of the list, until the next variable will be NULL */
  test_list->next->val = 2;
  test_list->next->next = malloc(sizeof(node_t));
  test_list->next->next->val = 3;
  test_list->next->next->next = malloc(sizeof(node_t));
  test_list->next->next->next->val = 4;
  /* this is the last node of the list. set next pointer to NULL */
  test_list->next->next->next->next = NULL;

  remove_by_value(&test_list, 3);
  push2end(test_list, 6);
  push2head(&test_list, 7);

  print_list(test_list);
  delete_list(test_list);

  return EXIT_SUCCESS;
}