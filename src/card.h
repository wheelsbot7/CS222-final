#ifndef CARD_H
#define CARD_H

#include <stdio.h>

typedef struct card_struct {
  int suit;
  int value;
} Card;

typedef struct deck_struct {
  Card *elements;
  unsigned int size;
} vector;

vector InitDeck();
void PrintCard(Card *c);
#endif
