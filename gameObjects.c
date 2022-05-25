/*
CMPT 125 Assignment 4 gameObjects.c
Author: Mathew Tse
Student ID: 301427861
SFU email: mta118@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).
Description: gameObjects.c contains functions that manage the entities
of the game. 
*/

#include "gameObjects.h"

//a function that initializes all the fields of a Deck.
// For each suit, the values of the cards are
// ‘A’, ‘2’, ‘3’, …, ‘9’, ,'T', ‘J’, ‘Q’, ‘K’.
void initializeDeck(Deck* theDeck, char* brandName){
  
  char values[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
  theDeck -> brand = brandName;
  int k = 0;

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++){
      theDeck -> cards[k].suit = i; // 0 = Spades 1 = Hearts, etc..
      theDeck -> cards[k].value = values[j];
      k++;
    }
  }
}

//a function that shuffles the deck
void shuffleDeck(Deck* theDeck){

  for (size_t i = 0; i < 52 - 1; i++){
    size_t j = i + rand() / (RAND_MAX / (52 - i) + 1);

    Suit suitTemp = theDeck -> cards[i].suit; 
    char valueTemp = theDeck -> cards[i].value;

    theDeck -> cards[i].suit = theDeck -> cards[j].suit;
    theDeck -> cards[i].value = theDeck -> cards[j].value;

    theDeck -> cards[j].suit = suitTemp;
    theDeck -> cards[j].value = valueTemp;
  }
}

//a function that prints the content of a Deck.
//accepts a second bool parameter:
//if true, print face up, if false, print face down.
//if the card is won by a player, leave it blank.
void printDeck(const Deck* theDeck, bool faceUp){

  //char suits[] = {Spades, Hearts, Clubs, Diamonds};
  char columns[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m'};
  int k = 0;

  // first print the abcdefgs on top 

  for (int j = 0; j < 13; j++){
    if (j == 0){
      printf("  "); // printf 2 spaces
    }
      printf("  %c",columns[j]);
  }
  printf("\n");

  // Loop to print out the cards
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 13; j++){

      //print out the row number  
      if (j == 0){
        printf("%d  ",i);
      }

      //only print cards that are not taken, value != 0 
      if (theDeck ->cards[k].value != '0'){
        if (faceUp == true){

          printf("%c", theDeck -> cards[k].value);

          if (theDeck -> cards[k].suit == Spades){
            printf("\u2660");
          }
          else if (theDeck -> cards[k].suit == Hearts){
            printf("\u2661");
          }
          else if (theDeck -> cards[k].suit == Clubs){
            printf("\u2663");
          }
          else if (theDeck -> cards[k].suit == Diamonds){
            printf("\u2662");
          }
          if (j != 12){ //no need for a space when printing the last card
            printf(" ");
          }
        }

        //print a rectangle instead of the card value & suit
        if (faceUp == false){
          printf("%c\u218C ", '?'); 
        }
      }
      
      // if the card value is 0, it's taken. Don't print it
      else if (theDeck ->cards[k].value == '0'){
        printf("   "); 
      }
      k++;
    }
    printf("\n");
  }
}


//a function that initializes all the fields of a Player.
void initializePlayer(Player* thePlayer, char* theName){
  thePlayer->name = theName;
  thePlayer->cardsWon = 0;
  thePlayer->winPile = *createCard_LList();
}


//a function clears the winning pile of the player by calling the necessary
// function on a Card_LList.
void clearPlayer(Player* thePlayer){

  clearCard_LList(&thePlayer->winPile);
}