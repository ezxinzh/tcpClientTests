/*
 * client.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: ezxinzh
 */
#if 1

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <pthread.h>
#include <vector>
#include "logHandle/logHandle.h"
#include "tcpClient/tcpClient.h"

using namespace std;
using namespace guohui;

#define DEFAULT_PORT (32006)
//#define DEFAULT_ADDR ("120.78.206.87")
#define DEFAULT_ADDR ("127.0.0.1")
//#define DEFAULT_ADDR ("192.168.1.6")
#define LOG_LOCATION ("logExample.txt")
#define max( a, b) (a > b) ? a : b
#define THREAD_NUMS 2

static bool newThread(pthread_t pthreadId, void *_start_routine(void *), void *_arg)
{
    if(pthread_create(&pthreadId, NULL, _start_routine, _arg))
    {
        printf("======pthread_create failed!\n");
        return false;
    }
    return true;
}

int main( int argc, char *argv[])
{
    pthread_t threadIds[THREAD_NUMS] = {0};
//    std::vector<guohui::tcpClient*> client_v;
    for(int i=0; i<THREAD_NUMS; i++)
    {
//        client_v.push_back(new(tcpClient));
    }

    /*==========================connect server==========================*/
    string buf = DEFAULT_ADDR;
    guohui::tcpClient* client1 = new guohui::tcpClient(32006, buf);
    newThread(threadIds[0], &guohui::tcpClientFunc, client1);
    usleep(100000);

    /*==========================log seng==========================*/
#if 1
    string buf1 = LOG_LOCATION;
    guohui::logHandle* logHand_1 = new guohui::logHandle(buf1);
    printf("======fun:%s line:%d do here\n", __FUNCTION__, __LINE__);
    if(client1->getConnfd() > 0)
    {
        logHand_1->setSockfd(client1->getConnfd());
    }
    else
    {
        printf("======fun[%s] line[%d] error connfd:%d\n", __FUNCTION__, __LINE__, client1->getConnfd());
        exit(-1);
    }
    newThread(threadIds[1], &guohui::logHandleFunc, logHand_1);
#endif

    for(;;)     //main thread
    {

    }

    return 0;
}

#endif



