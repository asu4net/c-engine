#ifndef ENGINE_DEBUG_H
#define ENGINE_DEBUG_H

// ==================================
// @Region: Log and Assert/Check.
// ==================================

#ifdef ENGINE_CONFIG_DEBUG
void log_(const char* fmt, ...);
#endif

#ifdef ENGINE_CONFIG_DEBUG
    #define Log(X, ...) (log_(X, ##__VA_ARGS__))
#else
    #define Log(X, ...)
#endif

#ifdef ENGINE_CONFIG_DEBUG
    #ifdef ENGINE_OS_WINDOWS
        #define StopAtThisLine() __debugbreak()
    #else
        #define StopAtThisLine()
#endif
#else
    #define StopAtThisLine()
#endif

#ifdef ENGINE_CONFIG_DEBUG
    #define Check(X) check_((X), "Check failed: %s\n", #X)
    #define CheckMsg(X, ...) check_((X), __VA_ARGS__)
    #define StaticCheck(C, ID) static U8 Glue(ID, __LINE__)[(C)?1:-1]
    #define Ensure(X) ensure_((X), "Ensure failed: %s\n", #X)
    #define EnsureMsg(X, ...) ensure_((X), __VA_ARGS__)
#else
    #define Check(X) ((void)0)
    #define CheckMsg(...) ((void)0)
    #define Ensure(X) (X)
    #define EnsureMsg(X, ...) (X)
#endif

#endif // ENGINE_DEBUG_H.