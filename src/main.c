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
  Card current;
  int valid = 1;
  int roundValid = 1;
  int chips = 1000;
  int bet = 0;
  int dealScore = 0;
  int pScore = 0;
  char buffer[20];
  int hitting;

  while (valid) {
    while (roundValid) {
      // Get bets
      while (1) {
        printf("You have %d chips. Enter your bet: ", chips);
        fgets(buffer, 20, stdin);
        bet = atoi(buffer);
        if (bet > chips) {
          printf("You don't have that many chips.\n");
        } else {
          break;
        }
      }

      // Reset scores
      dealScore = 0;
      pScore = 0;
      roundValid = 1;

      // Deal initial cards
      printf("\n=== Dealer's Cards ===\n");
      current = *getNextCard(deck);
      printf("Face-up card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      dealScore += getValue(current.rank);

      current = *getNextCard(deck);
      printf("Face-down card: [Hidden]\n");
      dealScore += getValue(current.rank);

      // Player turn
      printf("\n=== Player Turn ===\n");
      pScore = 0;
      hitting = 1;

      // Deal initial two cards
      current = *getNextCard(deck);
      printf("Card 1: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      pScore += getValue(current.rank);

      current = *getNextCard(deck);
      printf("Card 2: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      pScore += getValue(current.rank);

      // Hit/Stand loop
      while (hitting && pScore <= 21) {
        printf("Current score: %d\n", pScore);
        printf("Hit or Stand? (h/S): ");
        fgets(buffer, 20, stdin);
        if (!strcmp(buffer, "h\n") || !strcmp(buffer, "H\n")) {
          current = *getNextCard(deck);
          printf("New card: %s of %s\n", getRankName(current.rank),
                 getSuitName(current.suit));
          pScore += getValue(current.rank);

          if (pScore > 21) {
            printf("Busted! Score: %d\n", pScore);
            hitting = 0;
          }
        } else {
          hitting = 0;
        }
      }

      // Dealer's turn
      printf("\n=== Dealer's Turn ===\n");
      printf("Revealing face-down card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      printf("Dealer's total: %d\n", dealScore);

      // Dealer hits until 17 or higher
      while (dealScore < 17) {
        current = *getNextCard(deck);
        printf("Dealer hits: %s of %s\n", getRankName(current.rank),
               getSuitName(current.suit));
        dealScore += getValue(current.rank);
        printf("Dealer's new total: %d\n", dealScore);
      }

      // Determine results
      printf("\n=== Final Results ===\n");
      if (dealScore > 21) {
        printf("Dealer busted!\n");
      } else {
        printf("Dealer's final score: %d\n", dealScore);
      }

      printf("\nPlayer result:\n");
      printf("Your score: %d vs Dealer: %d\n", pScore, dealScore);

      if (pScore > 21) {
        printf("You busted! Lost %d chips\n", bet);
        chips -= bet;
      } else if (dealScore > 21) {
        printf("Dealer busted! You win %d chips\n", bet);
        chips += bet;
      } else if (pScore > dealScore) {
        printf("You win! Gained %d chips\n", bet);
        chips += bet;
      } else if (pScore == dealScore) {
        printf("Push! Your bet is returned\n");
      } else {
        printf("You lose! Lost %d chips\n", bet);
        chips -= bet;
      }
      printf("Player now has %d chips\n", chips);

      // Check if player has chips left
      roundValid = 0;
      if (chips > 0) {
        roundValid = 1;
      } else {
        printf("Player is out of chips!\n");
      }
    }

    // Check if player wants to continue
    printf("\nPlay another round? (y/N): ");
    fgets(buffer, 20, stdin);
    if (!strcmp(buffer, "y\n") || !strcmp(buffer, "Y\n")) {
      roundValid = 1;
      current = *getNextCard(deck);
    } else {
      valid = 0;
    }
  }

  printf("\n=== Game Over ===\n");
  printf("Final chip count:\n");
  printf("%d chips\n", chips);
}
void TwoPloop(Deck *deck) {
  Card current;
  int valid = 1;
  int roundValid = 1;
  int chips[2] = {1000, 1000}; // Chips for player 1 and player 2
  int bets[2] = {0, 0};
  int dealScore = 0;
  int pScores[2] = {0, 0};
  char buffer[20];
  int hitting;
  int currentPlayer;

  while (valid) {
    while (roundValid) {
      // Get bets from both players
      for (int i = 0; i < 2; i++) {
        while (1) {
          printf("Player %d, you have %d chips. Enter your bet: ", i + 1,
                 chips[i]);
          fgets(buffer, 20, stdin);
          bets[i] = atoi(buffer);
          if (bets[i] > chips[i]) {
            printf("You don't have that many chips.\n");
          } else {
            break;
          }
        }
      }

      // Reset scores
      dealScore = 0;
      pScores[0] = 0;
      pScores[1] = 0;
      roundValid = 1;

      // Deal initial cards
      printf("\n=== Dealer's Cards ===\n");
      current = *getNextCard(deck);
      printf("Face-up card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      dealScore += getValue(current.rank);

      current = *getNextCard(deck);
      printf("Face-down card: [Hidden]\n");
      dealScore += getValue(current.rank);

      // Player turns
      for (currentPlayer = 0; currentPlayer < 2; currentPlayer++) {
        printf("\n=== Player %d's Turn ===\n", currentPlayer + 1);
        pScores[currentPlayer] = 0;
        hitting = 1;

        // Deal initial two cards
        current = *getNextCard(deck);
        printf("Card 1: %s of %s\n", getRankName(current.rank),
               getSuitName(current.suit));
        pScores[currentPlayer] += getValue(current.rank);

        current = *getNextCard(deck);
        printf("Card 2: %s of %s\n", getRankName(current.rank),
               getSuitName(current.suit));
        pScores[currentPlayer] += getValue(current.rank);

        // Hit/Stand loop
        while (hitting && pScores[currentPlayer] <= 21) {
          printf("Current score: %d\n", pScores[currentPlayer]);
          printf("Hit or Stand? (h/S): ");
          fgets(buffer, 20, stdin);
          if (!strcmp(buffer, "h\n") || !strcmp(buffer, "H\n")) {
            current = *getNextCard(deck);
            printf("New card: %s of %s\n", getRankName(current.rank),
                   getSuitName(current.suit));
            pScores[currentPlayer] += getValue(current.rank);

            if (pScores[currentPlayer] > 21) {
              printf("Busted! Score: %d\n", pScores[currentPlayer]);
              hitting = 0;
            }
          } else {
            hitting = 0;
          }
        }
      }

      // Dealer's turn
      printf("\n=== Dealer's Turn ===\n");
      printf("Revealing face-down card: %s of %s\n", getRankName(current.rank),
             getSuitName(current.suit));
      printf("Dealer's total: %d\n", dealScore);

      // Dealer hits until 17 or higher
      while (dealScore < 17) {
        current = *getNextCard(deck);
        printf("Dealer hits: %s of %s\n", getRankName(current.rank),
               getSuitName(current.suit));
        dealScore += getValue(current.rank);
        printf("Dealer's new total: %d\n", dealScore);
      }

      // Determine results for each player
      printf("\n=== Final Results ===\n");
      if (dealScore > 21) {
        printf("Dealer busted!\n");
      } else {
        printf("Dealer's final score: %d\n", dealScore);
      }

      for (int i = 0; i < 2; i++) {
        printf("\nPlayer %d's result:\n", i + 1);
        printf("Your score: %d vs Dealer: %d\n", pScores[i], dealScore);

        if (pScores[i] > 21) {
          printf("You busted! Lost %d chips\n", bets[i]);
          chips[i] -= bets[i];
        } else if (dealScore > 21) {
          printf("Dealer busted! You win %d chips\n", bets[i]);
          chips[i] += bets[i];
        } else if (pScores[i] > dealScore) {
          printf("You win! Gained %d chips\n", bets[i]);
          chips[i] += bets[i];
        } else if (pScores[i] == dealScore) {
          printf("Push! Your bet is returned\n");
        } else {
          printf("You lose! Lost %d chips\n", bets[i]);
          chips[i] -= bets[i];
        }
        printf("Player %d now has %d chips\n", i + 1, chips[i]);
      }

      // Check if any player has chips left
      roundValid = 0;
      for (int i = 0; i < 2; i++) {
        if (chips[i] > 0) {
          roundValid = 1;
        } else {
          printf("Player %d is out of chips!\n", i + 1);
        }
      }
    }

    // Check if players want to continue
    printf("\nPlay another round? (y/N): ");
    fgets(buffer, 20, stdin);
    if (!strcmp(buffer, "y\n") || !strcmp(buffer, "Y\n")) {
      roundValid = 1;
      current = *getNextCard(deck);
    } else {
      valid = 0;
    }
  }

  printf("\n=== Game Over ===\n");
  printf("Final chip counts:\n");
  for (int i = 0; i < 2; i++) {
    printf("Player %d: %d chips\n", i + 1, chips[i]);
  }
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
