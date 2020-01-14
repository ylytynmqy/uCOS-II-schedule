/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 1998-2004, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
*                                            WIN32 Sample Code
*
* File : APP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                                CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE    128

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[4][TASK_STK_SIZE];//stack

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  Task1(void *p_arg);
static  void  Task2(void *p_arg);
static  void  Task3(void *p_arg);


/*
*********************************************************************************************************
*                                                _tmain()
*
* Description : This is the standard entry point for C++ WIN32 code.  
* Arguments   : none
*********************************************************************************************************
*/

void main(int argc, char *argv[])
{

    OSInit();                              /* Initialize "uC/OS-II, The Real-Time Kernel"                                      */
    OSTaskCreate(Task1,
                    (void *)0,
                    (OS_STK *)&TaskStk[0][TASK_STK_SIZE-1],
                    1);//priority
	OSTaskCreate(Task2,
		(void *)0,
		(OS_STK *)&TaskStk[1][TASK_STK_SIZE - 1],
		2);//priority 越小越高
	OSTaskCreate(Task3,
		(void *)0,
		(OS_STK *)&TaskStk[2][TASK_STK_SIZE - 1],
		3);//priority 越小越高
    OSStart();                             /* Start multitasking (i.e. give control to uC/OS-II)                               */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

void  Task1 ()
{
	int start;
	int end;
	int c = 1;
	int p = 4;
	int toDelay;
	while(TRUE) { 
		start = OSTimeGet();
		while(OSTCBCur->OSTCBDly>0){}
		end = OSTimeGet(); // end time 
		toDelay=p-(end-start) ; 
		start=start+p ; // next start time 
		OSTCBCur->OSTCBDly=c ; // reset the counter (c ticks for computation) 
		OSTimeDly (toDelay); // delay and wait (T-C) times
	}
}

void  Task2()
{
	int start;
	int end;
	int c = 2;
	int p = 6;
	int toDelay;
	while (TRUE) {
		start = OSTimeGet();
		while (OSTCBCur->OSTCBDly > 0) {}
		end = OSTimeGet(); // end time 
		toDelay = p - (end - start);
		start = start + p; // next start time 
		OSTCBCur->OSTCBDly = c; // reset the counter (c ticks for computation) 
		OSTimeDly(toDelay); // delay and wait (T-C) times
	}
}


void  Task3()
{
	int start;
	int end;
	int c = 3;
	int p = 12;
	int toDelay;
	while (TRUE) {
		start = OSTimeGet();
		while (OSTCBCur->OSTCBDly > 0) {}
		end = OSTimeGet(); // end time 
		toDelay = p - (end - start);
		start = start + p; // next start time 
		OSTCBCur->OSTCBDly = c; // reset the counter (c ticks for computation) 
		OSTimeDly(toDelay); // delay and wait (T-C) times
	}
}