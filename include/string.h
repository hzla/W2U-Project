#ifndef W2U_COMPAT_STRING_H
#define W2U_COMPAT_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dst, const void *src, size_t size);
void *memset(void *dst, int value, size_t size);
int memcmp(const void *lhs, const void *rhs, size_t size);
size_t strlen(const char *str);
char *strcpy(char *dst, const char *src);
char *strrchr(const char *str, int ch);

#ifdef __cplusplus
}
#endif

#endif
