#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000

#ifdef _WIN32  // Windows
#include <stdlib.h>

void clearScreen() { system("cls"); }

#elif __APPLE__  // macOS
#include <unistd.h>

void clearScreen() {
  printf("\033[H\033[J");  // ANSI escape code to clear the screen
}

#else  // Linux and other Unix-like systems
#include <unistd.h>

void clearScreen() {
  printf("\033[H\033[J");  // ANSI escape code to clear the screen
}

#endif

char **readFile(const char *filename, int *lineCount) {
  // Open the file for reading
  FILE *file = fopen(filename, "r");

  // Check if the file was opened successfully
  if (file == NULL) {
    printf("Failed to open the file for reading.\n");
    return NULL;  // Return NULL to indicate an error
  }

  // Count the number of lines in the file
  int count = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      count++;
    }
  }
  // Reset the file pointer to the beginning of the file
  fseek(file, 0, SEEK_SET);

  // Allocate memory for the array of strings
  char **lines =
      (char **)malloc((count + 1) * sizeof(char *));  // +1 for NULL terminator

  // Check if memory allocation was successful
  if (lines == NULL) {
    printf("Memory allocation failed.\n");
    fclose(file);
    return NULL;  // Return NULL to indicate an error
  }

  // Read each line from the file into the array
  char buffer[1024];  // Buffer to store each line
  int i = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';  // Remove the newline character
    }
    lines[i] = strdup(buffer);  // Duplicate the line and store it
    i++;
  }
  lines[count] = NULL;  // NULL-terminate the array

  // Close the file
  fclose(file);

  if (lineCount != NULL) {
    *lineCount = count;
  }

  return lines;
}

void freeLines(char **lines) {
  if (lines == NULL) {
    return;
  }
  for (int i = 0; lines[i] != NULL; i++) {
    free(lines[i]);
  }
  free(lines);
}

int findMatchingBracket(char *code, int currentPos) {
  int depth = 0;
  int direction = 1;  // Direction to search for matching bracket (forward)

  if (code[currentPos] == '[') {
    while (code[currentPos] != '\0') {
      if (code[currentPos] == '[') {
        depth++;
      } else if (code[currentPos] == ']') {
        depth--;
        if (depth == 0) {
          return currentPos;  // Found matching bracket
        }
      }
      currentPos += direction;
    }
  } else if (code[currentPos] == ']') {
    direction = -1;  // Search backward
    while (currentPos >= 0) {
      if (code[currentPos] == ']') {
        depth++;
      } else if (code[currentPos] == '[') {
        depth--;
        if (depth == 0) {
          return currentPos;  // Found matching bracket
        }
      }
      currentPos += direction;
    }
  }

  return -1;  // No matching bracket found
}

int interpretBrainf_ck(char *code) {
  char tape[TAPE_SIZE] = {0};  // Initialize tape with zeros
  char *ptr = tape;            // Pointer to the current cell in the tape

  int codePos = 0;  // Position in the code

  while (code[codePos] != '\0') {
    switch (code[codePos]) {
      case '>':  // move to the right cell
        if (ptr < tape + TAPE_SIZE) {
          ptr++;
        } else {
          printf("Error: Attempted to move right beyond tape bounds.\n");
          return 4;  // Exit the interpreter
        }
        break;
      case '<':  // move to the left cell
        if (ptr > tape) {
          ptr--;
        } else {
          printf("Error: Attempted to move left beyond tape bounds.\n");
          return 4;  // Exit the interpreter
        }
        break;
      case '+':  // increment current cell's value by 1
        if ((*ptr) != CHAR_MAX) {
          (*ptr)++;
        } else {
          printf("Error: A cell's value can not be more than %d\n", CHAR_MAX);
          return 5;
        }
        break;
      case '-':  // decrement current cell's value by 1
        if ((*ptr) != 0) {
          (*ptr)--;
        } else {
          printf("Error: A cell's value can not be less than %d\n", 0);
          return 5;
        }
        break;
      case '[':  // while loop opening
        if (*ptr == 0) {
          codePos = findMatchingBracket(code, codePos);
          if (codePos == -1) {
            printf("Error: Unmatched '[' bracket.\n");
            return 6;
          }
        }
        break;
      case ']':  // while loop ending
        if (*ptr != 0) {
          codePos = findMatchingBracket(code, codePos);
          if (codePos == -1) {
            printf("Error: Unmatched ']' bracket.\n");
            return 6;
          }
        }
        break;
      case '.':
        putchar(*ptr);  // print the ASCII char value of current cell
        break;
      case ',':
        // getting input and storing it in the current cell
        *ptr = getchar();
        break;
      default:
        // Ignore characters that are not Brainf*ck commands
        break;
    }
    codePos++;
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    char tape[TAPE_SIZE] = {0};  // Initialize tape with zeros
    char *ptr = tape;            // Pointer to the current cell in the tape
    char code[TAPE_SIZE];
    int codePos = 0;  // Position in the code

    while (1) {
      scanf("%s", code);
      if (!strcmp(code, "exit")) {
        break;
      } else if (!strcmp(code, "clear")) {
        clearScreen();
      }
      while (code[codePos] != '\0') {
        switch (code[codePos]) {
          case '>':  // move to the right cell
            if (ptr < tape + TAPE_SIZE) {
              ptr++;
            } else {
              printf("Error: Attempted to move right beyond tape bounds.\n");
              return 4;  // Exit the interpreter
            }
            break;
          case '<':  // move to the left cell
            if (ptr > tape) {
              ptr--;
            } else {
              printf("Error: Attempted to move left beyond tape bounds.\n");
              return 4;  // Exit the interpreter
            }
            break;
          case '+':  // increment current cell's value by 1
            if ((*ptr) != CHAR_MAX) {
              (*ptr)++;
            } else {
              printf("Error: A cell's value can not be more than %d\n",
                     CHAR_MAX);
              return 5;
            }
            break;
          case '-':  // decrement current cell's value by 1
            if ((*ptr) != 0) {
              (*ptr)--;
            } else {
              printf("Error: A cell's value can not be less than %d\n", 0);
              return 5;
            }
            break;
          case '[':  // while loop opening
            if (*ptr == 0) {
              codePos = findMatchingBracket(code, codePos);
              if (codePos == -1) {
                printf("Error: Unmatched '[' bracket.\n");
                return 6;
              }
            }
            break;
          case ']':  // while loop ending
            if (*ptr != 0) {
              codePos = findMatchingBracket(code, codePos);
              if (codePos == -1) {
                printf("Error: Unmatched ']' bracket.\n");
                return 6;
              }
            }
            break;
          case '.':
            putchar(*ptr);  // print the ASCII char value of current cell
            break;
          case ',':
            // getting input and storing it in the current cell
            *ptr = getchar();
            break;
          default:
            // Ignore characters that are not Brainf*ck commands
            break;
        }
        codePos++;
      }
    }
    return 0;
  }

  int lineCount;
  char **content = readFile(argv[1], &lineCount);

  if (content == NULL) {
    // readFile function handles error prints.
    return 2;
  }

  // Concatenate the lines into a single string
  size_t totalLength = 0;
  for (int i = 0; i < lineCount; i++) {
    totalLength += strlen(content[i]);
  }

  char *var = (char *)malloc(totalLength + 1);  // +1 for null terminator
  if (var == NULL) {
    perror("Memory allocation failed");
    return 3;
  }

  var[0] = '\0';  // Initialize the string as empty

  for (int i = 0; i < lineCount; i++) {
    strcat(var, content[i]);
  }

  int exit_code = interpretBrainf_ck(var);

  free(var);
  freeLines(content);
  return exit_code;
}
