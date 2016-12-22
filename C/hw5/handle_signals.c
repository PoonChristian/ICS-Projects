#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int interrupt_count = 0;
int stop_count = 0;
int quit_count = 0;

void print_counts()
{
	printf("\n");
	printf("Interrupt: %d\n", interrupt_count);
	printf("Stop: %d\n", stop_count);
	printf("Quit: %d\n", quit_count);
}

void interrupt_sig_handler(int signum)
{
	interrupt_count++;
	printf("\nI\n");
	fflush(stdout);
	signal(SIGINT, interrupt_sig_handler);
}

void quit_sig_handler(int signum)
{
	quit_count++;
	printf("\nQ\n");
	fflush(stdout);
	signal(SIGQUIT, quit_sig_handler);
}

void terminal_stop_sig_handler(int signum)
{
	stop_count++;
	if (stop_count == 3)
	{
		print_counts();
		exit(0);
	}
	else
	{
		printf("\nS\n");
		fflush(stdout);
		raise(SIGSTOP);
		signal(SIGTSTP, terminal_stop_sig_handler);
	}
}

void init_signal_handlers()
{
	signal(SIGINT, interrupt_sig_handler);
	signal(SIGQUIT, quit_sig_handler);
	signal(SIGTSTP, terminal_stop_sig_handler);
}

int main()
{
	init_signal_handlers();
	printf("");
	while (1)
	{
		printf("X\n");
		fflush(stdout);
	}
}
