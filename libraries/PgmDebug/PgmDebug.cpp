
#include "PgmDebug.h"

void PgmDebug::__PD_Print(char PROGMEM *fmt, ...) {
	char tmp[__PD_BUFF_SIZE];
	memset(tmp, 0, __PD_BUFF_SIZE);

	char c=0;
	int idx=0;
	while(c=pgm_read_byte(fmt+idx)) {
		if(idx>=__PD_BUFF_SIZE)
			return;
		tmp[idx++]=c;
	}

	char buff[__PD_BUFF_SIZE];
	memset(buff, 0, __PD_BUFF_SIZE);

	va_list ap;
	va_start(ap, tmp);
	vsprintf(buff, tmp, ap);
	va_end(ap);

	Serial.print(buff);
	Serial.flush();
}

void PgmDebug::__PD_Println(char PROGMEM *fmt, ...) {
	char tmp[__PD_BUFF_SIZE];
	memset(tmp, 0, __PD_BUFF_SIZE);

	char c=0;
	int idx=0;
	while(c=pgm_read_byte(fmt+idx)) {
		if(idx>=__PD_BUFF_SIZE)
			return;
		tmp[idx++]=c;
	}

	char buff[__PD_BUFF_SIZE];
	memset(buff, 0, __PD_BUFF_SIZE);

	va_list ap;
	va_start(ap, tmp);
	vsprintf(buff, tmp, ap);
	va_end(ap);

	Serial.print("mess ");
	Serial.println(buff);
	Serial.flush();
}

/*
void __PD_Println(char PROGMEM *fmt, ...) {
	char tmp[__PD_BUFF_SIZE];
	memset(tmp, 0, __PD_BUFF_SIZE);

	char c=0;
	int idx=0;
	while(c=pgm_read_byte(fmt+idx)) {
		if(idx>=__PD_BUFF_SIZE)
			return;
		tmp[idx++]=c;
	}
	va_list args;
	va_start(args, tmp);
	vsprintf(__PD_BUFF, tmp, args);
	va_end(args);

	Serial.println(__PD_BUFF);
}
*/
