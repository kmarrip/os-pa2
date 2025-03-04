
#ifndef _LOCK_H
#define _LOCK_H

#define NLOCKS 50  /*maximum number of locks*/

#define NFREE '\01'
#define NUSED '\02'


#define READ 0
#define WRITE 1

struct lentry{
    char lstate; // current state of the lock
    int lqhead; // head of the processes waiting for this lock
    int lqtail; // tail of the processes waiting for this lock 
    int ltype; // this can either be read or write lock
    int lprio; // maximum priority of the process among
    int lprocList[NPROC]; // list of processes waiting for this lock
}

extern struct lentry readWriteLocks[];
extern int nextLock;
extern unsigned long ctr1000;

bool isBadLock(int sem){
    // check if the lock is out of bound for lock array
    return s<0 || s >= NLOCKS;
}