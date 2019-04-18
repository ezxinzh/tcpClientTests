#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "logHandle.h"

using namespace std;

namespace guohui
{
void *logHandleFunc(void *arg)
{
    printf("======do here fun:%s line:%d\n", __FUNCTION__, __LINE__);
    guohui::logHandle * lp = (guohui::logHandle*)arg;

    lp->sendlineToServer();
}

logHandle::logHandle(string file):
        logFile_("logExample.txt"),
        sockfd_(0)
{
    strcpy(logFile_, file.c_str());
    in_.open(logFile_);
}
 
void logHandle::sendlineToServer()
{
    string line;

    for(;;)
    {
        if(in_)
        {
            getline(in_, line);
        }
        else
        {
            in_.clear();
            in_.close();
            in_.open(logFile_);
            cout <<"no such file" << endl;
        }

        if(!line.empty())
        {
            write(sockfd_, line.c_str(), line.length());
            std::cout<<line.c_str()<<endl;
        }
        usleep(500000);
    }
}
}

