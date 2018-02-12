/* process.h - isbadpid */

/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		8
#endif		

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

#define	PNMLEN		16	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

/* Process initialization constants */

#define	INITSTK		65536	/* Initial process stack size		*/
#define	INITPRIO	20	/* Initial process priority		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= NPROC) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */

struct procent {			/* Entry in the process table			*/
	uint16	prstate;		/* Process state: PR_CURR, etc.			*/
	pri16	prprio;			/* Process priority				*/
	char	*prstkptr;		/* Saved stack pointer				*/
	char	*prstkbase;		/* Base of run time stack			*/
	uint32	prstklen;		/* Stack length in bytes			*/
	char	prname[PNMLEN];		/* Process name					*/
	sid32	prsem;			/* Semaphore on which process waits		*/
	pid32	prparent;		/* ID of the creating process			*/
	umsg32	prmsg;			/* Message sent to this process			*/
	bool8	prhasmsg;		/* Nonzero iff msg is valid			*/
	int16	prdesc[NDESC];		/* Device descriptors for process		*/
long int	prtime;			/* Record the time in milliseconds on creation	*/
	volatile long int  wait,kill,ready,receive,suspend,recvtime,create,sleep,resched;
	volatile long int wait_time,kill_time,ready_time,receive_time,suspend_time,recvtime_time,create_time,sleep_time,resched_time;
	volatile uint32 	runtime_remaining;	/* Record the runtime remaining for STCF policy */
	bool8	burst_done;	/* Non zero if process is no longer running	*/
	bool8	is_userproc;		/* Non zero if it is a user process		*/
	uint32 number_bursts, burst_duration,sleep_duration;
	uint16 ta,qnum;

//	struct syscall_list* call_ptr 	/* Pointer to array of system call		*/
};

/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/
