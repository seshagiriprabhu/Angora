#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

#define FERROR "\t\tUnable to open file\n\n"
#define RERROR "\t\tUnable to read file\n\n"
#define YES "\t\tYes, that's a palindrome!\n\n"
#define NO "\t\tNope, that's not a palindrome\n\n"
#define MAX_LEN 128
#define HALF_LEN 64


int check_palindrome(char *buf) {
    int len = -1;
    int i;
    int steps;
    int pal = 1;
    int n = (int) strlen(buf);
    int array_len;

    if (buf[0] == 'x') {
        array_len = HALF_LEN;
    } else {
        array_len = MAX_LEN;
    }

    char string[array_len];

    for (i = 0; i < n; i++) {
        string[i] = '\0';
    }

    for (i = 0; i < n; i++) {
        string[i] = buf[i];
    }

    for (i = 0; string[i] != '\0'; i++) {
        len++;
    }

    steps = len;
    if (len % 2 == 1) {
        steps--;
    }

    for (i = 0; i <= steps/2; i++) {
        if (string[i] != string[len - 1 - i]) {
            pal = 0;
        }
    }

    return pal;
}


int main(int argc, char **argv)
{
    FILE *fd;
    char buf[MAX_LEN];
    int result;

    if (argc < 2) {
        return 0;
    }

    fd = fopen(argv[1], "rb");

    if (!fd) {
        printf("%s\n", FERROR);
    }

    size_t ret = fread(buf, sizeof *buf, MAX_LEN, fd);
    fclose(fd);

    if (ret < 128) {
        printf("%s\n", RERROR);
        return 0;
    }

    result = check_palindrome(buf);

    if (result == 1) {
        exit(1);
    } else if (result == 0) {
        printf("%s\n", NO);
    } else {
        printf("%s\n", YES);
    }

    return 0;
}
