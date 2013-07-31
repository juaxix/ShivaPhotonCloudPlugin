//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
//-----------------------------------------------------------------------------
#include <string.h>
//-----------------------------------------------------------------------------
S3DX_IMPLEMENT_AIVARIABLE_STRING_POOL   ( 524288 ) ;
S3DX_IMPLEMENT_AIENGINEAPI              ( MyPhotonCloud ) ;
S3DX_IMPLEMENT_PLUGIN                   ( MyPhotonCloud ) ;

//-----------------------------------------------------------------------------
//  AI Packages
//-----------------------------------------------------------------------------

#include "myPhotonCloud.h"

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

MyPhotonCloud::MyPhotonCloud ( )
{
    S3DX_REGISTER_PLUGIN  ( "com.xixgames.myphotoncloud" ) ;
    aContentsDirectory[0] = '\0' ;
	
	//Instanciate AI Packages
    S3DX::uint32 iAIPackageIndex = 0 ;

    if ( iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT ) aAIPackages [iAIPackageIndex++] = new myPhotonCloudPackage ( ) ;

	for ( ; iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT; iAIPackageIndex ++ )
	{
        aAIPackages[iAIPackageIndex] = NULL  ;		
	}

}

//-----------------------------------------------------------------------------

MyPhotonCloud::~MyPhotonCloud ( )
{
	for ( S3DX::uint32 iAIPackageIndex = 0 ; iAIPackageIndex < PLUGIN_AIPACKAGES_COUNT; iAIPackageIndex ++ )
	{
		if ( aAIPackages [iAIPackageIndex] )
		{
			delete aAIPackages [iAIPackageIndex] ; 
			aAIPackages[iAIPackageIndex] = NULL  ;
		}
	}
}


//-----------------------------------------------------------------------------
//  Plugin content directory
//-----------------------------------------------------------------------------

        void                    MyPhotonCloud::SetContentsDirectory  ( const char *_pDirectory ) { strcpy ( aContentsDirectory, _pDirectory ) ; }

//-----------------------------------------------------------------------------
//  AI packages
//-----------------------------------------------------------------------------

        S3DX::uint32            MyPhotonCloud::GetAIPackageCount     ( )                      const { return PLUGIN_AIPACKAGES_COUNT ; }
const   S3DX::AIPackage        *MyPhotonCloud::GetAIPackageAt        ( S3DX::uint32 _iIndex ) const { return (_iIndex < PLUGIN_AIPACKAGES_COUNT) ? aAIPackages[_iIndex] : NULL ; }

