#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define MIN_ASCII_CHAR 32 /* ' ' */
#define MAX_ASCII_CHAR 125 /* } */
#define MIN_STRING_SIZE 5
#define MAX_STRING_SIZE 5

char* RANDOM_CHARS = "[({ ax})]reset";
const int n = 14; 

char inputChar()
{
    // char c = MIN_ASCII_CHAR + rand() % (MIN_ASCII_CHAR - MAX_ASCII_CHAR - 1); /* Pick from [0, 255] ASCII characters */
    char c = RANDOM_CHARS[rand() % n];
    return c;
}

char *inputString()
{
    int i;

    int n;
    if (MIN_STRING_SIZE == MAX_STRING_SIZE)
        n = MIN_STRING_SIZE;
    else
        n = MIN_STRING_SIZE + rand() % (MAX_STRING_SIZE - MIN_STRING_SIZE);

    char* s = (char*)malloc((n+1) * sizeof(char)); /* n + 1 gives space for null terminator */
    for (i = 0; i < n; i++) s[i] = inputChar();
    s[n + 1] = '\0';
    return s;
}

void testme()
{
  srand(time(NULL));
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
    free(s);
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
