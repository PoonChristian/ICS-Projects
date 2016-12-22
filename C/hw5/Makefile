all: handle_signals my_shell
handle_signals: handle_signals.o
	gcc handle_signals.o -o handle_signals
handle_signals.o: handle_signals.c
	gcc -c handle_signals.c
my_shell: my_shell.o
	gcc my_shell.o -o my_shell
my_shell.o: my_shell.c
	gcc -c -std=c99 my_shell.c
