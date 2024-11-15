#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

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
#define TRANSACTION_EXPENSE 0
#define TRANSACTION_INCOME 1

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int health;
    int maxHealth;
    int energy;
    int maxEnergy;
    int exam_prep;
    int charisma;
    int stress;
    int intelligence;
    int experience;
    int level;
    int semester;
    float cgpa;
    int credits;
    int money;
} Character;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int quantity;
    int value;
    char description[MAX_DESCRIPTION_LENGTH];
} Item;

typedef struct
{
    Item items[MAX_INVENTORY];
    int count;
} Inventory;

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
    int credits;
    float grade;
    int difficulty;
} Course;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int day;
    int month;
} Event;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int memberCount;
    int joined;
} Club;

typedef struct
{
    char description[MAX_DESCRIPTION_LENGTH];
    int amount;
    int type; // 0 for expense 1 for income
    int day;
    int month;
} Transaction;

typedef struct
{
    Transaction transactions[100];
    int count;
} FinancialHistory;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int unlocked;
    int stress_modifier; // Added field
    int study_bonus;     // Added field
} Location;

typedef struct
{
    int act;
    int corruption_exposed;
    int library_secured;
    int dance_battle_won;
    int deanDefeated;
    int dance_skill; // Added based on usage in socialize()
} Story;

Character player;
Inventory inventory;
QuestLog questLog;
Club clubs[MAX_CLUBS];
int clubCount = 0;
Event events[MAX_EVENTS];
int eventCount = 0;
int currentDay = 1;
int currentMonth = 1;
FinancialHistory financialHistory = {0};
Location locations[MAX_LOCATIONS];
int locationCount = 0;
Story story = {1, 0, 0, 0, 0};

void attendWorkshop()
{
    if (player.energy < 40)
    {
        printf("You're too tired to attend a workshop!\n");
        return;
    }

    printf("\n----- Available Workshops -----\n");
    printf("1. KPH (Intelligence +5)\n");
    printf("2. OSDC (Charisma +5)\n");
    printf("3. uCR (Experience +30)\n");

    char input[10];
    printf("Enter workshop choice (0 to cancel): ");
    fgets(input, sizeof(input), stdin);
    int choice = atoi(input);

    switch (choice)
    {
    case 0:
        return;
    case 1:
        player.intelligence += 5;
        player.energy -= 40;
        player.experience += 20;
        printf("You learned new technical skills!\n");

        break;
    case 2:
        player.charisma += 5;
        player.energy -= 35;
        player.experience += 15;
        printf("Your communication skills improved!\n");

        break;
    case 3:
        player.experience += 30;
        player.energy -= 45;
        printf("You gained valuable career insights!\n");

        break;
    default:
        printf("Invalid workshop choice!\n");
    }
}

void TestExam()
{
    printf("HERE OU THE RULES! YOU CAN GAIN 10 CGPA , BUT YOU NEED TO GIVE A TEST\n");
    printf("it's a memory game, the number of rounds you will pass , it will gain that number of cgpa\n");
    printf("In every other round , numbers of previous round are also also asked\n");
    printf("LET'S START!\n");
    int d = 0, i;
    int a[10] = {0};
    srand(time(0));
    while (d != 11)
    {
        d++;
        int l = 1, u = 100;
        int random_number = (rand() % (u - l + 1)) + l;
        a[d - 1] = random_number;
        printf("Remember this number now!-%d", a[d - 1]);
        int b[d];
        sleep(3);
        system("cls");
        int t = 1;
        for (i = 0; i < d; i++)
        {
            scanf("%d", &b[i]);
            if (b[i] != a[i])
            {
                t = 0;
            }
        }
        if (t == 0)
        {
            break;
        }
        else
        {
            player.cgpa++;
        }
    }
}

void checkForEvents()
{
    for (int i = 0; i < eventCount; i++)
    {
        if (events[i].day == currentDay && events[i].month == currentMonth)
        {
            printf("\nEvent Alert: %s\n", events[i].name);
            printf("Description: %s\n", events[i].description);
        }
    }
}

void initClubs()
{
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

void joinClub()
{
    printf("\nAvailable Clubs:\n");
    for (int i = 0; i < clubCount; i++)
    {
        printf("%d. %s (%d members)\n", i + 1, clubs[i].name, clubs[i].memberCount);
        printf("   Description: %s\n", clubs[i].description);
    }

    int choice;
    char input[10];
    printf("Enter the number of the club you want to join: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    if (choice >= 1 && choice <= clubCount)
    {
        if (!clubs[choice - 1].joined)
        {
            clubs[choice - 1].joined = 1;
            clubs[choice - 1].memberCount++;
            printf("You've joined the %s!\n", clubs[choice - 1].name);
            player.experience += 20;
            player.charisma += 2;
            player.stress += 5;
            if (player.stress > 100)
                player.stress = 100;
        }
        else
        {
            printf("You're already a member of this club.\n");
        }
    }
    else
    {
        printf("Invalid club choice.\n");
    }
}

void printInventory()
{
    printf("\n----- Inventory -----\n");
    if (inventory.count == 0)
    {
        printf("Your inventory is empty.\n");
    }
    else
    {
        for (int i = 0; i < inventory.count; i++)
        {
            printf("%d. %s x%d (Value: $%d)\n", i + 1, inventory.items[i].name, inventory.items[i].quantity, inventory.items[i].value);
            printf("Description: %s\n", inventory.items[i].description);
        }
    }
}

void cafefight()
{
    printf("ERROR! ERROR! HUNGRY STUDENTS ATTACKED!! PROTECT YOURSELF\n");
    int num;
    printf("REMEMBER: if a number matches their hit your energy decreases, else your energy increases,\n3 consecutive mismatch will result in decrease of health");
    int d = 0;
    srand(time(0));
    while (d != 20)
    {
        while (1)
        {
            printf("Enter a hit b/w 1 and 10");
            scanf("%d", &num);
            if (num >= 1 && num <= 10)
            {
                break;
            }
        }
        int lower = 1;
        int upper = 10;
        int random_number = (rand() % (upper - lower + 1)) + lower;
        printf("HUNGRY STUDENT THROW: %d\n", random_number);
        int c = 0;
        if (num == random_number)
        {
            c++;
            player.energy -= 10;
            if (player.health == 0)
            {
                printf("YOU ARE OUT! BETTER LUCK NEXT TIME...");
                exit(0);
            }
            else if (c == 3)
            {
                player.health -= 10;
            }
            if (player.energy == 0)
            {
                player.health -= 10;
                player.energy += 40;
            }
        }
        else
        {
            c = 0;
            player.energy += 10;
        }
        d++;
    }
}

void eat()
{
    printf("Where would you like to eat?\n");
    printf("1. Cafeteria (Rs.30)\n");
    printf("2. Local Restaurant (Rs.150)\n");
    printf("3. Mess (Rs.0)\n");

    int choice;
    char input[10];
    printf("Enter your choice: ");
    fgets(input, sizeof(input), stdin);
    choice = atoi(input);
    int a = rand();
    switch (choice)
    {

    case 1:
        if (a % 2 == 0)
        {
            cafefight();
        }
        else
        {
            if (player.money >= 30)
            {
                player.money -= 30;
                player.health += 15;
                player.energy += 20;
                printf("You eat a meal at the cafeteria.\n");
            }
            else
            {
                printf("You don't have enough money to eat at the cafeteria.\n");
            }
        }
        break;
    case 2:
        if (player.money >= 150)
        {
            player.money -= 150;
            player.health += 25;
            player.energy += 30;
            player.stress -= 10;
            printf("You enjoy a delicious meal at a local restaurant.\n");
        }
        else
        {
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

    if (player.health > player.maxHealth)
        player.health = player.maxHealth;
    if (player.energy > player.maxEnergy)
        player.energy = player.maxEnergy;
    if (player.stress < 0)
        player.stress = 0;
    if (player.stress > 100)
        player.stress = 100;
}

void initCharacter()
{
    printf("Enter your name: ");
    fgets(player.name, MAX_NAME_LENGTH, stdin);
    player.name[strcspn(player.name, "\n")] = 0;
    player.energy = 100;
    player.maxEnergy = 100;
    player.health = 100;
    player.maxHealth = 100;
    player.exam_prep = 0;
    player.charisma = 10;
    player.intelligence = 10;
    player.stress = 0;
    player.experience = 0;
    player.level = 1;
    player.semester = 1;
    player.cgpa = 0.0;
    player.credits = 0;
    player.money = 1000;
}

void study()
{
    printf("Where do you want to study?\n1. LRC (energy=50, exam prep gain=20)\n2. Room (energy=20, exam prep gain=5)\n3. With Friends (energy=30, charisma gain=10, exam prep gain=20)\n");
    int st;
    scanf("%d", &st);
    getchar();
    printf("\nYou studied successfully!\n");
    switch (st)
    {
    case 1:
        player.energy -= 50;
        player.exam_prep += 20;
        break;
    case 2:
        player.energy -= 20;
        player.exam_prep += 5;
        break;
    case 3:
        player.energy -= 30;
        player.exam_prep += 20;
        player.charisma += 10;
        break;
    default:
        printf("Invalid choice.\n");
    }
}

void exercise()
{
    player.energy -= 10;
    player.stress -= 20;
    printf("You exercised! Stress decreased.\n");
}

void strangerTalk()
{
    player.energy -= 10;
    int r = rand() % 10;
    if (r < 5)
    {
        printf("You met a good person!\nCHARISMA INCREASED!\nSTRESS DECREASED!\n");
        player.charisma += 10;
        player.stress = (player.stress >= 10) ? player.stress - 10 : 0;
    }
    else if (r < 8)
    {
        printf("You failed to meet anyone.\n");
    }
    else
    {
        printf("You met a bully! CHARISMA DECREASES!\nSTRESS INCREASED!\n");
        player.stress += 10;
        player.charisma = (player.charisma >= 10) ? player.charisma - 10 : 0;
    }
}

void trackExam()
{
    if (currentDay == 15)
        printf("Your Exam is today!\n");
    else if (currentDay < 15)
        printf("Your Exam is in %d days.\n", 15 - currentDay);
    else
        printf("Your Exam is in %d days.\n", 45 - currentDay);
}

void mysleep()
{
    player.energy = (player.energy <= 50) ? player.energy + 50 : 100;
    player.health = (player.health + 10 > player.maxHealth) ? player.maxHealth : player.health + 10;
    player.stress = (player.stress >= 10) ? player.stress - 10 : 0;
    currentDay++;
    if (currentDay > 30)
    {
        currentDay = 1;
        currentMonth++;
        if (currentMonth > 12)
        {
            currentMonth = 1;
            player.semester++;
        }
    }
    printf("Sleep success! Energy increased, stress decreased.\n");
    printf("It's now day %d of month %d, semester %d.\n", currentDay, currentMonth, player.semester);
}

void printStatus()
{
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
    printf("Exam preparation : %d\n", player.exam_prep);
}

void addQuest(const char *questName, const char *questDescription, int expReward)
{
    if (questLog.count < MAX_QUESTS)
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
    if (questLog.count == 0)
    {
        printf("You have no active quests.\n");
    }
    else
    {
        for (int i = 0; i < questLog.count; i++)
        {
            printf("%d. %s: %s\n", i + 1, questLog.quests[i].name, questLog.quests[i].completed ? "Completed" : "In Progress");
            printf("Description: %s\n", questLog.quests[i].description);
        }
    }
}

void manageFinances()
{
    char input[20];
    printf("\n=== Financial Management ===\n");
    printf("Current Balance: ₹%d\n", player.money);

    printf("\n1. View Transaction History");
    printf("\n2. Make a Purchase");
    printf("\n3. Add Income");
    printf("\n4. View Budget Analysis");
    printf("\n0. Back\n");
    printf("\nChoice: ");

    fgets(input, sizeof(input), stdin);
    int choice = atoi(input);

    switch (choice)
    {
    case 1:
        printf("\n=== Transaction History ===\n");
        for (int i = 0; i < financialHistory.count; i++)
        {
            printf("%d/%d: ₹%d (%s) - %s\n",
                   financialHistory.transactions[i].day,
                   financialHistory.transactions[i].month,
                   financialHistory.transactions[i].amount,
                   financialHistory.transactions[i].type ? "Income" : "Expense",
                   financialHistory.transactions[i].description);
        }
        break;

    case 2:
    {
        printf("Enter expense amount: ₹");
        fgets(input, sizeof(input), stdin);
        int amount = atoi(input);

        if (amount > player.money)
        {
            printf("Insufficient funds!\n");
            return;
        }

        printf("Enter description: ");
        char desc[MAX_DESCRIPTION_LENGTH];
        fgets(desc, sizeof(desc), stdin);
        desc[strcspn(desc, "\n")] = 0;

        player.money -= amount;

        Transaction t = {0};
        strcpy(t.description, desc);
        t.amount = amount;
        t.type = TRANSACTION_EXPENSE;
        t.day = currentDay;
        t.month = currentMonth;
        financialHistory.transactions[financialHistory.count++] = t;

        printf("Transaction recorded! New balance: ₹%d\n", player.money);
        break;
    }

    case 3:
    {
        printf("Enter income amount: ₹");
        fgets(input, sizeof(input), stdin);
        int amount = atoi(input);

        printf("Enter source: ");
        char desc[MAX_DESCRIPTION_LENGTH];
        fgets(desc, sizeof(desc), stdin);
        desc[strcspn(desc, "\n")] = 0;

        player.money += amount;

        Transaction t = {0};
        strcpy(t.description, desc);
        t.amount = amount;
        t.type = TRANSACTION_INCOME;
        t.day = currentDay;
        t.month = currentMonth;
        financialHistory.transactions[financialHistory.count++] = t;

        printf("Income recorded! New balance: ₹%d\n", player.money);
        break;
    }
    }
}

void initLocations()
{
    // Location 1: Main Academic Block
    strcpy(locations[locationCount].name, "Main Academic Block");
    strcpy(locations[locationCount].description, "The heart of academic life where Professor Pataka roams. Watch out for surprise quizzes!");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = 10;
    locations[locationCount].study_bonus = 20;
    locationCount++;

    // Location 2: Chintu's Canteen
    strcpy(locations[locationCount].name, "Chintu's Canteen");
    strcpy(locations[locationCount].description, "The legendary hangout spot. Best maggi in town and source of valuable information!");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = -10;
    locations[locationCount].study_bonus = -5;
    locationCount++;

    // Location 3: Library
    strcpy(locations[locationCount].name, "Library");
    strcpy(locations[locationCount].description, "A battleground during exams. Prime study spots are highly contested!");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = 5;
    locations[locationCount].study_bonus = 30;
    locationCount++;

    // Location 4: Hostel
    strcpy(locations[locationCount].name, "Hostel");
    strcpy(locations[locationCount].description, "Your safe haven... usually. Watch out for Risky and Misky!");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = -15;
    locations[locationCount].study_bonus = 10;
    locationCount++;

    // Location 5: College Ground
    strcpy(locations[locationCount].name, "College Ground");
    strcpy(locations[locationCount].description, "Where dance battles and cultural events happen. Perfect for socializing!");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = -20;
    locations[locationCount].study_bonus = -10;
    locationCount++;

    // Location 6: Computer Lab
    strcpy(locations[locationCount].name, "Computer Lab");
    strcpy(locations[locationCount].description, "Home of coding battles and technical events. Tamboli's favorite spot.");
    locations[locationCount].unlocked = 1;
    locations[locationCount].stress_modifier = 15;
    locations[locationCount].study_bonus = 25;
    locationCount++;

    // Location 7: Dean's Office (Initially locked)
    strcpy(locations[locationCount].name, "Dean's Office");
    strcpy(locations[locationCount].description, "The final boss arena. Currently locked - need to progress story to access.");
    locations[locationCount].unlocked = 0; // Locked initially
    locations[locationCount].stress_modifier = 30;
    locations[locationCount].study_bonus = 0;
    locationCount++;
}

// Helper function to unlock locations based on story progress
void updateLocationAccess()
{
    // Unlock Dean's Office in Act 4 when corruption is exposed
    if (story.act == 4 && story.corruption_exposed)
    {
        for (int i = 0; i < locationCount; i++)
        {
            if (strcmp(locations[i].name, "Dean's Office") == 0)
            {
                locations[i].unlocked = 1;
                printf("\n=== ALERT: Dean's Office is now accessible! ===\n");
                break;
            }
        }
    }
}

// Updated change location function with proper error handling
void changeLocation()
{
    updateLocationAccess(); // Update available locations based on story progress

    printf("\n=== Available Locations ===\n");
    int availableLocations = 0;
    for (int i = 0; i < locationCount; i++)
    {
        if (locations[i].unlocked)
        {
            availableLocations++;
            printf("%d. %s\n", availableLocations, locations[i].name);
            printf("   %s\n", locations[i].description);
            if (locations[i].study_bonus != 0)
            {
                printf("   Study Bonus: %+d\n", locations[i].study_bonus);
            }
            if (locations[i].stress_modifier != 0)
            {
                printf("   Stress Impact: %+d\n", locations[i].stress_modifier);
            }
            printf("\n");
        }
    }

    if (availableLocations == 0)
    {
        printf("No locations available!\n");
        return;
    }

    printf("\nChoose location (0 to cancel): ");
    char input[10];
    fgets(input, sizeof(input), stdin);
    int choice = atoi(input) - 1;

    if (choice >= 0 && choice < locationCount && locations[choice].unlocked)
    {
        // Story progression checks
        if (strcmp(locations[choice].name, "Library") == 0 && story.act == 3)
        {
            printf("\n=== Library Lockdown Event! ===\n");
            printf("The library is packed with stressed students preparing for exams...\n");

            if (!story.library_secured)
            {
                printf("You'll need to fight for a study spot!\n");
                if (combat("Stressed Senior", 0))
                {
                    story.library_secured = 1;
                    printf("You've secured a prime study spot!\n");
                    player.intelligence += 5;
                    player.exam_prep += 20;
                }
            }
        }

        else if (strcmp(locations[choice].name, "Dean's Office") == 0 &&
                 story.act == 4 && !story.deanDefeated)
        {
            printf("\n=== Final Boss Battle! ===\n");
            printf("The Dean stands before you, ready to defend his corrupt empire!\n");
            if (combat("The Dean", 2))
            { // Debate battle
                story.deanDefeated = 1;
                printf("\nCongratulations! You've defeated the Dean and exposed the corruption!\n");
                printf("You are now a campus legend!\n");
                player.experience += 1000;
                player.money += 5000; // Whistleblower reward
            }
        }

        // Apply location effects
        player.stress += locations[choice].stress_modifier;
        if (player.stress < 0)
            player.stress = 0;
        if (player.stress > 100)
            player.stress = 100;

        printf("\nYou've moved to %s\n", locations[choice].name);
        printf("Stress %s by %d\n",
               locations[choice].stress_modifier > 0 ? "increased" : "decreased",
               abs(locations[choice].stress_modifier));

        // Apply study bonus if studying here
        if (locations[choice].study_bonus != 0)
        {
            printf("Study effectiveness %s by %d%%\n",
                   locations[choice].study_bonus > 0 ? "increased" : "decreased",
                   abs(locations[choice].study_bonus));
        }
    }
    else if (choice != -1)
    {
        printf("Invalid location choice!\n");
    }
}
void socialize()
{
    if (player.energy < 10)
    {
        printf("You're too tired to socialize!\n");
        return;
    }

    printf("\n=== Social Activities ===\n");
    printf("1. Chat with Friends");
    printf("\n2. Join a Club Event");
    printf("\n3. Organize a Study Group");
    printf("\n4. Attend a Party");
    printf("\n0. Back\n");
    printf("\nChoice: ");

    char input[10];
    fgets(input, sizeof(input), stdin);
    int choice = atoi(input);

    switch (choice)
    {
    case 1:
    {
        int chance = rand() % 100;
        player.energy -= 10;

        if (chance < 30)
        {
            printf("\nYou had a great conversation about the upcoming events!\n");
            player.charisma += 2;
            player.stress -= 10;

            // Story progression for Act 2
            if (story.act == 2 && !story.dance_battle_won && player.charisma >= 20)
            {
                printf("\nMisky notices your growing popularity...\n");
                printf("She challenges you to a dance battle!\n");
                if (combat("Misky", 1))
                { // Dance battle
                    story.dance_battle_won = 1;
                    player.dance_skill += 10;
                    printf("You're now the dance champion!\n");
                }
            }
        }
        else if (chance < 60)
        {
            printf("\nYou discover some interesting gossip about the Dean's activities...\n");
            if (!story.corruption_exposed && story.act == 4)
            {
                story.corruption_exposed = 1;
                printf("You've uncovered evidence of corruption!\n");
                player.experience += 300;
            }
        }
        else
        {
            printf("\nYou make a new friend!\n");
            player.charisma += 3;
            player.stress -= 15;
        }
        break;
    }

    case 2:
        if (clubCount > 0)
        {
            printf("\nAvailable Club Events:\n");
            for (int i = 0; i < clubCount; i++)
            {
                if (clubs[i].joined)
                {
                    printf("%d. %s Meeting\n", i + 1, clubs[i].name);
                }
            }
            // Handle club event...
        }
        else
        {
            printf("You haven't joined any clubs yet!\n");
        }
        break;

    case 3:
    {
        printf("\nOrganizing a study group...\n");
        player.energy -= 20;
        player.exam_prep += 15;
        player.intelligence += 2;
        player.charisma += 1;
        printf("The study session was productive!\n");
        printf("Exam Prep +15 | Intelligence +2 | Charisma +1\n");
        break;
    }

    case 4:
    {
        if (player.money < 100)
        {
            printf("You can't afford to attend the party! (Cost: ₹100)\n");
            return;
        }

        printf("\nAttending a college party...\n");
        player.money -= 100;
        player.energy -= 30;
        player.stress -= 25;
        player.charisma += 5;

        int event = rand() % 3;
        switch (event)
        {
        case 0:
            printf("You became the life of the party!\n");
            player.charisma += 3;
            break;
        case 1:
            printf("You networked with seniors and gained valuable advice!\n");
            player.intelligence += 2;
            break;
        case 2:
            printf("You got caught by Professor Pataka!\n");
            player.stress += 20;
            break;
        }
        break;
    }
    }
}

int combat(const char *opponent, int type)
{
    printf("\n=== Battle with %s ===\n", opponent);

    // Type 0: Regular battle
    // Type 1: Dance battle
    // Type 2: Debate battle

    int playerScore = 0;
    int opponentScore = 0;

    switch (type)
    {
    case 0: // Regular battle
        playerScore = player.health + player.energy + (rand() % 20);
        opponentScore = 100 + (rand() % 20);
        break;

    case 1: // Dance battle
        playerScore = player.charisma + story.dance_skill + (rand() % 20);
        opponentScore = 80 + (rand() % 20);
        break;

    case 2: // Debate battle
        playerScore = player.intelligence + player.charisma + (rand() % 20);
        opponentScore = 120 + (rand() % 20);
        break;
    }

    printf("Your score: %d\n", playerScore);
    printf("Opponent score: %d\n", opponentScore);

    if (playerScore > opponentScore)
    {
        printf("You won against %s!\n", opponent);
        player.experience += 50;
        return 1;
    }
    else
    {
        printf("You lost to %s!\n", opponent);
        player.stress += 10;
        return 0;
    }
}

void gameLoop()
{
    char input[20];
    while (1)
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
        fgets(input, sizeof(input), stdin);
        int choice = atoi(input);

        switch (choice)
        {
        case 1:
            printStatus();
            break;
        case 2:
            study();
            break;
        case 3:
            socialize();
            break;
        case 4:
            exercise();
            break;
        case 5:
            eat();
            break;
        case 6:
            mysleep();
            break;

        case 7:
            manageFinances();
            break;
        case 8:
            attendWorkshop();
            break;

        case 9:
            trackExam();
            break;
        case 10:
            joinClub();
            break;
        case 11:
            changeLocation();
            break;
        case 12:
            if (player.energy < 10)
                printf("NOT ENOUGH ENERGY , GET SOME SLEEP OR REST!");
            else
            {
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

int main()
{
    srand(time(NULL));
    initCharacter();
    initLocations();
    addQuest("Complete Assignment", "Submit your assignment by end of week.", 20);
    initClubs();
    addQuest("Meet New Friends", "Increase charisma by socializing.", 10);
    gameLoop();
    return 0;
}
