#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr);
int Create_Process_Path_List(char argv[1], FILE *fptr_studentsIds);

char path_list[MAX_NUM_OF_STUDENTS][ID_LENGTH+1] = { 0 };
static char path_to_studentIds[MAX_PATH_LEN] = { 0 };
static char path_to_final_grades[MAX_PATH_LEN] = { 0 };


int main(int argc, char *argv[])
{
	FILE *fptr_studentIds = NULL, *fptr_final_grades = NULL;
	if (argc != 2)
	{
		goto num_of_args_error;
	}
	sprintf(path_to_studentIds, "%s//studentIds.txt", argv[1]);
	sprintf(path_to_final_grades, "%s//final_grades.txt", argv[1]);
	fptr_studentIds = fopen(path_to_studentIds, "r");
	fptr_final_grades = fopen(path_to_final_grades, "w");
	if (fptr_studentIds== NULL | fptr_final_grades==NULL )
	{
		printf("Error while opening file. Exiting...");
		exit(FILE_EXIT_CODE);
	}
	int num_of_processes = Create_Process_Path_List(argv[1],fptr_studentIds);
	int grades_calculated_flag = Calculate_Grades(path_list);
	Collect_Grades(fptr_final_grades);
	return 0;
num_of_args_error:
	printf("Not enough arguments passed. Exiting...");
	return(ARG_EXIT_CODE);

}




BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}

int Create_Process_Path_List(char argv[1], FILE *fptr_studentsIds)
{
	int i = 0;
	while (fscanf(fptr_studentsIds, "%s", path_list[i])==1)
		i++;
	return i + 1;			//returns num of proccesses to open
}