#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_utils.h"
#include <unistd.h>

//defining the prototypes here 
void cmd_type(char **args);
void cmd_echo(char **args);
void cmd_exit(char **args);

// struct to defin the how the command should look like 
typedef struct Command{
    char *name;
    void (*func)(char **args);
}  Command_t;


void sanitizeCommand(char *string){
 string[strcspn(string,"\n")]='\0';
}
//Commands 
void cmd_exit(char **args){
    exit(0);
}

void cmd_echo(char **args){
    
    int i=1;
    while(args[i]!=NULL){
        printf("%s",args[i]);
        printf(" ");
        i++;
    }
    printf("\n");
    
}


Command_t commands[]={
    {"echo",cmd_echo},
    {"exit",cmd_exit},
    {"type",cmd_type}
};

void cmd_type(char **args){
    if(args[1]==NULL){
        return;
    }
    int found=0;
    int num_commands=(sizeof(commands)/sizeof(commands[0]));
    for(int i=0;i<num_commands;i++){
        if(strcmp(args[1],commands[i].name)==0){
            printf("%s is a shell builtin\n",args[1]);
            found=1;
            return;
        }
    }
    //we search for the path here to see if it is the executable
    char *env=getenv("PATH");
    //created a local copy to tokenize
    char *dirP=duplicateString(env);
    char *token=strtok(dirP,":");
    while(token!=NULL){
        int length=strlen(token)+strlen(args[1])+2;
        char *full_path=malloc(length);
        strcpy(full_path,token);
        strcat(full_path,"/");
        strcat(full_path,args[1]);

        //check if executable
        if(access(full_path,X_OK)==0){
          printf("%s is %s\n",args[1],full_path);  
          found=1;
          free(full_path);
          break;
        }
        token=strtok(NULL,":");

    free(full_path);
    }

    

    if(!found){
        printf("%s : not found\n",args[1]);
    }
    free(dirP);
}




int main(int argc, char *argv[]) {
    // Flush after every printf
    setbuf(stdout, NULL);
    // to store the command 
    char command[100];
    
    while(1){
        printf("$ ");
        fgets(command,sizeof(command),stdin);
        sanitizeCommand(command);
        //slpit the command
        char *args[10];
        int i=0;
        char *token=strtok(command," ");
        while(token!=NULL){
            args[i]=token;
            i++;
            token=strtok(NULL," ");

    }
   args[i]=NULL;
    //temp array 

   //handle blank enter 
   if(args[0]==NULL)
  {
    continue;
  }
  //executions of commands
  int found=1;
  for(int i=0;i<3;i++){
    if(strcmp(args[0],commands[i].name)==0){
      commands[i].func(args);
      found=0;
      break;
    }
  }
   if(found!=0){
      printf("{%s} : Command not found\n",args[0]);
    }

  }
  


  return 0;
}


