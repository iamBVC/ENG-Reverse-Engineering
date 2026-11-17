/* Recovered from the callable entry at 0x005640F2 in the original image. */
void sub_5640F2(char *text)
{
    char *decimal;
    char *suffix;
    char *trimmed;
    char *destination;
    char *source;
    unsigned char separator = DAT_0057ca14;

    decimal = text;
    while (*decimal != '\0' && (unsigned char)*decimal != separator)
        ++decimal;
    if (*decimal == '\0')
        return;

    suffix = decimal + 1;
    while (*suffix != '\0' && *suffix != 'e' && *suffix != 'E')
        ++suffix;

    trimmed = suffix;
    while (trimmed > decimal + 1 && trimmed[-1] == '0')
        --trimmed;
    if (trimmed > text && (unsigned char)trimmed[-1] == separator)
        --trimmed;

    destination = trimmed;
    source = suffix;
    do {
        *destination++ = *source;
    } while (*source++ != '\0');
}
