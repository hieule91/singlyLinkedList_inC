/**
 * CS 2110 - Fall 2017 - Homework #10
 *
 * @author HIEU LE
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return false if
 * the function returns a bool).
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/* The node struct. Has a next pointer, and data. */
/* DO NOT MODIFY THIS STRUCTURE */
/* Only this file should deal with the node struct */
typedef struct _list_node
{
    struct _list_node *next;
    void *data;
} node;

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked list. */
static node *create_node(void *data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void *data)
{
    // UNUSED_PARAMETER(data);
    node *newNode = malloc(sizeof(node));
    if (newNode != NULL) {
  		newNode->next = NULL;
  		newNode->data = data;
  		return newNode;
    }
    free(newNode);
    return NULL;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head and tail to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new list or NULL on failure
  */
list *create_list(void)
{
    list *newList = malloc(sizeof(list));
    if (newList != NULL) {
  		newList->size = 0;
  		newList->head = NULL;
  		newList->tail = NULL;
		  return newList;
    }
    free(newList);
    return NULL;

}

/** shallow_copy_list
  *
  * Creates a shallow copy of the list. This means a new list structure and
  * nodes should be created, but each node will point to the same data as the
  * list passed in.
  *
  * if malloc fails or the list is NULL, return NULL to indicate failure. If
  * any memory allocations failures occur, your code must not leak memory. That
  * is, if create_node() returns NULL, you must go back and free any nodes
  * you've allocated so far and the new list.
  *
  * @param listToCopy the list to shallow copy
  * @return a pointer to the new list or NULL on failure
  */
list *shallow_copy_list(list *listToCopy)
{
    // UNUSED_PARAMETER(listToCopy);
    // return NULL;
  if (listToCopy == NULL) {
      return NULL;
    }
    list *newList = create_list();
    if (newList == NULL) {
      return NULL;
    }
    node *newNode = listToCopy->head;
    while (newNode) { 
      bool success = push_back(newList, newNode->data);
      if (!success) {
        return NULL;
      }
      newNode = newNode->next;
    }
    return newList;

}

/** deep_copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any structure must copy
  * EVERYTHING!
  *
  * If listToCopy or copyFunc is NULL, return NULL. For memory allocations
  * failures, including if copyFunc() returns false (indicating a memory
  * allocation failure), your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must go back
  * and free all data in the new list, nodes in the new list, and the new list
  * itself.
  *
  * @param listToCopy A pointer to the list structure to make a copy of
  * @param copyFunc A function pointer to a function that makes a copy of the
  *                 data that's being used in this list, allocating space for
  *                 every part of that data on the heap. This is some function
  *                 you must write yourself for testing, tailored specifically
  *                 to whatever context you're using the list for in your test.
  *                 If copyFunc returns false for any element, deep_copy_list()
  *                 should return NULL.
  * @param freeFunc function used to free the nodes' data in the case of a
  *                 memory allocation failure when copying (see above)
  * @return The list structure created by copying the old one, or NULL on
  *         failure
  */
list *deep_copy_list(list *listToCopy, list_copy copyFunc, list_op freeFunc)
{
    // UNUSED_PARAMETER(listToCopy);
    // UNUSED_PARAMETER(copyFunc);
    // UNUSED_PARAMETER(freeFunc);
    // return false;
    if (listToCopy == NULL || copyFunc == NULL) {
      return NULL;
    }
    list *newList = create_list();
    if (newList == NULL) {
      return NULL;
    }
    node *newNode = listToCopy->head;
    while (newNode) { 
      void *data_Out = NULL;
      bool isCopied = copyFunc(newNode->data, &data_Out);
      // printf("haha \n");        
      if (!isCopied) {
        empty_list(newList, freeFunc);
        return NULL;
      }
      bool success = push_back(newList, data_Out);
      if (!success) {
        empty_list(newList, freeFunc);
        return NULL;
      }
      newNode = newNode->next;
    }
    return newList;
}

/** push_front
  *
  * Adds the element at the front of the list.
  *
  * @param listToPrependTo a pointer to the list structure.
  * @param data the data to add to the list.
  * @return false if the list is NULL, true if successful.
  */
bool push_front(list *listToPrependTo, void *data)
{
    // UNUSED_PARAMETER(listToPrependTo);
    // UNUSED_PARAMETER(data);
    if (listToPrependTo == NULL) {
    	return false;
    } else {
      node *newNode = create_node(data);
    	newNode->next = listToPrependTo->head;
      listToPrependTo->head = newNode;
      if (listToPrependTo->size == 0) {
        listToPrependTo->tail = newNode;
      }
    	listToPrependTo->size += 1;
    	return true;
    }

}

/** push_back
  *
  * Adds the element to the back of the list.
  *
  * @param listToAppendTo a pointer to the list structure.
  * @param data the data to add to the list.
  * @return false if the list is NULL, true if successful.
  */
bool push_back(list *listToAppendTo, void *data)
{
    // UNUSED_PARAMETER(listToAppendTo);
    // UNUSED_PARAMETER(data);
    if (listToAppendTo == NULL) {
    	return false;
    } else {
      node *newNode = create_node(data);
      if (listToAppendTo->size == 0) {
        listToAppendTo->head = newNode;
      } else {
        listToAppendTo->tail->next = newNode;
      }
      listToAppendTo->tail = newNode;
    	listToAppendTo->size += 1;
    	return true;
    }
}

/** add
  *
  * Add the element at the specified index in the list. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the list,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the list,
  * you should be able to add to index 2 but no further.
  *
  * @param listToAddTo a pointer to the list structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the list
  * @return false if the index is out of bounds or the list is NULL
  *         (do not add the data in this case)
  *         otherwise return true
  */
bool add(list *listToAddTo, int index, void *data)
{
    // UNUSED_PARAMETER(listToAddTo);
    // UNUSED_PARAMETER(index);
    // UNUSED_PARAMETER(data);
    // return false;
    if ((listToAddTo == NULL) || (index > listToAddTo->size) || (index < 0)) {
      return false;
    }
    if (index == 0) {
      push_front(listToAddTo, data);
    } else if (index == listToAddTo->size - 1) {
      push_back(listToAddTo, data);
    } else {
      node *newNode = create_node(data);
      node *curr = listToAddTo->head;
      for (int i = 0; i < index - 1; ++i) {
        curr = curr->next;
      }
      curr->next = newNode;
      // curr->next->next = listToAddTo->tail;
      listToAddTo->size += 1;
    }
    return true;
}

/** front
  *
  * Gets the data at the front of the list
  * If the list is empty or the list is NULL, return false.
  *
  * @param listToGetFrontOf a pointer to the list
  * @param dataOut A pointer to a pointer used to return the data at the first
  *                node in the list or NULL on failure.
  * @return false if dataOut is NULL or the list is NULL or empty, true if
  *         successful.
  */
bool front(list *listToGetFrontOf, void **dataOut)
{
    // UNUSED_PARAMETER(listToGetFrontOf);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToGetFrontOf == NULL || listToGetFrontOf->size == 0 ) {
      *dataOut = NULL;
      return false;
    }
    *dataOut = listToGetFrontOf->head->data;
    return true;
}

/** back
  *
  * Gets the data at the back of the list
  * If the list is empty or the list is NULL, return false.
  *
  * @param listToGetBackOf a pointer to the list
  * @param dataOut A pointer to a pointer used to return the data at the last
  *                node in the list or NULL on failure.
  * @return false if dataOut is NULL or the list is NULL or empty, true
  *         otherwise
  */
bool back(list *listToGetBackOf, void **dataOut)
{
    // UNUSED_PARAMETER(listToGetBackOf);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToGetBackOf == NULL || listToGetBackOf->size == 0) {
      *dataOut = NULL;
      return false;
    }
    *dataOut = listToGetBackOf->tail->data;
    return true;
}

/** get
  *
  * Gets the data at the specified index in the list
  *
  * @param listToGetDataFrom a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the list or NULL on failure.
  * @return false if dataOut is NULL or index is out of range of the list or
  *         the list is NULL, true otherwise
  */
bool get(list *listToGetDataFrom, int index, void **dataOut)
{
    // UNUSED_PARAMETER(listToGetDataFrom);
    // UNUSED_PARAMETER(index);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToGetDataFrom == NULL || listToGetDataFrom->size == 0 ) {
      *dataOut = NULL;
      return false;
    }
    // if (listToGetDataFrom->size == 0) {
    //  front(listToGetDataFrom, dataOut);
    // }
    // if (listToGetDataFrom->size == (index + 1)) {
    //  back(listToGetDataFrom, dataOut);
    // }
    node *curr = listToGetDataFrom->head;
    for (int i = 0; i < index; ++i)
    {
      curr = curr->next;
    }
    *dataOut = curr->data;
    return true;
}

/** size
  *
  * Gets the size of the list
  *
  * if the list is NULL, return false.
  *
  * @param listToGetSizeOf a pointer to the list structure
  * @param A pointer used to return the size of the list, set to -1 on NULL list
  * @return false if sizeOut is NULL or list is NULL, true otherwise
  */
bool size(list *listToGetSizeOf, int *sizeOut)
{
    // UNUSED_PARAMETER(listToGetSizeOf);
    // UNUSED_PARAMETER(sizeOut);
    if (sizeOut == NULL) { return false; }
  	if (listToGetSizeOf == NULL) {
  		*sizeOut = -1;
  		return false;
  	} else {
  		*sizeOut = listToGetSizeOf->size;
  		return true;
  	}
}

/** contains
  *
  * Traverses the list, trying to see if the list contains some data.
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * comparator says is equal. For instance, if you have a list of person structs:
  *   (Andrew, 26), (Nick, 24), (Collin, 23), (Marie, 23)
  * And you want to return any person whose age is 24, you could create a new
  * person struct (<NULL>, 24) with a comparator that returns 0 if age == 24 and
  * pass that into this function as "data" along with comparator. contains()
  * would then return (Nick, 24) In other words, data will be something with
  * value equality to what is in the list, but not necessarily something with
  * reference equality. Value equality will be defined by comparator.
  *
  * If there are multiple pieces of data in the list which are equal to the
  * "data" parameter, return any one of them.
  *
  * @param listToSearch a pointer to the list structure
  * @param data The data, to see if it exists in the list
  * @param comparator A function written by the user that will tell if two pieces
  *                of data are equal. Returns 0 if equal, something else
  *                otherwise. Imagine subtracting two numbers. Think of
  *                a comparator's compare function from Java.
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the list or NULL on failure
  * @return false if dataOut is NULL, list is NULL, comparator is NULL, or the
  *               list does not contain data, else true
  */
bool contains(list *listToSearch, void *data, list_eq comparator, void **dataOut)
{
    // UNUSED_PARAMETER(listToSearch);
    // UNUSED_PARAMETER(data);
    // UNUSED_PARAMETER(comparator);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToSearch == NULL || listToSearch->size == 0 || comparator == NULL) {
      *dataOut = NULL;
      return false;
    }
    node *curr = listToSearch->head;
    while (curr) {
      if (comparator(data, curr->data) == 0) {
        *dataOut = curr->data;
        return true;
      }
      curr = curr->next;
    }
    *dataOut = NULL;
    return false;
}


/** pop_front
  *
  * Removes the node at the front of the list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the list.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                node or NULL on failure
  * @return false if dataOut is NULL or the list is NULL or empty, else true
  */
bool pop_front(list *listToPopFrom, void **dataOut)
{
    // UNUSED_PARAMETER(listToPopFrom);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToPopFrom == NULL || listToPopFrom->size == 0) {
      *dataOut = NULL;
      return false;
    }
    *dataOut = listToPopFrom->head->data;
    if (listToPopFrom->size == 1) {
      free(listToPopFrom->head);
      listToPopFrom->head = NULL;
      listToPopFrom->tail = NULL;
    } else {
      node *oldHead = listToPopFrom->head;
      listToPopFrom->head = oldHead->next;
      free(oldHead);
    }
    listToPopFrom->size -= 1;
    return true;
}

/** pop_back
  *
  * Removes the node at the back of the list, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the list.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                node or NULL on failure
  * @return false if dataOut is NULL or the list is NULL or empty, else true
  */
bool pop_back(list *listToPopFrom, void **dataOut)
{
    // UNUSED_PARAMETER(listToPopFrom);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToPopFrom == NULL || listToPopFrom->size == 0) {
      *dataOut = NULL;
      return false;
    }
    *dataOut = listToPopFrom->tail->data;
    if (listToPopFrom->size == 1) {
      free(listToPopFrom->tail);
      listToPopFrom->head = NULL;
      listToPopFrom->tail = NULL;
    } else {
      node *curr = listToPopFrom->head; 
      for (int i = 0; i < listToPopFrom->size - 2; ++i) {
        curr = curr->next;
      }
      node *oldTail = curr->next;
      curr->next = NULL;
      listToPopFrom->tail = curr;
      free(oldTail);
    }
    listToPopFrom->size -= 1;
    return true;
}

/** list_remove
  *
  * Removes the data from the specified index in the list
  *
  * @param listToRemoveFrom a pointer to the list structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *                specified index in the list or NULL on failure
  * @return false if dataOut is NULL or list is NULL or index is out of range
  *         of the list, else true
  */
bool list_remove(list *listToRemoveFrom, int index, void **dataOut)
{
    // UNUSED_PARAMETER(listToRemoveFrom);
    // UNUSED_PARAMETER(index);
    // UNUSED_PARAMETER(dataOut);
    // return false;
    if (dataOut == NULL) { return false; }
    if (listToRemoveFrom == NULL || listToRemoveFrom->size == 0
      || index == listToRemoveFrom->size || index < 0) {
      *dataOut = NULL;
      return false;
    }
    if (index == 0) {
      return pop_front(listToRemoveFrom, dataOut);
    } else if (index == (listToRemoveFrom->size - 1)) {
      return pop_back(listToRemoveFrom, dataOut);
    } else {
      node *curr = listToRemoveFrom->head;  
      for (int i = 0; i < index - 1; ++i) {
        curr = curr->next;
      }
      *dataOut = curr->next->data;
      curr->next = curr->next->next;
      free(curr->next);
      listToRemoveFrom->size -= 1;
    }
    return true; 
}


/** empty_list
  *
  * Empties the list. After this is called, the list should be empty.
  * This does not free the list struct itself, just all nodes and data within.
  * Make sure to check that listToEmpty and freeFunc are not NULL before using
  * them.
  *
  * @param listToEmpty a pointer to the list structure
  * @param freeFunc function used to free the nodes' data.
  */
  
void empty_list(list *listToEmpty, list_op freeFunc)
{
    // UNUSED_PARAMETER(listToEmpty);
    // UNUSED_PARAMETER(freeFunc);
    if ((listToEmpty != NULL) && (freeFunc != NULL)) {
        node* curr = listToEmpty->head;
        while (curr) {
            node* oldNode = curr;
            curr = curr->next;
            freeFunc(oldNode->data);
            free(oldNode);
        }
        listToEmpty->head = NULL;
        listToEmpty->tail = NULL;
        listToEmpty->size = 0;
    }
}

/** traverse
  *
  * Traverses the list, calling a function on each node's data.
  *
  * @param listToTraverse a pointer to the list structure
  * @param doFunc a function that does something to each node's data.
  * @return true if the traversal was a success, false otherwise
  *         (listToTraverse1 or doFunc is null)
  */
bool traverse(list *listToTraverse, list_op doFunc)
{
    // UNUSED_PARAMETER(listToTraverse);
    // UNUSED_PARAMETER(doFunc);
    if ((listToTraverse != NULL) && (doFunc != NULL)) {
      node *curr = listToTraverse->head;
      while (curr) {
        // node* oldNode = curr;
        doFunc(curr->data);
        curr = curr->next;         
      }
      return true;
    }
    return false;
}

/** reverse
  *
  * Reverses the singly linked list in place.
  *
  * @param listToReverse to append to.
  * @return true if the operation was a success, false otherwise (listToReverse
  *         was NULL)
  */
bool reverse(list *listToReverse)
{
    // UNUSED_PARAMETER(listToReverse);
    // return false;

    if (listToReverse == NULL) {
      return false;
    } 
    // list *newList = create_list();
    // node *newNode = listToReverse->head;
    // void *data_Out = NULL;
    // while (newNode) {
    //   bool success = pop_back(listToReverse, &data_Out);
    //   if (success) {
    //     bool isAdded = push_back(newList, data_Out);
    //     if (!isAdded) {
    //       free(newList);
    //       return false;
    //     }
    //   }
    //   newNode = newNode->next;
    // }
    // listToReverse = shallow_copy_list(newList);
    // return true;

    listToReverse->tail = listToReverse->head;
    node *curr = listToReverse->head;
    listToReverse->head = NULL;
    while (curr != NULL) {
      node *temp = curr->next;
      curr->next = listToReverse->head;
      listToReverse->head = curr;
      curr = temp;
    }
    return true;
}

/** concat
  *
  * Concatinates firstList and secondList. This function should append
  * secondList to the end of firstList.
  *
  * NOTE: this function will effectively empty lastList onto firstList which
  *       means that lastList will be empty (head == tail == NULL and size == 0)
  *       at the end of the function and firstList will contain all the elements
  *       from both lists. Be sure to update the size, head, and tail pointers
  *       accordingly.
  *
  * example: if firstList is a->b->c and second list is d->e->f
  * after the function call, firstList will be a->b->c->d->e->f and
  * secondList will be empty.
  *
  *
  * @param firstList to append to.
  * @param secondList the list to append to firstList
  * @return true if the operation was a success, false otherwise (firstList or
  *         secondList is null)
  */
bool concat(list *firstList, list *lastList)
{
    // UNUSED_PARAMETER(firstList);
    // UNUSED_PARAMETER(lastList);
    // return false;
    if (firstList == NULL || lastList == NULL || firstList->size == 0 
      || lastList->size == 0) {
      return false;
    }
    firstList->tail->next = lastList->head;
    firstList->tail = lastList->tail;
    lastList->head = NULL;
    lastList->tail = NULL;
    firstList->size += lastList->size;
    lastList->size = 0;
    // free(lastList);
    return true;
}
