//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "myPhotonCloud.h"
//-----------------------------------------------------------------------------


#ifdef S3DX_DLL
	myPhotonCloudAPI myPhotonCloud ;
#endif

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_getPlayersNumberList ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.getPlayersNumberList" ) ;

    // Output Parameters 
    S3DX::AIVariable sPlayersNumberList ;
	
	sPlayersNumberList = myPhotonCloud.MyPhotonCloudConfig.getCurrentPlayersNumbers();

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = sPlayersNumberList ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_sendUserData ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.sendUserData" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable x  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable y  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable z  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable rx = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable ry = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable rz = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	myPhotonCloud.MyPhotonCloudConfig.sendUserDataToPhotonCloud( x, y, z, rx, ry, rz );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_disconnect ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.disconnect" ) ;


	myPhotonCloud.MyPhotonCloudConfig.disconnectPhotonCloud();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_createRoom ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.createRoom" ) ;


	myPhotonCloud.MyPhotonCloudConfig.createPhotonCloudRoom();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_joinRandomRoom ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.joinRandomRoom" ) ;


	myPhotonCloud.MyPhotonCloudConfig.joinPhotonCloudRandomRoom();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_getStatus ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.getStatus" ) ;

    // Output Parameters 
    S3DX::AIVariable nStatus ;


	nStatus = myPhotonCloud.MyPhotonCloudConfig.getPhotonCloudStatus ();

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nStatus ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_myPhotonCloud_connect ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "myPhotonCloud.connect" ) ;


	myPhotonCloud.MyPhotonCloudConfig.connect();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

myPhotonCloudPackage::myPhotonCloudPackage ( )
{
#ifdef S3DX_DLL
    myPhotonCloud.pfn_myPhotonCloud_getPlayersNumberList = Callback_myPhotonCloud_getPlayersNumberList ;
    myPhotonCloud.pfn_myPhotonCloud_sendUserData   = Callback_myPhotonCloud_sendUserData   ;
    myPhotonCloud.pfn_myPhotonCloud_disconnect     = Callback_myPhotonCloud_disconnect     ;
    myPhotonCloud.pfn_myPhotonCloud_createRoom     = Callback_myPhotonCloud_createRoom     ;
    myPhotonCloud.pfn_myPhotonCloud_joinRandomRoom = Callback_myPhotonCloud_joinRandomRoom ;
    myPhotonCloud.pfn_myPhotonCloud_getStatus = Callback_myPhotonCloud_getStatus ;
    myPhotonCloud.pfn_myPhotonCloud_connect = Callback_myPhotonCloud_connect ;
	
#endif
}

//-----------------------------------------------------------------------------

myPhotonCloudPackage::~myPhotonCloudPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "getPlayersNumberList", Callback_myPhotonCloud_getPlayersNumberList, "sPlayersNumberList", ""               , "Get a string with the list of number (ID) of players in the cloud", 0 }, 
    { "sendUserData"  , Callback_myPhotonCloud_sendUserData  , ""       , "x,y,z, rx,ry,rz", "Send basic user data to the cloud"    , 0 }, 
    { "disconnect"    , Callback_myPhotonCloud_disconnect    , ""       , "", "Disconnect from cloud"                , 0 }, 
    { "createRoom"    , Callback_myPhotonCloud_createRoom    , ""       , "", "Create a Room without params"         , 0 }, 
    { "joinRandomRoom", Callback_myPhotonCloud_joinRandomRoom, ""       , "", "Join a random room of my Photon Cloud", 0 }, 
    { "getStatus", Callback_myPhotonCloud_getStatus, "nStatus", "", "Get My Photon Cloud Connection Status", 0 }, 
    { "connect", Callback_myPhotonCloud_connect, "", "", "Connect with default params", 0 }    
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
	{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *myPhotonCloudPackage::GetName ( ) const
{
    return "myPhotonCloud" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 myPhotonCloudPackage::GetFunctionCount ( ) const
{
	if ( aMyFunctions[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyFunctions ) / sizeof( S3DX::AIFunction ) ;
	}
}

//-----------------------------------------------------------------------------

S3DX::uint32 myPhotonCloudPackage::GetConstantCount ( ) const
{
	if ( aMyConstants[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyConstants ) / sizeof( S3DX::AIConstant ) ;
	}
}

//-----------------------------------------------------------------------------

const S3DX::AIFunction *myPhotonCloudPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *myPhotonCloudPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
