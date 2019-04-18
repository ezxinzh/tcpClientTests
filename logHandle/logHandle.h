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

using namespace std;

namespace guohui
{
class logHandle
{
public:
    logHandle(string file);
    void sendlineToServer();
    void setSockfd(int sockfd)
    {
        if(sockfd > 0)
            sockfd_ = sockfd;
        else
            printf("======error sockfd!\n");
    }
private:
    ifstream in_;
    char logFile_[256];
    int sockfd_;
};

void *logHandleFunc(void *arg);
}



#endif /* LOGHANDLE_LOGHANDLE_H_ */
