# How-to-Talk-Linked-Lists

July 24, 2020

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Linked lists are the best and simplest example of a dynamic data structure that
uses pointers for its implementation. However, understanding pointers is crucial
to understanding how linked lists work. Linked lists function as an array that
can grow and shrink as needed, from any point in the array.

Linked lists have a few advantages over arrays:
1. Items can be added or removed from the middle of the list
2. There is no need to define an initial size

However, linked lists also have a few disadvantages:
1. There is no "random" access - it is impossible to reach the nth item in the
   array without first iterating over all items up until that item. This means
   we have to start from the beginning of the list and count how many times we
   advance in the list until we get to the desired item.
2. Dynamic memory allocation and pointers are required, which complicates the
   code and increases the risk of memory leaks and segment faults.
3. Linked lists have a much larger overhead over arrays, since linked list items
   are dynamically allocated (which is less efficient in memory usage) and each
   item in the list also must store an additional pointer.
   
What is a linked list?
A linked list is a set of dynamically allocated nodes, arranged in such a way
that each node contains one value and one pointer. The pointer always points to
the next member of the list. If the pointer is NULL, then it is the last node
in the list.

A linked list is held using a local pointer variable which points to the first
item of the list. If that pointer is also NULL, then the list is considered to
be empty.

Iterating over a list
Let's build a function that prints out all the items of a list. To do this, we
need to use a current pointer that will keep track of the node we are currently
printing. After printing the value of the node, we set the current pointer to 
the next node, and print again, until we've reached the end of the list (the
next node is NULL).

Adding an item to the end of the list
To iterate over all the members of the linked list, we use a pointer called 
current. We set it to start from the head and then in each step, we advance the
pointer to the next item in the list, until we reach the last item.

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

The best use cases for linked lists are stacks and queues, which we will now
implement:

Adding an item to the beginning of the list (pushing to the list)
To add to the beginning of the list, we will need to do the following:

1. Create a new item and set its value
2. Link the new item to point to the head of the list
3. Set the head of the list to be our new item

This will effectively create a new head to the list with a new value, and keep
the rest of the list linked to it.

Since we use a function to do this operation, we want to be able to modify the 
head variable. To do this, we must pass a pointer to the pointer variable (a 
double pointer) so we will be able to modify the pointer itself.

void push2head(node_t ** head, int val) {

  node_t * new_node;
  
  new_node = malloc(sizeof(node_t));

  new_node->val = val;
  
  new_node->next = *head;
  
  *head = new_node;
  
}

Removing the first item (popping from the list)
To pop a variable, we will need to reverse this action:

1. Take the next item that the head points to and save it
2. Free the head item
3. Set the head to be the next item that we've stored on the side

Here is the code:

int pop(node_t ** head) {

    int retval = -1;
    
    node_t * next_node = NULL;

    if (*head == NULL) {
    
        return -1;
        
    }

Removing the last item of the list
Removing the last item from a list is very similar to adding it to the end of
the list, but with one big exception - since we have to change one item before
the last item, we actually have to look two items ahead and see if the next 
item is the last one in the list:

int remove_last(node_t * head) {

    int retval = 0;
    
    /* if there is only one item in the list, remove it */
    
    if (head->next == NULL) {
    
        retval = head->val;
        
        free(head);
        
        return retval;
        
    }

    /* get to the last node in the list */
    
    node_t * current = head;
    
    while (current->next->next != NULL) {
    
        current = current->next;
        
    }

    /* now current points to the last item of the list, so let's remove current->next */
    
    retval = current->next->val;
    
    free(current->next);
    
    current->next = NULL;
    
    return retval;

}

Removing a specific item
To remove a specific item from the list, either by its index from the beginning 
of the list or by its value, we will need to go over all the items, continuously
looking ahead to find out if we've reached the node before the item we wish to
remove. This is because we need to change the location to where the previous node points to as well.

Here is the algorithm:

1. Iterate to the node before the node we wish to delete
2. Save the node we wish to delete in a temporary pointer
3. Set the previous node's next pointer to point to the node after the node we wish to delete
4. Delete the node using the temporary pointer

There are a few edge cases we need to take care of, so make sure you understand the code.

int remove_by_index(node_t ** head, int n) {

    int i = 0;
    
    int retval = -1;
    
    node_t * current = *head;
    
    node_t * temp_node = NULL;

    if (n == 0) {
    
        return pop(head);
        
    }

    for (int i = 0; i < n-1; i++) {
    
        if (current->next == NULL) {
        
            return -1;
            
        }
        
        current = current->next;
        
    }

    temp_node = current->next;
    
    retval = temp_node->val;
    
    current->next = temp_node->next;
    
    free(temp_node);

    return retval;

}

Linked Lists

What are the drawbacks of using sequential storage to represent stacks and queues?
One major drawback is that a fixed amount of storage remains allocated to the 
stack or queue even when the structure is actually using a smaller amount or
possibly no storage at all. Further, no more than that fixed amount of storage
may be allocated, thus introducing the possibility of overflow.

Assume that a program uses two stacks implemented in two separate arrays, s1.items
and s2.items. Further, assume that each of these arrays has 100 elements. Then
despite the fact that 200 elements are available for the two stacks, neither can
grow beyond 100 items. Even if the first stack contains only 25 items, the second
cannot contain more than 100.

One solution to this problem is to allocate a single array items of 200 elements.
The first stack occupies items[0], items[1], ..., items[top1], while the second
stack is allocated from the other end of the array, occupying items[199], 
items[198], ..., items[top2]. Thus when one stack is not occupying storage, the 
other stack can use that storage. Of course, two distinct sets of pop, push and 
empty routines are necessary for the two stacks, since one grows by incrementing
top1, while the other grows by decrementing top2.

Unfortunately, although such a scheme allows two stacks to share a commone area,
no such simple solution exists for three or more stacks or even two queues. 
Instead, one must keep track of the tops and bottoms (or fronts and rears) of 
all the structures sharing a single large array. Each time that the growth of one
structure is about to impinge on the storage currently being used by another,
neighboring structures must be shifted within the single array to allow for
growth.

In a sequential representation, the items of a stack or queue are implicitly 
ordered by the sequential order of storage. Thus, if q.items[x] represents an
element of a queue, the next element will be q.items[x+1] (or if x equals 
MAXQUEUE - 1, q.items[0]). Suppose that the items of a stack or a queue were
explicitly ordered, that is, each item contained within itself the address of
the next item. Such an explicit ordering gives rise to a data structure pictured
in Figure 4.2.1, which is known as a linear linked list. Each item in the list 
is called a node and contains two fields, an information field and a next 
address field. The information field holds the actual element on the list. The
next address field contains the address of the next node in the list. Such an
address, which is used to access a particular node, is known as a pointer. The
entire linked list is accessed from an external pointer list that points to
(contains the address of) the first node in the list. (By an "external" pointer,
we mean one that is not included within a node. Rather its value can be accessed
directly referencing a variable). The next address field of the last node in the
list contains a special value, known as a NULL, which is not a valid address.
The null pointer is used to signal the end of a list.

The list with no nodes on it is called the empty list or the null list. The 
value of the external pointer list to such a list is the null pointer. A list
can be initialized to the empty list by the operation list = null.

We now introduce some notation for use in algorithms (but not in C programs).
If p is a pointer to a node, node(p) refers to the node pointed to by p, info(p)
refers to the information portion of that node, and next(p) refers to the next
address portion and is therefore a pointer. Thus, if next(p) is not null, 
info(next(p)) refers to the information portion of the node that follows node(p)
in the list.

Inserting and Removing Nodes from a List

A list is a dynamic data structure. The number of nodes on a list may vary
dramatically as elements are inserted and removed. The dynamic nature of a list
may be contrasted with the static nature of arrays, whose size remains constant.

For example, suppose that we are given a list of integers and we desire to add
the integer 6 to the front of that list. That is, we wish to change the list so
that it appears as in Figure 4.2.2f. The first step is to obtain a node in
which to house the additional integer. If a list is to grow and shrink, there 
must be some mechanism for obtaining empty nodes to be added onto the list.
Note that, unlike an array, a list does come with a presupplied set of storage
locations into which elements can be placed.

Let us assume the existence of a mechanism for obtaining empty nodes. The 
operation 

  p = getnode();
  
obtains an empty node and sets the contents of a variable named p to the address
of that node. The value of p is then a pointer to this newly allocated node.

The next step is to insert the integer 6 into the info portion of the newly
allocated node. This is done by the operation

  info(p) = 6;
  
After setting the info portion of node(p), it is necessary to set the next 
portion of that node. Since node(p) is to be inserted at the front of the list,
the node that follows should be the current first node on the list. Since the
variable list contains the address of that first node, node(p) can be added to
the list by performing the operation

  next(p) = list;
  
The operation places the value of list(which is the address of the first node
on the list) into the next field of node(p).

At this point, p points to the list with the additional item included. However,
since list is an external pointer to the desired list, its value must be 
modified to the address of the new first node of the list. This can be done by
performing the operation
  
  list = p;
  
which changes the value of list to the value of p. This is because p is used 
as an auxiliary variable during the process of modifying the list but its
value is irrelevant to the status of the list before and after the process.
Once the foregoing operations have been performed, the value of p may be 
changed without affecting the list.

##############
Putting all the steps together, we have an algorithm for adding the integer 6
to the front of the list:

  p = getnode();
  
  info(p) = 6;
  
  next(p) = list;
  
  list = p;
  
The algorithm can obviously be generalized so that it adds any object x to the
front of a list list by replacing the operation info(p) = 6 with info(p) = x.
Convince yourself that the algorithm works correctly, even if the list is
initially empty (list == null).

The process of removing the first node of a nonempty list and storing the value
of its info field into a variable x is almost the exact opposite of the process
to add a node to the front of the list. The following operations are performed:

  p = list;
  
  list = next(p);
  
  x = info(p);
  
At this point, the algorithm has accomplished what it was supposed to do: the
first node has been removed from list, and x has been set to the desired value.
However, the algorithm is not yet complete. p still points to the node that was
formerly first on the list. However, that node is currently useless because it
is no longer on the list and its information has been stored in x. (The node
is not considered to be on the list despite the fact that next(p) points to a 
node on the list, since there is no way to reach node(p) from the external
pointer list).

The variable p is used as an auxiliary variable during the process of removing
the first node from the list.

It would be desirable to have some mechanism for making node(p) available for
reuse even if the value of the pointer p is changed. The operation that does 
this is
 
  freenode(p);
  
Once this operation has been performed, it becomes illegal to reference node(p),
since the node is no longer allocated. Since the value of p is a pointer to a
node that has been freed, any reference to that value is also illegal.

However, the node might be reallocated and a pointer to it reassigned to p by
the operation p = getnode(). Note that we say that the node "might be" reallocated,
since the getnode operation returns a pointer to some newly allocated node.
There is no guarantee that this new node is the same as the one that has just
been freed.

Another way of thinking of getnode and freenode is that getnode creates a new
node, whereas freenode destroys a node. Under this view, nodes are not used and
reused but are rather created and destroyed. We shall say more about the two
operations getnode and freenode and about the concepts they represent in a 
moment, but first we make the following interesting observation.

##############
Linked Implementation of Stacks

The operation of adding an element to the front of a linked list is quite 
similar to that of pushing an element onto a stack. In both cases,a new item is
added as the only immediately accessible item in a collection. A stack can be
accessed only through its top element, and a list can be accessed only from the 
pointer to its first element. Similarly, the operation of removing the first
element from a linked list is analogous to popping a stack. In both cases the 
only immediately accessible item of a collection is removed from that 
collection, and the next item becomes immediately accessible.

Thus we have discovered another way of implementing a stack. A stack may be
represented by a linear linked list.The first node of the list is the top of
the stack. If an external pointer s points to such a linked list, the 
opeartion push(s,x) may be implemented by

  p = getnode();
  
  info(p) = x;
  
  next(p) = s;
  
  s = p;
  
The operation empty(s) is merely a test of whether s equals null. The operation
x = pop(s) removes the first node from a nonempty list and signals underflow if
the list is empty.

  if (empty(s)) {
  
    printf("stack overflow");
    
    exit(1);
    
  }
  
  else {
  
    p = s;
    
    s = next(p);
    
    x = info(p);
    
    freenode(p);
    
  } /* end if */
  
The advantage of the list implementation is that all stacks being used by a 
program can share the same available list. When any stack needs a node, it can
obtain it from the single available list. When any stack no longer needs a
node, it returns the node to that same available list. As long as the total 
amount of space needed by all the stacks at any one time is less than the amount
of space initally available to them all, each stack is able to grow and shrink
to any size. No space has been preallocated to any single stack and no stack
is using space that it does not need. Furthermore, other data structures such
as queues may also share the same set of nodes.


##############
getnode and freenode Operations

Assume that an external pointer avail points to a list of available nodes. Then
the operation

  p = getnode();
  
is implemented as follows:

  if (avail == null) {
  
    printf("overflow");
    
    exit(1);
    
  }
  
  p = avail;
  
  avail = next(avail);
  
Since the possibility of overflow is accounted for in the getnode operation, it
need not be mentioned in the list implementation of push. If a stack is about
to overflow all available nodes, the statement p = getnode() within the push
operation results in an overflow.

The implementation of freenode(p) is straightforward:

  next(p) = avail;
  
  avail = p;
  
Linked Implementation of Queues

##############
##############
Lists in C

Array Implementation of Lists

How can linear lists be represented in C? Since a list is simply a collection
of nodes, an array of nodes immediately suggests itself. However, the nodes 
cannot be ordered by the array ordereing; each must contain within itself a
pointer to its successor. Thus a group of 500 nodes might be declared as an
array node as follows:

#define NUMNODES 500

struct nodetype {

  int info, next;
  
};

struct nodetype node[NUMNODES];

In this scheme a pointer to a node is represented by an array index. That is,
a pointer is an integer between 0 and NUMNODES - 1 that references a 
particular lement of the array node. The null pointer is represented by the 
integer - 1. Under this implementation, the C expression node[p] is used to
reference node(p), info(p) is referenced by node[p].info, and next(p) is 
referenced by node[p].next. null is represented by -1.

##############
##############

Allocating and Freeing Dynamic Variables

In C a pointer variable to an integer can be created by the declaration

  int *p;
  
  extern char *malloc();
  
  int *pi;
  
  float *pr;
  
  pi = (int *) malloc(sizeof (int));
  
  pr = (float *) malloc(sizeof (float));

I included some posts for reference.

https://github.com/noey2020/How-to-Talk-Queues

https://github.com/noey2020/How-to-Talk-Stacks

https://github.com/noey2020/How-to-Talk-Lists-Stacks-and-Queues

https://github.com/noey2020/How-to-Talk-Linear-Regression

https://github.com/noey2020/How-to-Talk-Statistics-Pattern-Recognition-101

https://github.com/noey2020/How-to-Write-SPI-STM32

https://github.com/noey2020/How-to-Write-SysTick-Handler-for-STM32

https://github.com/noey2020/How-to-Write-Subroutines-in-C-Assembly-STM32

https://github.com/noey2020/How-to-Write-Multitasking-STM32

https://github.com/noey2020/How-to-Generate-Triangular-Wave-STM32-DAC

https://github.com/noey2020/How-to-Generate-Sine-Table-LUT

https://github.com/noey2020/How-to-Illustrate-Multiple-Exceptions-

https://github.com/noey2020/How-to-Blink-LED-using-Standard-Peripheral-Library

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Have fun and happy coding!
