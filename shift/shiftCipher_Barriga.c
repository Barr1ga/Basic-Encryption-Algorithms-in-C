#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *shiftCipher(char doc[], int shift, char action[]);
void pause();
bool requireShift(int shift);

void main() {
  // Initial variable declaration
  char doc[MAX];
  int choice, shift = 0;
  char *cipher = NULL, *decryptedDoc = NULL;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set Document\n");
    printf("[2] Set Shift Count\n");
    printf("[3] Encrypt Document\n");
    printf("[4] Decrypt Document\n");
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user key input
    if (choice == 1) {
      printf("Set document text: ");
      scanf("%s", doc);
    }

    // Request user shift count input
    if (choice == 2) {
      printf("Enter shift count: ");
      scanf("%d", &shift);
    }

    // Run shift encryption
    if (choice == 3) {
      // Fails the cipher if key does not exist
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
        // If exists, free allocated memory
        if (cipher != NULL) {
          free(cipher);
        }
        cipher = shiftCipher(doc, shift, "encrypt");
        printf("Cipher: %s\n", cipher);
      }
    }

    // Run shift decryption
    if (choice == 4) {
      // Fails the cipher if key does not exist
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
        // If exists, free allocated memory
        if (decryptedDoc != NULL) {
          free(decryptedDoc);
        }
        decryptedDoc = shiftCipher(cipher, shift, "decrypt");
        printf("Decrypted document: %s\n", decryptedDoc);
      }
    }

    pause();
  } while (choice != 0);
}

/*
  A shift cipher involves replacing each letter in the message by a letter that
  is some fixed number of positions further along in the alphabet.

  To apply this cipher, manipulate character ASCII values with the ff. formulas:
  ENCRYPTION: shiftCipher(CHAR) = (CHAR - FIRST_VAL + SHIFT) % 10 + FIRST_VAL
  DECRYPTION: shiftCipher(CHAR) = (CHAR - FIRST_VAL + (LAST_VAL - SHIFT)) % 10 +
  FIRST_VAL

  The following block of code below follows the formula
  of the shift cipher.

  Ex. For simplicity, in numbers 1 - 10, shift cipher encrypts and decrypts
  plain texts by shifting each number(N) by shift(S), where N = 3 and S = 2,
  follows the ff.
  * shiftCipher(3) = (3 - 1 + 2) % 10 + 1
  *             n  = (4) % 10 + 1
  *             n  = 4 + 1
  *             n  = 5
  * shiftCipher(5) = (5 - 1 + (10 - 2)) % 10 + 1
  *             n  = (5 - 1 + 8) % 10 + 1
  *             n  = (12) % 10 + 1
  *             n  = 2 + 1
  *             n  = 3
*/
char *shiftCipher(char doc[], int shift, char action[]) {
  int i;
  char *result = calloc(strlen(doc), sizeof(char));
  if (result != NULL) {
    shift = strcmp(action, "encrypt") == 0 ? shift : 26 - shift;
    for (i = 0; i <= strlen(doc); i++) {
      // If current character is digit, shift character ASCII values
      if (isalnum(doc[i])) {
        if (isdigit(doc[i])) {
          result[i] = (doc[i] - '0' + shift) % 10 + '0';
        }
        // If current character is digit, shift character ASCII values
        if (islower(doc[i])) {
          result[i] = (doc[i] - 'a' + shift) % 26 + 'a';
        }
        // If current character is digit, shift character ASCII values
        if (isupper(doc[i])) {
          result[i] = (doc[i] - 'A' + shift) % 26 + 'A';
        }
        // If current character is neither, directly copy
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

/*
  Function to require shift input from user
*/
bool requireShift(int shift) {
  if (shift == 0) {
    printf("Please enter a valid shift count!\n");
    return false;
  }

  return true;
}
