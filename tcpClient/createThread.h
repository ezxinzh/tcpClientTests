/*
 * createThread.h
 *
 *  Created on: Apr 18, 2019
 *      Author: ezxinzh
 */

#ifndef TCPCLIENT_CREATETHREAD_H_
#define TCPCLIENT_CREATETHREAD_H_

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

class createThread
{
public:
    virtual bool newThread(pthread_t pthreadId, void *_start_routine(void *), void *_arg)
    {
        if(pthread_create(&pthreadId, NULL, _start_routine, _arg))
        {
            printf("======pthread_create failed!\n");
            return false;
        }
        return true;
    }
    virtual ~createThread(){}
    pid_t pid()
    {
        return getpid();
    }
    pthread_t tid()
    {
        return pthread_self();
    }
};



#endif /* TCPCLIENT_CREATETHREAD_H_ */
