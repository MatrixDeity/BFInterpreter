#include "interpreter.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            process_file(argv[i]);
        }
    } else {
        process_lines();
    }
    return 0;
}
