/* Original diagnostic helper: cdecl format string followed by varargs. */
#include <stdarg.h>

int sub_414600(const char *format, ...)
{
    char message[1024];
    size_t length;
    va_list arguments;
    if (strlen(format) >= sizeof message) return 0;
    va_start(arguments, format);
    vsnprintf(message, sizeof message - 1, format, arguments);
    va_end(arguments);
    length = strlen(message);
    message[length++] = '\n';
    message[length] = 0;
    OutputDebugStringA(message);
    fprintf(stderr, "[game] %s", message);
    return 0;
}
