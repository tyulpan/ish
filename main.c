#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define BUFF_SIZE 1024

char *read_line(void) {
  char *line = NULL;
  line = (char *)malloc(sizeof(char) * BUFF_SIZE);
  if (line == NULL) {
    fprintf(stderr, "[FAILED in read_line()]: Memory allocation\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0, c; TRUE; i++) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      line[i] = '\0';
      return line;
    } else {
      line[i] = c;
    }

    if (i % BUFF_SIZE == 0) {
      int new_buff_size = BUFF_SIZE / ((i / BUFF_SIZE) * 2);
      if (new_buff_size == 0) {
        fprintf(stderr, "[FAILED in read_line()]: Buffer overflow\n");
        exit(EXIT_FAILURE);
      }

      line = realloc(line, new_buff_size);
      if (!line) {
        fprintf(stderr, "[FAILED in read_line()]: Memory reallocation\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **get_lexemes(char *line) {
  char **lexemes = NULL;
  return lexemes;
}

char **get_tokens(char **lexemes) {
  char **tokens = NULL;
  return tokens;
}

int execute(char **lexemes, char **tokens) {
  return TRUE;
}

int main(int argc, char **argv) {
  char *line;
  char **lexemes;
  char **tokens;

  do {
    line = read_line();
    lexemes = get_lexemes(line);
    tokens = get_tokens(lexemes);
    if (!execute(lexemes, tokens))
      break;
  } while(TRUE);

  return (0);
}
