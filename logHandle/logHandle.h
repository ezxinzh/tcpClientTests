/*
 * logHandle.h
 *
 *  Created on: Apr 17, 2019
 *      Author: ezxinzh
 */

#ifndef LOGHANDLE_LOGHANDLE_H_
#define LOGHANDLE_LOGHANDLE_H_

#include <fstream>
#include <string.h>
#include <iostream>
#include "../tcpClient/createThread.h"

using namespace std;

namespace guohui
{
class logHandle:public createThread
{
public:
    logHandle(string file);
    void sendlineToServer();
    void setSockfd(int sockfd)
    {
        if(sockfd > 0)
        {
            sockfd_ = sockfd;
            printf("======tid[%lu] file[%s] func[%s] line[%d] set sockfd:%d.\n", \
                    this->tid(), __FILE__, __FUNCTION__, __LINE__, \
                    sockfd_);
        }
        else
            printf("======error sockfd!\n");
    }
    void sendFileLineByLine();
    void setConnPara(bool connFlag, int sockfd);
private:
    ifstream in_;
    char logFile_[256];
    pthread_mutex_t mutex_;
    bool connFlag_;
    int sockfd_;
};

void *logHandleFunc(void *arg);
}



#endif /* LOGHANDLE_LOGHANDLE_H_ */
