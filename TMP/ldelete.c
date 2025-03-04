#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <lock.h>
#include <stdio.h>


SYSCALL ldelete(int lockDescriptor)
{
	STATWORD ps;    
	int	pid;
	struct	lockEntry	*lockPointer;
	int i;


    //first diable the process
	disable(ps);
    
    //check if the lockDescriptor is bad
    if(isbadlock(lockDescriptor)){
        restroe(ps);
        return SYSERR;
    }
    //check if the lock is in free state, if yes return syserror since there is nothing to be done here
	if (rw_locks[lockDescriptor].lstate==LFREE) {
		restore(ps);
		return SYSERR;
	}
    // now delete the lock, get the pointer to the lock
    // and move the state to free state 
    // move the type to deleted
    // move the priority to -1, since this isn't going to be used anymore

	lockPointer = &rw_locks[lockDescriptor];
	lockPointer->lstate = LFREE;
	lockPointer->ltype = DELETED;
	lockPointer->lprio = -1;

	for (i=0;i<NPROC;i++)
	{
		if (lockPointer->lproc_list[i] == 1)
		{
			lockPointer->lproc_list[i] = 0;
			proctab[i].bm_locks[lockDescriptor] = 0;
		}
	}	
	
	if (nonempty(lockPointer->lqhead)) {
		while( (pid=getfirst(lockPointer->lqhead)) != EMPTY)
		  {
		    proctab[pid].plockret = DELETED;
		    proctab[pid].wait_lockid = -1;	
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	return(OK);
}