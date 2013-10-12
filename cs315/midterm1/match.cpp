#include <iostream>

char* match(char* input) {
    if (*input == '\0' || *input == ')' || 
            *input == ']' || *input == '}')
        return input;
    else {
        char* cur = match(input+1);
        if (*input == '(' && *cur == ')' ||
                *input == '[' && *cur == ']' ||
                *input == '{' && *cur == '}')
            return match(cur+1);
        else
            return input;
    }
}

bool is_balanced(char* input) {
    return *(match(input)) == '\0';
}

int main(void) {
    std::cout << is_balanced("[])") << std::endl;
}
