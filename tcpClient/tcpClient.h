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

<<<<<<< HEAD
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   // no-op
#define GUARDED_BY(x) \
  THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))
=======
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
#define MAXLINE 1024

namespace guohui
{
<<<<<<< HEAD
enum connStatus_t
{
    CONNECTING = 0,
    CONNECTED
};
=======
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
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
<<<<<<< HEAD
    void condWait();

=======
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
private:
    struct sockaddr_in serverAddr_;
    int serverPort_;
    char addr_[256];
    int connfd_;
<<<<<<< HEAD
    pthread_mutex_t mutex_;
    pthread_cond_t cond_ GUARDED_BY(mutex_);
    connStatus_t connStatus_ GUARDED_BY(mutex_);
=======
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
};

void *tcpClientFunc(void *arg);

}       //namespace guohui



#endif /* TCPCLIENT_TCPCLIENT_H_ */
