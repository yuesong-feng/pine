#include "Socket.h"
#include <cassert>

int main(){
    Socket svr_sock;
    assert( svr_sock.Create() == RC_SUCCESS );
    assert( svr_sock.Bind() == RC_SUCCESS );
    assert( svr_sock.Listen() == RC_SUCCESS );
    Socket clnt_sock;
    assert( svr_sock.Accept(&clnt_sock) == RC_SUCCESS );
    assert( clnt_sock.fd() != -1 );
    
    return 0;
}
