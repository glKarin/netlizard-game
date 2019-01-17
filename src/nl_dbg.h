#ifndef KARIN_NL_DBG_H
#define KARIN_NL_DBG_H

#if _KARIN_DBG
#define NL_ENABLE_DEBUG _KARIN_DBG
#else
#define NL_ENABLE_DEBUG 1
#endif

#define NL_LOG_LEVEL_NO_OUTPUT 0
#define NL_LOG_LEVEL_DEBUG 1
#define NL_LOG_LEVEL_INFO (1 << 1)
#define NL_LOG_LEVEL_WARNING (1 << 2)
#define NL_LOG_LEVEL_ERROR (1 << 3)
#define NL_LOG_LEVEL_FATAL (1 << 4)

#define NL_LOG_LEVEL_DEBUG_STR "Debu"
#define NL_LOG_LEVEL_INFO_STR "Info"
#define NL_LOG_LEVEL_WARNING_STR "Warn"
#define NL_LOG_LEVEL_ERROR_STR "Erro"
#define NL_LOG_LEVEL_FATAL_STR "Fata"

#if NL_ENABLE_DEBUG
#define NL_PAGE_DESTROY_DEBUG(x) printf("[%s]: '%s' page has destroyed!\n", NL_LOG_LEVEL_DEBUG_STR, x);
#define NL_PAGE_VISIBLE_DEBUG(x, f, t) printf("[%s]: '%s'->%s page is %s!\n", NL_LOG_LEVEL_DEBUG_STR, x, f, t);
#else
#define NL_PAGE_DESTROY_DEBUG(x)
#define NL_PAGE_VISIBLE_DEBUG(x, f)
#endif

#endif
