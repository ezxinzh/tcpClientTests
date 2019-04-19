#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "logHandle.h"

using namespace std;

namespace guohui
{
void *logHandleFunc(void *arg)
{
    guohui::logHandle * lp = (guohui::logHandle*)arg;
    lp->sendlineToServer();
}

logHandle::logHandle(string file):
        logFile_("logExample.txt"),
        sockfd_(0),
        connFlag_(false)
{
    strcpy(logFile_, file.c_str());
    in_.open(logFile_);
}
 
void logHandle::sendlineToServer()
{
    string line;

    for(;;)
    {
        if(connFlag_ == true)
        {
            if(in_)
            {
                getline(in_, line);
            }
            else
            {
                cout <<"tid["<<this->tid()<<"]no such file" << endl;
                in_.clear();
                in_.close();
                in_.open(logFile_);
                cout <<"tid["<<this->tid()<<"] open "<<logFile_<<" again"<< endl;
            }

            if(!line.empty())
            {
                write(sockfd_, line.c_str(), line.length());
    //            std::cout<<line.c_str()<<endl;
            }
            usleep(500000);
        }
        else
            printf("======tid[%lu] file[%s] func[%s] line[%d] connection not established!\n", \
                                    this->tid(), __FILE__, __FUNCTION__, __LINE__);
    }
}

void logHandle::sendFileLineByLine()
{
    string line;
    for(;;)
    {
        if(connFlag_ == true)
        {
            if(in_)
                getline(in_, line);
            else
            {
                cout <<"tid["<<this->tid()<<"] no such file"<< endl;
                in_.clear();
                in_.close();
                in_.open(logFile_);
                cout <<"tid["<<this->tid()<<"] open "<<logFile_<<" again"<< endl;
            }

            if(!line.empty())
                write(sockfd_, line.c_str(), line.length());
            usleep(500000);
        }
    }
}

void logHandle::setConnPara(bool connFlag, int sockfd)
{
    connFlag_ = connFlag;
    sockfd_ = sockfd;
    printf("======tid[%lu] file[%s] func[%s] line[%d] set connFlag_:%s sockfd_:%d.\n", \
                        this->tid(), __FILE__, __FUNCTION__, __LINE__, \
                        (connFlag_==true?"true":"false"), sockfd_);
    return;
}
}

