#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

#define LINE_SIZE 1024
#define TOKENS_SIZE 32

#define DELIM " \n\r\t\a"

char *read_line(void) {
  int buff_size = LINE_SIZE;
  int buff_tmp = 0;
  char *line = NULL;
  line = (char *)malloc(sizeof(char) * LINE_SIZE);
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

    if ((i + 1) % LINE_SIZE == 0) {
      buff_tmp = buff_size;
      buff_size += LINE_SIZE / ((i / LINE_SIZE) * 2);
      if (buff_size == buff_tmp) {
        fprintf(stderr, "[FAILED in read_line()]: Buffer overflow\n");
        exit(EXIT_FAILURE);
      }
    
      line = realloc(line, buff_size);
      if (!line) {
        fprintf(stderr, "[FAILED in read_line()]: Memory reallocation\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **get_tokens(char *line) {
  int buff_size = TOKENS_SIZE;
  int buff_tmp = 0, index = 0;
  char *token = NULL;
  char **tokens = NULL;
  char **tokens_tmp = NULL;
  tokens = (char **)malloc(sizeof(char *) * TOKENS_SIZE);
  if (tokens == NULL) {
    printf("[FAILED get_tokens()]: Memory allocation\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, DELIM);
  for (index = 0; token != NULL; index++) {
    tokens[index] = token;
    /*
    tokens[index] = NULL;
    tokens[index] = (char *)malloc(TOKEN_SIZE * sizeof(char));

    if (tokens[index] == NULL) {
      printf("[FAILED get_tokens()]: Memory allocation\n");

      for (int j = 0; j < index; j++)
        free(tokens[j]);
      free(tokens); 
      exit(EXIT_FAILURE);
    }
    */

    if ((index + 1) % TOKENS_SIZE == 0) {
      buff_tmp = buff_size;
      buff_size += TOKENS_SIZE / ((index / TOKENS_SIZE) * 2);
      if (buff_size == buff_tmp) {
        fprintf(stderr, "[FAILED in read_line()]: Buffer overflow\n");
        exit(EXIT_FAILURE);
      }
    
      tokens_tmp = tokens;
      tokens = realloc(line, sizeof(char *) * buff_size);
      if (!tokens) {
        fprintf(stderr, "[FAILED in get_tokens()]: Memory reallocation\n");
        free(tokens_tmp);
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, DELIM);
  }

  tokens[index] = token;
  return tokens;
}

int execute(char **tokens) {
  return TRUE;
}

int main(int argc, char **argv) {
  char *line;
  char **tokens;

  uid_t uid = geteuid();
  struct passwd *pw = getpwuid(uid);
  char hostname[HOST_NAME_MAX + 1];
  gethostname(hostname, HOST_NAME_MAX + 1);
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  do {
    if ((pw != NULL) && (hostname != NULL) && (cwd != NULL)) {
      printf("\033[1;32m");
      printf("%s@%s", pw->pw_name, hostname);
      printf("\033[01;33m");
      putchar(':');
      printf("\033[1;34m");
      printf("%s", cwd);
      printf("\033[01;33m");
      printf("$ ");
      printf("\033[0m");
    } else {
      fprintf(stderr, "[FAILED in main()]: Path Error\n");
      return (1);
    }

    line = read_line();
    tokens = get_tokens(line);
    if (!execute(tokens))
      break;
  } while(TRUE);

  return (0);
}
