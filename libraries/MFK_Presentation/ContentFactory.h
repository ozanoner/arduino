/*
 * by Ozan Oner
 *
 * produces ContentProviders,
 * lazy instantiation
 */

#ifndef _CONTENT_FACTORY_H_
#define _CONTENT_FACTORY_H_



#include "Arduino.h"
#include "ContentProvider.h"
#include "Flash.h"
#include "MFK_Pins.h"


class ContentFactory {
public:
	enum OperationTypeEnum {
		Addition,
		Subtraction,
		Multiplication,
		Division,
		Fun
	};
	
	enum ContentLevelEnum {
		Level1Content,
		Level2Content,
		Level3Content,
		// Level4Content,
	};

	// returns the only instance of ContentFactory
	static ContentFactory* getInstance() {
		static ContentFactory f;
		return &f;
	}
	// returns ContentProvider
	const ContentProvider* getContentProvider(OperationTypeEnum op,\
		   	ContentLevelEnum level);
private:
	// first idx OperationType, second ContentLevel
	ContentProvider* contentProvider[5][3];
	
	ContentFactory(); // private constructor
	ContentFactory(ContentFactory const&); // copy disabled
	void operator=(ContentFactory const&); // assigment disabled
};

#endif
