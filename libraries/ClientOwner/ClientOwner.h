
#ifndef _CLIENT_OWNER_H_
#define _CLIENT_OWNER_H_

template<class T>
class ClientOwner {
public:
	ClientOwner() {
		for(int i=0; i<5; i++)
			this->client[i]=NULL;
	};

	// returns client id, -1 if fails
	int registerClient(T* cl) {
		for(int i=0; i<5; i++) {
			if(this->client[i]==NULL) {
				this->client[i]=cl;
				return i;
			}
		}
		return -1;
	};
	
	//unregisters client
	void unregisterClient(int i) {
		if(i<0||i>4)
			return;
		this->client[i]=NULL;
	};
protected:
	T* client[5];
};

#endif

