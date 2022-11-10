#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *abash(char doc[]) {
  int i;
  char *result = malloc(sizeof(char) * strlen(doc));
  if (result != NULL) {
    for (i = 0; i <= strlen(doc); i++) {
      if (isupper(doc[i])) {
        result[i] = 'Z' - (doc[i] - 'A');
      } else if (islower(doc[i])) {
        result[i] = 'z' - (doc[i] - 'a');
      } else {
        result[i] = doc[i];
      }
    }

    return result;
  }
}

void main() {
  char doc[MAX];

  printf("Enter doc:");
  scanf("%s", doc);

  char *result = abash(doc);

  printf("doc: %s\n", doc);
  printf("cipher: %s", result);
}
