#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define MAX_NAME_LENGTH 50
#define MAX_INVENTORY 20
#define MAX_QUESTS 15
#define MAX_LOCATIONS 10
#define MAX_NPCS 20
#define MAX_DESCRIPTION_LENGTH 200
#define MAX_COURSES 5
#define MAX_SKILLS 10
#define MAX_CLUBS 5
#define MAX_EVENTS 10

typedef struct{
    char name[MAX_NAME_LENGTH];
    int health;
    int maxHealth;
    int energy;
    int maxEnergy;
    int intelligence;
    int charisma;
    int stress;
    int experience;
    int level;
    int semester;
    float cgpa;
    int credits;
    int money;
}Character;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
    int value;
    char description[MAX_DESCRIPTION_LENGTH];
}Item;

typedef struct {
    Item items[MAX_INVENTORY];
    int count;
}Inventory;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int completed;
    int experienceReward;
    int moneyReward;
    float cgpaBoost;
} Quest;

typedef struct
{
    Quest quests[MAX_QUESTS];
    int count;
} QuestLog;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int unlocked;
}Location;


typedef struct
{
    char name[MAX_NAME_LENGTH];
    int credits;
    float grade;
    int difficulty;
}Course;


typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int day;
    int month;
} Event;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int memberCount;
    int joined;
} Club;

Character player;
Inventory inventory;
QuestLog questLog;
Club clubs[MAX_CLUBS];
int clubCount = 0;
Event events[MAX_EVENTS];
int eventCount =0;
int currentDay= 1;
int currentMonth= 1;

void initCharacter()
{
    printf("Enter your name: ");
    fgets(player.name,MAX_NAME_LENGTH,stdin);
    player.name[strcspn(player.name,"\n")] = 0;
    player.energy =100;
    player.maxEnergy= 100;
    player.intelligence= 10;
    player.charisma =10;
    player.stress = 0;
    player.experience= 0;
    player.level = 1;
    player.semester=1;
    player.cgpa = 0.0;
    player.credits= 0;
    player.money =1000;
}
void strangerTalk(){
    player.energy-=10;
    int r = rand();
    if(r%5==0){
        printf("You met a good guy :) !!\nCHARISMA INCREASED!\nSTRESS DECREASED!");
        player.charisma+=10;
        if (player.stress>=10) player.stress-=10;
        else player.stress = 0;
    }
    else if(r%2==0) printf("You failed to meet anyone");
    else{
        printf("You met a bully :( !!\nCHARISMA DECREASES!\nSTRESS INCREASED!)");
        player.stress+=10;
        if (player.charisma>=10) player.charisma-=10;
        else player.charisma = 0;
    }
}

void trackExam(){
    if(currentDay==15) printf("Your Exam is today");
    else if(currentDay<15) printf("Your Exam is in %d days",15-currentDay);
    else printf("Your Exam is in %d days",45-currentDay);

}

void sleep(){
    if(player.energy<=50) player.energy+=50;
    else player.energy=100;
    player.health += 10;
    if (player.health > player.maxHealth) player.health = player.maxHealth;
    if (player.stress>=10) player.stress-=10;
    else player.stress = 0;
    currentDay++;
   if (currentDay > 30) {
        currentDay = 1;
        currentMonth++;
        if (currentMonth > 12) {
            currentMonth = 1;
            player.semester++;
        }
    }
    printf("Sleep success!!\nEnergy increased!\nStress decreased!");
    printf("It's now day %d of month %d, semester %d.\n", currentDay, currentMonth, player.semester);
    checkForEvents();
}

void printStatus() {
    printf("\n----- Character Status -----\n");
    printf("Name: %s\n", player.name);
    printf("Health: %d/%d\n", player.health, player.maxHealth);
    printf("Energy: %d/%d\n", player.energy, player.maxEnergy);
    printf("Intelligence: %d\n", player.intelligence);
    printf("Charisma: %d\n", player.charisma);
    printf("Stress: %d\n", player.stress);
    printf("Experience: %d\n", player.experience);
    printf("Level: %d\n", player.level);
    printf("Semester: %d\n", player.semester);
    printf("CGPA: %.2f\n", player.cgpa);
    printf("Credits: %d\n", player.credits);
    printf("Money: Rs.%d\n", player.money);
}

void addItem(const char* itemName, int quantity, int value, const char* description)
{
    if (inventory.count <MAX_INVENTORY)
    {
        for (int i = 0; i< inventory.count; i++)
        {
            if (strcmp(inventory.items[i].name, itemName) == 0)
            {
                inventory.items[i].quantity += quantity;
                printf("Added %d %s to the inventory.\n", quantity, itemName);
                return;
            }
        }
        strcpy(inventory.items[inventory.count].name,itemName);
        inventory.items[inventory.count].quantity = quantity;
        inventory.items[inventory.count].value =value;
        strcpy(inventory.items[inventory.count].description,description);
        inventory.count++;
        printf("Added %d %s to the inventory.\n", quantity, itemName);
    }
    else
    {
        printf("Inventory is full!\n");
    }
}

void printInventory()
{
    printf("\n----- Inventory -----\n");
    if(inventory.count ==0)
    {
        printf("Your inventory is empty.\n");
    }
    else
    {
        for(int i = 0; i < inventory.count; i++)
        {
            printf("%d. %s x%d (Value: $%d)\n", i + 1, inventory.items[i].name, inventory.items[i].quantity, inventory.items[i].value);
            printf("Description: %s\n", inventory.items[i].description);
        }
    }
}

void addQuest(const char* questName, const char* questDescription, int expReward)
{
    if (questLog.count <MAX_QUESTS)
    {
        strcpy(questLog.quests[questLog.count].name, questName);
        strcpy(questLog.quests[questLog.count].description, questDescription);
        questLog.quests[questLog.count].completed = 0;
        questLog.quests[questLog.count].experienceReward = expReward;
        questLog.count++;
        printf("New quest added: %s\n", questName);
    }
    else
    {
        printf("Quest log is full!\n");
    }
}

void printQuests()
{
    printf("\n----- Quest Log -----\n");
    if (questLog.count ==0)
    {
        printf("You have no active quests.\n");
    }
    else
    {
        for (int i = 0;i<questLog.count; i++)
        {
            printf("%d. %s: %s\n", i+1, questLog.quests[i].name, questLog.quests[i].completed ? "Completed" : "In Progress");
            printf("Description: %s\n",questLog.quests[i].description);
        }
    }
}

void initEvents()
{
    strcpy(events[0].name, "Induction");
    strcpy(events[0].description, "Welcome event for new students to get familiar with the campus.");
    events[0].day = 15;
    events[0].month = 7;

    strcpy(events[1].name, "T1 Examination");
    strcpy(events[1].description, "First round of major exams for the semester.");
    events[1].day = 5;
    events[1].month = 9;

    strcpy(events[2].name, "Midterm Examination");
    strcpy(events[2].description, "Second round of major exams for the semester");
    events[2].day = 11;
    events[2].month = 10;

    strcpy(events[3].name, "Diwali Break");
    strcpy(events[3].description, "holidays.");
    events[3].day = 25;
    events[3].month = 10;

    strcpy(events[4].name, "End Term Examination");
    strcpy(events[4].description, "Final Examination for the semester");
    events[4].day = 2;
    events[4].month = 12;


    eventCount = 5;
}

void checkForEvents()
{
    for (int i = 0; i<eventCount;i++)
    {
        if (events[i].day==currentDay && events[i].month==currentMonth)
        {
            printf("\nEvent Alert: %s\n",events[i].name);
            printf("Description: %s\n",events[i].description);
            // @sansriti implement some event specific actions here
        }
    }
}

void eat() {
    printf("Where would you like to eat?\n");
    printf("1. Cafeteria (Rs.30)\n");
    printf("2. Local Restaurant (Rs.150)\n");
    printf("3. Mess (Rs.0)\n");

    int choice;
    char input[10];
    printf("Enter your choice: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    switch(choice) {
        case 1:
            if (player.money >= 30) {
                player.money -= 30;
                player.health += 15;
                player.energy += 20;
                printf("You eat a meal at the cafeteria.\n");
            } else {
                printf("You don't have enough money to eat at the cafeteria.\n");
            }
            break;
        case 2:
            if (player.money >= 150) {
                player.money -= 150;
                player.health += 25;
                player.energy += 30;
                player.stress -= 10;
                printf("You enjoy a delicious meal at a local restaurant.\n");
            } else {
                printf("You don't have enough money to eat at a restaurant.\n");
            }
            break;
        case 3:
            player.health += 10;
            player.energy += 15;
            printf("You eat from the campus mess, Annapurna.\n");
            break;
        default:
            printf("Invalid choice. You skip the meal.\n");
            player.health -= 5;
            player.energy -= 10;
            player.stress += 5;
    }

    if (player.health > player.maxHealth) player.health = player.maxHealth;
    if (player.energy > player.maxEnergy) player.energy = player.maxEnergy;
    if (player.stress < 0) player.stress = 0;
    if (player.stress > 100) player.stress = 100;
}

void initClubs() {
    strcpy(clubs[0].name, "Open Source Development Society");
    strcpy(clubs[0].description, "A club for Development enthusiasts and aspiring programmers.");
    clubs[0].memberCount = 30;
    clubs[0].joined = 0;

    strcpy(clubs[1].name, "Knuth Programming hub");
    strcpy(clubs[1].description, "Improve your DSA and Competetive programming skills");
    clubs[1].memberCount = 50;
    clubs[1].joined = 0;

    strcpy(clubs[2].name, "DebSoc");
    strcpy(clubs[2].description, "Improve your public speaking and argumentation skills.");
    clubs[2].memberCount = 25;
    clubs[2].joined = 0;

    strcpy(clubs[3].name, "Cresendo");
    strcpy(clubs[3].description, "Improve your singing and music skills");
    clubs[3].memberCount = 20;
    clubs[3].joined = 0;

    strcpy(clubs[4].name, "Thespian");
    strcpy(clubs[4].description, "Express yourself through acting and stage production.");
    clubs[4].memberCount = 20;
    clubs[4].joined = 0;

    clubCount = 5;
}

void joinClub() {
    printf("\nAvailable Clubs:\n");
    for (int i = 0; i < clubCount; i++) {
        printf("%d. %s (%s members)\n", i + 1, clubs[i].name, clubs[i].joined ? "Joined" : clubs[i].memberCount);
        printf("   Description: %s\n", clubs[i].description);
    }

    int choice;
    char input[10];
    printf("Enter the number of the club you want to join: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    if (choice >= 1 && choice <= clubCount) {
        if (!clubs[choice - 1].joined) {
            clubs[choice - 1].joined = 1;
            clubs[choice-1].memberCount++;
            printf("You've joined the %s!\n", clubs[choice - 1].name);
            player.experience += 20;
            player.charisma += 2;
            player.stress += 5;
            if (player.stress > 100) player.stress = 100;
        } else {
            printf("You're already a member of this club.\n");
        }
    } else {
        printf("Invalid club choice.\n");
    }
}

void gameLoop()
{
    char input[20];
    while (42)
    {
        printf("\nWhat would you like to do? \n");
        printf("1. Check Status\n");
        printf("2. Study\n");
        printf("3. Socialize\n");
        printf("4. Exercise\n");
        printf("5. Eat\n");
        printf("6. Sleep\n");
        printf("7. Manage Finances\n");
        printf("8. Attend Workshop\n");
        printf("9. Track Exam\n");
        printf("10. Join Club\n");
        printf("11. Change Location\n");
        printf("12. Talk to a stranger\n");
        printf("13. View Inventory\n");
        printf("14. View Quests\n");
        printf("15. Quit Game\n");
        printf("Enter your choice: ");
        fgets(input,sizeof(input), stdin);
        int choice =atoi(input);

        switch (choice)
        {
            case 1:
                printStatus();
                break;
            case 2:
                //studyCourse();
                break;
            case 3:
                //socializeWithFriends();
                break;
            case 4:
                //exercise();
                break;
            case 5:
                eat();
                break;
            case 6:
                sleep();
                break;

            case 7:
               // manageFinances();
                break;
            case 8:
               // attendWorkshop();
                break;

            case 9:
                trackExam();
                break;
            case 10:
                joinClub();
                break;
            case 11:
               // changeLocation();
                break;
            case 12:
                if(player.energy<10) printf("NOT ENOUGH ENERGY , GET SOME SLEEP OR REST!");
                else{
                    player.energy-=10;
                    strangerTalk();
                }
                break;
            case 13:
                printInventory();
                break;
            case 14:
                printQuests();
                break;
            case 15:
                printf("Thanks for playing! Goodbye!\n");
                return;
            default:
                printf("Enter a valid choice you illiterate.\n");
        }

        }
    }

int main() {
    srand(time(NULL));
    initCharacter();
    initEvents();
    initClubs();
    addQuest("Ace Your First Semester", "Achieve a CGPA of 8.5 or higher in your first semester.\n", 0.2);
    addQuest("Join a Club", "Become a member of at least one student club.\n", 0.1);
    addQuest("Master a Skill", "Reach level 5 in any skill.\n",0.15);
    printf("Welcome to the Jaypee Institute of Information Technology!\n");
    printf("You are a new student at JIIT, embarking on a journey of barbadi and depression.\n");
    gameLoop();
}
