
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lock.h>
#include <stdio.h>

int lcreate(){
    STATWORD ps;
    int lockDescriptor;

    disable(ps);
    lockDescriptor = newlock();
    if(lockDescriptor == SYSERR){
        restore(ps);
        return SYSERR;
    }
    restore(ps);
    return lockDescriptor;
}


LOCAL int newLock(){
    int lockDescriptor;
    int i;
    
    for(i =0;i<NLOCKs;i++){
        // check for the first available lock, if its in LFREE state
        // if not not return a syserr
        lockDescriptor = nextLock;
        nextLock = nextLock - 1;
        if(lockDescriptor < 0 ){
            nextLock = NLOCKs - 1;
        }
        if(rw_locks[ld].lstate == LFREE){
            rw_locks[ld].lstate = LUSED;
            return ld;
        }
    }
    return SYSERR;
}