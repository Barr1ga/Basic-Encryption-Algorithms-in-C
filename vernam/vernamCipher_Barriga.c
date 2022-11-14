#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

char *vernamCipher(char text[], char *key);
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
    printf("---------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set key\n");
    printf("[4] Encrypt plain text\n");
    printf("[5] Decrypt cipher text\n");
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
      printf("test");
    }

    // Request user key input
    if (choice == 3) {
      printf("Set key: ");
      fflush(stdin);
      key = generateKey(plainText);
      // scanf("%[^\n]", key);
    }

    // Run polyalphabetic encryption
    if (choice == 4) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (cipherText != NULL) {
          free(cipherText);
        }
        cipherText = vernamCipher(plainText, key);
        printf("Cipher Text: %s\n", cipherText);
      }
    }

    // Run polyalphabetic decryption
    if (choice == 5) {
      // Fails the cipher if key does not exist
      if (requireKey(key) == true) {
        // If exists, free allocated memory
        if (newPlainText != NULL) {
          free(newPlainText);
        }
        newPlainText = vernamCipher(cipherText, key);
        printf("Plain Text: %s\n", newPlainText);
      }
    }

    pause();
  } while (choice != 0);
}

/*
  Vernam Cipher operates on using XOR bit plaintext with key. The length of
  plaintext must be equal with the used key, because on each plaintext
  character, the process of XOR operation being performed using one key
  character

  In the Vernam cipher, each iteration consists of converting each character in
  the text string and the key string into an int value that represent their
  position in the alphabet. These derived int values are then used against each
  other with an XOR operation. The result of this operation then determines the
  output used for the cipher string

  To apply this cipher, manipulate character ASCII values with the ff. formula:
  ENCRYPTION: vernamCipher(TEXT_CHAR, KEY_CHAR) = ((TEXT_CHAR - 'A') ^
  (tolower(KEY_CHAR) - 'a')) % 26 + 'a';

  The following block of code below follows the formula
  in implementing the vernam cipher.
*/
char *vernamCipher(char text[], char *key) {
  // Allocate pointer memory
  char *result = calloc(strlen(text), sizeof(char));

  if (result == NULL || checkLength(text, key) == false) {
    return NULL;
  }

  // Loop through the text string
  for (int textIdx = 0; textIdx < strlen(text); textIdx++) {
    // Check if the current character is a printable character
    if (isgraph(text[textIdx]) && !isspace(text[textIdx])) {
      // If the current character is uppercase, apply the following formula
      if (isupper(text[textIdx])) {
        result[textIdx] =
            ((text[textIdx] - 'A') ^ (tolower(key[textIdx]) - 'a')) % 26 + 'a';
      }

      // If the current character is lowercase, apply the following formula
      if (islower(text[textIdx])) {
        result[textIdx] =
            ((text[textIdx] - 'a') ^ (tolower(key[textIdx]) - 'a')) % 26 + 'a';
      }

      // If the current character is not printable, directly copy the current
      // character into the resulting string
    } else {
      result[textIdx] = text[textIdx];
    }
  }

  return result;
}

char *getFileContent(char fileName[]) {
  int size = 10, textIdx = 0;
  char *result = calloc(size, sizeof(char)), *temp, character;
  FILE *file = fopen(fileName, "r");

  if (result == NULL || file == NULL) {
    return NULL;
  }

  while ((character = fgetc(file)) != EOF) {
    if (textIdx == size - 1) {
      size += 10;
      temp = realloc(result, sizeof(char) * size);
      if (temp != NULL) {
        result = temp;
        free(temp);
      }
    }

    result[textIdx] = character;
    textIdx++;
  }
  printf("%s", result);
  // fclose(file);
  // fclose(file);
  return result;
}

bool writeFileContent(char *text, char fileName[]) {
  FILE *file = fopen(fileName, "w");

  if (file == NULL) {
    printf("There was a problem opening this file!\n");
    return false;
  }

  fprintf(file, "%s", text);
  fclose(file);
  return true;
}

/*
 Function to generate random value key equal to the size of text*/
char *generateKey(char text[]) {
  char *result = calloc(strlen(text), sizeof(char));

  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int textIdx = 0; textIdx < strlen(text); textIdx++) {
    int key = rand() % (int)(sizeof charset - 1);
    result[textIdx] = charset[key];
  }

  return result;
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
