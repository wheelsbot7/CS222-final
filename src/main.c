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

int main(int argc, char *argv[]) {
  vector deck = InitDeck();
  int i;
  for (i = 0; i < 52; ++i) {
    PrintCard(&deck.elements[i]);
  }
  return 0;
}
