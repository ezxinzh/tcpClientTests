/*
 * tcpClient.h
 *
 *  Created on: Apr 17, 2019
 *      Author: ezxinzh
 */

#ifndef TCPCLIENT_TCPCLIENT_H_
#define TCPCLIENT_TCPCLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "../logHandle/logHandle.h"

using namespace std;

#define MAXLINE 1024

namespace guohui
{
class tcpClient
{
public:
    tcpClient(int port, string addr);
    bool buildConnect();
    void handle_connection();
    int getConnfd()
    {
        return connfd_;
    }
private:
    struct sockaddr_in serverAddr_;
    int serverPort_;
    char addr_[256];
    int connfd_;
};

void *tcpClientFunc(void *arg);

}       //namespace guohui



#endif /* TCPCLIENT_TCPCLIENT_H_ */
