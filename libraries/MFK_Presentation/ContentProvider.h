
/*
 * Almost strategy pattern.
 * Underlying 'getContent' implementation differs acc.to contentCallback function.
 * If you convert this class to a class with pure 'getContent' function
 * and create subclasses with different implementations of 'getContent',
 * it becomes strategy pattern.
 * But we have similar effect with that ContentProvider.
 */

#ifndef _CONTENT_PROVIDER_H_
#define _CONTENT_PROVIDER_H_

#include "Arduino.h"

class ContentProvider {
protected:
	void (*contentCallback)(char *, int &);
public:
	ContentProvider(void (*cb)(char *, int &))
	{
		this->contentCallback=cb; 
	};
	char* getContent(char *contentBuff, int& answer)
	{
		if(this->contentCallback!=NULL)
		{
			this->contentCallback(contentBuff, answer);
			return contentBuff;
		}
		Serial.println(F("getContent returns NULL"));
		return NULL;
	};
};

#endif
