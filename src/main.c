/*
 * main.c - main file for Project 3 SIMS
 * Authoer:
 * Date:
 * Purpose:
 */
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void OnePloop(Card *deck) {
  Card current = *deck;
  printf("Draw 2 cards\n");
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
  current = *current.next;
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
}

void TwoPloop(Card *deck) {
  Card current = *deck;
  printf("Draw 2 cards\n");
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
  current = *current.next;
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
}

int main() {
  // Create a deck of cards
  Card *deck = createDeck();
  char buffer[20];
  shuffleDeck(deck);

  printf("1 or 2 Players? ");
  fgets(buffer, 2, stdin);
  if (atoi(buffer) == 1) {
    OnePloop(deck);
  } else {
    TwoPloop(deck);
  }
  freeDeck(deck);

  return 0;
}
