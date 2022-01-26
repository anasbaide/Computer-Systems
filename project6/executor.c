/*
Name: Ana Sofia Baide
UID: 118441368
Grace: abaide
*/

#include <stdio.h>
#include "executor.h"
#include "command.h"
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h>
#include <sysexits.h>


/*recursive function prototype*/
static int execute_rec(struct tree *t, int in_fd, int out_fd);

/*Function call*/
int execute(struct tree *t)
{
  return execute_rec(t, -1, -1);
  return 0;
}

/*Recursive function that is call in execute*/
static int execute_rec(struct tree *t, int in_fd, int out_fd)
{
  pid_t pid_one, pid_three;
  int close_check, dup2_check;
  int status, check_rec;

  /*For no conjunction*/
  if (t->conjunction == NONE)
  {
    /*Exit program*/
    if (!strcmp(t->argv[0], "exit"))
    {
      exit(0);
    }

    /*change directory*/
    else if (!strcmp(t->argv[0], "cd"))
    {
      if (t->argv[1])
      {
        chdir(t->argv[1]);
      }
      else
      {
        chdir(getenv("HOME"));
      }
    }
    /*running*/
    else
    {
      /*check the fork*/
      pid_one = fork();
      if (pid_one < 0)
      {
        err(EX_OSERR, "Fork error\n");
      }
      else if (!pid_one)
      {
        /*input redirection*/
        if (t->input)
        {
          in_fd = open(t->input, O_RDONLY);
          if (in_fd < 0)
          {
            err(EX_OSERR, "Input error\n");
          }
          dup2_check = dup2(in_fd, STDIN_FILENO);
          if (dup2_check < 0)
          {
            err(EX_OSERR, "dup2 error\n");
          }

          close_check = close(in_fd);
          if (close_check < 0)
          {
            err(EX_OSERR, "Close error\n");
          }
        }
        /*output redirection*/
        if (t->output)
        {
          out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664);
          if (out_fd < 0)
          {
            err(EX_OSERR, "Opening error\n");
          }
          dup2_check = dup2(out_fd, STDIN_FILENO);
          if (dup2_check < 0)
          {
            err(EX_OSERR, "dup2 error\n");
          }

          close_check = close(out_fd);
          if (close_check < 0)
          {
            err(EX_OSERR, "Close error\n");
          }
        }
        execvp(t->argv[0], t->argv);
        fprintf(stderr, "Failed to execute %s\n", t->argv[0]);
        exit(-1);
      }
      else
      {
        wait(&status);
        return status;
      }
    }
  }
  /*in case of an AND*/
  else if (t->conjunction == AND)
  {
    check_rec = execute_rec(t->left, in_fd, out_fd);
    if (!check_rec)
    {
      execute_rec(t->right, in_fd, out_fd);
    }
  }
  /*in case of a pipe*/
  else if (t->conjunction == PIPE)
  {
    int pipe_fd[2];
   /*check for ambigious redirect*/
    if (t->left->output)
    {
      printf("Ambiguous output redirect.\n");
    }
    else
    {
      if (t->right->input)
      {
        printf("Ambiguous input redirect.\n");
      }
      else
      {
        if (t->input)
        {
          in_fd = open(t->input, O_RDONLY);
          if (in_fd < 0)
          {
            err(EX_OSERR, "Input error\n");
          }
        }
        if (t->output)
        {
          out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664);
          if (out_fd < 0)
          {
            err(EX_OSERR, "Output error\n");
          }
        }
        if (pipe(pipe_fd) < 0)
        {
          err(EX_OSERR, "Pipe error");
        }
        pid_one = fork();
        if (pid_one < 0)
        {
          err(EX_OSERR, "Fork error");
        }
        if (!pid_one)
        {
          close(pipe_fd[0]);
          if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
          {
            err(EX_OSERR, "dup2 error");
          }
          execute_rec(t->left, in_fd, pipe_fd[1]);
          close(pipe_fd[1]);
          exit(0);
        }
        else
        {
          close(pipe_fd[1]);
          if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
          {
            err(EX_OSERR, "dup2 error");
          }
          execute_rec(t->right, pipe_fd[0], out_fd);
          close(pipe_fd[0]);
          wait(NULL);
        }
      }
    }
  }
  else if (t->conjunction == SUBSHELL)
  {
    pid_three = fork();
    if (pid_three < 0)
    {
      err(EX_OSERR, "Fork error");
    }
    else if (!pid_three)
    {
      if (t->input)
      {
        in_fd = open(t->input, O_RDONLY);
        if (in_fd < 0)
        {
          err(EX_OSERR, "Input error\n");
        }
      }
      if (t->output)
      {
        out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        if (out_fd < 0)
        {
          err(EX_OSERR, "Output error\n");
        }
      }
      execute_rec(t->left, in_fd, out_fd);
      exit(0);
    }
    else
    {
      wait(NULL);
    }
  }
  return 0;
}

/*
Name: Ana Sofia Baide
UID: 118441368
Grace: abaide
*/

