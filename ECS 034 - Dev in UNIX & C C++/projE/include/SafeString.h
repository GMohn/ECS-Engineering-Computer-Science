#ifndef SAFESTRING_H
#define SAFESTRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

char SafeStringIsValid(const char *str);
char *SafeStringAllocate(size_t maxlen);
char *SafeStringFromCstr(const char *str);
void SafeStringDestroy(const char *str);
size_t SafeStringMaxLength(const char *str);
size_t SafeStringLength(const char *str);
char *SafeStringCopy(char *dest, const char *src);
char *SafeStringConcatenate(char *dest, const char *src);
size_t SafeStringResize(char **str, size_t newsize);

#ifdef __cplusplus
}
#endif

#endif