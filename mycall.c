#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include "mycall.h"
#include <linux/string.h>
struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};

asmlinkage long sys_printProcesses(int UserID, int *count, int index, int *pid, char comm[], int *prio, char policy[])
{
	struct task_struct *task;
        if (*count!=0)
        {
          int j =0;
          for_each_process(task)
                  if (task->cred->uid.val == UserID)
                  {
			  if ( j == index)
                          {
                            *pid = task->pid;
                            strcpy(comm,task->comm);
                            *prio = task->prio;
			    if (task->policy == 0)
			    {
				printk("Policy = TS\n");
				return 0;
			    }
			    
			    if (task->policy ==  1)
			    {
				printk("Policy = FF\n");
				return 1;
			    }
			    if (task->policy == 2)
                            { 
                                printk("Policy = RR\n");
				return 2;
                            }
			    if (task->policy == 3)
			    {
				printk("Policy = B\n");
				return 3;
			    }
                          }
                          j = j+1;
                  }
        }

        else
        {
          int i=0;
          for_each_process(task)
                  if (task->cred->uid.val == UserID)
                  {
			i = i+1;
                  }
          *count =i;
        }

        return 0;//This return value does not correspont to task->policy. It is a dummy return value.
}

