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

// Function to get the card's integer value in Blackjack, aces high
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

// Essentially a macro to call createCard() 52 times with the correct paramaters
Deck *createDeck() {
  Deck *deck = (Deck *)malloc(sizeof(Deck));
  if (deck == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  deck->head = NULL;
  Card *tail = NULL;
  deck->size = 0;

  for (int s = HEARTS; s < NUM_SUITS; s++) {
    for (int r = ACE; r < NUM_RANKS; r++) {
      Card *newCard = createCard(s, r);
      deck->size++;

      if (deck->head == NULL) {
        deck->head = newCard;
        tail = newCard;
      } else {
        tail->next = newCard;
        tail = newCard;
      }
    }
  }

  deck->current = deck->head; // Start at the first card
  return deck;
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

// Function to shuffle the deck by swapping random cards
void shuffleDeck(Deck *deck) {
  if (deck == NULL || deck->head == NULL)
    return;

  // Convert linked list to array for easier shuffling
  Card **cards = (Card **)malloc(deck->size * sizeof(Card *));
  Card *current = deck->head;
  for (int i = 0; i < deck->size; i++) {
    cards[i] = current;
    current = current->next;
  }

  // Fisher-Yates shuffle
  srand(time(NULL));
  for (int i = deck->size - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    // Swap the cards
    Suit tempSuit = cards[i]->suit;
    Rank tempRank = cards[i]->rank;
    cards[i]->suit = cards[j]->suit;
    cards[i]->rank = cards[j]->rank;
    cards[j]->suit = tempSuit;
    cards[j]->rank = tempRank;
  }

  free(cards);
  deck->current = deck->head; // Reset to first card after shuffling
}

// Function to get next card by the current card's pointer, with code to shuffle
// if the end of the deck is reached
Card *getNextCard(Deck *deck) {
  if (deck == NULL || deck->current == NULL) {
    return NULL;
  }

  Card *currentCard = deck->current;

  // Move to next card
  deck->current = deck->current->next;

  // If we've reached the end, shuffle and reset
  if (deck->current == NULL) {
    printf("\nReached end of deck - shuffling and resetting...\n");
    shuffleDeck(deck);
  }

  return currentCard;
}

// Test function to verify deck generation
void printDeckState(Deck *deck) {
  printf("Deck contains %d cards\n", deck->size);

  // Print the next 5 cards or remaining cards
  printf("Next cards: ");
  Card *temp = deck->current;
  int count = 0;
  while (temp != NULL && count < 5) {
    printf("%s of %s", getRankName(temp->rank), getSuitName(temp->suit));
    temp = temp->next;
    count++;
    if (temp != NULL && count < 5)
      printf(", ");
  }
  printf("\n");
}

// Function to free each card 1 by 1 since we didn't malloc the deck directly,
// only the cards
void freeDeck(Deck *deck) {
  Card *current = deck->head;
  while (current != NULL) {
    Card *next = current->next;
    free(current);
    current = next;
  }
  free(deck);
}
