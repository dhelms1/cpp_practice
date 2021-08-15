# Linked List

- A **linked list** is a sequence of nodes, with each node containing a pointer to its successor

  - Note: the las node in the list points to *NULL*.

- Time complexity of a linked list:

  | Type          | Insert | Find | Remove |
  | ------------- | ------ | ---- | ------ |
  | Unsorted List | O(1)   | O(n) | O(n)   |
  | Sorted List   | O(n)   | O(n) | O(n)   |

- From CSCI 211: Porject 2 & 3 should b reviewed.



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



## Array

```cpp
```



## Linked List

```cpp
```





# Queue

