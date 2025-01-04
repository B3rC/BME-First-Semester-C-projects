#include <stdio.h>
#define MEMORY_SIZE 32768

int syntax_check(const char *program);

int syntax_check(const char *program) {
    int balance = 0;
    for (int i = 0; program[i] != '\0'; ++i) {
        if (program[i] == '[') {
            balance++;
        } else if (program[i] == ']') {
            balance--;
            if (balance < 0) {
                return 0; // Too many closing brackets
            }
        }
    }
    return balance == 0; // All brackets are paired
}

int main(void) {

    // Program that prints inputs in reverse
    //char program_code[] = ">,+[>,+]<[-.<]";

    // Sierpinski triangle program
    char program_code[]="[ThisprogramprintsSierpinskitriangleon80-columndisplay.]>++++[<++++++++>-]>++++++++[>++++<-]>>++>>>+>>>+<<<<<<<<<<[-[->+<]>[-<+>>>.<<]>>>[[->++++++++[>++++<-]>.<<[->+<]+>[->++++++++++<<+>]>.[-]>]]+<<<[-[->+<]+>[-<+>>>-[->+<]++>[-<->]<<<]<<<<]++++++++++.+++.[-]<]+++++*****Made*By:*NYYRIKKI*2002*****";

    int memory_tape[MEMORY_SIZE] = {0};
    int *ptr = memory_tape;

    // First, check if the program contains syntax errors with '[' and ']' symbols
    if (!syntax_check(program_code)) {
        printf("Error: The program contains a syntax error!\n");
        return 1;
    }

    // Now, the interpreter itself
    for (int i = 0; program_code[i] != '\0'; i++) {
        switch(program_code[i]) {
            case '>':
                if (ptr < memory_tape + MEMORY_SIZE - 1) {
                    ptr++;
                }
                else {
                    printf("Error: Out of bounds\n");
                    return 1;
                }
            break;

            case '<':
                if (ptr > memory_tape) {
                    ptr--;
                }
                else {
                    printf("Error: Out of bounds\n");
                    return 1;
                }
            break;

            case '+':
                (*ptr)++;
            break;

            case '-':
                (*ptr)--;
            break;

            case '.':
                printf("%c", *ptr);
            break;

            case ',':
                {
                    char temp;
                    if (scanf("%c", &temp) == EOF) {
                        *ptr = -1;
                    } else {
                        *ptr = (int)temp;
                    }
                }
                break;

            case '[':
                // If the current cell value is 0, skip the loop
                if (*ptr == 0) {
                    int loop = 1;
                    while (loop > 0) {
                        i++;
                        if (program_code[i] == '[') loop++;
                        if (program_code[i] == ']') loop--;
                    }
                }
            break;

            case ']':
                // If the current cell value is not 0, jump to the corresponding starting point
                if (*ptr != 0) {
                    int loop = 1;
                    while (loop > 0) {
                        i--;
                        if (program_code[i] == ']') loop++;
                        if (program_code[i] == '[') loop--;
                    }
                }
            break;

            default:
            break;
        }
    }

    return 0;
}
