
#include "../src/card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Test function for createCard()
int test_createCard() {
  Card *card = createCard(HEARTS, ACE);
  if (card == NULL) {
    printf("test_createCard failed: returned NULL\n");
    return 1;
  }
  if (card->suit != HEARTS || card->rank != ACE) {
    printf("test_createCard failed: wrong suit or rank\n");
    free(card);
    return 1;
  }
  if (card->next != NULL) {
    printf("test_createCard failed: next not NULL\n");
    free(card);
    return 1;
  }
  free(card);
  return 0;
}

// Test function for getSuitName()
int test_getSuitName() {
  const char *name = getSuitName(HEARTS);
  if (strcmp(name, "Hearts") != 0) {
    printf("test_getSuitName failed: wrong name for HEARTS\n");
    return 1;
  }
  name = getSuitName(SPADES);
  if (strcmp(name, "Spades") != 0) {
    printf("test_getSuitName failed: wrong name for SPADES\n");
    return 1;
  }
  return 0;
}

// Test function for getRankName()
int test_getRankName() {
  const char *name = getRankName(ACE);
  if (strcmp(name, "Ace") != 0) {
    printf("test_getRankName failed: wrong name for ACE\n");
    return 1;
  }
  name = getRankName(KING);
  if (strcmp(name, "King") != 0) {
    printf("test_getRankName failed: wrong name for KING\n");
    return 1;
  }
  return 0;
}

// Test function for getValue()
int test_getValue() {
  if (getValue(ACE) != 11) {
    printf("test_getValue failed: wrong value for ACE\n");
    return 1;
  }
  if (getValue(FIVE) != 5) {
    printf("test_getValue failed: wrong value for FIVE\n");
    return 1;
  }
  if (getValue(KING) != 10) {
    printf("test_getValue failed: wrong value for KING\n");
    return 1;
  }
  return 0;
}

// Test function for createDeck()
int test_createDeck() {
  Deck *deck = createDeck();
  if (deck == NULL) {
    printf("test_createDeck failed: returned NULL\n");
    return 1;
  }
  if (deck->size != 52) {
    printf("test_createDeck failed: wrong deck size\n");
    freeDeck(deck);
    return 1;
  }

  // Verify all cards are present
  int counts[NUM_SUITS][NUM_RANKS] = {0};
  Card *current = deck->head;
  while (current != NULL) {
    counts[current->suit][current->rank]++;
    current = current->next;
  }

  for (int s = HEARTS; s < NUM_SUITS; s++) {
    for (int r = ACE; r < NUM_RANKS; r++) {
      if (counts[s][r] != 1) {
        printf("test_createDeck failed: missing cards\n");
        freeDeck(deck);
        return 1;
      }
    }
  }

  freeDeck(deck);
  return 0;
}

// Test function for deckLength()
int test_deckLength() {
  Deck *deck = createDeck();
  int length = deckLength(deck->head);
  if (length != 52) {
    printf("test_deckLength failed: wrong length\n");
    freeDeck(deck);
    return 1;
  }

  // Test with empty deck
  Deck emptyDeck = {NULL, NULL, 0};
  length = deckLength(emptyDeck.head);
  if (length != 0) {
    printf("test_deckLength failed: wrong length for empty deck\n");
    freeDeck(deck);
    return 1;
  }

  freeDeck(deck);
  return 0;
}

// Test function for getCardAt()
int test_getCardAt() {
  Deck *deck = createDeck();

  // Test first card
  Card *card = getCardAt(deck->head, 0);
  if (card == NULL || card->suit != HEARTS || card->rank != ACE) {
    printf("test_getCardAt failed: wrong first card\n");
    freeDeck(deck);
    return 1;
  }

  // Test last card
  card = getCardAt(deck->head, 51);
  if (card == NULL || card->suit != SPADES || card->rank != KING) {
    printf("test_getCardAt failed: wrong last card\n");
    freeDeck(deck);
    return 1;
  }

  // Test out of bounds
  card = getCardAt(deck->head, 52);
  if (card != NULL) {
    printf("test_getCardAt failed: out of bounds not NULL\n");
    freeDeck(deck);
    return 1;
  }

  freeDeck(deck);
  return 0;
}

// Test function for swapCards()
int test_swapCards() {
  Deck *deck = createDeck();

  // Get original cards
  Card *first = getCardAt(deck->head, 0);
  Card *last = getCardAt(deck->head, 51);
  Suit firstSuit = first->suit;
  Rank firstRank = first->rank;
  Suit lastSuit = last->suit;
  Rank lastRank = last->rank;

  // Swap first and last cards
  swapCards(deck->head, 0, 51);

  // Verify swap
  if (first->suit != lastSuit || first->rank != lastRank ||
      last->suit != firstSuit || last->rank != firstRank) {
    printf("test_swapCards failed: cards not swapped correctly\n");
    freeDeck(deck);
    return 1;
  }

  freeDeck(deck);
  return 0;
}

// Test function for shuffleDeck()
int test_shuffleDeck() {
  Deck *deck = createDeck();

  // Record original order
  int originalOrder[52];
  Card *current = deck->head;
  for (int i = 0; i < 52; i++) {
    originalOrder[i] = current->suit * 100 + current->rank;
    current = current->next;
  }

  // Shuffle and check if order changed
  shuffleDeck(deck);

  current = deck->head;
  int different = 0;
  for (int i = 0; i < 52; i++) {
    int newValue = current->suit * 100 + current->rank;
    if (newValue != originalOrder[i]) {
      different = 1;
      break;
    }
    current = current->next;
  }

  if (!different) {
    printf("test_shuffleDeck failed: deck order unchanged\n");
    freeDeck(deck);
    return 1;
  }

  // Verify all cards are still present
  int counts[NUM_SUITS][NUM_RANKS] = {0};
  current = deck->head;
  while (current != NULL) {
    counts[current->suit][current->rank]++;
    current = current->next;
  }

  for (int s = HEARTS; s < NUM_SUITS; s++) {
    for (int r = ACE; r < NUM_RANKS; r++) {
      if (counts[s][r] != 1) {
        printf("test_shuffleDeck failed: missing cards after shuffle\n");
        freeDeck(deck);
        return 1;
      }
    }
  }

  freeDeck(deck);
  return 0;
}

// Test function for getNextCard()
int test_getNextCard() {
  Deck *deck = createDeck();

  // Get first card
  Card *card = getNextCard(deck);
  if (card == NULL || card->suit != HEARTS || card->rank != ACE) {
    printf("test_getNextCard failed: wrong first card\n");
    freeDeck(deck);
    return 1;
  }

  // Get second card
  card = getNextCard(deck);
  if (card == NULL || card->suit != HEARTS || card->rank != TWO) {
    printf("test_getNextCard failed: wrong second card\n");
    freeDeck(deck);
    return 1;
  }

  // Test deck reset after reaching end
  Deck *smallDeck = (Deck *)malloc(sizeof(Deck));
  smallDeck->head = createCard(HEARTS, ACE);
  smallDeck->head->next = createCard(DIAMONDS, ACE);
  smallDeck->size = 2;
  smallDeck->current = smallDeck->head;

  card = getNextCard(smallDeck);
  card = getNextCard(smallDeck);
  card = getNextCard(smallDeck); // Should trigger shuffle and reset

  if (card == NULL) {
    printf("test_getNextCard failed: deck not reset after end\n");
    freeDeck(smallDeck);
    freeDeck(deck);
    return 1;
  }

  freeDeck(smallDeck);
  freeDeck(deck);
  return 0;
}

// Main test runner
int main(void) {
  printf("Running tests...\n\n");
  int failed = 0;
  // Run tests and update failed count
  failed += test_createCard();
  failed += test_getSuitName();
  failed += test_getRankName();
  failed += test_getValue();
  failed += test_createDeck();
  failed += test_deckLength();
  failed += test_getCardAt();
  failed += test_swapCards();
  failed += test_shuffleDeck();
  failed += test_getNextCard();
  printf("\nTest Results:\n");
  if (failed == 0) {
    printf("\nAll tests passed!\n");
    return 0;
  } else {
    printf("\n%d tests failed!\n", failed);
    return 1;
  }
}
