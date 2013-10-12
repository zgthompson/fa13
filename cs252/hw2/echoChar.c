#include <unistd.h>

int main(void)
{
    char aLetter;

    write(STDOUT_FILENO, "Enter one character: ", 21);
    read(STDIN_FILENO, &aLetter, 1);
    write(STDOUT_FILENO, "You entered: ", 13);
    write(STDOUT_FILENO, &aLetter, 1);

    return 0;
}
