/* pikuShell                         #
#     by mcb3k                       # 
#         v0.3     34.2.2k11         #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//has an issue with commands over 8 chars

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LEN 100
#define true 1

int main()
{
	pid_t pid;
	int status;
	char cmdString[MAX_LEN];
	char *command;
	char *parameters[MAX_LEN];//figure out if better to have  ** or *var[MAX_LEN]
	
	while(true)	
	{
		printf("?> "); //display the prompt.

		fgets(cmdString, sizeof(cmdString)-1, stdin); //get the input from the user
		
	       if (cmdString[0]=='e' && cmdString[1]=='x') // if cmdString is exit, then quit.
		{
		  if (cmdString[2]=='i' && cmdString[3]=='t')
		  return 0;
		}

	       if (cmdString[0]=='q' || cmdString[0]=='Q') //if cmdString is qq, the quit
		 {
		   if (cmdString[1]=='q' || cmdString[1]=='Q')
		     return 0;
		 }

		if (&cmdString[0] == NULL) //if the string returned by fgets is null, error out.
		{
		  printf ("Something has gone wrong. Oops! ");
		  exit(1); 
		}
		
		//parse it, oh yeah!
		command = strtok(cmdString, " \n");
		//printf("This is what strtok produces: %s\n", command);
		
		//now to get those parameters
		int i = 0;
		while ( command != NULL)
		  {
		    parameters[i] = malloc(sizeof(cmdString));
		    strncpy(parameters[i], command, sizeof(command));
		    // printf( "This is what you typed: %s\n", parameters[i]); //Comment this out before submitting...
		    command = strtok ( NULL, "  \n");
		    //printf("printing command variable: %s\n", command);
		    i++;
		  }
		//null terminate the string
		parameters[i]=NULL;

		//now to fork it!
		pid = fork();
		if (pid == 0)//if the child, become the program you always wanted to be!
		{
		 
		  // printf("I AM THE CHILD! I will now execute %s\n", parameters[0]); //for debugging purposes. Maybe create a debug mode?
		  execvp(parameters[0], parameters); //execve is not what we're looking for, execp* something is.
		  printf("There was an error executing your command"); //if this line executes, something went wrong.
		  exit(2); //kill the child
		}
		else if (pid > 0)//if the parent, wait for the child to stop being st00pid
		{
		  waitpid(-1, &status,0);
		}
		else 
		{
		  printf("There was an error creating your requested process.\n");
		  exit(3);
		}
	}
}
		
	
