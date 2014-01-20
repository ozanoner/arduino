// debug print library with program memory strings.
// use PD_String(name) to create program memory strings
// then you can call PDPrint(name, params) or PDPrintln(name, params)
// if you don't have DEBUG, nothing will be printed on Serial

#include "Arduino.h"
#include <avr/pgmspace.h>
#include <stdarg.h>


#ifndef _PGM_DEBUG_H_
#define _PGM_DEBUG_H_


#define PDString(n) char PROGMEM n[]
#define __PD_BUFF_SIZE 64

class PgmDebug {
	public:
		static void __PD_Print(char PROGMEM *, ...);
		static void __PD_Println(char PROGMEM *, ...);
};


#ifdef DEBUG
#define PDPrint(fmt) PgmDebug::__PD_Print(fmt)
#define PDPrintParams(fmt, ...) PgmDebug::__PD_Print(fmt, __VA_ARGS__)
#define PDPrintln(fmt) PgmDebug::__PD_Println(fmt)
#define PDPrintlnParams(fmt, ...) PgmDebug::__PD_Println(fmt, __VA_ARGS__)

#else
#define PDPrint(fmt)
#define PDPrintParams(fmt, ...)
#define PDPrintln(fmt)
#define PDPrintlnParams(fmt, ...)
#endif

#endif

