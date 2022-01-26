/*
Ana Sofia Baide
UID: 118441368
Grace: abaide
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"

/*
This function initializes a Calendar struct based on the parameters.
It allocates memory for the parameters.
*/
int init_calendar(const char *name, int days,
                  int (*comp_func)(const void *ptr1, const void *ptr2),
                  void (*free_info_func)(void *ptr), Calendar **calendar)
{
  /*Checks for null pointers*/
  if (calendar == NULL || name == NULL)
  {
    return FAILURE;
  }

  /*Checks that days is valid*/
  if (days < 1)
  {
    return FAILURE;
  }

  /*Allocates memory for calendar*/
  (*calendar) = malloc(sizeof(Calendar));
  if (calendar)
  {
    /*Allocates memory for name and events*/
    (*calendar)->name = malloc(strlen(name) + 1);
    (*calendar)->events = calloc(days, sizeof(Event *));

    /*Check if allocation done correctly*/
    if ((*calendar)->name && (*calendar)->events)
    {
      /*Add information*/
      strcpy((*calendar)->name, name);
      (*calendar)->days = days;
      (*calendar)->total_events = 0;

      (*calendar)->comp_func = comp_func;
      (*calendar)->free_info_func = free_info_func;

      return SUCCESS;
    }
  }
  return FAILURE;
}

/*
This function prints, to the designated output stream, the calendar’s name,
days, and total number of events if print all is true; otherwise this
information is not printed. Information about each event (name, start time,
and duration) is printed regardless of the value of print all.
*/
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all)
{
  Event *current;
  int i;

  /*Check for null pointers*/
  if (calendar == NULL || output_stream == NULL)
  {
    return FAILURE;
  }

  /*Print info*/
  if (print_all)
  {
    fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
    fprintf(output_stream, "Days: %d\n", calendar->days);
    fprintf(output_stream, "Total Events: %d\n\n", calendar->total_events);
  }

  /*header*/
  fprintf(output_stream, "**** Events ****\n");

  /*Print if events exist*/
  if (calendar->total_events > 0)
  {
    for (i = 0; i < calendar->days; i++)
    {
      /*Prints day*/
      fprintf(output_stream, "Day %d\n", i + 1);

      /*Gets info*/
      current = calendar->events[i];
      while (current)
      {
        fprintf(output_stream,
                "Event's Name: \"%s\", Start_time: %d, Duration: %d\n",
                current->name, current->start_time, current->duration_minutes);
        current = current->next;
      }
    }
  }
  return SUCCESS;
}

/*
This function adds the specified event to the event list associated with
parameter day, ensuring that the resulting event list is in increasing sorted
order according to the comparison function (field comp func).
*/
int add_event(Calendar *calendar, const char *name, int start_time,
              int duration_minutes, void *info, int day)
{
  /*Event pointers needed*/
  Event *current, *previous = NULL, *new_item, *event;

  /*Check for null pointers*/
  if (calendar == NULL || name == NULL)
  {
    return FAILURE;
  }

  /*Check for valid start time*/
  if (start_time < 0 || start_time > 2400 || duration_minutes <= 0)
  {
    return FAILURE;
  }

  /*Check for valid days*/
  if (day < 1 || day > calendar->days)
  {
    return FAILURE;
  }

  /*Sees if event exists*/
  if (find_event(calendar, name, &event) == SUCCESS)
  {
    return FAILURE;
  }

  if (calendar->comp_func == NULL)
  {
    return FAILURE;
  }

  /*Allocates space*/
  new_item = malloc(sizeof(Event));
  if (new_item == NULL)
  {
    return FAILURE;
  }

  new_item->name = malloc(strlen(name) + 1);
  if (new_item->name == NULL)
  {
    return FAILURE;
  }

  /*Inputs the data*/
  strcpy(new_item->name, name);
  new_item->start_time = start_time;
  new_item->duration_minutes = duration_minutes;
  new_item->info = info;
  new_item->next = NULL;
  /*Points at current data*/
  current = calendar->events[day - 1];

  /*Add it in the head*/
  if (current == NULL)
  {
    calendar->events[day - 1] = new_item;
  }
  else
  {
    /*Loop through the items*/
    while (current != NULL && calendar->comp_func(current, new_item) < 0)
    {
      previous = current;
      current = current->next;
    }

    /*Move to the next item*/
    new_item->next = current;

    if (previous == NULL)
    {
      calendar->events[day - 1] = new_item;
    }
    else
    {
      previous->next = new_item;
    }
  }
  /*Increase the amount of events*/
  (calendar->total_events)++;
  return SUCCESS;
}

/*
This function returns SUCCESS if calendar has an event with the specified name.
In this case, it returns a pointer to that event via parameter event if the
parameter is not NULL (no pointer is returned if parameter event is NULL).
*/
int find_event(Calendar *calendar, const char *name, Event **event)
{
  Event *current;
  int i;

  /*Check for null pointer*/
  if (calendar == NULL || name == NULL || event == NULL)
  {
    return FAILURE;
  }

  /*Go through all of the days*/
  for (i = 0; i < calendar->days; i++)
  {
    /*Compares string until found*/
    current = calendar->events[i];
    while (current && strcmp(current->name, name))
    {
      current = current->next;
    }

    if (current)
    {
      *event = current;
      return SUCCESS;
    }
  }
  return FAILURE;
}

/*
This function returns SUCCESS if calendar has an event with the specified name
in the specified day. In this case, it returns a pointer to that event via
parameter event iff the parameter is not NULL.
*/
int find_event_in_day(Calendar *calendar, const char *name, int day,
                      Event **event)
{
  Event *current;
  /*Check for a null pointer*/
  if (calendar == NULL || name == NULL || event == NULL)
  {
    return FAILURE;
  }

  /*Check if days is valid*/
  if (day < 1 || day > calendar->days)
  {
    return FAILURE;
  }

  /*Set the current*/
  current = calendar->events[day - 1];
  while (current != NULL)
  {
    /*Compare names*/
    if (!strcmp(current->name, name))
    {
      *event = calendar->events[day - 1];
      return SUCCESS;
    }
    /*Go to the next one*/
    current = current->next;
  }
  return FAILURE;
}


/*
This function returns SUCCESS if the calendar has the specified event. In this
case, it removes the event from the calendar, updates the number of events,
and frees any memory allocated for the event. It calls the free info func on
the event’s info field iff both of these are non-NULL.
*/
int remove_event(Calendar *calendar, const char *name)
{
  Event *current, *previous = NULL, *event;
  int i;

  /*Check if they are null*/
  if (calendar == NULL && name == NULL)
  {
    return FAILURE;
  }

  /*If event doesnt exist*/
  if(find_event(calendar, name, &event)){
    return FAILURE;
  }

  /*Iterate through days*/
  for (i = 0; i < calendar->days; i++)
  {
    current = calendar->events[i];
    if (current != NULL && !strcmp( current->name, name))
    {
      calendar->events[i] = current->next;
      free(current->name);

      if (current->info && calendar->free_info_func)
      {
        calendar->free_info_func(current->info);
      }
      free(current);
      calendar->total_events--;
      return SUCCESS;
    }

    while (current != NULL && strcmp(current->name, name))
    {
      previous = current;
      current = current->next;
    }

    if (current == NULL)
    {
      return FAILURE;
    }

    previous->next = current->next;

    free(current->name);

    if (current->info && calendar->free_info_func)
    {
      calendar->free_info_func(current->info);
    }
    free(current);
    calendar->total_events--;
    return SUCCESS;
  }
  return FAILURE;
}

/*
This function returns the info pointer associated with the specified event.
The function returns NULL if the event is not found. Assume the calendar and
name parameters are not NULL.
*/
void *get_event_info(Calendar *calendar, const char *name)
{
  Event *event;

  /*Find the event*/
  if(find_event(calendar, name, &event) == SUCCESS){
    return event->info;
  }
  return NULL;
}

/*
It removes every event (processing the event as described in function remove
event) and sets every event list to empty. The array of pointers
to event lists is not removed.
*/
int clear_calendar(Calendar *calendar)
{
  int i;
  if (calendar == NULL)
  {
    return FAILURE;
  }

  for (i = 0; i < calendar->days; i++)
  {
    clear_day(calendar, i + 1);
  }
  return SUCCESS;
}

/*
It removes all the events for the specified day (processing each event as
described in function remove event), sets the day’s event list to empty, and
returns SUCCESS.
*/
int clear_day(Calendar *calendar, int day)
{
  Event *current, *previous;

  /*Check for null pointers*/
  if (calendar == NULL)
  {
    return FAILURE;
  }

  /*Check if day is correct*/
  if (day < 1 || day > calendar->days)
  {
    return FAILURE;
  }

  /*Check if total of events greater than 0*/
  if (calendar->total_events > 0)
  {
    current = calendar->events[day - 1];

    /*If current node not null*/
    while (current)
    {
      previous = current;
      current = current->next;

      /*Free*/
      free(previous->name);

      /*Check if free function is available to free info*/
      if (calendar->free_info_func && previous->info)
      {
        calendar->free_info_func(previous->info);
      }

      free(previous);

      /*Decreases number of events and sets events to null*/
      (calendar->total_events)--;
    }
    calendar->events[day - 1] = NULL;
    return SUCCESS;
  }
  return FAILURE;
}

/*
it removes every event (processing the event as described in function remove
event), frees all memory that was dynamically allocated for the calendar, and
returns SUCCESS.
*/
int destroy_calendar(Calendar *calendar)
{

  if (calendar == NULL)
  {
    return FAILURE;
  }

  free(calendar->name);
  clear_calendar(calendar);
  free(calendar->events);
  free(calendar);
  return SUCCESS;
}

/*
Ana Sofia Baide
UID: 118441368
Grace: abaide
*/
