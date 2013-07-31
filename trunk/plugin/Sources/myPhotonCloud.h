//-----------------------------------------------------------------------------
#ifndef __myPhotonCloud_h__
#define __myPhotonCloud_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
#include "myPhotonCloudConfig.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class myPhotonCloudPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	myPhotonCloudPackage         ( ) ;
                               ~myPhotonCloudPackage         ( ) ;

	//-------------------------------------------------------------------------
    //  Accessors
	//-------------------------------------------------------------------------

    const   char               *GetName             ( ) const ;
            S3DX::uint32        GetFunctionCount    ( ) const ;
            S3DX::uint32        GetConstantCount    ( ) const ;
    const   S3DX::AIFunction   *GetFunctionAt       ( S3DX::uint32 _iIndex ) const ;
    const   S3DX::AIConstant   *GetConstantAt       ( S3DX::uint32 _iIndex ) const ;

} ;

//-----------------------------------------------------------------------------
// Package API declaration
//-----------------------------------------------------------------------------
class myPhotonCloudAPI
{
public :
	//Config Server Here
	myPhotonCloudConfig MyPhotonCloudConfig;
    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                myPhotonCloudAPI       ( ) 
                                {
                                    pfn_myPhotonCloud_getPlayersNumberList = NULL ;
                                    pfn_myPhotonCloud_sendUserData   = NULL ;
                                    pfn_myPhotonCloud_disconnect     = NULL ;
                                    pfn_myPhotonCloud_createRoom     = NULL ;
                                    pfn_myPhotonCloud_joinRandomRoom = NULL ;
                                    pfn_myPhotonCloud_getStatus = NULL ;
                                    pfn_myPhotonCloud_connect = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_myPhotonCloud_getPlayersNumberList ;
    S3DX::AICallback        pfn_myPhotonCloud_sendUserData ;
    S3DX::AICallback        pfn_myPhotonCloud_disconnect ;
    S3DX::AICallback        pfn_myPhotonCloud_createRoom ;
    S3DX::AICallback        pfn_myPhotonCloud_joinRandomRoom ;
    S3DX::AICallback        pfn_myPhotonCloud_getStatus ;
    S3DX::AICallback        pfn_myPhotonCloud_connect ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline S3DX::AIVariable     getPlayersNumberList (  ) { S3DX::AIVariable vOut ; if ( pfn_myPhotonCloud_getPlayersNumberList ) pfn_myPhotonCloud_getPlayersNumberList ( 0, NULL, &vOut ); return vOut ; }
    inline void                 sendUserData   ( const S3DX::AIVariable& x, const S3DX::AIVariable& y, const S3DX::AIVariable& z, const S3DX::AIVariable& rx, const S3DX::AIVariable& ry, const S3DX::AIVariable& rz ) { S3DX_DECLARE_VIN_06( x, y, z, rx, ry, rz ) ; if ( pfn_myPhotonCloud_sendUserData ) pfn_myPhotonCloud_sendUserData ( 6, vIn, NULL );  }
    inline void                 disconnect     (  ) { if ( pfn_myPhotonCloud_disconnect ) pfn_myPhotonCloud_disconnect ( 0, NULL, NULL );  }
    inline void                 createRoom     (  ) { if ( pfn_myPhotonCloud_createRoom ) pfn_myPhotonCloud_createRoom ( 0, NULL, NULL );  }
    inline void                 joinRandomRoom (  ) { if ( pfn_myPhotonCloud_joinRandomRoom ) pfn_myPhotonCloud_joinRandomRoom ( 0, NULL, NULL );  }
    inline S3DX::AIVariable     getStatus (  ) { S3DX::AIVariable vOut ; if ( pfn_myPhotonCloud_getStatus ) pfn_myPhotonCloud_getStatus ( 0, NULL, &vOut ); return vOut ; }
    inline void                 connect (  ) { if ( pfn_myPhotonCloud_connect ) pfn_myPhotonCloud_connect ( 0, NULL, NULL );  }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------


} ;

extern myPhotonCloudAPI myPhotonCloud;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
