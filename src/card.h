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

typedef struct {
  Card *head;    // First card in the deck
  Card *current; // Current card position
  int size;      // Number of cards in the deck
} Deck;

// Function to create a new card
Card *createCard(Suit suit, Rank rank);

int getValue(Rank rank);
void shuffleDeck(Deck *deck);
const char *getSuitName(Suit suit);
const char *getRankName(Rank rank);
Deck *createDeck();
void printDeckState(Deck *deck);
void freeDeck(Deck *deck);
Card *getNextCard(Deck *deck);
int deckLength(Card *deck);
Card *getCardAt(Card *deck, int index);
void swapCards(Card *deck, int i, int j);
#endif
