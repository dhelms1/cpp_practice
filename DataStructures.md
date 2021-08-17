# Linked List

- A **linked list** is a sequence of nodes, with each node containing a pointer to its successor

  - Note: the las node in the list points to *NULL*.

- Time complexity of a linked list:

  | Type          | Insert | Find | Remove |
  | ------------- | ------ | ---- | ------ |
  | Unsorted List | O(1)   | O(n) | O(n)   |
  | Sorted List   | O(n)   | O(n) | O(n)   |

- From CSCI 211: Project 2/3, Lab 4/5



## Unsorted List

```cpp
class ListNode {
public:
  int m_val;
  ListNode *m_next;
  ListNode(int val, ListNode *next = NULL) { m_val = val; m_next = next; }
};

ListNode *insert_at_beginning(ListNode *head, int val) {
  return new ListNode(val, head);
}

ListNode *insert_at_end(ListNode *head, int val) {
  ListNode *node = head;
  if (node == NULL)
    insert_at_beginning(head, val);
  else {
    while(node->m_next != NULL) {
      node = node->m_next;
    }
    ListNode *newNode = new ListNode(val, NULL);
    node->m_next = newNode;
  }
}

void print_list(ListNode *head) {
  ListNode *node = head;
  while(node != NULL) {
    std::cout << node->m_next << " ";
    node = node->m_next;
  }
  std::cout << std::endl;
}

ListNode *find(ListNode *head, int val) {
  ListNode *node = head;
  while (node != NULL) {
    if (node->m_val == val)
      break;
    node = node->m_next;
  }
  return node;
}

ListNode *insert_after(ListNode *head, int_after_val, int new_val) {
  ListNode *node = head;
  if (node == NULL) // empty list
    return insert_at_beginning(head, new_val);
  // find node containing after_val
  node = find(node, after_val);
  if (node == NULL)
    return insert_at_end(head, new_val);
  ListNode *newNode = new ListNode(new_val, node->m_next);
  node ->m_next = NewNode; // assign current pointer to newNode
  return node
}
```



## Sorted List

```cpp
class SortedList {
public:
  SortedList();
  void insert(int value);
  void remove(int value);
  void print();
private:
  class Node {
  public:
    Node(int value, Node *next);
    int m_value;
    Node *m_next;
  };
  Node *m_head;
};

void SortedList::print() {
  Node *node = m_head;
  while (node != NULL) {
    cout << node->m_value;
    node = node->m_next;
  }
  cout << endl;
}

void SortedList::insert(int value) {
  if (m_head == NULL || value < node->m_value) // empty or less than
    m_head = new Node(value, m_head);
  else {
    Node *node = m_head;
    while (node->m_next != NULL && node->m_next->m_value < value)
      node = node->m_next;
    node->m_next = newNode(value, node->m_next); // node points to new node
  }
}

bool SortedList::remove(int value) {
  bool result = false;
  std::cout << "Removing " << value << std::endl;
  if (m_head != NULL) {
    if (m_head->m_value == value) {
      Node *nodeToDelete = m_head;
      m_head = m_head->m_next;
      delete nodeToDelete;
      result = true;
    }
    else {
    	Node *node = m_head;
    	while (node->m_next != NULL && node->m_next->m_value < value)
      	node = node->m_next;
    	if (node->m_next != NULL && node->m_next->m_value == value) {
        Node *nodeToDelete = node->m_next;
        node->m_next = NodeToDelete->m_next;
        delete NodeToDelete;
        result = true;
      }
  	}
  }
  return result;
}
```





# Stack

- A **stack** is a *last in, first out (LIFO)* data structure, where there is a top down approach.
- A stack is is usually implemented as a list, with additions and removals taking place at one end of the list
  - **Static stacks** - these are fixed sizes, implemented as an *array*.
  - **Dynamic stacks** - these are variable size and implemented as *linked lists*.
- Stacks have the following time complexities:

| Type        | Insert | Find  | Remove |
| ----------- | ------ | ----- | ------ |
| Array       | O(1)   | *N/A* | O(1)   |
| Linked List | O(1)   | *N/A* | O(1)   |

- From CSCI 211: Project 4, Lab 6



## Array

```cpp
class Stack {
private:
  int *m_array;
  int m_stackSize, m_top;
public:
  Stack(int stackSize);
  bool push(int value);
  bool pop(int &value);
  bool isFull();
  bool isEmpty();
};

int const EMPTY = -1;

Stack::Stack(int stackSize) {
  m_stackSize = stackSize;
  m_top = EMPTY;
  m_array = (int *)malloc(stackSize*sizeof(int));
}

bool Stack::push(int value) {
  bool result = false;
  if(!isFull()) {
    (isEmpty() ? m_top = 0 : m_top++);
    m_array[m_top] - value;
    result = true;
  }
  std::cout << "push(" << value << ") : " << (result ? "Success." : "Failed.") << std::endl;
}

bool Stack::pop(int &value) {
  bool result = false;
  if(!isEmpty()) {
    value = m_array[m_top];
    m_top--;
    result = true;
    std::cout << "pop(): output value " << value << " : " << (result ? "Success." : "Failed.") << std::endl;
  }
}

bool Stack::isFull() {
  assert(m_top < m_stackSize);
  return (m_top == m_stackSize - 1);
}

bool Stack::isEmpty() {
  return (m_top == EMPTY);
}
```



## Linked List

- Since we are using a linked list, no predetermined size and can push all we want and pop until head is *NULL*.

```cpp
class Stack {
public: 
  Stack();
  void push(int value);
  bool pop(int &value);
  bool isEmpty();
private:
  class Node {
  public:
    Node(int value, Node *next) { m_value = value; m_next = next; }
    int m_value;
    Node *m_next;
  };
  Node *m_head; // define outside of node class
};

Stack::Stack() { m_head = NULL; }
bool Stack::isEmpty() { return (m_head == NULL); }
void Stack::push(int value) { m_head = new Node(value, m_head); }
```





# Queue

- A **queue** is a *first in, first out (FIFO)* data structure, similar to waiting in a line.
- Queue's have the following time complexities:

| Type        | Insert | Find  | Remove |
| ----------- | ------ | ----- | ------ |
| Array       | O(1)   | *N/A* | O(1)   |
| Linked List | O(1)   | *N/A* | O(1)   |

- From CSCI 211: Project 5, Lab 8



## Array

- Imagine this as a circle of array values that loop (when end of array is reached, go back to beginning).
- Note: the **%** operator is since we want to loop back to first position after reaching end.

```cpp
class Queue {
public:
  Queue(int stackSize);
  bool enqueue(int value);
  bool dequeue(int &value);
  void print();
  bool isFull();
  bool isEmpty();
private:
  int *m_array;
  int m_count, m_size, m_first, m_last;
};

Queue::Queue(int stackSize) {
  m_size = stackSize;
  m_first, m_last, m_count = 0;
  m_array = (int *) malloc(stackSize*sizeof(int));
}

void Queue::print() {
  if(!isEmpty()) {
    for (int pos = m_first; (postion % m_size) != (m_lst % m_size); pos++)
      std::cout << m_array[pos % m_size] << " ";
    std::cout << std::endl;
  }
}

bool Queue::isEmpty() {
  assert(m_count <= m_size && m_count >= 0);
  return (m_count == 0);
}

bool Queue::isFull() {
  assert(m_count <= m_size && m_count >= 0);
  return (m_count == m_size);
}

bool Queue::enqueue(int value) {
  bool result = false;
  if(!isFull()) {
    m_array[m_last] = value;
    m_last = (m_last + 1) % m_size;
    m_count++;
    result = true;
  }
  return result;
}

bool Queue::dequeue(int value) {
  bool result = false;
  if(!isFull()) {
    value_out = m_array[m_first];
    m_first = (m_first + 1) % m_size;
    m_count--;
    result = true;
  }
  return result;
}
```



## Linked List

- For a linked list implementation of a queue, we remove from front and insert at the end of the list.

```cpp
class Queue {
public:
  Queue();
  bool enqueue(int value);
  bool dequeue(int &value_out);
  void print();
  bool isEmpty();
private:
  class Node {
  public:
    Node(int value, Node *next) { m_value = value; m_next = next; }
    int m_value;
    Node *m_next;
  };
  Node *m_head; // part of Queue class
};

Queue::Queue() { m_head = NULL; }
bool Queue::isEmpty() { return (m_head == NULL); }

void Queue::print() {
  Node *node = m_head;
  while (node != NULL) {
    std::cout << node->m_value << " ";
    node = node->m_next;
  }
  std::cout << std::endl;
}

bool Queue::enqueue(int value) {
  bool result = false;
  if (isEmpty()) {
    m_head = new Node(value, NULL);
    result = true;
  }
  else {
    Node *node = m_head;
    while (node->m_next != NULL)
      node = node->m_next;
    node->m_next = new Node(value, NULL);
    result = true;
  }
  return result;
}

bool Queue::dequeue(int &value_out) {
  bool result = false;
  if (!isEmpty()) {
    value_out = m_head->m_value;
    Node *temp = m_head->m_next;
    delete m_head;
    m_head = temp;
    result = true;
  }
  return result;
}
```





# Priority Queue

- A **priority queue** is a data structure in which we use a *LIFO* order, but go through priorities (level) in that given order.
- Priority Queue's have the following time complexities:

| Type        | Insert | Find  | Remove |
| ----------- | ------ | ----- | ------ |
| Array       | O(n)   | *N/A* | O(n)   |
| Linked List | O(n)   | *N/A* | O(n)   |

- From CSCI 211: Project 5, Lab 8



## Linked List

- Note: since they are placed in order, when we *dequeue* we only have to take the m_head value (then set the new m_head).

```cpp
class Pqueue
{
public:
  Pqueue();
  void enqueue(int priority, string *value);
  bool dequeue (int *priority_out, string **value_out);
  void print();
  bool isEmpty();
private:
  class Node {
  public:
    int m_priority;
    string *m_value;
    Node *m_next;
    Node(int priority, string *value, Node *next) { m_priority = priority; m_value = value; m_next = next; }
  };
  Node *m_head; // part of Queue class
};

Pqueue::Pqueue() { m_head = NULL; }
bool Pqueue::isEmpty() { return (m_head == NULL) }

void Pqueue::enqueue(int priority, string *value) {
  if (isEmpty())
    m_head = new Node(priority, value, NULL);
  else {
    // Priority is less than m_head (insert before)
    if (priority < m_head->m_priority)
      m_head = new Node(priority, value, m_head);
    // Priority greater than m_head (inset after)
    else {
      Node *ptr = m_head;
      while (ptr->m_next != NULL && ptr->m_next->m_priority <= priority)
        ptr = ptr->m_next;
      ptr->m_next = new Node(priority, value, ptr->m_next);
    }
  }
}

bool Pqueue::dequeue(int *priority_out, string **value_out) {
  bool result = false;
  if(!isEmpty()) {
    *value_out = m_head->m_value; // have to dereference once
    *priority_out = m_head->m_priority;
    Node *temp = m_head->m_next;
    delete m_head;
    m_head = temp;
    result = true;
  }
  return result;
}

void Pqueue::print() {
  Node *ptr = m_head;
  std::cout << "Pqueue contents:" << std::endl;
  while (ptr != NULL) {
		std::cout << ptr->m_value << "(Priority " << ptr->m_priority << "), ";
    ptr = ptr->m_next;
  }
  std::cout << std::endl;
}

enum Priority {
  IMMEDIATE, // 0
  URGENT,    // 1
  ROUTINE    // 2
};

int main() {
  Pqueue myPqueue;
  myPqueue.enqueue(ROUTINE, new string("Patient 1: Broken arm"));
  myPqueue.enqueue(IMMEDIATE, new string("Patient 2: Chest pain"));
  myPqueue.enqueue(URGENT, new string("Patient 3: Severe back pain"));
  myPqueue.print();
}
```





# Binary Search Tree (ADT)

- The **ADT BST** is when no node can have more than two children (degree is either 0, 1, or 2).
- The **root** is the parent node, which can have a left/right **child** node.
- The root have a **node level** of 1, and this increases as you go down each level of the tree.
- The **height** is the number of nodes on the longest path.
  - Note: a **full tree** is when each level has two child nodes (no empty spots on tree).
- We have the following time complexities for a BST:

| Type       | Insert   | Find     | Remove   |
| ---------- | -------- | -------- | -------- |
| Best Case  | O(log n) | O(log n) | O(log n) |
| Worst Case | O(n)     | O(n)     | O(n)     |

- Note: when the BST is **balanced**, we have the following time complexities

| Type       | Insert   | Find     | Remove   |
| ---------- | -------- | -------- | -------- |
| Best Case  | O(log n) | O(log n) | O(log n) |
| Worst Case | O(log n) | O(log n) | O(log n) |

- From CSCI 211: Project 7



## Linked List

```cpp
#include <queue.h>

class Book { // Parent class
...
}

typedef enum {
  PRE_ORDER;
  POST_ORDER;
  IN_ORDER;
  BREADTH_FIRST;
}; TraversalOrder;

class Books {
  public:
    Books() { m_root = NULL; }
    ~Books() {};
    void insert (Book *book)
    bool find(string key, Book *&book);
    void print();
  private:
    class Node {
      public:
        Node(Book *book) { m_book = book; m_left = NULL; m_right = NULL; }
        Book *m_book;
        Node *m_left;
        Node *m_right;
    };
    void insert(Book *book, Node *root); // Declare private version of insert
    bool find(string key, Book *&book, Node *root); // Declare private version of find
    void print(Node *);
    Node *m_root;
};


```

