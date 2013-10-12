#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char myString[256];
    char c;
    int count = 0;

    write(STDOUT_FILENO, "Enter one line: ", 16);

    while ((c = getchar()) != '\n') {
        myString[count++] = c;
    }
    myString[count] = '\0';

    //printf("%s\n", myString);
    write(STDOUT_FILENO, myString, count);
    return 0;
}
