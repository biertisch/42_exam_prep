#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void alarm_handler(int sig)
{
	(void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	//pointer check
	if (!f)
		return (0);

	//fork
	pid_t pid = fork();
	if (pid == -1)
		return (-1);

	//child
	if (pid == 0)
	{
		//set alarm
		alarm(timeout);
		//run function
		f();
		exit(0);
	}

	//parent
	//set alarm handler
	struct sigaction sa;
	sa.sa_handler = alarm_handler;
	if (sigemptyset(&sa.sa_mask))
	{
		kill(pid, SIGKILL);
		waitpid(pid, NULL, 0);
		return (-1);
	}
	sa.sa_flags = 0;
	if (sigaction(SIGALRM, &sa, NULL))
	{
		kill(pid, SIGKILL);
		waitpid(pid, NULL, 0);
		return (-1);
	}

	//set alarm
	alarm(timeout);

	//wait for child
	int status;
	if (waitpid(pid, &status, 0))
	{
		kill(pid, SIGKILL);
		waitpid(pid, &status, 0);
		//if interrupted by alarm, f timed out
		if (errno == EINTR)
		{
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);
		}
		return (-1);
	};

	//remove alarm
	alarm(0);

	//inspect if f exited normally
	int res;
	if (WIFEXITED(status))
	{
		res = WEXITSTATUS(status);
		if (res != 0)
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", res);
			return (0);
		}
		if (verbose)
			printf("Nice function!\n");
		return (1);
	}

	//inspect if f exited with a signal
	if (WIFSIGNALED(status))
	{
		res = WTERMSIG(status);
		if (res == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
		}
		else if (verbose)
			printf("Bad function: %s\n", strsignal(res));
		return (0);
	}

	return (-1);
}
