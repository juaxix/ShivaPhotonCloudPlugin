#pragma once

#ifndef __NETWORK_LOGIC_H
#define __NETWORK_LOGIC_H
//Get these values from the PC Dashboard: https://cloud.exitgames.com/Dashboard
#define MY_PHOTON_CLOUD_APP_ID L"Enter your app id here"
#define MY_PHOTON_CLOUD_APP_VERSION L"1.0"

#ifndef __OUTPUT_LISTENER_H
#define __OUTPUT_LISTENER_H

#ifndef _EG_ANDROID_PLATFORM
#include <iostream>
#endif
#include "LoadBalancing-cpp/inc/LoadBalancingClient.h"
#include <comdef.h>  // you will need this
#if defined _EG_WIN32_PLATFORM
#	define SLEEP(ms) Sleep(ms)
#else
#	define SLEEP(ms) usleep(ms*1000)
#endif

class OutputListener
{
public:
	virtual ~OutputListener(void){};
	virtual void write(const ExitGames::Common::JString& str) = 0;
	virtual void writeLine(const ExitGames::Common::JString& str) = 0;
	virtual void debugReturn(const ExitGames::Common::JString& str)
	{
		#ifndef _EG_ANDROID_PLATFORM
			std::wcerr << str << std::endl;
		#endif
		
		_bstr_t b(str);
		const char* c = b;
		
		S3DX::log.message("myPhotonCloud Plugin:",
			c
		);
	}
};

#endif

typedef enum _State
{
	STATE_INITIALIZED = 0,
	STATE_CONNECTING,
	STATE_CONNECTED,
	STATE_JOINING,
	STATE_JOINED,
	STATE_LEAVING,
	STATE_LEFT,
	STATE_DISCONNECTING,
	STATE_DISCONNECTED
} State;

typedef enum _Input
{
	INPUT_NON = 0,
	INPUT_CREATE_GAME,
	INPUT_JOIN_RANDOM_GAME,
	INPUT_LEAVE_GAME,
	INPUT_EXIT
} Input;



class NetworkLogicListener : public ExitGames::Common::ToString
{
public:
	using ExitGames::Common::ToString::toString;
	virtual void stateUpdate(State newState) = 0;
	virtual ExitGames::Common::JString& toString(ExitGames::Common::JString& retStr, bool withTypes=false) const;
};



class StateAccessor
{
public:
	State getState(void) const;
	void setState(State newState);
	void registerForStateUpdates(NetworkLogicListener* listener);

private:
	State mState;
	ExitGames::Common::JVector<NetworkLogicListener*> mStateUpdateListeners;
};



class NetworkLogic : private ExitGames::LoadBalancing::Listener
{
public:
	NetworkLogic(); //empty constructor
	NetworkLogic(OutputListener* listener, const wchar_t* appVersion);
	void registerForStateUpdates(NetworkLogicListener* listener);
	void registerForStateUpdates(NetworkLogicListener* nlistener,OutputListener* slistener );
	void run(void);
	void connectNow(void); //invoke by juaxix
	void connect(void);
	void opCreateRoom(void);
	void opJoinRandomRoom(void);
	void disconnect(void);
	void sendEvent(void);
	void sendUserData(ExitGames::Common::Hashtable uData);
	void joinRandomRoom();
	Input getLastInput(void) const;
	void setLastInput(Input newInput);
	State getState(void) const;
	int getCurrentPlayerNumber(void) {return this->mLoadBalancingClient.getLocalPlayer().getNumber();};
	ExitGames::Common::JVector<int> getCurrentRoomPlayerNumbers(void);
private:
	//From Common::BaseListener
	// receive and print out Photon datatypes debug out here
	virtual void debugReturn(const ExitGames::Common::JString& string);

	//From LoadBalancing::LoadBalancingListener
	// receive and print out Photon LoadBalancing debug out here
	virtual void debugReturn(ExitGames::Common::DebugLevel::DebugLevel debugLevel, const ExitGames::Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Hashtable& eventContent);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void gotQueuedReturn(void);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);

	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	ExitGames::Common::JString mGameID;
	ExitGames::Common::Logger mLogger;
	StateAccessor mStateAccessor;
	Input mLastInput;
	OutputListener* mOutputListener;
};

#endif
