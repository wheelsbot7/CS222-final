/*
 * main.c - main file for Final Project
 * Authoer:
 * Date:
 * Purpose:
 */
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void OnePloop(Deck *deck) {
  Card current = *getNextCard(deck);
  int valid = 1;
  int roundValid = 1;
  int chips = 1000;
  int bet = 10;
  int dealScore = 0;
  int pScore = 0;
  char buffer[20];
  int hitting;
  while (valid) {
    while (roundValid) {
      while (1) {
        printf("You have %d chips. Enter your current bet: ", chips);
        fgets(buffer, 20, stdin);
        bet = atoi(buffer);
        if (bet > chips) {
          printf("You don't have that many chips.\n");
        } else {
          break;
        }
      }
      dealScore = 0;
      pScore = 0;
      hitting = 1;
      roundValid = 1;
      // Individual round logic
      printf("Dealer's face-up card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      dealScore += getValue(current.rank);
      printf("Dealer's current score: %d\n", dealScore);
      current = *getNextCard(deck);
      printf("Dealer's face-down card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      dealScore += getValue(current.rank);
      printf("Dealer's SECRET score: %d (pretend you can't see this)\n",
             dealScore);

      current = *getNextCard(deck);
      printf("Your cards: \n%s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      pScore += getValue(current.rank);
      current = *getNextCard(deck);
      printf("%s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      pScore += getValue(current.rank);
      while (hitting) {
        if (pScore > 21) {
          chips -= bet;
          printf("Current score: %d\n", pScore);
          printf("Busted! You now have %d chips\n", chips);
          roundValid = 0;
          hitting = 0;
        } else {
          printf("Current score: %d\n", pScore);
          printf("Hit or Stand? (h/S): ");
          fgets(buffer, 20, stdin);
          if (!strcmp(buffer, "h\n") || !strcmp(buffer, "H\n")) {
            current = *getNextCard(deck);
            printf("%s of %s\n", getRankName(current.rank),
                   getSuitName(current.suit));
            pScore += getValue(current.rank);
          } else {
            hitting = 0;
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
    }
    printf("Try again? (y/N): ");
    fgets(buffer, 20, stdin);
    if (!strcmp(buffer, "y\n") || !strcmp(buffer, "Y\n")) {
      roundValid = 1;
      current = *getNextCard(deck);
      continue;
    } else {
      valid = 0;
    }
  }
}

void TwoPloop(Deck *deck) {
  Card current = *getNextCard(deck);
  printf("Draw 2 cards\n");
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
  current = *getNextCard(deck);
  printf("%s of %s\n", getRankName(current.rank), getSuitName(current.suit));
}

int main() {
  // Create a deck of cards
  Deck *deck = createDeck();
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
