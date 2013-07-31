#include "PrecompiledHeader.h"
#include "myPhotonCloudConfig.h"


void StdOutputListener::write(const ExitGames::Common::JString& str)
{
	std::wcout << str;
	_bstr_t b(str);
	const char* c = b;
		
	S3DX::log.message("myPhotonCloud Plugin:",
		c
	);
}

void StdOutputListener::writeLine(const ExitGames::Common::JString& str)
{
	write(str);
	write(L"\n");
}



int StdUI::serverConnection(int option)
{
	switch (option){
	case 0: //initialize and connect
		networkLogic.registerForStateUpdates(this, &mOutputListener);
		networkLogic.connectNow();
		
		break;
	case 1: //each frame must synch with server using: networkLogic.mLoadBalancingClient.service()
		networkLogic.run();
		return networkLogic.getState();
		break;
	case 2: //once connected you can join a random room
		networkLogic.joinRandomRoom();
		break;

	case 3: //connect again
		networkLogic.connectNow();
		break;
	case 4: // create room without params
		networkLogic.opCreateRoom();
		break;
	case 5: //disconnect
		networkLogic.disconnect();
		break;

	default:
		return -1;
		break;
	}
	return 0;
	/*mOutputListener.writeLine(L"always:");
	mOutputListener.writeLine(L"0 - exit");
	mOutputListener.writeLine(L"--------------------");
	mOutputListener.writeLine(L"outside a game room:");
	mOutputListener.writeLine(L"1 - create game");
	mOutputListener.writeLine(L"2 - join random game");
	mOutputListener.writeLine(L"--------------------");
	mOutputListener.writeLine(L"inside a game room:");
	mOutputListener.writeLine(L"1 - leave game");
	mOutputListener.writeLine(L"--------------------");
	while(networkLogic.getLastInput() != INPUT_EXIT && networkLogic.getState() != STATE_DISCONNECTED)
	{
		int ch = '\0';// getcharIfKbhit();
		switch(networkLogic.getState())
		{
		case STATE_CONNECTED:
			switch(ch)
			{
			case '0':
				networkLogic.setLastInput(INPUT_EXIT);
				break;
			case '1':
				networkLogic.setLastInput(INPUT_CREATE_GAME);
				break;
			case '2':
				networkLogic.setLastInput(INPUT_JOIN_RANDOM_GAME);
				break;
			default:
				networkLogic.setLastInput(INPUT_NON);
				break;
			}
			break;
		case STATE_JOINED:
			switch(ch)
			{
			case '0':
				networkLogic.setLastInput(INPUT_EXIT);
				break;
			case '1':
				networkLogic.setLastInput(INPUT_LEAVE_GAME);
				break;
			default:
				networkLogic.setLastInput(INPUT_NON);
				break;
			}
			break;
		default:
			switch(ch)
			{
			case '0':
				networkLogic.setLastInput(INPUT_EXIT);
				break;
			default:
				networkLogic.setLastInput(INPUT_NON);
				break;
			}
			break;
		}
		networkLogic.run();
		SLEEP(100);
	}*/
}

void StdUI::sendUserDataToServer(float x,float y,float z, float rx,float ry,float rz) {
	//Create hashtable
	ExitGames::Common::Hashtable userData = ExitGames::Common::Hashtable();
	//Add user data
	
	userData.put<const char*,float>("x",x);
	userData.put<const char*,float>("y",y);
	userData.put<const char*,float>("z",z);
	userData.put<const char*,float>("rx",rx);
	userData.put<const char*,float>("ry",ry);
	userData.put<const char*,float>("rz",rz);
	networkLogic.sendUserData(userData);
}

ExitGames::Common::JString StdUI::getCurrentRoomPlayersNumbers() {
	//Get list
	ExitGames::Common::JVector<int> playersIDs = networkLogic.getCurrentRoomPlayerNumbers();
	ExitGames::Common::JString playerString;
	for (unsigned int i=0; i<playersIDs.getSize(); i++){
		playerString += playersIDs[i] + ",";
	}
	return playerString;
}

myPhotonCloudConfig::myPhotonCloudConfig(void)
{
	initialized = false;
}

void myPhotonCloudConfig::connect(){
	if (!initialized){
		S3DX::log.warning("Server initialization");
		ui.serverConnection(0);
		initialized = true;
	} else {
		ui.serverConnection(0);
	}
}

int myPhotonCloudConfig::getPhotonCloudStatus(){

	return ui.serverConnection(1);
}

void myPhotonCloudConfig::joinPhotonCloudRandomRoom () {
	ui.serverConnection(2);
}

void myPhotonCloudConfig::createPhotonCloudRoom () {
	ui.serverConnection(4);
}

void myPhotonCloudConfig::disconnectPhotonCloud(){
	ui.serverConnection(5);
}

void myPhotonCloudConfig::sendUserDataToPhotonCloud(float x, float y, float z, float rx, float ry, float rz){
	ui.sendUserDataToServer(x,y,z,rx,ry,rz);
}

S3DX::AIVariable myPhotonCloudConfig::getCurrentPlayersNumbers()  {
	_bstr_t b(ui.getCurrentRoomPlayersNumbers());
	const char* c = b;
	return S3DX::AIVariable(c);
}

myPhotonCloudConfig::~myPhotonCloudConfig(void)
{

}
