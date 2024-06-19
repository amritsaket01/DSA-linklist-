#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# ifndef MAIN_H

typedef struct 
{
    int hours;
    int minutes;
} TIME;

typedef struct FlightPlan
{
    int flight_id;
    TIME departure_time;
    TIME ETA;
    struct FlightPlan* next;
} FlightPlan;

typedef struct Bucket 
{
    int bucket_id;
    TIME start_time;
    TIME end_time;
    FlightPlan* flight_plans;
    struct Bucket* next;
} Bucket;

int timediff(TIME A, TIME B);
int maxtime(TIME A, TIME B) ;
void cancel_flight_plan(Bucket* dashboard, int flight_id) ;
void show_flight_status(Bucket* dashboard, int flight_id);
void show_flight_plans_within_hour(Bucket* dashboard, TIME current_time) ;
Bucket* create_bucket(int bucket_id, TIME start_time, TIME end_time) ;
FlightPlan* create_flight_plan(int flight_id, TIME departure_time, TIME ETA);
void insert_flight_plan(Bucket **dashboard, FlightPlan *newFlightPlan);
void Print(Bucket *bucket);

# endif