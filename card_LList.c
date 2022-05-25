/*
CMPT 125 Assignment 4 card_LList.c
Author: Mathew Tse
Student ID: 301427861
SFU email: mta118@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).
Description: card_LList.c that contains the functions for the linked
list of the cards
*/

#include "card_LList.h"

//a function that creates a new Card_LList, which is an empty linked list.

Card_LList* createCard_LList(){

  //create a new list, if memory allocation fails, exit(0)
  Card_LList* newList = malloc(sizeof(Card_LList));
  if (newList == NULL){
    exit(0);
  }

  newList->head = NULL;
  newList->tail = NULL;
  return newList;
}

//a function that removes all the nodes from the list
// by freeing them one by one. The result is an empty linked list.
void clearCard_LList(Card_LList* theList){
  
  Card_Node* temp = theList->head;

  //keep freeing until there are no more nodes 
  while (temp != NULL){
    Card_Node* nodeToFree = temp;
    temp = temp->next; 
    free(nodeToFree);
  }

  theList->head = NULL;
  theList->tail = NULL;
}


//a function that checks if the list is empty.
// If it is empty, return true; otherwise return false.
bool isEmptyCard_LList(Card_LList* theList){
  
  // if head and tail are NULL, the card list is empty
  if (theList->head == NULL || theList->tail == NULL){
    return true;
  }
  else{
    return false;
  }
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertFrontCard_LList(Card_LList* theList, Card* theCard){

  //allocate memory for a node, if fail, exit(0)
  Card_Node* newNode = malloc(sizeof(Card_Node));  
  if (newNode == NULL){
    exit(0);
  }

  newNode->card = theCard;

  // not an empty linked list, set newNode to be the head
  if (theList->head != NULL){
    newNode->next = theList->head;
    theList->head = newNode;
  }

  //empty linked list, head and tail will be newNode
  else{
    newNode->next = NULL;
    theList->head = newNode;
    theList->tail = newNode;
  }
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertEndCard_LList(Card_LList* theList, Card* theCard){

  //allocate memory for a node, if fail, exit(0)
  Card_Node* newNode = malloc(sizeof(Card_Node));
  if (newNode == NULL){
    exit(0);
  }

  newNode->card = theCard;

  //not an empty linked list, set newNode to be the tail
  if (theList->tail != NULL){
    theList->tail->next = newNode;
    theList->tail = newNode;
  }

  //empty linked list, set newNode to be the head and tail
  else{
    newNode->next = NULL;
    theList->head = newNode;
    theList->tail = newNode;
  }
}

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeFrontCard_LList(Card_LList* theList){

  if (theList->head != NULL){

    //copy the address of the card, update the head, free the node
    Card* cardToRemove = theList->head->card;
    Card_Node* newHead = theList->head->next;
    free(theList->head);
    theList -> head = newHead;

    return cardToRemove;
  }

  //returns NULL if linked list is empty
  return NULL;
}

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeEndCard_LList(Card_LList* theList){

  if (theList->tail != NULL){
    
    // find the second last node
    Card_Node* currentNode = theList->head;

    // when currentNode -> next -> next == NULL, 
    // currentNode will be the 2nd last node

    while(currentNode->next->next != NULL){ 
      currentNode = currentNode->next;
    }
     
    // copy address of last card, free the node, update tail
    Card* cardToRemove = theList->tail->card; 
    free(theList->tail);
    theList->tail = currentNode; 

    return cardToRemove;
  }
  
  //returns NULL if linked list is empty
  return NULL;
}