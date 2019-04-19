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
#include "createThread.h"

using namespace std;

#define MAXLINE 1024

namespace guohui
{
enum connStatus_t
{
    CONNECTING = 0,     //failed
    CONNECTED
};
class tcpClient:public createThread
{
public:
    tcpClient(int port, string addr, string logfile);
    virtual ~tcpClient();
//    bool newThread(pthread_t pthreadId, void *_start_routine(void *), void *_arg) override;
    bool buildConnect();
    void handle_connection();
    int getConnfd()
    {
        int connfd_temp;
        pthread_mutex_lock(&mutex_);
        connfd_temp = connfd_;
        pthread_mutex_unlock(&mutex_);
        return connfd_temp;
    }
    void condWait();
    guohui::logHandle* get_logHandle_();
    sockaddr_in getServerAddr()
    {
        return serverAddr_;
    }

private:
    struct sockaddr_in serverAddr_;
    int serverPort_;
    char addr_[256];

    pthread_mutex_t mutex_;
    pthread_cond_t cond_ GUARDED_BY(mutex_);
    connStatus_t connStatus_ GUARDED_BY(mutex_);
    int connfd_ GUARDED_BY(mutex_);
    guohui::logHandle* logHandle_;
};

void *tcpClientFunc(void *arg);

}       //namespace guohui



#endif /* TCPCLIENT_TCPCLIENT_H_ */
