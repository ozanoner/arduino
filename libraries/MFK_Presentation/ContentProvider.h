
/*
 * by Ozan Oner
 *
 * content provider for page.chapter
 * instanciated in ContentFactory
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
	char* getContent(char *contentBuff, int& answer) const
	{
		if(this->contentCallback!=NULL)
		{
			this->contentCallback(contentBuff, answer);
			return contentBuff;
		}
		// Serial.println(F("getContent returns NULL"));
		return NULL;
	};
};

#endif
