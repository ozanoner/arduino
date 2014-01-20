
#define DEBUG


#ifndef _SIM5218_H_
#define _SIM5218_H_



// module on pin
#define SIM5218_ONPIN 2

// chars
#define SIM5218_CR 0x0D
#define SIM5218_LF 0x0A
#define SIM5218_END 0x1A

// general commands && responses
#define SIM5218_CMD_AT "AT"
#define SIM5218_CMD_SET_CPIN "AT+CPIN=%s"

#define SIM5218_RESP_OK "OK"
#define SIM5218_RESP_ERROR "ERROR"

// network register
#define SIM5218_QUE_NW_REG "AT+CREG?"
#define SIM5218_RESP_NW_REG_HOME "+CREG: 0,1"

// sms
#define SIM5218_CMD_SET_SMS_MESS_FMT "AT+CMGF=%d"
#define SIM5218_CMD_SET_SMS_MEM "AT+CPMS=\"%s\",\"%s\",\"%s\""
#define SIM5218_CMD_SEND_SMS "AT+CMGS=\"%s\""
#define SIM5218_CMD_READ_DEL_SMS "AT+CMGRD=%d"
#define SIM5218_CMD_READ_SMS "AT+CMGR=%d"
#define SIM5218_CMD_DEL_SMS "AT+CMGD=%d,%d"

#define SIM5218_RESP_READ_DEL_SMS "+CMGRD:"
#define SIM5218_RESP_READ_SMS "+CMGR:"

#define SIM5218_SMS_MESS_FMT_PDU 0
#define SIM5218_SMS_MESS_FMT_TEXT 1

#define SIM5218_SMS_DEL_ALL 4
#define SIM5218_SMS_DEL_READ 2


// gps
#define SIM5218_CMD_GPS_ON "AT+CGPS=%d"
#define SIM5218_EXE_GPSINFO "AT+CGPSINFO"

#define SIM5218_RESP_GPSINFO "+CGPSINFO:"

// imei
#define SIM5218_CMD_READ_IMEI "AT+SIMEI?"
#define SIM5218_CMD_SET_IMEI "AT+SIMEI=%s"
#define SIM5218_TEST_SET_IMEI "AT+SIMEI=?"

#define SIM5218_RESP_READ_IMEI "+SIMEI: "


// buffers
#define SIM5218_INT_BUFF_SIZE 512
#define SIM5218_CMD_BUFF_SIZE 64
#define SIM5218_SMS_BUFF_SIZE 256
#define SIM5218_MSISDN_SIZE 15
#define SIM5218_ERROR_BUFF_SIZE 64

// errors
// sendCmd errors
#define SIM5218_ERRC_RESP_BUFFER_FULL 1
#define SIM5218_ERRC_ERROR_RECEIVED 2
#define SIM5218_ERRC_UNEXPECTED_RESULT 3
#define SIM5218_ERRC_TIMEOUT 4
#define SIM5218_ERRC_PARSE_FAILED 5
#define SIM5218_ERRC_NO_DATA 6
#define SIM5218_ERRC_UNEXPECTED_END_OF_DATA 7

// other functions' error
#define SIM5218_ERRC_NWREG_TIMEOUT 8
#define SIM5218_ERRC_READSMS_UNEXPECTED_EOD 9
#define SIM5218_ERRC_GETGPS_UNEXPECTED_EOD 10
#define SIM5218_ERRC_GETGPS_NO_DATA 11
#define SIM5218_ERRC_GETGPS_TIMEOUT 12
#define SIM5218_ERRC_GETGPS_PARSE 13
#define SIM5218_ERRC_READIMEI_NO_START 14
#define SIM5218_ERRC_READIMEI_NO_END 15

// others 
#define SIM5218_DEFAULT_TIMEOUT 2500
#define SIM5218_SENDCMD_DELAY 1000


// test
#define DEL_SMS 1

#include "Arduino.h"

class SIM5218 {
	public:
		SIM5218(HardwareSerial *inSerial);

		// initilize serial
		void initialize();

		// wakes up using SIM5218_ONPIN
		// returns nonzero if fails
		int8_t wakeup(unsigned long timeout);



		// returns 0 for success
		// if error, returns nonzero and sets errCode
		int8_t sendCmd(const char *cmd, const char *waitfor, unsigned long timeout);
		// with default timeout of 2000
		int8_t sendCmd(char *cmd, char *waitfor);
		// with default waitfor of "OK"
		int8_t sendCmd(const char *cmd);

		void printErrCodeDesc();

		// sends SIM5218_CMD_AT, waits for "OK" response
		// returns NONZERO if READY
		int8_t isReady();

		

		int errCode;

		// returns nonzero if fails
		int8_t setPIN(char *pin);

		// waits for network registration
		// returns nonzero if fails
		int8_t waitNetworkReg(unsigned long timeout);


		// initialize sms values to default
		// message fmt: text
		// storage: sim
		// delete all sim sms
		int8_t initializeSMS();

		// sets sms message fmt
		// msgFmt: SIM5218_SMS_MESS_FMT_PDU or SIM5218_SMS_MESS_FMT_TEXT
		int8_t setSMSMessFmt(int8_t msgFmt);

		// sends "mess" to "msisdn"
		// sets message format to SIM5218_SMS_MESS_FMT_TEXT
		int8_t sendSMS(const char *msisdn, const char *mess);

		int8_t setSMSStorage(const char *s1, const char *s2, const char *s3);

		int8_t setSMSStorageSIM();

		// deletes sms at idx, depending on flag
		int8_t delSMS(int idx, int flag);

		int8_t querySMS(unsigned long start, unsigned long period, void (*callback)(char *content, int size, int8_t err));

		void cancelQuerySMS();

		// reads sms and fills smsBuffer
		int8_t readSMS(int8_t del);
		// returns sms buffer
		char *getSMSBuffer();
		// clears sms buffer
		void clearSMSBuffer();

		char *getMsisdn();
	

		// default correction values exist but you can use new values with this function
		// correction values for coordinates according to google earth
		void initializeGPS(float northC, float eastC); 

		// open GPS when needed.
		// starts GPS in standalone mode 
		int8_t startGPS();

		int8_t stopGPS();

		// start: starts after value ms
		// period: call period in ms, negative value disables periodic call. min val is 5000 ms.
		// callback: callback function when coordinates detected
		// stopGPS is called automatically when needed.
		int8_t queryGPS(unsigned long start, unsigned long period, void (*callback)(float n, float e, int8_t err));

		void cancelQueryGPS();

		

		// general timer utility for internal state controls.
		// should be used in loop() function.
		// 1- checks active GPS query
		void update();

		char *getRespBuffer();
		char *getErrorBuffer();
		void printBuffers();



		char *readIMEI();
		int8_t setIMEI(char *);

	protected:
		HardwareSerial *hwSerialComm;

		uint8_t respLen;
		char respBuffer[SIM5218_INT_BUFF_SIZE];
		char errorBuffer[SIM5218_ERROR_BUFF_SIZE];
		char cmdBuffer[SIM5218_CMD_BUFF_SIZE];
		char smsBuffer[SIM5218_SMS_BUFF_SIZE];

		// default -1
		int8_t smsMessFmt;

		char msisdn[SIM5218_MSISDN_SIZE];
		void extractMsisdn(char *start, char *msisdn, int maxSize);


		void printDebugInfo(char *s);
		void printDebugInfo(int i);
		// void printDebugInfo(char c);

		float northCorrection;
		float eastCorrection;
		// default -1, 0=off, 1=on
		int8_t isGPSOn;

		// gpsPeriod is added to nextGPSCall after each getGPSCoordinates
		unsigned long gpsPeriod;
		// if 0, query is deactive
		unsigned long nextGPSCall;


		int gpsCallCount;
		// gpsCallback will be called in updateSIM5218 depending on nextGPSCall value
		void (*gpsCallback)(float n, float e, int8_t err);

		int8_t getGPSCoordinates(float &north, float &east);
		float parseGPSResponse();




		unsigned long smsPeriod;
		unsigned long nextSMSCall;
		void (*smsCallback)(char *content, int size, int8_t err);

		// use after sendCmd for SIM5218_SENDCMD_DELAY delay
		void delayMe();
		char newlineStr[3];
};




#endif
