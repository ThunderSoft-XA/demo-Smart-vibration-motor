#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdint.h>

#define LOG_CRITICAL 0x00
#define LOG_ERROR    0x01
#define LOG_WARNING  0x02
#define LOG_INFO     0x03
#define LOG_DEBUG    0x04
#define LOG_DUMP     0x05

#define LOG_LEVEL LOG_DUMP

extern void iofPrintf(char* format, ...);

#define gizLog(level, format, args...) \
{ \
    if(LOG_LEVEL >= level) \
    { \
        switch(level) \
        { \
            case LOG_CRITICAL: \
                iofPrintf("[CRITICAL]"format, ##args); \
                break; \
            case LOG_ERROR: \
                iofPrintf("[ERR]"format, ##args); \
                break; \
            case LOG_WARNING: \
                iofPrintf("[WARNING]"format, ##args); \
                break; \
            case LOG_INFO: \
                iofPrintf("[INFO]"format, ##args); \
                break; \
            case LOG_DEBUG: \
                iofPrintf("[DEBUG]"format, ##args); \
                break; \
            case LOG_DUMP: \
                iofPrintf(format, ##args); \
                break; \
            default: \
                break; \
        } \
    } \
}

#define desensitizationLog(level,str,strPar) \
{\
    uint8_t len = 0; \
    char star = '*'; \
    char tempStr[33]; \
    memset(tempStr,star,33); \
    len = strlen(strPar); \
    switch(len) \
    {\
        case 10 : \
            memcpy(tempStr,strPar,4); \
            tempStr[10] = '\0'; \
            gizLog(level,"%s: PASSCODE:%s.\n", str,tempStr); \
            break; \
        case 22 : \
            memcpy(tempStr,strPar,4); \
            memcpy(&tempStr[18],&strPar[18],4); \
            tempStr[22] = '\0'; \
            gizLog(level,"%s: DID:%s.\n", str,tempStr); \
            break; \
        case 32: \
            memcpy(tempStr,strPar,4); \
            memcpy(&tempStr[28],&strPar[28],4); \
            tempStr[32] = '\0'; \
            gizLog(level,"%s: PS:%s.\n", str,tempStr); \
            break; \
    } \
}

#endif /*_LOG_H_*/
