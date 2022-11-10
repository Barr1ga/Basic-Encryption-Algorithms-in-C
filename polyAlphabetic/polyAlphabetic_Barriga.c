#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *polyAlphabeticCipher(char plainText[], char key[], char action[]);
void pause();
bool requireKey(char *key);

void main() {
  // Initial variable declaration
  char plainText[MAX], key[MAX];
  char *cipherText = NULL, *newPlainText = NULL;
  int choice;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set key\n");
    printf("[3] Encrypt plain text\n");
    printf("[4] Decrypt cipher text\n");
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user plain text input
    if (choice == 1) {
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", plainText);
    }

    // Request user key input
    if (choice == 2) {
      printf("Set key: ");
      fflush(stdin);
      scanf("%[^\n]", key);
    }

    // Run polyalphabetic encryption
    if (choice == 3) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (cipherText != NULL) {
          free(cipherText);
        }
        cipherText = polyAlphabeticCipher(plainText, key, "encrypt");
        printf("Cipher Text: %s\n", cipherText);
      }
    }

    // Run polyalphabetic decryption
    if (choice == 4) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (newPlainText != NULL) {
          free(newPlainText);
        }
        newPlainText = polyAlphabeticCipher(cipherText, key, "decrypt");
        printf("Plain Text: %s\n", newPlainText);
      }
    }

    pause();
  } while (choice != 0);
}

/*
  Vigenère cipher is the sequence of Caesar ciphers with different
  transformations on each character of the plain text depending on the current
  character selected in the key. The current character of the key is determined
  by looping through all the characters of the key string iteratively similar to
  a circular array traversal.

  To apply this cipher, manipulate character ASCII values with the ff. formulas:
  ENCRYPTION: shiftCipher(CHAR) = (TEXT_CHAR - FIRST_VAL + (KEY_CHAR -
  FIRST_VAL)) % 10 + FIRST_VAL DECRYPTION: shiftCipher(CHAR) = (TEXT_CHAR -
  FIRST_VAL + (LAST_VAL - (KEY_CHAR - FIRST_VAL))) % 10 + FIRST_VAL

  The following block of code below follows the formula
  of the Vigenère cipher in implementing the polyalphabeic cipher.

  Ex. For simplicity, in numbers 1 - 10, Vigenère cipher encrypts and decrypts
  plain texts by shifting each number(N) by shift(S), where N = 3 and S = 2,
  follows the ff. pattern:
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
char *polyAlphabeticCipher(char plainText[], char key[], char action[]) {
  int textIdx, keyIdx;
  // Allocate pointer memory
  char *result = calloc(strlen(plainText), sizeof(char));
  if (result != NULL) {
    for (textIdx = 0, keyIdx = 0; textIdx <= strlen(plainText);
         textIdx++, keyIdx = (keyIdx + 1) % strlen(key)) {
      // If action == "encrypt", use shift as it is, else, deduct shift from max
      // count of alphabet characters (26)
      int shift = strcmp(action, "encrypt") == 0
                      ? tolower(key[keyIdx]) - 'a'
                      : 26 - (tolower(key[keyIdx]) - 'a');

      if (isalnum(plainText[textIdx])) {
        // If current character is digit, shift character ASCII values
        if (isdigit(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - '0' + shift) % 10 + '0';
        }
        // If current character is digit, shift character ASCII values
        if (islower(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - 'a' + shift) % 26 + 'a';
        }
        // If current character is digit, shift character ASCII values
        if (isupper(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - 'A' + shift) % 26 + 'A';
        }
        // If current character is neither, directly copy
      } else {
        result[textIdx] = plainText[textIdx];
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
  Function to require key input from user
*/
bool requireKey(char *key) {
  if (key == NULL) {
    printf("Please enter a valid key!\n");
    return false;
  }

  return true;
}
