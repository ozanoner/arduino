


#include "SIM5218.h"
#include "PgmDebug.h"



PDString(SIM5218_M0)=">> TEST DEBUG PRINT";
// error strings
PDString(SIM5218_M1)=">> ERROR: SIM5218_CMD_SET_CPIN failed";
// PDString(SIM5218_M2)=">> ERROR: waitNetworkReg TIMEOUT";
PDString(SIM5218_M3)=">> ERROR: SIM5218_CMD_SET_SMS_MESS_FMT failed";
PDString(SIM5218_M4)=">> ERROR: SIM5218_CMD_SET_SMS_MEM failed";
PDString(SIM5218_M5)=">> ERROR: SIM5218_CMD_DEL_SMS failed";
PDString(SIM5218_M6)=">> ERROR: SIM5218_CMD_READ_SMS failed";
PDString(SIM5218_M7)=">> ERROR: SIM5218_CMD_SEND_SMS (wait >) failed";
PDString(SIM5218_M8)=">> ERROR: SIM5218_CMD_SEND_SMS failed";
PDString(SIM5218_M9)=">> ERROR: SIM5218_CMD_GPS_ON(1) failed";
PDString(SIM5218_M10)=">> ERROR: SIM5218_CMD_GPS_ON(0) failed";
PDString(SIM5218_M11)=">> ERROR: SIM5218_EXE_GPSINFO failed";
PDString(SIM5218_M12)=">> ERROR: SIM5218_CMD_READ_IMEI failed";
PDString(SIM5218_M13)=">> ERROR: SIM5218_CMD_SET_IMEI failed";


// errCode 
PDString(SIM5218_E1)="SIM5218_ERRC_RESP_BUFFER_FULL";
PDString(SIM5218_E2)="SIM5218_ERRC_ERROR_RECEIVED";
PDString(SIM5218_E3)="SIM5218_ERRC_UNEXPECTED_RESULT";
PDString(SIM5218_E4)="SIM5218_ERRC_TIMEOUT";
PDString(SIM5218_E5)="SIM5218_ERRC_PARSE_FAILED";
PDString(SIM5218_E6)="SIM5218_ERRC_NO_DATA";
PDString(SIM5218_E7)="SIM5218_ERRC_UNEXPECTED_END_OF_DATA";

PDString(SIM5218_E8)="SIM5218_ERRC_NWREG_TIMEOUT";
PDString(SIM5218_E9)="SIM5218_ERRC_READSMS_UNEXPECTED_EOD";
PDString(SIM5218_E10)="SIM5218_ERRC_GETGPS_UNEXPECTED_EOD";
PDString(SIM5218_E11)="SIM5218_ERRC_GETGPS_NO_DATA";
PDString(SIM5218_E12)="SIM5218_ERRC_GETGPS_TIMEOUT";
PDString(SIM5218_E13)="SIM5218_ERRC_GETGPS_PARSE";
PDString(SIM5218_E14)="SIM5218_ERRC_READIMEI_NO_START";
PDString(SIM5218_E15)="SIM5218_ERRC_READIMEI_NO_END";


SIM5218::SIM5218(HardwareSerial *inSerial) {
	this->hwSerialComm = inSerial;
	this->smsMessFmt = -1;
	this->northCorrection = 0.155955;
	this->eastCorrection = 0.170837;
	this->isGPSOn=-1;
}

void SIM5218::initialize() {
	this->hwSerialComm->begin(115200);

	this->newlineStr[0]=SIM5218_CR;
	this->newlineStr[1]=SIM5218_LF;
	this->newlineStr[2]=0;
}

int8_t SIM5218::sendCmd(const char *cmd, const char *waitfor, unsigned long timeout) {
	while(this->hwSerialComm->available())
		this->hwSerialComm->read();
	this->errCode=0;
	this->respLen=0;
	memset(this->respBuffer, 0, SIM5218_INT_BUFF_SIZE);
	memset(this->errorBuffer, 0, SIM5218_ERROR_BUFF_SIZE);

	this->hwSerialComm->print(cmd);
	this->hwSerialComm->write(SIM5218_CR);
	this->hwSerialComm->write(SIM5218_LF);

	int waitforLen = strlen(waitfor);
	timeout += millis();
	int8_t readingError=0;
	char c;
	int idx=0;

	while(1) {
		if(this->hwSerialComm->available())
		{
			if(readingError) {
				c = this->hwSerialComm->read();
				if(c == SIM5218_CR || c == SIM5218_LF)
					return SIM5218_ERRC_ERROR_RECEIVED;
				this->errorBuffer[idx++] = c;
				if(idx>=SIM5218_ERROR_BUFF_SIZE) {
					this->errorBuffer[SIM5218_ERROR_BUFF_SIZE-1]=0;
					return SIM5218_ERRC_ERROR_RECEIVED;
				}
			}
			else {
				this->respBuffer[idx++] = this->hwSerialComm->read();
				if(idx>=SIM5218_INT_BUFF_SIZE) {
					this->respBuffer[SIM5218_INT_BUFF_SIZE-1]=0;
					this->errCode = SIM5218_ERRC_RESP_BUFFER_FULL;
					return SIM5218_ERRC_RESP_BUFFER_FULL;
				}
			}
		}
		else if(timeout<millis()) {
			if(readingError) {
				return SIM5218_ERRC_ERROR_RECEIVED;
			}
			else {
				this->errCode = SIM5218_ERRC_TIMEOUT;
				return SIM5218_ERRC_TIMEOUT;
			}	
		}

		if(waitforLen>0 && !readingError) {
			if(idx>waitforLen && !strncmp(this->respBuffer+idx-waitforLen, waitfor, waitforLen)) {
				return 0;
			} 
			else if(idx>=5 && !strncmp(this->respBuffer+idx-5, SIM5218_RESP_ERROR, 5)) {
				this->errCode = SIM5218_ERRC_ERROR_RECEIVED;
				readingError=1;
				memset(this->errorBuffer, 0, SIM5218_ERROR_BUFF_SIZE);
				idx=0;
			}
		}
	}

	return 0;
}

int8_t SIM5218::sendCmd(char *cmd, char *waitfor) {
	return this->sendCmd(cmd, waitfor, SIM5218_DEFAULT_TIMEOUT);
}

int8_t SIM5218::sendCmd(const char *cmd) {
	return this->sendCmd(cmd, SIM5218_RESP_OK, SIM5218_DEFAULT_TIMEOUT);
}

void SIM5218::printErrCodeDesc() {
	switch(this->errCode) {
	case SIM5218_ERRC_RESP_BUFFER_FULL:
		PDPrintln(SIM5218_E1);
		break;
	case SIM5218_ERRC_ERROR_RECEIVED:
		PDPrintln(SIM5218_E2);
		break;
	case SIM5218_ERRC_UNEXPECTED_RESULT:
		PDPrintln(SIM5218_E3);
		break;
	case SIM5218_ERRC_TIMEOUT:
		PDPrintln(SIM5218_E4);
		break;
	case SIM5218_ERRC_PARSE_FAILED:
		PDPrintln(SIM5218_E5);
		break;
	case SIM5218_ERRC_NO_DATA:
		PDPrintln(SIM5218_E6);
		break;
	case SIM5218_ERRC_UNEXPECTED_END_OF_DATA:
		PDPrintln(SIM5218_E7);
		break;
	default:
		break;
	}
}



int8_t SIM5218::wakeup(unsigned long timeout) {
	if(this->isReady())
		return 0;

	digitalWrite(SIM5218_ONPIN, HIGH);
	delay(3000);
	digitalWrite(SIM5218_ONPIN, LOW);

	timeout+=millis();
	while(!this->isReady()) {
		if(timeout < millis()) {
			return 1;
		}
		delay(1000);
	}
	return 0;
}

int8_t SIM5218::isReady() {
	return !this->sendCmd(SIM5218_CMD_AT);
}

// not tested
int8_t SIM5218::setPIN(char *pin) {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_SET_CPIN, pin);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M1);
		return -1;
	}
	return 0;
}

int8_t SIM5218::waitNetworkReg(unsigned long timeout) {
	timeout += millis();
	while(this->sendCmd(SIM5218_QUE_NW_REG, SIM5218_RESP_NW_REG_HOME, SIM5218_DEFAULT_TIMEOUT)) {
		if(timeout<millis()) {
			PDPrintln(SIM5218_E8);
			this->errCode = SIM5218_ERRC_NWREG_TIMEOUT;
			return -1;
		}
		delay(SIM5218_DEFAULT_TIMEOUT);
	}
	return 0;
}

int8_t SIM5218::setSMSMessFmt(int8_t msgFmt) {
	if(msgFmt == this->smsMessFmt)
		return 0;

	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_SET_SMS_MESS_FMT, msgFmt);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M3);
		return -1;
	}
	else {
		this->smsMessFmt = msgFmt;
	}
	return 0;
}


int8_t SIM5218::setSMSStorage(const char *s1, const char *s2, const char *s3) {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_SET_SMS_MEM, s1, s2, s3);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M4);
		this->printBuffers();
		return -1;
	}
	return 0;
}

int8_t SIM5218::setSMSStorageSIM() {
	return this->setSMSStorage("SM", "SM", "SM");
}

int8_t SIM5218::delSMS(int idx, int flag) {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_DEL_SMS, idx, flag);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M5);
		return -1;
	}
	return 0;
}

int8_t SIM5218::querySMS(unsigned long start, unsigned long period, void (*callback)(char *content, int size, int8_t err)) {
	if(this->nextSMSCall>0)
		return 0;
	this->nextSMSCall = start>0? millis()+start: 0;
	this->smsPeriod = period<=0? 0: period<5000? 5000: period;
	this->smsCallback = callback;

	if(this->nextSMSCall == 0) {
		this->smsCallback(this->smsBuffer, SIM5218_SMS_BUFF_SIZE, \
			this->readSMS(DEL_SMS));
		if(this->smsPeriod>0)
			this->nextSMSCall = millis()+this->smsPeriod;
	} 
	return 0;
}

void SIM5218::cancelQuerySMS() {
	this->nextSMSCall=0;
}

int8_t SIM5218::readSMS(int8_t del) {
	char *cmd, *resp;
	if(del) {
		cmd = SIM5218_CMD_READ_DEL_SMS;
		resp = SIM5218_RESP_READ_DEL_SMS;
	} 
	else {
		cmd = SIM5218_CMD_READ_SMS;
		resp = SIM5218_RESP_READ_SMS;
	}
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, cmd, 1);

	this->delayMe();
	int ret = this->sendCmd(this->cmdBuffer);
	if(ret) {
		if(this->errCode == SIM5218_ERRC_ERROR_RECEIVED) {
			if(this->errorBuffer[0])
				Serial.print("mess ");
				Serial.println(this->errorBuffer);
		} else {
			PDPrintln(SIM5218_M6);
			this->printErrCodeDesc();
		}
		return -1;
	}

	memset(this->smsBuffer, 0, SIM5218_SMS_BUFF_SIZE);
	char *start = strstr(this->respBuffer, resp);
	if(start>0) {
		start+=strlen(resp);

		memset(this->msisdn, 0, SIM5218_MSISDN_SIZE);
		this->extractMsisdn(start, this->msisdn, SIM5218_MSISDN_SIZE-1);

		start = strstr(start, this->newlineStr);
		if(start<=0)
		{
			PDPrintln(SIM5218_E9);
			this->errCode = SIM5218_ERRC_READSMS_UNEXPECTED_EOD;
			return -1;
		}
		start+=2;
		char *end=strstr(start, SIM5218_RESP_OK);
		if(end>0 && end-4>=start) {
			*(end-4)=0;
		} 
		else {
			if(strlen(start)>=SIM5218_SMS_BUFF_SIZE) {
				start[SIM5218_SMS_BUFF_SIZE-1]=0;
			}
		}
		strcpy(this->smsBuffer, start);
	}
	else {
		PDPrintln(SIM5218_E9);
		this->errCode = SIM5218_ERRC_READSMS_UNEXPECTED_EOD;
		return -1;
	}

	return 0;
}

void SIM5218::extractMsisdn(char *start, char *msisdn, int maxSize) {
	char *mstart=strchr(start, ',');

	if(*(++mstart) != '"') {
		return; 
	}
	int i=0;
	while(*(++mstart)!='"' && i<maxSize) {
		msisdn[i++] = *mstart;
	}
}



int8_t SIM5218::initializeSMS() {

	// PDPrintln(SIM5218_M0);
	if(this->setSMSStorageSIM())
		return -1;

	if(this->delSMS(1, SIM5218_SMS_DEL_READ)) 
		return -1;

	if(this->setSMSMessFmt(SIM5218_SMS_MESS_FMT_TEXT))
		return -1;

	delay(SIM5218_DEFAULT_TIMEOUT);
	return 0;
}

int8_t SIM5218::sendSMS(const char *msisdn, const char *mess) {
	int retCode;

	if(this->setSMSMessFmt(SIM5218_SMS_MESS_FMT_TEXT))
		return -1;

	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_SEND_SMS, msisdn); 

	this->delayMe();
	if(retCode = this->sendCmd(this->cmdBuffer, ">", SIM5218_DEFAULT_TIMEOUT))
	{
		PDPrintln(SIM5218_M7);
		return -1;
	}

	this->hwSerialComm->print(mess);
	this->hwSerialComm->write(SIM5218_END);
	if(retCode = this->sendCmd(""))
	{
		PDPrintln(SIM5218_M8);
		this->printErrCodeDesc();
		if(this->errCode == SIM5218_ERRC_ERROR_RECEIVED) {
			PDPrintln(this->errorBuffer);
		}
		return -1;
	}

	return 0;
}


void SIM5218::printDebugInfo(char *s) {
}

void SIM5218::printDebugInfo(int i) {
}

void SIM5218::initializeGPS(float northC, float eastC) {
	this->northCorrection = northC;
	this->eastCorrection = eastC;
	this->isGPSOn = -1;
}

int8_t SIM5218::startGPS() {
	if(this->isGPSOn>0)
		return 0;
	if(this->stopGPS())
		return -1;
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_GPS_ON, 1); 

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M9);
		return -1;
	}
	this->isGPSOn = 1;
	this->nextGPSCall = 0;

	return 0;
}


int8_t SIM5218::stopGPS() {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_GPS_ON, 0); 
	if(this->sendCmd(this->cmdBuffer)) {
		PDPrintln(SIM5218_M10);
		return -1;
	}

	this->isGPSOn = 0;
	return 0;
}

void SIM5218::cancelQueryGPS() {
	this->nextGPSCall=0;
	this->stopGPS();
}

int8_t SIM5218::queryGPS(unsigned long start, unsigned long period, void (*callback)(float n, float e, int8_t err)) {
	if(this->isGPSOn<=0 && this->startGPS()) {
		return -1;
	}

	this->nextGPSCall = start>0? millis()+start: 0;
	if(period>0)
		this->gpsPeriod = period<5000? 5000: period;
	else
		this->gpsPeriod=0;
	this->gpsCallback = callback;
	this->gpsCallCount=0;

	float north;
	float east;
	if(start<=0) {
		callback(north, east, this->getGPSCoordinates(north, east));
	}
	return 0;
}

int8_t SIM5218::getGPSCoordinates(float &north, float &east) {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_EXE_GPSINFO);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer, SIM5218_RESP_GPSINFO, SIM5218_DEFAULT_TIMEOUT)) {
		PDPrintln(SIM5218_M11);
		return -1;
	}

	int idx=0;
	float f=0;

	delay(1000);
	unsigned long timeout = millis()+SIM5218_DEFAULT_TIMEOUT;

	int8_t b;
	if(!this->hwSerialComm->available()) {
		PDPrintln(SIM5218_E10);
		this->errCode=SIM5218_ERRC_GETGPS_UNEXPECTED_EOD;
		return -1;
	}
	b=this->hwSerialComm->read();
	if(!isdigit(b)) {
		memset(this->respBuffer, 0, SIM5218_INT_BUFF_SIZE);
		do {
			if(!this->hwSerialComm->available())
				break;
			this->respBuffer[idx] = this->hwSerialComm->read();
			if(this->respBuffer[idx]<=0 || ++idx>=SIM5218_INT_BUFF_SIZE)
				break;
		} while(1);

		PDPrintln(SIM5218_E11);
		this->errCode=SIM5218_ERRC_GETGPS_NO_DATA;
		return -1;
	}

	int8_t buffOffset=0;

	do
	{
		if(!this->hwSerialComm->available())
		{
			if(millis()>timeout)
			{
				PDPrintln(SIM5218_E12);
				this->errCode =SIM5218_ERRC_GETGPS_TIMEOUT;
				return -1;
			}
			delay(100);
			continue;
		}

		memset(this->respBuffer, 0, SIM5218_INT_BUFF_SIZE);

		if(b>0) {
			this->respBuffer[0]=b;
			buffOffset=1;
			b=0;
		}
		else {
			buffOffset=0;
		}


		if(this->hwSerialComm->readBytesUntil(',', respBuffer+buffOffset, SIM5218_INT_BUFF_SIZE-buffOffset)<=0) {
			PDPrintln(SIM5218_E13);
			this->errCode = SIM5218_ERRC_GETGPS_PARSE;
			return -1;
		}

		f = this->parseGPSResponse();
		if(f<=0) {
			PDPrintln(SIM5218_E13);
			this->errCode = SIM5218_ERRC_GETGPS_PARSE;
			return -1;
		}

		if(this->hwSerialComm->readBytesUntil(',', this->respBuffer, SIM5218_INT_BUFF_SIZE)<=0) 
		{
			PDPrintln(SIM5218_E13);
			this->errCode = SIM5218_ERRC_GETGPS_PARSE;
			return -1;
		}
		if(this->respBuffer[0]=='N') {
			north=f;
		} 
		else if(this->respBuffer[0]=='E') {
			east=f;
			break;
		}
	} while(1);

	while(this->hwSerialComm->read()>0);
	return 0;
}

float SIM5218::parseGPSResponse() {
	float f=0;
	int idx=0;
	char c=this->respBuffer[idx++];

	while(1) {
		if(c == '.')
			break;
		if(!isdigit(c)) {
			return -1;
		}
		f *=10;
		f +=c-'0';
		c=this->respBuffer[idx++];  
	}

	float dp=10;

	c=this->respBuffer[idx++];
	while(1) {
		if(!isdigit(c)) {
			return f/100;
		}
		if(dp<=1000000)
		{  
			f += (c-'0')/dp;
			dp *=10;
		}
		c=this->respBuffer[idx++];
	}

	return -1;
}


void SIM5218::update() {
	unsigned long now = millis();
	if(this->nextGPSCall>0 && this->nextGPSCall<now) {
		if(this->gpsPeriod>0) {
			while(this->nextGPSCall <= now)
				this->nextGPSCall += this->gpsPeriod;
		}
		else
			this->nextGPSCall=0;
		float north;
		float east;
		this->gpsCallback(north, east, this->getGPSCoordinates(north, east));
	}

	if(this->nextSMSCall>0 && this->nextSMSCall<now) {
		if(this->smsPeriod>0) {
			while(this->nextSMSCall <= now)
				this->nextSMSCall += this->smsPeriod;
		}
		else
			this->nextSMSCall=0;
		this->smsCallback(this->smsBuffer, SIM5218_SMS_BUFF_SIZE, \
			this->readSMS(DEL_SMS));
	}
}

char* SIM5218::getRespBuffer() {
	return this->respBuffer;
}

char* SIM5218::getErrorBuffer() {
	return this->errorBuffer;
}

void SIM5218::printBuffers() {
	this->printErrCodeDesc();
	if(this->respBuffer[0]) {
		Serial.print(">> Response buffer:'");
		Serial.println(this->respBuffer);
	}
	if(this->errorBuffer[0]) {
		Serial.print(">> Error buffer:'");
		Serial.println(this->errorBuffer);
	}
}


void SIM5218::delayMe() {
	delay(SIM5218_SENDCMD_DELAY);
}

char* SIM5218::readIMEI() {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_READ_IMEI);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer, SIM5218_RESP_OK, 10000)) {
		PDPrintln(SIM5218_M12);
		return NULL;
	}

	char *start = strstr(this->respBuffer, SIM5218_RESP_READ_IMEI);
	if(start == NULL) {
		PDPrintln(SIM5218_E14);
		this->errCode = SIM5218_ERRC_READIMEI_NO_START;
		return NULL;
	}
	start += strlen(SIM5218_RESP_READ_IMEI);
	char *end = strstr(start, this->newlineStr);
	if(end == NULL) {
		PDPrintln(SIM5218_E15);
		this->errCode = SIM5218_ERRC_READIMEI_NO_END;
		return NULL;
	}

	int idx=0;
	while(start<end) {
		this->respBuffer[idx++]=*start;
		start++;
	}
	this->respBuffer[idx]=0;

	return this->respBuffer;
}

int8_t SIM5218::setIMEI(char *imei) {
	memset(this->cmdBuffer, 0, SIM5218_CMD_BUFF_SIZE);
	sprintf(this->cmdBuffer, SIM5218_CMD_SET_IMEI, imei);

	this->delayMe();
	if(this->sendCmd(this->cmdBuffer, SIM5218_RESP_OK, 10000)) {
		PDPrintln(SIM5218_M13);
		return -1;
	}
	return 0;
}

char* SIM5218::getSMSBuffer() {
	return this->smsBuffer;
}

void SIM5218::clearSMSBuffer() {
	memset(this->smsBuffer, 0, SIM5218_SMS_BUFF_SIZE);
}

char *SIM5218::getMsisdn() {
	return this->msisdn;
}
