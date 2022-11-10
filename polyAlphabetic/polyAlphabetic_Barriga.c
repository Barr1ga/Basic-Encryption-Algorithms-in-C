#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *polyAlphabeticCipher(char plainText[], char key[], char action[]);
void pause();

void main() {
  char plainText[MAX], key[MAX];
  char *cipherText = NULL, *newPlainText = NULL;
  int choice;

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

    if (choice == 1) {
      printf("Set plain text: ");
      scanf("%s", plainText);
    }

    if (choice == 2) {
      printf("Set key: ");
      scanf("%s", key);
    }

    if (choice == 3) {
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = polyAlphabeticCipher(plainText, key, "encrypt");
      printf("Cipher Text: %s\n", cipherText);
    }

    if (choice == 4) {
      if (newPlainText != NULL) {
        free(newPlainText);
      }
      newPlainText = polyAlphabeticCipher(cipherText, key, "decrypt");
      printf("Cipher Text: %s\n", newPlainText);
    }

    pause();
  } while (choice != 0);
}

char *polyAlphabeticCipher(char plainText[], char key[], char action[]) {
  int textIdx, keyIdx;
  char *result = calloc(strlen(plainText), sizeof(char));
  if (result != NULL) {
    for (textIdx = 0, keyIdx = 0; textIdx <= strlen(plainText);
         textIdx++, keyIdx = (keyIdx + 1) % strlen(key)) {
      int shift = strcmp(action, "encrypt") == 0
                      ? tolower(key[keyIdx]) - 'a'
                      : 26 - (tolower(key[keyIdx]) - 'a');

      if (isalnum(plainText[textIdx])) {
        if (isdigit(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - '0' + shift) % 10 + '0';
        }
        if (islower(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - 'a' + shift) % 26 + 'a';
        }
        if (isupper(plainText[textIdx])) {
          result[textIdx] = (plainText[textIdx] - 'A' + shift) % 26 + 'A';
        }
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
