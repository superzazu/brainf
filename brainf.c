#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 30000

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        return 1;
    }

    // loading program file
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "%s: cannot open file\n", argv[0]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long program_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* program = calloc(program_len, sizeof(char));
    fread(program, sizeof(char), program_len, file);

    fclose(file);

    // brainfuck interpretation
    uint8_t mem[MEMORY_SIZE] = {0}; // memory
    int ptr = 0; // pointer to memory
    int pc = 0; // program counter

    while (program[pc] != '\0') {
        switch (program[pc]) {
        case '>': ptr += 1; break;
        case '<': ptr -= 1; break;
        case '+': mem[ptr] += 1; break;
        case '-': mem[ptr] -= 1; break;
        case '.': putchar(mem[ptr]); fflush(stdout); break;
        case ',': mem[ptr] = getchar(); break;
        case '[': {
            if (mem[ptr] == 0) {
                // finding the corresponding closing bracket:
                int count = 1;
                while (count) {
                    pc += 1;
                    if (program[pc] == '[') {
                        count += 1;
                    }
                    if (program[pc] == ']') {
                        count -= 1;
                    }
                }
            }
        } break;
        case ']': {
            // finding the corresponding opening bracket:
            int count = 1;
            while (count) {
                pc -= 1;
                if (program[pc] == ']') {
                    count += 1;
                }
                if (program[pc] == '[') {
                    count -= 1;
                }
            }
            continue;
        } break;
        default: break; // ignoring all other characters
        }

        pc += 1;
    }

    free(program);
    return 0;
}
