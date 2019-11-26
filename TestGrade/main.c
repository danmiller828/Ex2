#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define NUM_OF_THREADS 13
#define WAIT_FOR_ALL   1

static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,LPDWORD p_thread_id);

int main(int argc, char *argv[])
{
	HANDLE p_thread_handles[NUM_OF_THREADS];
	DWORD p_thread_ids[NUM_OF_THREADS];
	Calculate_Grades(p_thread_handles, argv[1]);
	WaitForMultipleObjects(NUM_OF_THREADS,p_thread_handles,WAIT_FOR_ALL,INFINITE);
	return 0;
}

static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,LPDWORD p_thread_id)
{
	HANDLE thread_handle;

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	thread_handle = CreateThread(
		NULL,            /*  default security attributes */
		0,               /*  use default stack size */
		p_start_routine, /*  thread function */
		NULL,            /*  argument to thread function */
		0,               /*  use default creation flags */
		p_thread_id);    /*  returns the thread identifier */

	if (NULL == thread_handle)
	{
		printf("Couldn't create thread\n");
		exit(ERROR_CODE);
	}

	return thread_handle;
}
