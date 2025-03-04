#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lock.h>
#include <stdio.h>

struct lentry readerWriterLocks[NLOCKS];

void linit(){
    struct lentry *lockPointer;
    nextlock = NLOCKS - 1;

    int i,j;

    for(i =0;i<NLOCKS;i++){
        lockpointer = &readerWriterLocks[i];
        lockpointer->lstate= LFREE;
        lockpointer-> lqhead = newqueue();
        lockpointer->lqtail = 1 + lockpointer -> lqhead;
        lockpointer->ltype = DELETED;
        lockpointer->lprio = -1;
        

        //now update the bitmask for all the process that might be waiting for this lock
        for(j =0;j<NPROC;j++)
        lockpointer->lproc_list[j] = 0;
    }

}