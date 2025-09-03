#include "types.h"

#if defined(IS_WINDOWS) || defined(IS_MACOS)
#define CDROM_SUPPORT 0
#elif IS_LINUX
#define CDROM_SUPPORT 1
#endif
