#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *abash(char doc[]);
void pause();

void main() {
  // Initial variable declaration
  char plainText[MAX];
  char *cipherText = NULL, *newPlainText = NULL;
  int choice;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Encrypt plain text\n");
    printf("[3] Decrypt cipher text\n");
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user plain text input
    if (choice == 1) {
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", plainText);
    }

    // Run abash encryption
    if (choice == 2) {
      // If exists, free allocated memory
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = abash(plainText);
      printf("Cipher Text: %s\n", cipherText);
    }

    // Run abash decryption
    if (choice == 3) {
      // If exists, free allocated memory
      if (newPlainText != NULL) {
        free(newPlainText);
      }
      newPlainText = abash(cipherText);
      printf("Plain Text: %s\n", newPlainText);
    }

    pause();
  } while (choice != 0);
}

/* The Atbash cipher is a particular type of monoalphabetic cipher formed by
  taking the alphabet (or abjad, syllabary, etc.) and mapping it to its reverse,
  so that the first letter becomes the last letter, the second letter becomes
  the second to last letter, and so on. For example, the Latin alphabet would
  work like this.

  To apply this cipher, canipulate character ASCII values with
  'abash(CHAR) = LAST_VAL - (CHAR - FIRST_VAL)' for flipping characters.

  Ex. In numbers 1 - 10, flipping N,
  where number(N) = 3 follows the ff. pattern:
  *      abash(3) = 10 - (3 - 1)
  *            n  = 10 - (2)
  *            n  = 8
*/
char *abash(char doc[]) {
  int i;
  // Allocate pointer memory
  char *result = calloc(strlen(doc), sizeof(char));
  if (result != NULL) {
    for (i = 0; i <= strlen(doc); i++) {
      // If current character is uppercase, flip character value
      if (isupper(doc[i])) {
        result[i] = 'Z' - (doc[i] - 'A');

        // If current character is uppercase, flip character value
      } else if (islower(doc[i])) {
        result[i] = 'z' - (doc[i] - 'a');

        // Direct copy if current character is a symbol or digit
      } else {
        result[i] = doc[i];
      }
    }

    return result;
  }
}

void pause() {
  printf("**press any key to continue**\n");
  getch();
}
