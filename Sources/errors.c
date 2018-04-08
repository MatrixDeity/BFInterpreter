#include <stdio.h>

#include "errors.h"

static const char* errors[] = {
    [ERR_UNDEFINED]             = "Undefined error!",
    [ERR_TOO_MUCH_INSTRUCTIONS] = "You passed too much instructions into the interpreter!",
    [ERR_INCORRECT_CYCLE]       = "One or more of your cycles is incorrect! "
                                  "(maybe you are just too stupid for BrainFuck...)",
    [ERR_BAD_FILE]              = "The passed file is damaged or not existing!"
};
static const int err_num = sizeof(errors) / sizeof(errors[0]);

void throw_error(error_t err) {
    const char* err_desc = get_error_description(err);
    fprintf(stderr, "\nProcess terminated with error 0x%x:\n%s\n\n", err, err_desc);
    exit(err);
}

const char* get_error_description(error_t err) {
    if (err <= ERR_UNDEFINED || err >= err_num) {
        return errors[ERR_UNDEFINED];
    }
    return errors[err];
}
