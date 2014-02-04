/*
 * Singleton pattern: There will be only one instance of ContentFactory.
 * Factory pattern: Creates ContentProvider instances acc.to user request.
 */

#ifndef _CONTENT_FACTORY_H_
#define _CONTENT_FACTORY_H_

// analog pin for random seed
#define RANDOM_SEED_PIN 3

#include "Arduino.h"
#include "ContentProvider.h"
#include "Flash.h"


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

	static ContentFactory* getInstance() {
		static ContentFactory f;
		return &f;
	}
	ContentProvider *getContentProvider(OperationTypeEnum op, ContentLevelEnum level);
private:
	// first idx OperationType, second ContentLevel
	ContentProvider* contentProvider[5][3];
	ContentFactory();
	ContentFactory(ContentFactory const&); // copy disabled
	void operator=(ContentFactory const&); // assigment disabled
};

#endif
