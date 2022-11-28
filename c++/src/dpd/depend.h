#pragma once
#include <stdint.h>

#ifdef NDEBUG
#define Dprintf(FORMAT, ...) ((void)0)
#define DebugPuts(MSG) ((void)0)
#else
#define Dprintf(FORMAT, ...) \
    fprintf(stderr, "----- Debug  func -> %s() in %s, line %i: " FORMAT "\n", \
        __func__, __FILE__, __LINE__, __VA_ARGS__)
#define DebugPuts(MSG) Dprintf("%s", MSG)
#endif
