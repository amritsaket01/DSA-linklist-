#include "main.h"
int timediff(TIME A, TIME B) 
{
    return (A.hours - B.hours) * 60 + (A.minutes - B.minutes);
}

int maxtime(TIME A, TIME B) 
{
    if (A.hours == B.hours && A.minutes == B.minutes)
        return 0;
    else if (A.hours > B.hours || (A.hours == B.hours && A.minutes > B.minutes))
        return -1;
    else
        return 1;
}

void cancel_flight_plan(Bucket* dashboard, int flight_id) 
{
    Bucket* current_bucket = dashboard;
    while (current_bucket != NULL) 
    {
        FlightPlan* prev = NULL;
        FlightPlan* current = current_bucket->flight_plans;
        while (current != NULL && current->flight_id != flight_id) 
        {
            prev = current;
            current = current->next;
        }

        if (current != NULL) 
        {
            if (prev == NULL) 
            {
                current_bucket->flight_plans = current->next;
            } else 
            {
                prev->next = current->next;
            }
            free(current);
            break;
        }

        current_bucket = current_bucket->next;
    }
}

void show_flight_status(Bucket* dashboard, int flight_id) 
{
    Bucket* current_bucket = dashboard;
    while (current_bucket != NULL) 
    {
        FlightPlan* current = current_bucket->flight_plans;
        while (current != NULL && current->flight_id != flight_id) 
        {
            current = current->next;
        }

        if (current != NULL) 
        {
            printf("Flight ID: %d\n", current->flight_id);
            printf("Departure Time: %d:%d\n", current->departure_time.hours, current->departure_time.minutes);
            printf("ETA: %d:%d\n", current->ETA.hours, current->ETA.minutes);
            return;
        }

        current_bucket = current_bucket->next;
    }

    printf("Flight ID %d not found.\n", flight_id);
}

void show_flight_plans_within_hour(Bucket* dashboard, TIME current_time) 
{
    TIME next_hour = current_time;
    next_hour.minutes = 0;
    next_hour.hours++;

    Bucket* current_bucket = dashboard;
    while (current_bucket != NULL) 
    {
        if (timediff(current_bucket->start_time, current_time) <= 0 &&
            timediff(current_bucket->end_time, next_hour) <= 0) 
            {
            printf("Bucket ID: %d\n", current_bucket->bucket_id);
            FlightPlan* current_flight = current_bucket->flight_plans;
            while (current_flight != NULL) 
            {
                printf("Flight ID: %d\n", current_flight->flight_id);
                printf("Departure Time: %d:%d\n", current_flight->departure_time.hours, current_flight->departure_time.minutes);
                printf("ETA: %d:%d\n", current_flight->ETA.hours, current_flight->ETA.minutes);
                current_flight = current_flight->next;
            }
        }
        current_bucket = current_bucket->next;
    }
//     int hr, min;
//     printf("Enter current time hours and minutes\n");
//     scanf("%d %d", &hr, &min);
//     current_time.hours = hr;
//     current_time.minutes = min;
//     TIME notTime; 
// Bucket *temp=*dashboard;
// FlightPlan *next = temp->next;
// 	FlightPlan *dummy = createFlightSchedule(-11, notTime, notTime);
//         FlightPlan *dummyTail = dummy;
//         FlightPlan *store = createFlightSchedule(-1, notTime, notTime), *storeTail = store;
//         while (temp)
//             if (temp->start_time.minutes >= current_time.minutes)
//             {
//                 dummyTail->next = dashboard;
//                 dummyTail = dummyTail->next;
//             }
//             else
//             {
//                 if (storeTail == NULL)
//                 {
//                     storeTail = dashboard;
//                     store = storeTail;
//                 }
//                 else
//                 {
//                     storeTail->next = dashboard;
//                     storeTail = storeTail->next;
//                 }
// 	 *dashboard = C;
//         P->next = NULL;
//         C = (*bucket)->next;
//         while (C->next)
//         {
//             C = C->next;
//         }
//         C->next = Start;
}
// void rearrangeBuckets(Bucket **buckets, int currentTime) {
//     Bucket *temp = *buckets;
//     Bucket *prev = NULL;
//     while (temp != NULL) {
//         TIME startETA = temp->start_time;
//         TIME endETA = temp->end_time;
//         if (currentTime >= startETA.hours && currentTime < endETA.hours) {
//             break;
//         }
//         prev = temp;
//         temp = temp->next;
//     }
//     if (temp == NULL) {
//         printf("No active buckets found.\n");
//         return;
//     }
//     Bucket *newBuckets = NULL;
//     Bucket *lastBucket = NULL;
//     while (temp != NULL) {
//         int newStartETA = currentTime;
//         int newEndETA = newStartETA + 60 * 60; // 1 hr time period
//         Bucket *newBucket = create_bucket(temp->bucket_id, newStartETA, newEndETA);
//         newBucket->flight_plans = temp->flight_plans;
//         if (newBuckets == NULL) {
//             newBuckets = newBucket;
//         } else {
//             lastBucket->next = newBucket;
//         }
//         lastBucket = newBucket;
//         temp = temp->next;
//     }
//     *buckets = newBuckets;
// }

Bucket* create_bucket(int bucket_id, TIME start_time, TIME end_time) 
{
    Bucket* new_bucket = (Bucket*)malloc(sizeof(Bucket));
    new_bucket->bucket_id = bucket_id;
    new_bucket->start_time = start_time;
    new_bucket->end_time = end_time;
    new_bucket->flight_plans = NULL;
    new_bucket->next = NULL;
    return new_bucket;
}

FlightPlan* create_flight_plan(int flight_id, TIME departure_time, TIME ETA) 
{
    FlightPlan* new_flight_plan = (FlightPlan*)malloc(sizeof(FlightPlan));
    new_flight_plan->flight_id = flight_id;
    new_flight_plan->departure_time = departure_time;
    new_flight_plan->ETA = ETA;
    new_flight_plan->next = NULL;
    return new_flight_plan;
}

void insert_flight_plan(Bucket **dashboard, FlightPlan *newFlightPlan)
{
    Bucket *Temp = *dashboard;
    Bucket *prev;
    
    while(Temp->start_time.hours < newFlightPlan->ETA.hours )
    {
        Temp = Temp->next;
    }
    if(Temp->start_time.hours == newFlightPlan->ETA.hours)
    {
        if(Temp->flight_plans == NULL)
        {
            Temp->flight_plans = newFlightPlan;
        }
        else
        {
            FlightPlan *current = Temp->flight_plans;
            FlightPlan *previous = NULL;

// If the flight plan list is empty or the new flight plan has the earliest departure time
            if(!current || current->departure_time.hours > newFlightPlan->departure_time.hours || (current->departure_time.hours == newFlightPlan->departure_time.hours && current->departure_time.minutes > newFlightPlan->departure_time.minutes))
            {
                newFlightPlan->next = current;
                Temp->flight_plans = newFlightPlan;
            }
            else
            {
                // Traverse the list to find the correct position for the new flight plan
                while(current && (current->departure_time.hours < newFlightPlan->departure_time.hours || (current->departure_time.hours == newFlightPlan->departure_time.hours && current->departure_time.minutes < newFlightPlan->departure_time.minutes)))
                {
                    previous = current;
                    current = current->next;
                }

                // Insert the new flight plan into the correct position
                newFlightPlan->next = current;
                if(previous)
                    previous->next = newFlightPlan;
                else
                    Temp->flight_plans = newFlightPlan;
            }

        }
    }

    
}
void Print(Bucket *bucket) 
 {
    Bucket *temp = bucket;
    while (temp)
    {
        printf("\n");
        printf("Bucket ID: %d\n", temp->bucket_id);
        printf("Start Time: %d:%d\n", temp->start_time.hours, temp->start_time.minutes);
        printf("End Time: %d:%d\n", temp->end_time.hours, temp->end_time.minutes);
        FlightPlan *temp2 = temp->flight_plans;
        while (temp2)
        {
            printf("Flight ID: %d\n", temp2->flight_id);
            printf("Departure Time: %d:%d\n", temp2->departure_time.hours, temp2->departure_time.minutes);
            printf("ETA: %d:%d\n", temp2->ETA.hours, temp2->ETA.minutes);
            printf("\n");
            temp2 = temp2->next;
        }
        temp = temp->next;
        printf("\n");
    }
}
