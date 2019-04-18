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
tcpClient::tcpClient(int port, string addr):
        serverPort_(port),
<<<<<<< HEAD
        connfd_(0),
        mutex_(PTHREAD_MUTEX_INITIALIZER),
        cond_(PTHREAD_COND_INITIALIZER),
        connStatus_(CONNECTING)
=======
        connfd_(0)
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
{
    strcpy(addr_, addr.c_str());
//    printf("======port:%d addr:%s\n", serverPort_, addr_);
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(serverPort_);
    serverAddr_.sin_addr.s_addr = inet_addr(addr_);
}

bool tcpClient::buildConnect()
{
    connfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if( connfd_ < 0)
    {
        printf("======socket error");
        return false;
    }

    if(connect(connfd_, (struct sockaddr*)&serverAddr_, sizeof(serverAddr_)) < 0)
    {
        printf("======connect failed");
        return false;
    }
    else
    {
        printf("======connect server:%s successful.\n", inet_ntoa(serverAddr_.sin_addr));
        write(connfd_, "hello server, i am client.\n", strlen("hello server, i am client.\n"));
    }
    printf("======fun:%s line:%d connfd:%d\n", __FUNCTION__, __LINE__, this->getConnfd());
<<<<<<< HEAD

    pthread_mutex_lock(&mutex_);
    connStatus_ = CONNECTED;
    pthread_cond_signal(&cond_);
    pthread_mutex_unlock(&mutex_);

=======
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
    return true;
}

void tcpClient::handle_connection()
{
    char sendline[MAXLINE] = {0};
    char recvline[MAXLINE] = {0};
//    int maxfdp, stdineof;
    struct pollfd pfds[2];
<<<<<<< HEAD
    /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */
=======
    /* ������������� */
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
    int n;
    if(connfd_ < 0)
        return;
    pfds[0].fd = connfd_;
    pfds[0].events = POLLIN;
<<<<<<< HEAD
    /* 锟斤拷颖锟阶硷拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */
=======
    /* ��ӱ�׼���������� */
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    int cnt = 0;
    char buf[256] = {0};
    char buf1[256] = "\n                       hello, welcome to my world";

    while(1)
    {
        poll(pfds, 2, -1);
        if(pfds[0].revents & POLLIN)
        {
            memset(recvline, 0, MAXLINE);
            n = read(pfds[0].fd, recvline, MAXLINE);
            if(n == 0)
            {
                fprintf(stderr, "client:server is closed.");
                close(pfds[0].fd);
            }
            write(STDOUT_FILENO, recvline, n);
            write(STDOUT_FILENO, "\n", n);
            if(cnt >= 32767)
                cnt = 0;
            cnt += 1;
            sprintf(buf, " %d times\n", cnt);
            strcpy(sendline, buf1);
            strcat(sendline, buf);
            write(pfds[0].fd, sendline, strlen(sendline));
        }
<<<<<<< HEAD
        /* 锟斤拷锟皆憋拷准锟斤拷锟斤拷锟角凤拷准锟斤拷锟斤拷 */
=======
        /* ���Ա�׼�����Ƿ�׼���� */
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
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

<<<<<<< HEAD
void tcpClient::condWait()
{
    pthread_mutex_lock(&mutex_);
    if(connStatus_ != CONNECTED)
        pthread_cond_wait(&cond_, &mutex_);
    pthread_mutex_unlock(&mutex_);
    return;
}

void *tcpClientFunc(void *arg)
{
=======
void *tcpClientFunc(void *arg)
{
    printf("======3\n");
>>>>>>> 8e9b9e9ff3dd12ffb94c157fbd696e8c322d135a
    guohui::tcpClient *cp = (guohui::tcpClient*)arg;
    cp->buildConnect();
    cp->handle_connection();
}
}       //namespace guohui




