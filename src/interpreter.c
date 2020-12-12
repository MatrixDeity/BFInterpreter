#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "interpreter.h"
#include "errors.h"
#include "constants.h"

typedef void(*operator)();

void move_left();
void move_right();
void increase();
void decrease();
void print();
void input();
void begin_loop();
void end_loop();

void load_instructions(FILE* source, int stopcode);
void add_instruction(char op);
char next_instruction();
char prev_instruction();
void set_instruction(int pos);
void execute_instructions();
void execute(char op);
void reset_all();
bool is_operator(char op);
bool loop_condition();

static char buffer[BUFFER_SIZE];
static char instructions[INSTRUCTIONS_SIZE];
static const operator operators[OPERATORS_SIZE] = {
    [MOVE_LEFT_OPERATOR]    = move_left,
    [MOVE_RIGHT_OPERATOR]   = move_right,
    [INCREASE_OPERATOR]     = increase,
    [DECREASE_OPERATOR]     = decrease,
    [PRINT_OPERATOR]        = print,
    [INPUT_OPERATOR]        = input,
    [BEGIN_CYCLE_OPERATOR]  = begin_loop,
    [END_CYCLE_OPERATOR]    = end_loop
};
static char* buff_ptr = buffer;
static char* inst_ptr = instructions;

void process_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        throw_error(ERR_BAD_FILE);
    }
    load_instructions(file, EOF);
    fclose(file);
    execute_instructions();
}

void process_lines() {
    printf("Welcome to BrainFuck Interpreter!\n");
    printf("By MatrixDeity, 2018-2020.\n");
    while (true) {
        printf("$ ");
        load_instructions(stdin, NL);
        execute_instructions();
        puts("");
    }
}

void move_left() {
    if (buff_ptr == buffer) {
        buff_ptr = buffer + BUFFER_SIZE - 1;
    } else {
        --buff_ptr;
    }
}

void move_right() {
    if (buff_ptr == buffer + BUFFER_SIZE - 1) {
        buff_ptr = buffer;
    } else {
        ++buff_ptr;
    }
}

void increase() {
    ++*buff_ptr;
}

void decrease() {
    --*buff_ptr;
}

void print() {
    putchar(*buff_ptr);
}

void input() {
    *buff_ptr = (char)getchar();
    while (getchar() != NL);
}

void begin_loop() {
    if (loop_condition()) {
        return;
    }
    char op;
    int nested = 1;
    while (op = next_instruction()) {
        nested += (op == BEGIN_CYCLE_OPERATOR);
        nested -= (op == END_CYCLE_OPERATOR);
        if (nested == 0) {
            return;
        }
    }
}

void end_loop() {
    if (!loop_condition()) {
        return;
    }
    char op;
    int nested = 0;
    while (op = prev_instruction()) {
        nested += (op == END_CYCLE_OPERATOR);
        nested -= (op == BEGIN_CYCLE_OPERATOR);
        if (nested == 0) {
            return;
        }
    }
}

void load_instructions(FILE* source, int stopcode) {
    int brc = 0;
    reset_all();
    for (int op; (op = getc(source)) != stopcode;) {
        brc += (op == BEGIN_CYCLE_OPERATOR);
        brc -= (op == END_CYCLE_OPERATOR);
        if (brc < 0) {
            throw_error(ERR_INCORRECT_CYCLE);
        }
        add_instruction(op);
    }
    if (brc != 0) {
        throw_error(ERR_INCORRECT_CYCLE);
    }
}

void add_instruction(char op) {
    if (!is_operator(op)) {
        return;
    }
    if (inst_ptr == instructions + INSTRUCTIONS_SIZE) {
        throw_error(ERR_TOO_MUCH_INSTRUCTIONS);
    }
    *inst_ptr++ = op;
}

char next_instruction() {
    if (inst_ptr == instructions + INSTRUCTIONS_SIZE) {
        return NULL;
    }
    return *inst_ptr++;
}

char prev_instruction() {
    --inst_ptr;
    if (inst_ptr < instructions) {
        return NULL;
    }
    return *inst_ptr;
}

void set_instruction(int pos) {
    if (pos < 0 || pos >= INSTRUCTIONS_SIZE) {
        return;
    }
    inst_ptr = instructions + pos;
}

void execute_instructions() {
    set_instruction(0);
    char op;
    while (op = next_instruction()) {
        execute(op);
    }
}

void execute(char op) {
    if (!is_operator(op)) {
        return;
    }
    operators[op]();
}

void reset_all() {
    set_instruction(0);
    buff_ptr = buffer;
    memset(buffer, 0, sizeof(buffer));
    memset(instructions, 0, sizeof(instructions));
}

bool is_operator(char op) {
    return operators[op] != NULL;
}

bool loop_condition() {
    return *buff_ptr != 0;
}
