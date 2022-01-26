#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2)
{
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

typedef struct task_info
{
   double cost;
   char *prog_language;
} Task_info;

static Task_info *create_task_info(double cost, const char *prog_language)
{
   Task_info *task_info = malloc(sizeof(Task_info));

   if (task_info)
   {
      task_info->prog_language = malloc(strlen(prog_language) + 1);
      if (task_info->prog_language)
      {
         task_info->cost = cost;
         strcpy(task_info->prog_language, prog_language);
         return task_info;
      }
   }

   return NULL;
}

static void free_task_info(void *ptr)
{
   Task_info *task_info = (Task_info *)ptr;

   free(task_info->prog_language);
   free(task_info);
}

/*
Tests for:
   init_calendar
   print_calendat
   destroy_calendar
*/
static int test1()
{
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Test Calendar 1", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (print_calendar(calendar, stdout, 1) == SUCCESS)
      {
         return destroy_calendar(calendar);
      }
   }

   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event (add two events with the same name)
*/
static int test2()
{
   int days = 5;
   Calendar *calendar;

   if (init_calendar("Test Calendar 2", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS)
      {
         if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == FAILURE &&
             add_event(calendar, "CMSC216", 300, 50, NULL, 5) == FAILURE)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Test for:
   init_calendar
   print_calendar
   add_event
   find_event
*/
static int test3()
{
   int days = 5;
   Calendar *calendar;
   Event *event;

   if (init_calendar("Test Calendar 3", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         if (find_event(calendar, "CMSC216", &event) == SUCCESS &&
             find_event(calendar, "MATH216", &event) == FAILURE)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event
   find_event_in_day
*/

static int test4()
{
   int days = 5;
   Calendar *calendar;
   Event *event;

   if (init_calendar("Test Calendar 4", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         if (find_event_in_day(calendar, "CMSC216", 1, &event) == SUCCESS &&
             find_event_in_day(calendar, "CMSC216", 2, &event) == FAILURE)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event 
   remove_event
*/
static int test5()
{
   int days = 5;
   Calendar *calendar;

   if (init_calendar("Test Calendar 5", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS)
      {
         if (remove_event(calendar, "CMSC216") == SUCCESS)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event
   get_event_info (test if returns even info)
*/
static int test6()
{
   int days = 5;
   Calendar *calendar;
   Task_info *info, *info1;

   if (init_calendar("Test Calendar 6", days, comp_minutes, free_task_info, &calendar) == SUCCESS)
   {
      info = create_task_info(35000, "Java");
      if (add_event(calendar, "CMSC216", 300, 50, info, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 2) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         info1 = get_event_info(calendar, "CMSC216");
         if (info1)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event
   get_event_info (returns NULL)
*/

static int test7()
{
   int days = 5;
   Calendar *calendar;
   Task_info *info;

   if (init_calendar("Test Calendar 7", days, comp_minutes, free_task_info, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         info = get_event_info(calendar, "CMSC216");
         if (!info)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

/*
Tests for:
   init_calendar
   print_calendar
   clear_day
   destroy_calendar
*/
static int test8()
{
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Test Calendar 8", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 2) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         if (clear_day(calendar, 1) == SUCCESS)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }

   return FAILURE;
}

/*
Test for:
   init_calendar
   add_event (add events when comp_func is Null)
*/
static int test9()
{
   int days = 5;
   Calendar *calendar;

   if (init_calendar("Test Calendar 9", days, NULL, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == FAILURE)
      {
         if (print_calendar(calendar, stdout, 1) == SUCCESS)
         {
            return destroy_calendar(calendar);
         }
      }
   }
   return FAILURE;
}

/*
Tests for:
   init_calendar
   print_calendar
   clear_day
   destroy_calendar
*/
static int test10()
{
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Test Calendar 10", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "MATH241", 500, 50, NULL, 2) == SUCCESS &&
          add_event(calendar, "CMSC250", 400, 50, NULL, 2) == FAILURE)
      {
         if (clear_calendar(calendar) == SUCCESS)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }

   return FAILURE;
}

/*
Test for:
   init_calendar
   add_events with the same comp value so that the most recent one is added 
   before
*/
static int test11()
{
   int days = 5;
   Calendar *calendar;

   if (init_calendar("Test Calendar 10", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS &&
          add_event(calendar, "CMSC250", 300, 50, NULL, 1) == SUCCESS)
      {
         if (print_calendar(calendar, stdout, 1) == SUCCESS)
         {
            return destroy_calendar(calendar);
         }
      }
   }
   return FAILURE;
}


/*
Test for:
   init_calendar
   add_event 
   remove_event that is already removed
*/
static int test12()
{
   int days = 5;
   Calendar *calendar;

   if (init_calendar("Test Calendar 12", days, comp_minutes, NULL, &calendar) == SUCCESS)
   {
      if (add_event(calendar, "CMSC216", 300, 50, NULL, 1) == SUCCESS)
      {
         if (remove_event(calendar, "CMSC216") == SUCCESS &&
            remove_event(calendar, "CMSC216") == FAILURE)
         {
            if (print_calendar(calendar, stdout, 1) == SUCCESS)
            {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}


int main()
{
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE)
      result = FAILURE;
   if (test2() == FAILURE)
      result = FAILURE;
   if (test3() == FAILURE)
      result = FAILURE;
   if (test4() == FAILURE)
      result = FAILURE;
   if (test5() == FAILURE)
      result = FAILURE;
   if (test6() == FAILURE)
      result = FAILURE;
   if (test7() == FAILURE)
      result = FAILURE;
   if (test8() == FAILURE)
      result = FAILURE;
   if (test9() == FAILURE)
      result = FAILURE;
   if (test10() == FAILURE)
      result = FAILURE;
   if (test11() == FAILURE)
      result = FAILURE;
   if (test12() == FAILURE)
      result = FAILURE;

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/

   if (result == FAILURE)
   {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
