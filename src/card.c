#include "card.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to create a new card
Card *createCard(Suit suit, Rank rank) {
  Card *newCard = (Card *)malloc(sizeof(Card));
  if (newCard == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  newCard->suit = suit;
  newCard->rank = rank;
  newCard->next = NULL;
  return newCard;
}

// Function to get the suit name as a string
const char *getSuitName(Suit suit) {
  static const char *suitNames[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  return suitNames[suit];
}

// Function to get the rank name as a string
const char *getRankName(Rank rank) {
  static const char *rankNames[] = {"",   "Ace",  "2",     "3",   "4",
                                    "5",  "6",    "7",     "8",   "9",
                                    "10", "Jack", "Queen", "King"};
  return rankNames[rank];
}

int getValue(Rank rank) {
  switch (rank) {
  case ACE:
    return 11; // Can be 1 or 11, 11 is more interesting so we're doing that
  case TWO:
    return 2;
  case THREE:
    return 3;
  case FOUR:
    return 4;
  case FIVE:
    return 5;
  case SIX:
    return 6;
  case SEVEN:
    return 7;
  case EIGHT:
    return 8;
  case NINE:
    return 9;
  case TEN:
  case JACK:
  case QUEEN:
  case KING:
    return 10;
  default:
    return 0; // Should never happen
  }
}

// Function to create a standard deck of 52 cards
Card *createDeck() {
  Card *head = NULL;
  Card *tail = NULL;

  for (int s = HEARTS; s < NUM_SUITS; s++) {
    for (int r = ACE; r < NUM_RANKS; r++) {
      Card *newCard = createCard(s, r);

      if (head == NULL) {
        head = newCard;
        tail = newCard;
      } else {
        tail->next = newCard;
        tail = newCard;
      }
    }
  }

  return head;
}

// Function to get the length of the deck
int deckLength(Card *deck) {
  int count = 0;
  Card *current = deck;
  while (current != NULL) {
    count++;
    current = current->next;
  }
  return count;
}

// Function to get a card at a specific index
Card *getCardAt(Card *deck, int index) {
  Card *current = deck;
  for (int i = 0; i < index && current != NULL; i++) {
    current = current->next;
  }
  return current;
}

// Function to swap two cards in the deck by their indices
void swapCards(Card *deck, int i, int j) {
  if (i == j)
    return;

  // Find the cards at positions i and j
  Card *cardI = getCardAt(deck, i);
  Card *cardJ = getCardAt(deck, j);

  // Swap the data (not the pointers, to keep the list structure)
  Suit tempSuit = cardI->suit;
  Rank tempRank = cardI->rank;

  cardI->suit = cardJ->suit;
  cardI->rank = cardJ->rank;

  cardJ->suit = tempSuit;
  cardJ->rank = tempRank;
}

// Function to shuffle the deck
void shuffleDeck(Card *deck) {
  int length = deckLength(deck);

  // Seed the random number generator
  srand(time(NULL));

  for (int i = length - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    swapCards(deck, i, j);
  }
}

// Function to print the deck
void printDeck(Card *deck) {
  Card *current = deck;
  int count = 0;

  while (current != NULL) {
    printf("%-5s of %-8s", getRankName(current->rank),
           getSuitName(current->suit));
    count++;

    // Print 4 cards per line for better formatting
    if (count % 4 == 0) {
      printf("\n");
    } else {
      printf("\t");
    }

    current = current->next;
  }
  printf("\nTotal cards in deck: %d\n", count);
}

// Function to free the memory used by the deck
void freeDeck(Card *deck) {
  Card *current = deck;
  while (current != NULL) {
    Card *next = current->next;
    free(current);
    current = next;
  }
}
