#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    ERR_UNDEFINED               = 0x1,
    ERR_TOO_MUCH_INSTRUCTIONS   = 0x2,
    ERR_INCORRECT_CYCLE         = 0x3,
    ERR_BAD_FILE                = 0x4
} error_t;

void throw_error(error_t err);
const char* get_error_description(error_t err);

#endif // ERRORS_H
