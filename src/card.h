#ifndef CARD_H
#define CARD_H

#include <stdio.h>

// Define the card suits
typedef enum { HEARTS, DIAMONDS, CLUBS, SPADES, NUM_SUITS } Suit;

// Define the card ranks
typedef enum {
  ACE = 1,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  NUM_RANKS
} Rank;

// Define a structure for a playing card
typedef struct Card {
  Suit suit;
  Rank rank;
  struct Card *next; // Pointer to the next card in the deck
} Card;

// Function to create a new card
Card *createCard(Suit suit, Rank rank);

int deckLength(Card *deck);
Card *getCardAt(Card *deck, int index);
void swapCards(Card *deck, int i, int j);
void shuffleDeck(Card *deck);
const char *getSuitName(Suit suit);
const char *getRankName(Rank rank);
Card *createDeck();
void printDeck(Card *deck);
void freeDeck(Card *deck);
#endif
