#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "linked-list.h"


typedef enum CommandMode {
	BACKGROUND_MODE,
	FOREGROUND_MODE
} CommandMode;

typedef struct Command {
	int argc;
	char** argv;
	char* cmdline;
	CommandMode mode;
} Command;

typedef struct Child {
	pid_t pid;
	char* cmdline;
} Child;

void freeCommand(Command* command) {
	free(command->argv);
	free(command->cmdline);
	free(command);
}

void freeChild(Child* child) {
	free(child->cmdline);
	free(child);
}


/* Create a Command structure from a command line. */
Command* extractCommand(char* cmdline) {
	Command* command = malloc(sizeof(Command));
	command->argc = 0;
	command->argv = NULL;
	command->cmdline = malloc(sizeof(char) * (strlen(cmdline) + 1));
	strcpy(command->cmdline, cmdline);
	
	/* First, let's count the number of parameters. */
	char* token = strtok(cmdline, " ");
	while (token) {
		command->argc++;
		token = strtok(NULL, " ");
	}
	
	/* strtok modified cmdline, so let's restore it. */
	strcpy(cmdline, command->cmdline);
	
	/* Now, extract the parameters. */
	command->argv = malloc(sizeof(char*) * (command->argc + 1));
	command->argv[0] = strtok(cmdline, " ");
	
	for (int i = 1; i < command->argc; i++) {
		command->argv[i] = strtok(NULL, " ");
	}
	
	if (command->argc && strcmp("&", command->argv[command->argc - 1]) == 0) {
		command->argc--;
		command->mode = BACKGROUND_MODE;
	}
	else {
		command->mode = FOREGROUND_MODE;
	}
	
	command->argv[command->argc] = NULL;
	return command;
}

/* Execute a Command. */
void executeCommand(Command* command, LinkedList* bgChildren) {
	if (command->argc != 0) {				/* Only if command not empty, execute it. */
		pid_t childPid = fork();
		
		if (childPid == 0) {
			execvp(command->argv[0], command->argv);
			fprintf(stderr, "Error: %s.\n", strerror(errno));
			exit(errno);
		}
		else if (childPid > 0) {
			if (command->mode == FOREGROUND_MODE) {
				waitpid(childPid, NULL, 0);
			}
			else {
				printf("[%zu]\t%i\n", getLength(bgChildren), childPid);
				Child* child = malloc(sizeof(Child));
				child->pid = childPid;
				child->cmdline = malloc(sizeof(char) * strlen(command->cmdline));
				strcpy(child->cmdline, command->cmdline);
				push(bgChildren, child);
			}
		}
		else {
			fprintf(stderr, "Error when creating child process: %s.\n", strerror(errno));
		}
	}
}

void checkBgExits(LinkedList* bgChildren) {
	pid_t endedChildPid;
	
	do {
		endedChildPid = waitpid(-1, NULL, WNOHANG);
		
		if (endedChildPid > 0) {
			size_t index = 0;
			LinkedList* ll = bgChildren;
			
			while (!isEmpty(ll) && ((Child*) ll->head)->pid != endedChildPid) {
				ll = ll->tail;
				index++;
			}
			
			printf("[%zu]\tDone\t%i\t\t%s\n", index, endedChildPid, ((Child*) ll->head)->cmdline);
			pop(ll);
		}
	} while (endedChildPid > 0);
}


int main() {
	LinkedList* bgChildren = newLinkedList();
	
	while (1) {
		/* Print a prompt, and return a buffer that contains the user command. */
		char* cmdline = readline("mysh $ ");
		
		/* Extract the Command, and execute it. */
		Command* cmd = extractCommand(cmdline);
		unsigned char exitAsked = cmd->argc > 0 && strcmp(cmd->argv[0], "exit") == 0;
		
		if (!exitAsked) {
			executeCommand(cmd, bgChildren);
		}
		
		checkBgExits(bgChildren);
		freeCommand(cmd);
		free(cmdline);
		
		if (exitAsked) {
			break;
		}
	}
	
	LinkedList* ll = bgChildren;
	
	while (!isEmpty(ll)) {
		freeChild((Child*) ll->head);
		ll = ll->tail;
	}
	
	freeLinkedList(bgChildren);
	return EXIT_SUCCESS;
}
