#include <conio.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define ENCRYPT 1
#define DECRYPT 0

char *rsa(char text[], int key, int product);
char *getFileContent(char fileName[]);
void setPrimePairsFromString(char *primePairString, int *primeP, int *primeQ);
void pause();
void setPublicKey(int *publicKey, int totient);
void setPrimePairFromString(char *primeString, int *primeP, int *primeQ);
void setPrivateKey(int *privateKey, int publicKey, int totient);
void setProduct(int *product, int primeP, int primeQ);
void setTotient(int *totient, int primeP, int primeQ);
void setPrimePairs(int *primeP, int *primeQ);
bool isPrime(int number);
bool writeFileContent(char *text, char fileName[]);
bool isFactorOfNumber(int x, int number);
bool requirePrimePair(int primeP, int primeQ);
bool requireTotient(int totient);
bool requirePublicKey(int publicKey);
long long int power(char base, int power);

void main() {
  // Initial variable declaration
  char *primeString = NULL, *keyString = NULL, *plainText = NULL,
       *cipherText = NULL, *newPlainText = NULL;
  // int primeP = -1, primeQ = -1, privateKey = -1, publicKey = -1, product =
  // -1,
  //     totient = -1, choice;
  int primeP = 2, primeQ = 13, privateKey = -1, publicKey = 5, product = 26,
      totient = 12, choice;

  // Menu page
  do {
    system("CLS");
    printf("-------------------------------\n");
    printf("[0] Exit\n");
    printf("[1] Set plain text\n");
    printf("[2] Set plain text from file\n");
    printf("[3] Set prime numbers\n");
    printf("[4] Set prime numbers from file\n");
    printf("[5] Set product\n");
    printf("[6] Set totient\n");
    printf("[7] Set public key\n");
    printf("[8] Set public key from file\n");
    printf("[9] Set private key\n");
    printf("[10] Set private key from file\n");
    printf("[11] Set cipher text\n");
    printf("[12] Set cipher text from file\n");
    printf("[13] Encrypt plain text\n");
    printf("[14] Decrypt cipher text\n");
    printf("[15] Save plain text to file\n");
    printf("[16] Save prime numbers to file\n");
    printf("[17] Save public key to file\n");
    printf("[18] Save private key to file\n");
    printf("[19] Save cipher to file\n");
    printf("[20] Save new plain text to file\n");
    printf("-------------------------------\n");
    printf("Product: %d\n", product);
    printf("Totient: %d\n", totient);
    printf("Public key: %d\n", publicKey);
    printf("Private key: %d\n", privateKey);
    printf("Prime numbers: (%d, %d)\n", primeP, primeQ);
    printf("Plain text: %s\n", plainText);
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

    // Request user prime pair input
    if (choice == 3) {
      fflush(stdin);
      setPrimePairs(&primeP, &primeQ);
      printf("Prime numbers: (%d, %d)\n", primeP, primeQ);
    }

    // Set prime pair from file
    if (choice == 4) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      primeString = getFileContent(fileName);
      setPrimePairFromString(primeString, &primeP, &primeQ);
      printf("Prime numbers: (%d, %d)\n", primeP, primeQ);
    }

    // Set product
    if (choice == 5) {
      if (requirePrimePair(primeP, primeQ) == true) {
        setProduct(&product, primeP, primeQ);
        printf("Product: %d\n", product);
      }
    }

    // Set totient
    if (choice == 6) {
      if (requirePrimePair(primeP, primeQ) == true) {
        setTotient(&totient, primeP, primeQ);
        printf("Totient: %d\n", totient);
      }
    }

    // Set public key
    if (choice == 7) {
      if (requireTotient(totient) == true) {
        setPublicKey(&publicKey, totient);
        printf("Public key: %d\n", publicKey);
      }
    }

    // Set public key from file
    if (choice == 8) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (keyString != NULL) {
        free(keyString);
      }
      keyString = getFileContent(fileName);
      publicKey = atoi(keyString);
      printf("Public key: %d\n", publicKey);
    }

    // Set private key
    if (choice == 9) {
      if (requirePublicKey(publicKey) == true &&
          requireTotient(totient) == true) {
        setPrivateKey(&privateKey, publicKey, totient);
        printf("Private key: %d\n", privateKey);
      }
    }

    // Set private key from file
    if (choice == 10) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (keyString != NULL) {
        free(keyString);
      }
      keyString = getFileContent(fileName);
      publicKey = atoi(keyString);
      printf("Public key: %d\n", publicKey);
    }

    // Request user cipher text input
    if (choice == 11) {
      if (cipherText != NULL) {
        free(cipherText);
      }
      cipherText = calloc(MAX, sizeof(char));
      printf("Set cipher text: ");
      fflush(stdin);
      scanf("%[^\n]", cipherText);
    }

    // Set cipher text from file
    if (choice == 12) {
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

    // Run rsa encryption
    if (choice == 13) {
      // Fails the cipher if key does not exist
      if (requirePrimePair(primeP, primeQ) == true) {
        // If exists, free allocated memory
        if (cipherText != NULL) {
          free(cipherText);
        }
        cipherText = rsa(plainText, privateKey, product);
        printf("Cipher Text: %s\n", cipherText);
      }
    }

    // Run rsa decryption
    if (choice == 14) {
      // Fails the cipher if key does not exist
      if (requirePrimePair(primeP, primeQ) == true) {
        // If exists, free allocated memory
        if (newPlainText != NULL) {
          free(newPlainText);
        }
        newPlainText = rsa(cipherText, publicKey, product);
        printf("Plain Text: %s\n", newPlainText);
      }
    }

    // Save plain text to file
    if (choice == 15) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(plainText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save prime numbers to file
    if (choice == 16) {
      char temp[MAX];
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);

      if (primeString != NULL) {
        free(primeString);
      }

      primeString = calloc(MAX, sizeof(char));
      sprintf(temp, "%d", primeP);
      strcat(primeString, temp);
      primeString[strlen(primeString)] = ',';
      sprintf(temp, "%d", primeQ);
      strcat(primeString, temp);

      if (writeFileContent(primeString, fileName)) {
        printf("Saved\n");
      }
    }

    // Save public key to file
    if (choice == 17) {
      char temp[MAX];
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);

      sprintf(temp, "%d", publicKey);
      if (writeFileContent(temp, fileName)) {
        printf("Saved\n");
      }
    }

    // Save private key to file
    if (choice == 18) {
      char temp[MAX];
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);

      sprintf(temp, "%d", privateKey);
      if (writeFileContent(temp, fileName)) {
        printf("Saved\n");
      }
    }

    // Save cipher text to file
    if (choice == 19) {
      char fileName[MAX];
      printf("File name: ");
      fflush(stdin);
      scanf("%[^\n]", fileName);
      if (writeFileContent(cipherText, fileName)) {
        printf("Saved\n");
      }
    }

    // Save new plain text to file
    if (choice == 20) {
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
  ## Generate keys:
      * Select two prime numbers
      * Calculate PRODUCT = (PRIME_P * PRIME_Q)
      * Calculate TOTIENT = (PRIME_P - 1) * (PRIME_Q - 1)
      * Select PUBLIC_KEY
          * Must be prime
          * Must not be less than TOTIENT
          * Must not be a factor of the TOTIENT
      * Select private key
          * Product of PRIVATE_KEY and PUBLIC_KEY, divided by TOTIENT must
  result in a remainder of 1
          * (PRIVATE_KEY * PUBLIC_KEY) % TOTIENT = 1
*/
char *rsa(char text[], int key, int product) {
  char *result = calloc(strlen(text), sizeof(char));
  int textIdx;

  if (result == NULL && key == -1) {
    return NULL;
  }
  printf("rsa\n");
  printf("key: %d\n", key);
  for (textIdx = 0; textIdx < strlen(text); textIdx++) {
    if (isgraph(text[textIdx]) && !isspace(text[textIdx])) {
      if (isupper(text[textIdx])) {
        result[textIdx] =
            (char)((power((text[textIdx] - 'A'), key) % product) + 'A');
      }

      if (islower(text[textIdx])) {
        result[textIdx] =
            (char)((power((text[textIdx] - 'a'), key) % product) + 'a');
      }
    } else {
      result[textIdx] = text[textIdx];
    }
  }
  return result;
}

/*
  Function to set public key with respect to the ff. constraints
  * Must be prime
  * Must be less than totient
  * Must not be a factor of the totient
*/
void setPublicKey(int *publicKey, int totient) {
  int tempNum;
  do {
    printf(" * Must be prime\n");
    printf(" * Must be less than totient\n");
    printf(" * Must not be a factor of the totient\n");
    printf("Enter public key value: ");
    fflush(stdin);
    scanf("%d", &tempNum);

    if (!isPrime(tempNum) || isFactorOfNumber(tempNum, totient) == true) {
      printf("Please enter a valid a public key!\n");
    }

  } while (!isPrime(tempNum) || isFactorOfNumber(tempNum, totient) == true);

  *publicKey = tempNum;
}

/*
  Function to set private key with respect to the ff. constraints
  * Product of private key and public key, divided by totient must result in a
  remainder of 1
  * (PRIVATE_KEY * PUBLIC_KEY) mod TOTIENT = 1
*/
void setPrivateKey(int *privateKey, int publicKey, int totient) {
  int tempNum, idx;

  for (idx = MAX; idx >= 0; idx--) {
    if ((idx * publicKey) % totient == 1) {
      tempNum = idx;
    }
  }

  *privateKey = tempNum;
}

/*
  Function to set prime pair from string
*/
void setPrimePairFromString(char *primeString, int *primeP, int *primeQ) {
  int idx, flag;
  *primeP = 0;
  *primeQ = 0;

  for (idx = 0; idx < strlen(primeString) && primeString[idx] != ','; idx++) {
  }

  *primeP = atoi(primeString);
  *primeQ = atoi(&primeString[idx + 1]);
}

/*
  Function to set product value following the ff. formula
  * PRODUCT = PRIME_P * PRIME_Q
*/
void setProduct(int *product, int primeP, int primeQ) {
  *product = primeP * primeQ;
}

/*
  Function to set totient value following the ff. formula
  * TOTIENT = (PRIME_P - 1) * (PRIME_Q - 1)
*/
void setTotient(int *totient, int primeP, int primeQ) {
  *totient = (primeP - 1) * (primeQ - 1);
}

/*
 Function to generate random value key equal to the size of text
*/
void setPrimePairs(int *primeP, int *primeQ) {
  do {
    printf("Enter first prime value: ");
    fflush(stdin);
    scanf("%d", primeP);

    if (!isPrime(*primeP)) {
      printf("Please enter a valid a prime number!\n");
    }

  } while (!isPrime(*primeP));

  do {
    printf("Enter second prime value: ");
    fflush(stdin);
    scanf("%d", primeQ);

    if (!isPrime(*primeQ)) {
      printf("Please enter a valid a prime number!\n");
    }

  } while (!isPrime(*primeQ));
}

void setPrimePairsFromString(char *primePairString, int *primeP, int *primeQ) {}

/*
  Function to determine whether current number is prime
*/
bool isPrime(int number) {
  for (int idx = 2; idx < number; idx++) {
    if (number % idx == 0 && idx != number) {
      return false;
    }
  }

  return true;
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
  Function to determine whether X is a factor of NUMBER
*/
bool isFactorOfNumber(int x, int number) {
  if (x % number == 0) {
    return true;
  }
  return false;
}

void pause() {
  printf("**press any key to continue**\n");
  getch();
}

/*
  Function to require prime pair from user
*/
bool requirePrimePair(int primeP, int primeQ) {
  if (primeP == -1 || primeQ == -1) {
    printf("Please set the two prime numbers!\n");
    return false;
  }

  return true;
}

/*
  Function to require totient value from user
*/
bool requireTotient(int totient) {
  if (totient == -1) {
    printf("Please set the totient value!\n");
    return false;
  }

  return true;
}

/*
  Function to require public key
*/
bool requirePublicKey(int publicKey) {
  if (publicKey == -1) {
    printf("Please set the public key value!\n");
    return false;
  }

  return true;
}

/*
  Function to determine the power of a character
*/
long long int power(char base, int power) {
  long long int result;

  result = (long long int)pow(base, power);

  return result;
}