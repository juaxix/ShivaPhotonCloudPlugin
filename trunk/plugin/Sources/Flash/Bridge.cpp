//-----------------------------------------------------------------------------
extern "C" bool (* hermes_onRegisterPlugin) ( void *, const char * ) ;
//-----------------------------------------------------------------------------
namespace S3DX
{
    extern "C" bool RegisterStaticallyLinkedPlugin ( void *_pPlugin, const char *_pName )
    {
        return hermes_onRegisterPlugin ( _pPlugin, _pName ) ;
    }
}
//-----------------------------------------------------------------------------
