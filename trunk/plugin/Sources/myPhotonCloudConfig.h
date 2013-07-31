#pragma once

//Now we can load the Network logic class:
#include "NetworkLogic.h"


class StdOutputListener: public OutputListener
{
public:
	virtual void write(const ExitGames::Common::JString& str);
	virtual void writeLine(const ExitGames::Common::JString& str);
};
class StdUI: public NetworkLogicListener
{
public:
	int serverConnection(int option);
	void sendUserDataToServer(float x,float y,float z, float rx,float ry,float rz);
	ExitGames::Common::JString getCurrentRoomPlayersNumbers() ;
private:
	virtual void stateUpdate(State newState)
	{}
	
private:
	StdOutputListener mOutputListener;
	NetworkLogic networkLogic;
};

class myPhotonCloudConfig
{
private:
	StdUI ui;
	bool initialized;
	NetworkLogic networklogic();
public:
	myPhotonCloudConfig(void);
	void connect();
	int getPhotonCloudStatus();
	void joinPhotonCloudRandomRoom();
	void createPhotonCloudRoom();
	void disconnectPhotonCloud();
	void sendUserDataToPhotonCloud(float x, float y, float z, float rx, float ry, float rz);
	S3DX::AIVariable getCurrentPlayersNumbers() ;
	~myPhotonCloudConfig(void);
};

