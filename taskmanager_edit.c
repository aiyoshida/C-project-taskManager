
#define _CRT_SECURE_NO_WARNINGS// to avoid errors of fopen function
#include <stdio.h>
#include <stdlib.h> // to use malloc function
#include <string.h>

//using linked list for base data structure.
typedef struct tasks {
    char task_name[20];
    char task_description[200];
    char category[20];

    int s_year; //The start date of the task
    int s_month;
    int s_day;

    int e_year;//The end date of the task
    int e_month;
    int e_day;

    int priority;
    char dep[20];//Shows what this task depend to other task.
    struct tasks *next; 
}tasks;


// list of functionss
tasks *CreateNewTask();// to create a new task. Return pointer of the new task node.
void SeeUrUnfinishedTasks(tasks *head2); //To see the list of unfinished tasks.
tasks *sortdate(tasks *unfinished);//To set the linked list up to chronologinal order.
void SeeUrCategoriesAndTasks(tasks *head3); //To see the list of categories and tasks
void SeeUrdep(tasks *head4);// To see the list of depending tasks.

//main function
int main (void)
{
    int choice;//variable for user option. options are 1 to 4.

    FILE *fp;//This code make sure database.txt exists. If not, create here.
    fp = fopen("database.txt", "a+");
    fclose(fp);

    //first manu
    printf("\n");
    printf("What would you like to do?\n");
    printf("----------------------------------------------------------------------------\n");
    printf("1) Create a new task and category\n");
    printf("2) See your unfinished tasks\n");
    printf("3) See your categories and tasks\n");
    printf("4) See depended tasks\n");
    printf("----------------------------------------------------------------------------\n");
    printf("Please enter the number which you would like to do: ");
    
    scanf("%d", &choice);//ask user input

    if (choice == 1)//When user choose option 1.
    {
        fp = fopen("database.txt", "a+");
        tasks *head1 = (tasks*)malloc(sizeof(tasks));
            if (head1 == NULL)
            {
                printf("failed");
                exit(0);
            }

        head1 = CreateNewTask();

        //to write data into file
        fprintf(fp, "%s#", head1->task_name);
        fprintf(fp, "%s#", head1->task_description);
        fprintf(fp, "%s#", head1->category);
        fprintf(fp, "%d#", head1->s_year);
        fprintf(fp, "%d#", head1->s_month);
        fprintf(fp, "%d#", head1->s_day);
        fprintf(fp, "%d#", head1->e_year);
        fprintf(fp, "%d#", head1->e_month);
        fprintf(fp, "%d#", head1->e_day);
        fprintf(fp, "%d#", head1->priority);
        fprintf(fp, "%s\n", head1->dep);

        free(head1);
        fclose(fp);
        
    }


    if(choice == 2){
    
        fp = fopen("database.txt", "r");
        tasks *head2 = NULL;

            char str1[500];
                while (fgets(str1, 500, fp)!=NULL)//read every one line from the file
                {
                    tasks *current = (tasks*)malloc(sizeof(tasks));
                    if(current == NULL)
                    {
                        printf("failed");
                        exit (0);
                    }
                    //This sscanf transform char[] from file into each value. 
                    sscanf(str1, "%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%d#%d#%d#%s", current->task_name, current->task_description, current->category, &current->s_year, &current->s_month, &current->s_day, &current->e_year, &current->e_month, &current->e_day, &current->priority, current->dep);
                    
                    current->next = head2;
                    head2 = current;
         
                }

            fclose(fp);
            
            SeeUrUnfinishedTasks(head2);

    }



    if(choice == 3)
    {
        fp = fopen("database.txt", "r");
        tasks *head3 = NULL;

        char str2[500];
                while (fgets(str2, 500, fp)!=NULL)//read every one line from the file
                {
                    tasks *current = (tasks*)malloc(sizeof(tasks));
                    if(current == NULL)
                    {
                        printf("failed");
                        exit (0);
                    }
                    //This sscanf transform char[] from file into each value. 
                    sscanf(str2, "%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%d#%d#%d#%s", current->task_name, current->task_description, current->category, &current->s_year, &current->s_month, &current->s_day, &current->e_year, &current->e_month, &current->e_day, &current->priority, current->dep);
                    
                    current->next = head3;
                    head3 = current;
                }
            fclose(fp);

            SeeUrCategoriesAndTasks(head3);
    }
    
    
    if(choice == 4)
    {
        fp = fopen("database.txt", "r");//open for reading.
        
        tasks *head4 = NULL;
        char str4[500];
                while (fgets(str4, 500, fp)!=NULL)
                {
                    tasks *current4 = (tasks*)malloc(sizeof(tasks));
                        if(current4 == NULL)
                        {
                            printf("failed");
                            exit (0);
                        }
                    //This sscanf transform char[] from file into each value. 
                    sscanf(str4, "%[^#]#%[^#]#%[^#]#%d#%d#%d#%d#%d#%d#%d#%s", current4->task_name, current4->task_description, current4->category, &current4->s_year, &current4->s_month, &current4->s_day, &current4->e_year, &current4->e_month, &current4->e_day, &current4->priority, current4->dep);
                    
                    current4->next = head4;
                    head4 = current4;
                }
            fclose(fp);

            SeeUrdep(head4);//send pointer to show depend tasks.
    }
    if((choice < 1)||(choice > 4)){//In the case when user input invalid value.(not 1 to 4).
        printf("There is not such option!");
    }

    return 0;
}




//function of 1) Create a new task. Ask user the information about new tasks
tasks *CreateNewTask()
{
    //To allocate memory
    tasks *s = (tasks*) malloc (sizeof(tasks));
    if (s ==  NULL)
    exit(0);

    //Ask information to users
    printf("Please fill in below\n");
    printf("----------------------------------------------------------------------------\n");
    printf("1) Please enter name of the task (within 20 characters): ");
    fflush(stdin);
    scanf("%[^\n]s", s->task_name);
    fflush(stdin);
    printf("\n2) Enter the description of the task (within 200 characters): ");
    fflush(stdin);//Clear output console
    scanf("%[^\n]s", s->task_description);
    printf("\n3) Please enter the name of this category: ");
    scanf("%s", s->category);
    printf("4) Please enter the expected start date of the task: \n");
    printf("year:   ");
    scanf("%d", &s->s_year);
    printf("month:  ");
    scanf("%d", &s->s_month);
    printf("day:    ");
    scanf("%d", &s->s_day);
    printf("5) Please enter the expected end date of the task: \n");
    printf("year:   ");
    scanf("%d", &s->e_year);
    printf("month:  ");
    scanf("%d", &s->e_month);
    printf("day:    ");
    scanf("%d", &s->e_day);
    printf("6) Please select the priority of the task from 1(low) to 10(High): ");
    scanf("%d", &s->priority);
    printf("\n7) Any related task? If yes, write the related task name, if no, enter 0: ");
    scanf("%s", s->dep);
    printf("----------------------------------------------------------------------------\n");   
    s->next = NULL;

    return s;
    free(s);    
}



//function of “2) See your unfinished tasks” start date is considered.
void SeeUrUnfinishedTasks(tasks *head2)
{

    //in the case to do list is empty
    int year, month, day;//variable to ask user today's date.

    printf("Please fill in below\n");
    printf("----------------------------------------------------------------------------\n");
    printf("Please enter today date: \n");
    printf("year:   ");
    scanf("%d", &year);
    printf("month:  ");
    scanf("%d", &month);
    printf("day:    ");
    scanf("%d", &day);
    printf("----------------------------------------------------------------------------\n");

        tasks *tmp2 = head2;
        
        //In the case when task lisk is empty.
        if(head2 == NULL)
        {
            printf("You have no unfinished task!");
        }
     
        while (tmp2 != NULL)//
        {
            if((tmp2->s_year < year) && (tmp2->e_year > year))//Compare year
            {
            printf("Task name: %s\n", tmp2->task_name);
            printf("Task description: %s\n", tmp2->task_description);
            printf("Task category: %s\n",tmp2->category);
            printf("Start date: %d/", tmp2->s_year);
            printf("%d/", tmp2->s_month);
            printf("%d\n", tmp2->s_day);
            printf("End date: %d/", tmp2->e_year);
            printf("%d/", tmp2->e_month);
            printf("%d\n", tmp2->e_day);
            printf("Priority: %d\n",tmp2->priority);
            printf("Name of the depending task: %s", tmp2->dep);
            printf("\n\n\n");
            }
            else if((tmp2->s_year == year) && (tmp2->e_year == year) && (tmp2->s_month < month) && (tmp2->e_month > month))//compare month
            {
            printf("Task name: %s\n", tmp2->task_name);
            printf("Task description: %s\n", tmp2->task_description);
            printf("Task category: %s\n",tmp2->category);
            printf("Start date: %d/", tmp2->s_year);
            printf("%d/", tmp2->s_month);
            printf("%d\n", tmp2->s_day);
            printf("End date: %d/", tmp2->e_year);
            printf("%d/", tmp2->e_month);
            printf("%d\n", tmp2->e_day);
            printf("Priority: %d\n",tmp2->priority);
            printf("Name of the depending task: %s", tmp2->dep);
            printf("\n\n\n");

            }else if((tmp2->s_year == year) && (tmp2->e_year == year) &&(tmp2->s_month == month) && (tmp2->e_month == month) && (tmp2->s_day < day) && (tmp2->e_day > day))//compare day
            {
            printf("Task name: %s\n", tmp2->task_name);
            printf("Task description: %s\n", tmp2->task_description);
            printf("Task category: %s\n",tmp2->category);
            printf("Start date: %d/", tmp2->s_year);
            printf("%d/", tmp2->s_month);
            printf("%d\n", tmp2->s_day);
            printf("End date: %d/", tmp2->e_year);
            printf("%d/", tmp2->e_month);
            printf("%d\n", tmp2->e_day);
            printf("Priority: %d\n",tmp2->priority);
            printf("Name of the depending task: %s", tmp2->dep);
            printf("\n\n\n");
            }
            tmp2 = tmp2->next;//To move next
        }
}


//Function of “3) See your categories and tasks”
void SeeUrCategoriesAndTasks(tasks *head3)
{
    char show[30];
    tasks *tmp3 = head3;
    printf("Please enter the name of the category you would like to see: ");
    scanf("%s", show);//Ask user to what category user wants to see.
    printf("\n----------------------------------------------------------------------------\n");
    
    while (tmp3 != NULL)
    {
        if(strcmp(tmp3->category, show)== 0)//list tasks which has the category which user input.
        {
            printf("Task name: %s\n", tmp3->task_name);
            printf("Task description: %s\n", tmp3->task_description);
            printf("Task category: %s\n",tmp3->category);
            printf("Start date: %d/", tmp3->s_year);
            printf("%d/", tmp3->s_month);
            printf("%d\n", tmp3->s_day);
            printf("End date: %d/", tmp3->e_year);
            printf("%d/", tmp3->e_month);
            printf("%d\n", tmp3->e_day);
            printf("Priority: %d\n",tmp3->priority);
            printf("Name of the depending task: %s", tmp3->dep);
            printf("\n\n\n");
        }
        tmp3 = tmp3->next;
    }
    
    printf("----------------------------------------------------------------------------\n");
}


//Function to list depend tasks.
void SeeUrdep(tasks *head4)
{
    if(head4 == NULL)
    {// In the case task list is empty.
        printf("Task list is empty.");
    }

    char depend[30];
    tasks *tmp4 = head4;
    tasks *tmp44 = head4;
    printf("Please enter the name of the depend task you would like to see: ");
    scanf("%s", depend);
    printf("\n----------------------------------------------------------------------------\n");
    printf("An independent task\n\n");
    
    while (tmp44 != NULL)//This show the independent task.
    {
        if(strcmp(tmp44->task_name, depend) == 0)
        {
            printf("Task name: %s\n", tmp44->task_name);
            printf("Task description: %s\n", tmp44->task_description);
            printf("Task category: %s\n",tmp44->category);
            printf("Start date: %d/", tmp44->s_year);
            printf("%d/", tmp44->s_month);
            printf("%d\n", tmp44->s_day);
            printf("End date: %d/", tmp44->e_year);
            printf("%d/", tmp44->e_month);
            printf("%d\n", tmp44->e_day);
            printf("Priority: %d\n",tmp44->priority);
            printf("\n\n");
        }
        tmp44 = tmp44->next;
    }
    
    printf("Tasks which depends on the task above\n\n");

    while (tmp4 != NULL)//This list depend tasks.
    {
        if(strcmp(tmp4->dep, depend) == 0)
        {
            printf("Task name: %s\n", tmp4->task_name);
            printf("Task description: %s\n", tmp4->task_description);
            printf("Task category: %s\n",tmp4->category);
            printf("Start date: %d/", tmp4->s_year);
            printf("%d/", tmp4->s_month);
            printf("%d\n", tmp4->s_day);
            printf("End date: %d/", tmp4->e_year);
            printf("%d/", tmp4->e_month);
            printf("%d\n", tmp4->e_day);
            printf("Priority: %d\n",tmp4->priority);
            printf("\n\n");
        }
            tmp4 = tmp4->next;
    }
    
    printf("----------------------------------------------------------------------------\n");
}

