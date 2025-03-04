#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lock.h>
#include <stdio.h>


int getProcessPriority(struct pentry *pptr){
    return pptr->pinh == 0 ? pptr -> pprio : pptr -> pinh;
}

//get the lock id which is in the wait queue for priority inheritence
int getLockPriorirytInheritance(int pid){
    struct pentry *pptr = &proctab[pid];
    int lockDescriptor = pptr->wait_lockId;
    return isbadlock(lockDescriptor) ? -1 : lockDescriptor;
}

int getMaxWaitPriorityForPriorityInheritence(int pid){
    int i;
    int returnValue = 0;
    struct pentry *pptr = &proctab[pid];
    struct lentry *lptr;

    //for all the all locks that are waiting for this one process
    //lookup all the processes and get the maximum priority of that process
    for(i =0;i<NLOCKS;i++){
        if(pptr->bm_locks[i]!=1)continue;
        lptr = &readerWriterLocks[i];
        returnValue  = lptr->lprio > returnValue ? lptr->lprio : returnValue;
    }
    return returnValue;
}