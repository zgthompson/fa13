#include <string>
#include <iostream>

char next_match(char* input) {
    if (input[0] == '\0') {
        return 'T';
    }
    else if (input[0] == ')') {
        return ')';
    }
    else if (next_match(input+1) == ')') {
        return next_match(input+2);
    }
    else
        return 'F';
}



int main(void) {
    std::cout << next_match("(()") << std::endl;
}

        
