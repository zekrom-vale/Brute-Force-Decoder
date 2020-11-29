#ifndef CONFIG_H
#define CONFIG_H
#include <stdbool.h>

#ifndef __USE_XOPEN2K8
#define __USE_XOPEN2K8
#endif

#define DBG true

#if DBG
#ifndef GUARD_SIZE
#define GUARD_SIZE 0x4000U
#endif
#else
#ifndef GUARD_SIZE
#define GUARD_SIZE 0U
#endif
#endif
#endif

#ifndef STACK_SIZE
#define STACK_SIZE 0x10000U
#endif

#ifndef OUT
#define OUT stdout
#endif