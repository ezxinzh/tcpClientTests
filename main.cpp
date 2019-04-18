/*
 * client.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: ezxinzh
 */

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
#define DEFAULT_ADDR ("120.78.206.87")
//#define DEFAULT_ADDR ("127.0.0.1")
//#define DEFAULT_ADDR ("192.168.1.6")
#define LOG_LOCATION ("logExample.txt")
#define max( a, b) (a > b) ? a : b
#define THREAD_NUMS 2

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
      printf("Usage:\n  %s threadnums \n", argv[0]);
      return 0;
    }

    int threadNums = THREAD_NUMS;
    if(argc > 1)
    {
        threadNums = atoi(argv[1]);
        printf("======file[%s] func[%s] line[%d] threadNums:%d.\n", \
                        __FILE__, __FUNCTION__, __LINE__, threadNums);
    }
    pthread_t threadIds[threadNums] = {0};
    std::vector<guohui::tcpClient*> client_v;
    string buf = DEFAULT_ADDR;

    string buf1 = LOG_LOCATION;

    for(int i=0; i<threadNums; i++)
    {
        client_v.push_back(new guohui::tcpClient(32006, buf, buf1));
    }

    /*==========================connect server==========================*/
    std::vector<guohui::tcpClient*>::iterator it;
    int i = 0;
    for(it = client_v.begin(); it!=client_v.end(); it ++)
    {
        (*it)->newThread(threadIds[i], &guohui::tcpClientFunc, *it);
        i++;
        usleep(100000);
    }
//    guohui::tcpClient* client1 = new guohui::tcpClient(32006, buf, buf1);
//    newThread(threadIds[0], &guohui::tcpClientFunc, client1);

    for(;;)     //main thread
    {

    }

    return 0;
}



