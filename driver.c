#include "main.h"
static int Id = 10;
int main() 
{
    Bucket* dashboard = NULL;

    // Sample usage
    TIME current_time = {4, 30};
    int choice;
    Bucket *temp;
    temp = dashboard;

      for (int i = 0; i < 24; i++) 
      {
        Bucket* newBucket = malloc(sizeof(Bucket));
        newBucket->bucket_id = Id + i;
        newBucket->start_time.hours = i;
        newBucket->start_time.minutes = 0;
        newBucket->end_time.hours = i + 1;
        newBucket->end_time.minutes = 0;
        newBucket->flight_plans = NULL;   // Initially, no flight plans
        newBucket->next = NULL;

        // Link the new bucket to the existing list
        if(temp != NULL)
        {
            temp->next = newBucket;
            temp = temp->next;   
        }
        else if(temp == NULL)
        {
            temp = newBucket;
            dashboard = temp;
        }
    }


    // Sample flight plans

        int flightPlans[25][5] = {
         {101, 13, 45, 14, 15},
         {125, 12, 45, 14, 35},
        {102, 14, 0, 15, 45},
        {103, 15, 30, 16, 45},
        {104, 16, 1, 17, 30},
        {105, 17, 0, 18, 30},
        {106, 18, 30, 19, 45},
        {107, 19, 15, 20, 30},
        {108, 20, 0, 21, 15},
        {109, 21, 30, 22, 45},
        {110, 22, 15, 23, 30},
        {111, 23, 0, 0, 15},
        {112, 0, 30, 1, 45},
        {113, 1, 15, 2, 30},
        {114, 2, 0, 3, 15},
        {115, 3, 30, 4, 45},
        {116, 4, 15, 5, 30},
        {117, 5, 45, 6, 10},
        {118, 6, 30, 7, 45},
        {119, 7, 15, 8, 30},
        {120, 8, 0, 9, 15},
        {121, 9, 30, 10, 45},
        {122, 10, 15, 11, 30},
        {123, 11, 0, 12, 15},
        {124, 12, 30, 13, 45},
    };

    // Insert flight plans into the dashboard
    for (int i = 0; i < 25; i++) 
    {
        TIME ETA;
        TIME Depart;
        ETA.hours = flightPlans[i][3];
        ETA.minutes = flightPlans[i][4];
        Depart.hours = flightPlans[i][1];
        Depart.minutes = flightPlans[i][2];
        FlightPlan *a = create_flight_plan(flightPlans[i][0],Depart,ETA);
        insert_flight_plan(&dashboard,a);

    }

    printf("\n");
    Print(dashboard);
    while (1) 
    {
        printf("\n1. Insert a new flight plan\n");
        printf("2. Cancel a flight plan\n");
        printf("3. Show flight status\n");
        printf("4. Show flight plans within next hour\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: 
            {
                int bucket_id, flight_id, dep_hour, dep_min, eta_hour, eta_min;
                printf("Enter flight ID: ");
                scanf("%d", &flight_id);
                printf("Enter departure time (hh:mm): ");
                scanf("%d %d", &dep_hour, &dep_min);
                printf("Enter ETA (hh:mm): ");
                scanf("%d %d", &eta_hour, &eta_min);
                TIME departure_time = {dep_hour, dep_min};
                TIME ETA = {eta_hour, eta_min};
                FlightPlan* new_flight_plan = create_flight_plan(flight_id, departure_time, ETA);
                if (dashboard == NULL) 
                {
                    TIME start_time = {dep_hour, 0};
                    TIME end_time = {start_time.hours + 1, 0};
                    dashboard = create_bucket(bucket_id, start_time, end_time);
                }
                insert_flight_plan(&dashboard, new_flight_plan);
                Print(dashboard);
                break;
            }
            case 2: 
            {
                int flight_id;
                printf("Enter flight ID to cancel: ");
                scanf("%d", &flight_id);
                cancel_flight_plan(dashboard, flight_id);
                Print(dashboard);
                break;
            }
            case 3: 
            {
                int flight_id;
                printf("Enter flight ID to show status: ");
                scanf("%d", &flight_id);
                show_flight_status(dashboard, flight_id);
                break;
            }
            case 4: 
            {
                printf("Showing flight plans within next hour:\n");
               
                show_flight_plans_within_hour(dashboard, current_time);
                Print(dashboard);
                break;
            }
            case 5: 
            {
                // Free allocated memory
                while (dashboard != NULL) 
                {
                    Bucket* temp = dashboard;
                    dashboard = dashboard->next;
                    FlightPlan* current_flight = temp->flight_plans;
                    while (current_flight != NULL) {
                        FlightPlan* temp_flight = current_flight;
                        current_flight = current_flight->next;
                        free(temp_flight);
                    }
                    free(temp);
                }
                return 0;
            }
            default: 
            {
                printf("Invalid choice! Please enter a valid option.\n");
                break;
            }
        }
    }

    return 0;
}