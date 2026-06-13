// VS2015+ compatibility fix for legacy libraries
// This fixes the ___iob_func linking error with old pre-compiled libraries

#include <stdio.h>
#include <io.h>

#ifdef __cplusplus
extern "C" {
#endif

// Fix for ___iob_func linking error in VS2015+
#if defined(_MSC_VER) && _MSC_VER >= 1900  // VS2015 and later
    FILE _iob[] = { *stdin, *stdout, *stderr };
    extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

#ifdef __cplusplus
}
#endif