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
  int valid = 1;
  int roundValid = 1;
  int chips = 1000;
  int bet = 10;
  int dealScore = 0;
  int pScore = 0;
  char buffer[20];
  while (valid) {
    printf("Dealer's face-up card: %s of %s\n", getRankName(current.rank),
           getSuitName(current.suit));
    dealScore += getValue(current.rank);
    printf("Dealer's current score: %d\n", dealScore);
    current = *current.next;
    printf("Dealer's face-down card: %s of %s\n", getRankName(current.rank),
           getSuitName(current.suit));
    dealScore += getValue(current.rank);
    printf("Dealer's SECRET score: %d\n", dealScore);
    // Individual round logic

    current = *current.next;
    printf("Your cards: \n%s of %s\n", getRankName(current.rank),
           getSuitName(current.suit));
    pScore += getValue(current.rank);
    current = *current.next;
    printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
    pScore += getValue(current.rank);
    while (roundValid) {
      if (pScore > 21) {
        printf("%d Busted.\n", pScore);
        roundValid = 0;
      } else {
        printf("Current score: %d\n", pScore);
        printf("Hit or Stand? (h/S): ");
        fgets(buffer, 20, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (!strcmp(buffer, "h\n") || !strcmp(buffer, "H\n")) {
          current = *current.next;
          printf("%s of %s\n", getRankName(current.rank),
                 getSuitName(current.suit));
          pScore += getValue(current.rank);
        } else {
          if (pScore > dealScore) {
            chips += bet;
            printf("Jackpot! You now have %d chips\n", chips);
            roundValid = 0;
          } else if (pScore == dealScore) {
            printf("Tie! You now have %d chips\n", chips);
            roundValid = 0;
          } else {
            chips -= bet;
            printf("Busted! You now have %d chips\n", chips);
            roundValid = 0;
          }
        }
      }
    }
    valid = 0;
  }
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
  fgets(buffer, 20, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  if (atoi(buffer) == 1) {
    OnePloop(deck);
  } else {
    TwoPloop(deck);
  }
  freeDeck(deck);

  return 0;
}
