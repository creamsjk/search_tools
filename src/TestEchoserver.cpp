#include "../include/EchoServer.h"

int main(int argc, char **argv)
{
    SplitTool sp;
    Echoserver server(4, 10, "127.0.0.1", 8888, &sp);
    
    server.start();

    return 0;
}

