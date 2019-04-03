#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
int main()
{
	printf("Divesh Basina,Natalie Bui, Alexia Camino-Wanca\n");

	printf("Input UserName for processes information\n");
	char username[10];
	scanf("%s",username);
	printf("Given username: %s\n ",username);

	struct passwd pwd =*getpwnam(username);
	int UserID = pwd.pw_uid;
	int index = 0;
	int count = 0;
	int pid = 0;
	int prio = 0;
	char comm[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char policy[] = "qwe";
	long int ret_status = syscall(398,UserID,&count,index,&pid,&comm,&prio,&policy);
	if(ret_status==0)
	{
		printf("System call executed correctly. Use dmesg to check the syscall output.\n");
		printf("Number of UserProcesses: %d\n",count);
	}

	else
	{
		printf("System call did not execute as expected\n");
	}
	int iter = count;
	for(int i = 0; i<iter; i++)
	{
		long int policyValue = syscall(398,UserID,&count,i,&pid,&comm,&prio,&policy);
		prio = -(prio-139);
		if(policyValue==0)
        	{
			printf("PID: %d\t\t COMM: %s\t\t PRIO: %d\t\t CLS: TS\n",pid,comm,prio);
        	}

		if(policyValue==1)
                {
                        printf("PID: %d\t\t COMM: %s\t\t PRIO: %d\t\t CLS: FF\n",pid,comm,prio);
                }

		if(policyValue==2)
                {
                        printf("PID: %d\t\t COMM: %s\t\t PRIO: %d\t\t CLS: RR\n",pid,comm,prio);
                }

		if(policyValue==3)
                {
                        printf("PID: %d\t\t COMM: %s\t\t PRIO: %d\t\t CLS: B\n",pid,comm,prio);
                }

	}

	return 0;
}
