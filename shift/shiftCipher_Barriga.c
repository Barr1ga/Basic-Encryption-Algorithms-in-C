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
  char doc[MAX];
  int choice, shift = 0;
  char *cipher = NULL, *decryptedDoc = NULL;

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

    if (choice == 1) {
      printf("Set document text: ");
      scanf("%s", doc);
    }

    if (choice == 2) {
      printf("Enter shift count: ");
      scanf("%d", &shift);
    }

    if (choice == 3) {
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
        if (cipher != NULL) {
          free(cipher);
        }
        cipher = shiftCipher(doc, shift, "encrypt");
        printf("Cipher: %s\n", cipher);
      }
    }

    if (choice == 4) {
      if (requireShift(shift) == true) {
        printf("Shift count [%d]\n", shift);
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

char *shiftCipher(char doc[], int shift, char action[]) {
  int i;
  char *result = calloc(strlen(doc), sizeof(char));
  if (result != NULL) {
    shift = strcmp(action, "encrypt") == 0 ? shift : 26 - shift;
    for (i = 0; i <= strlen(doc); i++) {
      if (isalnum(doc[i])) {
        if (isdigit(doc[i])) {
          result[i] = (doc[i] - '0' + shift) % 10 + '0';
        }
        if (islower(doc[i])) {
          result[i] = (doc[i] - 'a' + shift) % 26 + 'a';
        }
        if (isupper(doc[i])) {
          result[i] = (doc[i] - 'A' + shift) % 26 + 'A';
        }
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

bool requireShift(int shift) {
  if (shift == 0) {
    printf("Please enter a valid shift count!\n");
    return false;
  }

  return true;
}
