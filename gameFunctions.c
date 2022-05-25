/*
CMPT 125 Assignment 4 gameFunctions.c
Author: Mathew Tse
Student ID: 301427861
SFU email: mta118@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).
Description: gameFunctions.c that contains many of the functions that will
be called in main.c
*/

#include "gameFunctions.h"
#define ASCIIVALOFZERO 48
#define ASCIIVALOFa 97

//a function that adds the card to the player's winning pile by calling
// the appropriate function from card_LList and update the cards won.
// Also marks the card as taken ('0').

void addCardToPlayer(Player* thePlayer, Card* theCard){

  thePlayer -> cardsWon += 1;
  insertEndCard_LList(&thePlayer->winPile, theCard);

  //marks the card as taken '0'
  theCard->value = '0';
}

//a function that checks if the user choice is valid:
// if any of the choices are invalid, report that and return false.
bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col){

  int rows = (row - ASCIIVALOFZERO) + 1; //number of rows 
  int cols = (col - ASCIIVALOFa) + 1; // number of columns

  bool rowWithinRange = false;
  bool colWithinRange = false;

  //check if it's within the row and col range 
  if (rows >= 1 && rows <= 4){ //since rows go from 0 to 3
    rowWithinRange = true;
  }

  if (cols >= 1 && cols <= 13){ //since there are 13 columns
    colWithinRange = true;
  }
  
  if (rowWithinRange == false || colWithinRange == false){
    printf("Error: The card you picked has invalid index(es).\n");
    return false;
  }

  //determine the index in the deck
  int indexInDeck = 0;
  if (rowWithinRange == true && colWithinRange == true){

    for (int i = 1; i <= rows; i++){
      if (i == rows){
        indexInDeck += cols;
      }
      else{ 
        indexInDeck += 13; // 13 cards in a row when i != rows 
      }
    }
    indexInDeck-=1; //subtract by 1 since it's the index
  }

  if (theDeck->cards[indexInDeck].value == '0'){
    printf("Error: The card you picked is already taken.\n");
    return false;
  }
  
  return true;
}

//a function that checks if there is a match:
// if the two choices are the same, report it and return false.
// if there is a match, return true; otherwise, return false.
bool checkForMatch(Deck* theDeck, Player* thePlayer,
  char r1, char c1, char r2, char c2){
    
    int firstCardRow = r1 - ASCIIVALOFZERO + 1; //number of rows 
    int firstCardColumn = c1 - ASCIIVALOFa + 1; // number of columns 

    int secondCardRow = r2 - ASCIIVALOFZERO + 1; //number of rows 
    int secondCardColumn = c2 - ASCIIVALOFa + 1; // number of columns 

    //check if the inputs are duplicates
    if (firstCardRow == secondCardRow && 
      firstCardColumn == secondCardColumn){
        printf("Error: Both cards are the same.\n");
        return false;
    }

    // if the input is valid, check if the value of the two cards are identical
    if (checkPlayerInput(theDeck, thePlayer, r1, c1) == true 
      && checkPlayerInput(theDeck, thePlayer, r2, c2) == true){

        int firstCardIndex = 0;
        int secondCardIndex = 0;
        
        //calculating the index for the first card 
        for (int i = 1; i <= firstCardRow; i++){
          if (i == firstCardRow){
            firstCardIndex += firstCardColumn;
          }
          else{
            firstCardIndex += 13; 
          }
        }
        firstCardIndex -=1; // subtract 1 since it's the index 

        //calculating the index for the second card 
        for (int i = 1; i <= secondCardRow; i++){
          if (i == secondCardRow){
            secondCardIndex += secondCardColumn;
          }
          else{
            secondCardIndex += 13;
          }
        }
        secondCardIndex -= 1;

        // if the values are the same, add card to player winpile 
        if (theDeck ->cards[firstCardIndex].value == 
          theDeck->cards[secondCardIndex].value){
            addCardToPlayer(thePlayer, &theDeck->cards[firstCardIndex]); 
            addCardToPlayer(thePlayer, &theDeck->cards[secondCardIndex]); 
            return true;
          }
      }

    return false;
  }


//a function that checks if the game has a winner
// (all cards in the deck is taken)
bool checkForWinner(const Deck* theDeck){

  int numberOfZeros = 0;

  // loop through all the cards, if there are 
  // still cards of value != '0', no winner.
  
  for(int i = 0; i < 52; i++){
    if (theDeck->cards[i].value == '0'){
      numberOfZeros += 1;
    }    
  }

  if (numberOfZeros == 52){
    return true;
  }
  
  else{
    return false;
  }
}

