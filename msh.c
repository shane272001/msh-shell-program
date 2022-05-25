/*
 * Name: Shane Purdy
 * ID: 1001789955
 */
 
// The MIT License (MIT)
// 
// Copyright (c) 2016 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports ten arguments

int main()
{
    char * command_string = (char*) malloc( MAX_COMMAND_SIZE );
	// Initialize the history array, index, and count
    char *history[15];
    int h_index = 0;
    int h_count = 0;
    // Initialize the number of times the history for the pids and the commands has changed
    int changes = 0;
    // Allocate memory for each index
    for(int i = 0; i < 15; i++)
    {
        history[i] = (char *)malloc(15);
    }
    // Initialize pid index and count
    int pid_i = 0;
    int pid_c = 0;
    // Shell with prompt
    while( 1 )
    {
        // Print out the msh prompt
        printf ("msh> ");
  
        // Read the command from the commandline.  The
        // maximum command that will be read is MAX_COMMAND_SIZE
        // This while command will wait here until the user
        // inputs something since fgets returns NULL when there
        // is no input
        while( !fgets (command_string, MAX_COMMAND_SIZE, stdin) );

        /* Parse input */
        char *token[MAX_NUM_ARGUMENTS];

        int   token_count = 0;                                 
                                                           
        // Pointer to point to the token
        // parsed by strsep
        char *argument_ptr;                                         
                                                           
        char *working_string  = strdup( command_string );                

        // We are going to move the working_string pointer so
        // keep track of its original value so we can deallocate
        // the correct amount at the end
        //char *head_ptr = working_string;

        // Tokenize the input strings with whitespace used as the delimiter
        while ( ( (argument_ptr = strsep(&working_string, WHITESPACE ) ) != NULL) && 
                (token_count<MAX_NUM_ARGUMENTS))
        {
	  	    token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
		    if( strlen( token[token_count] ) == 0 )
            {
                token[token_count] = NULL;
            }
		    token_count++;
		}

        // If nothing was entered, do nothing
        if(token[0] == NULL)
        {
		}
		// Check if exit or quit were entered and leave if so
		else if(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0) 
		{
			exit(0);
		}
		else
		{
			// Initialize the variable used later on for execution
			int exe;
			// Initialize the status
			int status;
			// Put entered command into history
			history[h_index] = token[0];
			// Increment index and count
			h_index++;
			h_count++;
			// Roll back count due to max pid history being 15
			if(h_count > 15)
			{
				h_count = 15;
			}
			// Reset history to 0 if it is greater than 15 values
			if(h_index > 14)
			{
				h_index = 0;
			}
			// Creating a list to hold the pids
			pid_t pidlist[15];
			// Fork the process
			pid_t pid = fork();
			// Place forked pid into pidlist
			pidlist[pid_i] = pid;
			// Increment pid index and count
			pid_i++;
			pid_c++;
			// Roll back pid count if above max PID - 15
			if(pid_c > 15)
			{
				pid_c = 15;
			}
			// Reset pid index if over maximum pids
			if(pid_i > 14)
			{
				pid_i = 0;
			}
			// Check if the first character entered was "!" and if the length is either 2 or 3
			if(token[0][0] == '!')
			{
				// Checks each possible !# value and changes the entered command to the value in history
				if(strcmp(token[0], "!0") == 0)
				{
					token[0] = history[0];
				}
				else if(strcmp(token[0], "!1") == 0)
				{
					token[0] = history[1];
				}
				else if(strcmp(token[0], "!2") == 0)
				{
					token[0] = history[2];
				}
				else if(strcmp(token[0], "!3") == 0)
				{
					token[0] = history[3];
				}
				else if(strcmp(token[0], "!4") == 0)
				{
					token[0] = history[4];
				}
				else if(strcmp(token[0], "!5") == 0)
				{
					token[0] = history[5];
				}
				else if(strcmp(token[0], "!6") == 0)
				{
					token[0] = history[6];
				}
				else if(strcmp(token[0], "!7") == 0)
				{
					token[0] = history[7];
				}
				else if(strcmp(token[0], "!8") == 0)
				{
					token[0] = history[8];
				}
				else if(strcmp(token[0], "!9") == 0)
				{
					token[0] = history[9];
				}
				else if(strcmp(token[0], "!10") == 0)
				{
					token[0] = history[10];
				}
				else if(strcmp(token[0], "!11") == 0)
				{
					token[0] = history[11];
				}
				else if(strcmp(token[0], "!12") == 0)
				{
					token[0] = history[12];
				}
				else if(strcmp(token[0], "!13") == 0)
				{
					token[0] = history[13];
				}
				else if(strcmp(token[0], "!14") == 0)
				{
					token[0] = history[14];
				}
				else
				{
					printf("Command not in history.");
				}
			}
			// This is the child Process
			if(pid == 0)
			{
				// Exec is called to execute the command
				exe = execvp(token[0], &token[0]);
				// Checks if it executed correctly, and if it didn't, then it moves into the if statement
				if(exe == -1)
				{
					// Checks if the input command is valid or not with the commands from this program
					if(((token[0][0] != '!') != 0) && (strcmp(token[0], "cd") != 0) && 
					(strcmp(token[0], "pidhistory") != 0) && (strcmp(token[0], "history")))
					{
						// Output if the command isn't valid
						printf("%s: Command not found.\n", token[0]);
					}
				}
				break;
			}
			else
			{
				wait(&status);
			}
			// This is the parent process
			if(pid != 0)
			{
				// Checks the entered command for cd
				if(strcmp(token[0], "cd") == 0)
				{
					// Changes the directory based on the second entered argument
					chdir(token[1]);
				}
			}
			// If the user enters "history," then output the history of commands
			if(strcmp(token[0], "history") == 0)
			{
				// Print history up til 15 history, or the amount entered
				// if there are less than 15 commands having been entered
				for(int i = 0; i < h_count; i++)
				{
					printf("%d.  %s\n", i, history[i]);
				}
				changes++;
			}
			// If the user enters "pidhistory," then output pid list
			if(strcmp(token[0], "pidhistory") == 0)
			{
				// Print pids up til 15 pids, or the amount entered if there are less
				// than 15 pids
				for(int i = 0; i < pid_c; i++)
				{
					printf("%d.  %d\n", i + 1, pidlist[i]);
				}
				changes++;
			}
		}
    }
    // Free memory for history
	for(int i = 0; i < 15; i++)
	{
		free(history[i]);
	}
    return 0;
    // e2520ca2-76f3-11ec-90d6-0242ac120003
}
