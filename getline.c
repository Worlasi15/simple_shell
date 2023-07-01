#include "shell.h"

char* my_getline()
{
    static char* buffer = NULL;
    static size_t buffer_size = 0;
    static size_t chars_read = 0;
    int c;
     size_t i = 0;
     char* new_buffer;

    /** If the buffer is empty, allocate a new one*/
    if (buffer == NULL) {
        buffer_size = 1024;
        buffer = (char*) malloc(buffer_size);
        if (buffer == NULL) {
            return NULL;
        }
    }

    /*Read characters from standard input until a newline is found*/

    while ((c = getchar()) != EOF && c != '\n') {
        if (i == buffer_size - 1) {
            buffer_size *= 2;
            new_buffer = (char*) realloc(buffer, buffer_size);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[i++] = c;
    }

    if (c == EOF && i == 0) {
        return NULL;
    }

    buffer[i] = '\0';
    chars_read += i;

    return buffer;
}
