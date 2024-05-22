#ifndef __POKEROBO_PSX_PS2_COMMONS_H__
#define __POKEROBO_PSX_PS2_COMMONS_H__

#include <Arduino.h>

#ifndef POKEROBO_PSX_TRACE_ENABLED
#define POKEROBO_PSX_TRACE_ENABLED         1
#endif

#ifndef POKEROBO_PSX_DEBUG_ENABLED
#define POKEROBO_PSX_DEBUG_ENABLED         1
#endif

class PSxDebugLogger {
  public:
    static void debug(char* s0,
        char* s1=NULL,
        char* s2=NULL,
        char* s3=NULL,
        char* s4=NULL,
        char* s5=NULL,
        char* s6=NULL,
        char* s7=NULL,
        char* s8=NULL,
        char* s9=NULL,
        char* s10=NULL,
        char* s11=NULL,
        char* s12=NULL,
        char* s13=NULL,
        char* s14=NULL,
        char* s15=NULL,
        char* s16=NULL,
        char* s17=NULL,
        char* s18=NULL,
        char* s19=NULL);
};

#endif
