/*
 * tcpClient.cpp
 *
 *  Created on: Apr 17, 2019
 *      Author: ezxinzh
 */
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include "tcpClient.h"

using namespace std;

namespace guohui
{
tcpClient::tcpClient(int port, string addr, string logfile):
        serverPort_(port),
        connfd_(0),
        mutex_(PTHREAD_MUTEX_INITIALIZER),
        cond_(PTHREAD_COND_INITIALIZER),
        connStatus_(CONNECTING),
        logHandle_(new guohui::logHandle(logfile))
{
    strcpy(addr_, addr.c_str());
//    printf("======port:%d addr:%s\n", serverPort_, addr_);
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(serverPort_);
    serverAddr_.sin_addr.s_addr = inet_addr(addr_);
}

tcpClient::~tcpClient()
{
    delete logHandle_;
    logHandle_ = NULL;
}

bool tcpClient::buildConnect()
{
    connfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if( connfd_ < 0)
    {
        printf("======tid[%lu] socket error\n", this->tid());
        return false;
    }

    if(connect(connfd_, (struct sockaddr*)&serverAddr_, sizeof(serverAddr_)) < 0)
    {
        printf("======tid[%lu] connect failed\n", this->tid());
        return false;
    }
    else
    {
        printf("======tid[%lu] file[%s] func[%s] line[%d] connect server:%s successful.\n", \
                this->tid(), __FILE__, __FUNCTION__, __LINE__, inet_ntoa(serverAddr_.sin_addr));
        write(connfd_, "hello server, i am log client.\n", strlen("hello server, i am client.\n"));
    }
//    printf("======file[%s] fun[%s] line[%d] connfd:%d\n", \
//            __FILE__, __FUNCTION__, __LINE__, this->getConnfd());

    pthread_mutex_lock(&mutex_);
    connStatus_ = CONNECTED;
    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&mutex_);

    return true;
}

void tcpClient::handle_connection()
{
    char sendline[MAXLINE] = {0};
    char recvline[MAXLINE] = {0};
//    int maxfdp, stdineof;
    struct pollfd pfds[2];
    int n;
    if(connfd_ < 0)
        return;
    /* connected socket */
    pfds[0].fd = connfd_;
    pfds[0].events = POLLIN;
    /* standard input and output */
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    int cnt = 0;
    char buf[256] = {0};
    char buf1[256] = "hello, i am log client.";

    //==========================send logFile line by line to logServer
    pthread_t logHandleId;
    if(this->newThread(logHandleId, &guohui::logHandleFunc, logHandle_))
        printf("======tid[%lu] file[%s] func[%s] line[%d] logHandle thread created.\n", \
                this->tid(), __FILE__, __FUNCTION__, __LINE__);
    else
        printf("======tid[%lu] file[%s] func[%s] line[%d] create logHandle thread failed!\n", \
                this->tid(), __FILE__, __FUNCTION__, __LINE__);

    while(1)
    {
        poll(pfds, 2, -1);
        if(pfds[0].revents & POLLIN)
        {
            memset(recvline, 0, MAXLINE);
            n = read(pfds[0].fd, recvline, MAXLINE);
            if(n == 0)
            {
                fprintf(stderr, "tid[%lu] client:server is closed.\n", this->tid());
                close(pfds[0].fd);
            }
            write(STDOUT_FILENO, recvline, n);
            if(cnt >= 32767)
                cnt = 0;
            cnt += 1;
//            memset(sendline, 0, sizeof(sendline)/sizeof(char));
//            sprintf(buf, " %d times\n", cnt);
//            strcpy(sendline, buf1);
//            strcat(sendline, buf);
            write(pfds[0].fd, buf1, strlen(buf1));
        }

        if(pfds[1].revents & POLLIN)
        {
            n = read(STDIN_FILENO, recvline, MAXLINE);
            if(n == 0)
            {
                shutdown(connfd_, SHUT_WR);
                continue;
            }
            write(connfd_, recvline, n);
        }
    }
}

void tcpClient::condWait()
{
    pthread_mutex_lock(&mutex_);
    if(connStatus_ != CONNECTED)
        pthread_cond_wait(&cond_, &mutex_);
    pthread_mutex_unlock(&mutex_);
    return;
}

guohui::logHandle* tcpClient::get_logHandle_()
{
    return logHandle_;
}

void *tcpClientFunc(void *arg)
{
    guohui::tcpClient *cp = (guohui::tcpClient*)arg;
    if(cp->buildConnect())
        cp->get_logHandle_()->setSockfd(cp->getConnfd());
    cp->handle_connection();
}
}       //namespace guohui




