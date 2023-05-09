// C Program to design a shell in Linux
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


// max number of characters supported in a command
#define MAXLIST 128 

#define clear() printf("\033[H\033[J")
int chd_index=-1;

// Function to hanlde SIGINT signal
void sigint_handler(int signal){
  
  fprintf(stdout, "\n");
  fflush(stdout);
  exit(0);
}

// Function to print Current Directory.
void printDir()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s~$ ", cwd);
}

//Functions define 
void cmd_history(char ** args,int index){
    int counter=1;
	for(int i=index;i>=0 && counter<=5;i--){
		printf("%s\n",args[i]);
		counter+=1;
	}
}
void ps_history(int * args){
    int status;
    for(int i=chd_index;i>=0;i--){
		int pid=args[i];
		if(waitpid(pid,&status, WNOHANG)==0){//running
			printf("%d RUNNING\n",args[i]);			

		} 
		else{
			printf("%d STOPPED\n",args[i]);
			//stopped
		}
}
}
void cd(char ** args){
    chdir(args[1]);
} 

// Function where the system command is executed
void execarr(char** parsed,int * args)
{
	// Forking a child
	pid_t pid = fork();
	int bg_chk=0;

	if (pid == -1) {
		printf("\nError in fork..");
		return;
	} else if (pid == 0) {
		// printf("Child process\n");
		// if(strcmp(parsed[0],"&")==0)
		if(*parsed[0]=='&'){
			parsed[0]+=1;
			// Update parsed by removing "&" symbol
			bg_chk=1;
		}
		if(parsed[0]==NULL) printf("Error in execution of command...\n");//handling only & case
		//bg complete
		if(strcmp(parsed[0],"echo")==0){
			if(*parsed[1]=='$'){// environment var printing
				parsed[1]+=1;
				printf("%s\n",getenv(parsed[1]));
				exit(0);
			}
		}
		if(strcmp(parsed[0],"cd")==0){
			chdir(parsed[1]);
			exit(0);
		}
		if (execvp(parsed[0], parsed) < 0) {
			printf("Error in execution of command..\n");
		}
		exit(0);
	} else {
		chd_index+=1;
		args[chd_index]=pid;
		// int status;
		// printf("sleep out\n");
		if(*parsed[0]!='&' && bg_chk==0) {
						// printf("sleep in\n");
						// if(waitpid(pi0d,&status,1)==-1) printf("Error in wait\n");
						wait(NULL);
						}
		return;
	}
}

// Function where the piped system commands is executed
void execarrPiped(char** parsed, char** parsedpipe,int * args,int index)
{
	// 0 is read end, 1 is write end
	int fd[2];
	// pid_t p1, p2;
	int pid_1,pid_2;

	if (pipe(fd) < 0) {
		printf("\nError in Pipe");
		return;
	}
	pid_1 = fork();
	if (pid_1 < 0) {
		printf("\nError in fork");
		return;
	}

	if (pid_1 == 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		
		close(fd[1]);
		//support change directory in piping
		if(strcmp(parsed[0],"cd")==0){
			chdir(parsed[1]);
			exit(0);
		}//
				
		if(strcmp(parsed[0],"cmd_history")==0){
			cmd_history(parsed,index);
			exit(0);
		}//
				
		if(strcmp(parsed[0],"ps_history")==0){
			ps_history(args);
			exit(0);
		}//
		if (execvp(parsed[0], parsed) < 0) {
			
			printf("\nError while executing command 1..");
			 exit(0);}
	} else {
		
		chd_index+=1;// Take pid of child 1
		args[chd_index]=pid_1;
		pid_2 = fork();

		if (pid_2 < 0) {
			printf("\nError in fork");
			 return;}

		if (pid_2 == 0) {
			close(fd[1]);

			dup2(fd[0], STDIN_FILENO);
			 close(fd[0]);
		//support change directory in piping
		if(strcmp(parsedpipe[0],"cd")==0){
		chdir(parsed[1]);
		exit(0);
		} 
		if(strcmp(parsedpipe[0],"cmd_history")==0){
			cmd_history(parsedpipe,index);
			exit(0);
		}//
				
		if(strcmp(parsedpipe[0],"ps_history")==0){
			ps_history(args);
			exit(0);
		}//
			if (execvp(parsedpipe[0], parsedpipe) < 0) {
				
				printf("\n Error while executing command 2..");
				 exit(0);
			}
		} else {
			close(fd[0]);
             close(fd[1]);
			chd_index+=1;
			args[chd_index]=pid_2;
			// int status1,status2;
			// if(waitpid(pid_1,&status1,WNOHANG)==-1) printf("Error in wait\n");
			// if(waitpid(pid_2,&status2,WNOHANG)==-1) printf("Error in wait\n");
            wait(NULL);
			 wait(NULL);
			// printf("PID of Child1 process of pipe: %d",p1);
			// printf("PID of Child2 process of pipe: %d",p2);
            
		}
	}
}



int main()
{   signal(SIGINT, sigint_handler);
	char Str[MAXLIST]; 
	char *p_arr[MAXLIST];
	char* p_arrPiped[MAXLIST];
	char* arr[MAXLIST];
    char* temp[MAXLIST];
    char* temp_e[MAXLIST];
	int chd_arr[10000]; //can take upto 1000 child pid's
	int execFlag = 0;
	int index=-1;
    int flag;
    char text[MAXLIST];
    clear();

	while (1) {
		flag=0;
		// print shell line
		printDir();
        char text[MAXLIST];
		index+=1;
		// take input
        fgets(text,MAXLIST,stdin);
		// if(strlen(text)>=128) {printf("String length exceeded 128 characters\n");
		// continue;}
        text[strlen(text)-1]='\0';
        int n=strlen(text)-1;
        arr[index]=malloc(n*sizeof(char));
        strcpy(arr[index],text);

        temp[0]=strtok(text,"|");
        int i=0;
        while(temp[i]!=NULL)
            temp[++i]=strtok(NULL,"|");

        if(temp[1]!=NULL){//piped intialise
            //flag
            flag=2;
            p_arr[0]=strtok(temp[0]," ");
			i=0;
			while(p_arr[i]!=NULL)
			      p_arr[++i]=strtok(NULL," ");

            p_arrPiped[0]=strtok(temp[1]," ");
            i=0;
            while(p_arrPiped[i]!=NULL)
                p_arrPiped[++i]=strtok(NULL," ");
        
    }
        if(temp[1]==NULL){//Piping is not there chk for env
			temp_e[0]=strtok(temp[0],"=");
			i=0;
			while(temp_e[i]!=NULL)
				temp_e[++i]=strtok(NULL,"=");
			
            // if(p_arr[1]==NULL)

			if(temp_e[1]==NULL){//env is not there
                p_arr[0]=strtok(temp_e[0]," ");
			    i=0;
			    while(p_arr[i]!=NULL)
				    p_arr[++i]=strtok(NULL," ");
            }
            if(temp_e[1]!=NULL) flag=1;
            
		}
        
    if(flag==2) execarrPiped(p_arr,p_arrPiped,chd_arr,index);
	
	else if(flag==1){
        if (setenv(temp_e[0],temp_e[1], 1) != 0) {
        perror("setenv");}

	}
	//chk for background symbol
    else if(strcmp(p_arr[0],"&")==0) {
		execarr(p_arr,chd_arr);//handling commands executed by execvp in background
	}
    else {
        if(strcmp(p_arr[0], "cd") ==0){
			// if(p_arr[1] == NULL){
				// int home = chdir(HOME);
			// }
			// else if(strcmp(p_arr[1], "~") == 0){
				// int home_ = chdir(HOME);
			// }
			// else{
				cd(p_arr); 
			// }
		}
		// else if(strcmp(p_arr[0],"\n")==0) {}
		else if(strcmp(p_arr[0], "cmd_history") ==0){
			cmd_history(arr,index);
		}
		else if(strcmp(p_arr[0], "ps_history") ==0){
			ps_history(chd_arr);
		}
        else execarr(p_arr,chd_arr);}
   
    }

    
	return 0;
}
