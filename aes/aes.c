#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

char *aes(char text[], char *key);
char *getFileContent(char fileName[]);
bool writeFileContent(char *text, char fileName[]);
bool requireKey(char *key);
char *generateKey(char text[]);
bool checkLength(char text[], char *key);
void pause();

void main() {
  // Initial variable declaration
  char *key = NULL, *plainText = NULL, *cipherText = NULL, *newPlainText = NULL;
  int choice;

  // Menu page
  do {
    system("CLS");
    printf("-------------------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Generate key\n");
    printf("[4] Set key from file\n");
    printf("[5] Set cipher text\n");
    printf("[6] Set cipher text from file\n");
    printf("[7] Encrypt plain text\n");
    printf("[8] Decrypt cipher text\n");
    printf("[9] Save plain text to file\n");
    printf("[10] Save cipher to file\n");
    printf("[11] Save key to file\n");
    printf("[12] Save new plain text to file\n");
    printf("-------------------------------\n");
    printf("Plain text: %s\n", plainText);
    printf("Key: %s\n", key);
    printf("Cipher text: %s\n", cipherText);
    printf("New plain text: %s\n", newPlainText);
    printf("-------------------------------\n");
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

    // Generate random value key
    if (choice == 3) {
      printf("Set key: ");
      fflush(stdin);
      key = generateKey(plainText);
      printf("Key: %s\n", key);
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
        cipherText = aes(plainText, key);
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
        newPlainText = aes(cipherText, key);
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
  aes

  The following block of code below follows the formula
  in implementing the aes cipher.
*/
char *aes(char text[], char *key) {
  // Allocate pointer memory
  char *result = calloc(strlen(text), sizeof(char));
  int textIdx;

  if (result == NULL || checkLength(text, key) == false) {
    return NULL;
  }

  result[textIdx] = '\0';
  return result;
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

/*
  Function to require key input from user
*/
bool requireKey(char *key) {
  if (key == NULL) {
    printf("The key you are using is invalid!\n");
    return false;
  }

  return true;
}

/*
    Function to check if key and text is same length
*/
bool checkLength(char text[], char *key) {
  if (strlen(text) != strlen(key)) {
    printf("The key should have the same length with the text!\n");
    return false;
  }

  return true;
}
