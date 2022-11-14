#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *abash(char doc[]);
char *getFileContent(char fileName[]);
bool writeFileContent(char *text, char fileName[]);
void pause();

void main() {
  // Initial variable declaration
  char *plainText = NULL, *cipherText = NULL, *newPlainText = NULL;
  int choice;

  // Menu page
  do {
    system("CLS");
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set cipher text\n");
    printf("[4] Set cipher text from file\n");
    printf("[5] Encrypt plain text\n");
    printf("[6] Decrypt cipher text\n");
    printf("[7] Save plain text to file\n");
    printf("[8] Save cipher to file\n");
    printf("[9] Save new plain text to file\n");
    printf("---------------------\n");
    printf("Plain text: %s\n", plainText);
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
    }

    // Request user cipher text input
    if (choice == 3) {
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = calloc(MAX, sizeof(char));
      printf("Set cipher text: ");
      fflush(stdin);
      scanf("%[^\n]", cipherText);
    }

    // Set cipher text from file
    if (choice == 4) {
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

    // Run abash encryption
    if (choice == 5) {
      // If exists, free allocated memory
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = abash(plainText);
      printf("Cipher Text: %s\n", cipherText);
    }

    // Run abash decryption
    if (choice == 6) {
      // If exists, free allocated memory
      if (newPlainText != NULL) {
        free(newPlainText);
      }
      newPlainText = abash(cipherText);
      printf("Plain Text: %s\n", newPlainText);
    }

    // Save plain text to file
    if (choice == 7) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(plainText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save cipher text to file
    if (choice == 8) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(cipherText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save new plain text to file
    if (choice == 9) {
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
