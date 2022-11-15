#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *polyAlphabeticCipher(char plainText[], char key[], char action[]);
char *getFileContent(char fileName[]);
bool writeFileContent(char *text, char fileName[]);
void pause();
bool requireKey(char *key);

void main() {
  // Initial variable declaration
  char *plainText = NULL, *key = NULL, *cipherText = NULL, *newPlainText = NULL;
  int choice;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set key\n");
    printf("[4] Set key from file\n");
    printf("[5] Set cipher text\n");
    printf("[6] Set cipher text from file\n");
    printf("[7] Encrypt plain text\n");
    printf("[8] Decrypt cipher text\n");
    printf("[9] Save plain text to file\n");
    printf("[10] Save cipher to file\n");
    printf("[11] Save key to file\n");
    printf("[12] Save new plain text to file\n");
    printf("---------------------\n");
    printf("Plain text: %s\n", plainText);
    printf("Key: %s\n", key);
    printf("Cipher text: %s\n", cipherText);
    printf("New plain text: %s\n", newPlainText);
    printf("---------------------\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Request user plain text input
    if (choice == 1) {
      if (plainText != NULL) {
        free(plainText);
      }
      plainText = calloc(MAX, sizeof(char));
      printf("Set plain text: ");
      fflush(stdin);
      scanf("%[^\n]", plainText);
    }

    // Set plain text from file
    if (choice == 2) {
      char fileName[MAX];
      if (plainText != NULL) {
        free(plainText);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      plainText = getFileContent(fileName);
      printf("Plain text: %s\n", plainText);
    }

    // Request user key input
    if (choice == 3) {
      if (key != NULL) {
        free(key);
      }
      key = calloc(MAX, sizeof(char));
      printf("Set key: ");
      fflush(stdin);
      scanf("%[^\n]", key);
    }

    // Request user key from file
    if (choice == 4) {
      char fileName[MAX];
      if (key != NULL) {
        free(key);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      key = getFileContent(fileName);
      printf("Key: %s\n", key);
    }

    // Request user cipher text input
    if (choice == 5) {
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = calloc(MAX, sizeof(char));
      printf("Set cipher text: ");
      fflush(stdin);
      scanf("%[^\n]", cipherText);
    }

    // Set cipher text from file
    if (choice == 6) {
      char fileName[MAX];
      if (cipherText != NULL) {
        free(cipherText);
      }
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      cipherText = getFileContent(fileName);
      printf("Cipher text: %s\n", cipherText);
    }

    // Run polyalphabetic encryption
    if (choice == 7) {
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
    if (choice == 8) {
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

    // Save plain text to file
    if (choice == 9) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(plainText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save cipher text to file
    if (choice == 10) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(cipherText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save key to file
    if (choice == 11) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(key, fileName)) {
        printf("Saved\n");
      }
    }

    // Save new plain text to file
    if (choice == 12) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(newPlainText, fileName)) {
        printf("Saved\n");
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
// v
// cab
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

/*
 Function to read contents from a file into a text string
*/
char *getFileContent(char fileName[]) {
  int size = MAX, textIdx = 0;
  char *result = calloc(size, sizeof(char)), *temp, character;
  FILE *file = fopen(fileName, "r");

  // Guard clause to fail file reading if memory wasnt allocated or file pointer
  // returns null
  if (result == NULL || file == NULL) {
    return NULL;
  }

  // Loop through the file contents by character
  while ((character = fgetc(file)) != EOF) {
    // Reallocate memory to fit data if index reaches the last byte
    if (textIdx == size - 1) {
      size += MAX;
      temp = realloc(result, sizeof(char) * size);
      if (temp != NULL) {
        result = temp;
        free(temp);
      }
    }

    // Save current character from file
    result[textIdx] = character;
    textIdx++;
  }

  // Close file pointer
  fclose(file);
  result[textIdx] = '\0';
  return result;
}

/*
 Function to write contents from a text string into a file
*/
bool writeFileContent(char *text, char fileName[]) {
  FILE *file = fopen(fileName, "w");

  // Guard clause to fail writing if text string and file pointer is null
  if (file == NULL || text == NULL) {
    return false;
  }

  // Write into file
  fprintf(file, "%s", text);

  // Close file pointer
  fclose(file);
  return true;
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
