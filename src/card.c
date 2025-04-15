#include "card.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector InitDeck() {
  vector deck;
  deck.size = 52;
  deck.elements = (Card *)malloc(deck.size * sizeof(Card));

  if (deck.elements == NULL) {
    // Handle memory allocation failure
    deck.size = 0;
    return deck;
  }

  int index = 0;
  // 4 suits (0-3) and 13 values (1-13)
  for (int suit = 0; suit < 4; suit++) {
    for (int value = 1; value <= 13; value++) {
      deck.elements[index].suit = suit;
      deck.elements[index].value = value;
      index++;
    }
  }

  return deck;
}

void PrintCard(Card *c) { printf("suit: %d, value: %d\n", c->suit, c->value); }
