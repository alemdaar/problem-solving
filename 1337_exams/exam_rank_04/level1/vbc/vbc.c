#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *line;

void error_exit(char c, int type) {
    if (type == 0)
        fprintf(stderr, "Unexpected token '%c'\n", c);
    else
        fprintf(stderr, "Unexpected end of input\n");
    exit(1);
}

int P();
// int M();

int X() {
    char c = *line;
    int res = 0;

    if (c == '\0')
        error_exit(0, 1);

    if (isdigit(c)) {
        res = c - '0';
        line++;
    } else if (c == '(') {
        line++;
        res = P();

        if (*line == ')')
            line++;
        else if (*line == '\0')
            error_exit(0, 1);
        else
            error_exit(*line, 0);
    } else
        error_exit(c, 0);

    return res;
}

int M() {
    int res = X();

    while (*line == '*') {
        line++;
        res *= X();
    }

    return res;
}

int P() {
    int res = M();

    while (*line == '+') {
        line++;
        res += M();
    }

    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;

    line = argv[1];
    int result = P();

    if (*line != '\0') {
        error_exit(*line, 0);
    }

    printf("%d\n", result);

    return 0;
}