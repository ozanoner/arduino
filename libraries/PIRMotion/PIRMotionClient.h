
#ifndef _PIRMOTION_CLIENT_H_
#define _PIRMOTION_CLIENT_H_

class PIRMotionClient {
public:
	PIRMotionClient() { };

	void setCallback(void (*cb)(void)) {
		this->motCallback=cb;
	};
	
	virtual void invokePMotCallback() {
		if(this->motCallback!=NULL)
			this->motCallback();
	};
protected:
	void (*motCallback)(void);
};

#endif
