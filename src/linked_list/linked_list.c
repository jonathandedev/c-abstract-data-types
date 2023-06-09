/**
 * @file linked_list.c
 * @brief Linked list data type implementation
 * @author Jonathan E
 * @date 07-04-2023
 * 
 * This is an implementation of a linked list data type that can be used to store
 * generic data.
 * This implementation is a singly linked list that makes use of a series of
 * nodes as the underlying collection.
 * The data stored in the nodes is a void pointer which is dynamically allocated
 * to the heap.
*/

#include "linked_list.h"

/**
 * Creates a new linked list using a node structure as the underlying collection.
 * This function uses malloc to allocate memory for the linked list.
 * 
 * @return A pointer to the new linked list, or NULL if the memory allocation
 *         failed.
*/
LinkedList* new_LinkedList() {
  LinkedList* list = malloc(sizeof(LinkedList));
  // If the memory allocation failed, return NULL.
  if (list == NULL) {
    return NULL;
  }

  // Initialise the list.
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

/**
 * Adds an element to the linked list.
 * The data is stored in the node as a void pointer. Note that the data is not
 * copied, but rather the pointer to the data is stored in the node.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @param void*       the data to be stored in the node.
 * @return true if the node was added successfully, false otherwise.
*/
bool LinkedList_add(LinkedList* list, void* data) {
  // If the list is NULL, return false.
  if (list == NULL) {
    return false;
  }

  List_Node* new_node = malloc(sizeof(List_Node));
  // If the memory allocation failed, return false.
  if (new_node == NULL) {
    return false;
  }

  // Initialise the node.
  new_node->data = data;
  new_node->next = NULL;

  // Add the node to the list.
  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }

  list->size++;
  return true;
}

/**
 * Removes a given index from the linked list.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @param int         the index of the node to be removed.
 * @return true if the node was removed successfully, false otherwise.
*/
bool LinkedList_remove(LinkedList* list, int index) {
  // If the list is NULL, return false.
  if (list == NULL) {
    return false;
  }

  // If the index is out of bounds, return false.
  if (index < 0 || index >= list->size) {
    return false;
  }

  // If the index is 0, remove the head.
  if (index == 0) {
    List_Node* new_node = list->head;
    list->head = list->head->next;
    free(new_node);
  } else {
    // Find the node before the node to be removed.
    List_Node* new_node = list->head;
    for (int i = 0; i < index - 1; i++) {
      new_node = new_node->next;
    }

    // Remove the node.
    List_Node* temp = new_node->next;
    new_node->next = new_node->next->next;
    free(temp);
  }

  list->size--;
  return true;
}

/**
 * Gets the data from the linked list at the specified index.
 * The data is stored in the node as a void pointer. Note that the data is not
 * copied, but rather the pointer to the data is returned.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @param int         the index of the node to get the data from.
 * @return the data from the node at the specified index, or NULL if the index
 *         is out of bounds.
*/
void* LinkedList_get(LinkedList* list, int index) {
  // If the list is NULL, return NULL.
  if (list == NULL) {
    return NULL;
  }

  // If the index is out of bounds, return NULL.
  if (index < 0 || index >= list->size) {
    return NULL;
  }

  // Find the node at the specified index.
  List_Node* new_node = list->head;
  for (int i = 0; i < index; i++) {
    new_node = new_node->next;
  }

  return new_node->data;
}

/**
 * Gets the size of the linked list.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @return the size of the linked list, or -1 if the list is NULL.
*/
int LinkedList_size(LinkedList* list) {
  // If the list is NULL, return 0.
  if (list == NULL) {
    return -1;
  }

  return list->size;
}

/**
 * Checks if the linked list is empty.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @return true if the linked list is empty, false otherwise.
*/
bool LinkedList_isEmpty(LinkedList* list) {
  // If the list is NULL, return true.
  if (list == NULL) {
    return true;
  }

  return list->size == 0;
}

/**
 * Checks if the linked list contains the specified data.
 * The data is stored as a node in a series of nodes. Note that the data is not
 * copied, but rather the pointer to the data is copied. When checking if the
 * linked list contains the specified data, the pointer to the data is checked.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @param void*       the data to check for.
 * @return true if the linked list contains the specified data, false otherwise.
*/
bool LinkedList_contains(LinkedList* list, void* data) {
  // If the list is NULL, return false.
  if (list == NULL) {
    return false;
  }

  // Find the node with the specified data.
  List_Node* new_node = list->head;
  while (new_node != NULL) {
    if (new_node->data == data) {
      return true;
    }
    new_node = new_node->next;
  }

  return false;
}

/**
 * Gets the index of the node with the specified data.
 * The data is stored as a node in a series of nodes. Note that the data is not
 * copied, but rather the pointer to the data is copied. When checking if the
 * linked list contains the specified data, the pointer to the data is checked.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @param void*       the data to check for.
 * @return the index of the node with the specified data, or -1 if the data is
 *         not found.
*/
int LinkedList_indexOf(LinkedList* list, void* data) {
  // If the list is NULL, return -1.
  if (list == NULL) {
    return -1;
  }

  // Find the node with the specified data.
  List_Node* new_node = list->head;
  int index = 0;
  while (new_node != NULL) {
    if (new_node->data == data) {
      return index;
    }
    new_node = new_node->next;
    index++;
  }

  return -1;
}

/**
 * Prints the linked list as a list of pointers.
 * 
 * @param LinkedList* the pointer to the linked list.
*/
void LinkedList_print(LinkedList* list) {
  // If the list is NULL, return.
  if (list == NULL) {
    printf("NULL\n");
    return;
  }

  // Print the list.
  printf("[");
  List_Node* new_node = list->head;
  while (new_node != NULL) {
    printf("%p ", new_node->data);
    new_node = new_node->next;
  }
  printf("]\n");
}

/**
 * Prints the linked list as a list of integers.
 * 
 * @param LinkedList* the pointer to the linked list.
*/
void LinkedList_printInt(LinkedList* list) {
  // If the list is NULL, return.
  if (list == NULL) {
    printf("NULL\n");
    return;
  }

  // Print the list.
  printf("[");
  List_Node* new_node = list->head;
  while (new_node != NULL) {
    printf("%d ", *(int*)new_node->data);
    new_node = new_node->next;
  }
  printf("]\n");
}

/**
 * Clears the linked list.
 * 
 * @param LinkedList* the pointer to the linked list.
 * @return true if the nodes were removed successfully, false otherwise.
*/
bool LinkedList_clear(LinkedList* list) {
  // If the list is NULL, return false.
  if (list == NULL) {
    return false;
  }

  // Remove all nodes.
  while (list->head != NULL) {
    List_Node* new_node = list->head;
    list->head = list->head->next;
    free(new_node);
  }

  list->size = 0;
  return true;
}

/**
 * Frees the memory allocated for the linked list.
 * 
 * @param list the pointer to the linked list.
*/
void LinkedList_free(LinkedList* list) {
  // If the list is NULL, return false.
  if (list == NULL) {
    return;
  }

  // Remove all nodes.
  while (list->head != NULL) {
    List_Node* new_node = list->head;
    list->head = list->head->next;
    free(new_node);
  }

  // Deallocate the list.
  free(list);
}
