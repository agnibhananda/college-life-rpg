#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_NAME_LENGTH 50
#define MAX_INVENTORY 10
#define MAX_QUESTS 5

typedef struct{
    char name[MAX_NAME_LENGTH];
    int health;
    int maxhealth;
    int attack;
    int defense;
    int experience;
    int level;
}Character;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
}Item;

typedef struct{
    Item items[MAX_INVENTORY];
    int count;
}Inventory;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    char description[100];
    int completed;
}Quest;

typedef struct{
    Quest quests[MAX_QUESTS];
    int count;
}QuestLog;

Character player;
Inventory inventory;
QuestLog questLog;

void initCharacter(){
    printf("What is your name: ");
    fgets(player.name, MAX_NAME_LENGTH, stdin);
    player.name[strcspn(player.name,"\n")] = 0;
    player.health =100;
    player.maxhealth= 100;
    player.attack = 5;
    player.defense = 2;
    player.experience= 0;
    player.level =1;
}

void printStatus(){
    printf("\n----- Character Status -----\n");
    printf("Name:%s\n", player.name);
    printf("Health:%d/%d\n",player.health, player.maxhealth);
    printf("Attack:%d\n",player.attack);
    printf("Defense:%d\n",player.defense);
    printf("Experience:%d\n",player.experience);
    printf("Level:%d\n",player.level);
}

void addItem(const char*itemName){
    if(inventory.count < MAX_INVENTORY){
        for(int i = 0; i < inventory.count; i++){
            if(strcmp(inventory.items[i].name, itemName) == 0)
                {
                inventory.items[i].quantity++;
                printf("Added %s to  the inventory.\n", itemName);
                return;
            }
        }
        strcpy(inventory.items[inventory.count].name,itemName);
        inventory.items[inventory.count].quantity= 1;
        inventory.count++;
        printf("Added %s to the inventory.\n",itemName);
    }else{
        printf("Inventory is full!\n");
    }
}

void printInventory(){
    printf("\n----- Inventory -----\n");
    if(inventory.count== 0) {
        printf("Your inventory is empty.\n");
    }else{
        for(int i = 0;i<inventory.count;i++) {
            printf("%s x%d\n",inventory.items[i].name,inventory.items[i].quantity);
        }
    }
}

void addQuest(const char* questName, const char* questDescription){
    if(questLog.count < MAX_QUESTS){
        strcpy(questLog.quests[questLog.count].name, questName);
        strcpy(questLog.quests[questLog.count].description, questDescription);
        questLog.quests[questLog.count].completed = 0;
        questLog.count++;
        printf("New quest added: %s\n", questName);
    }else{
        printf("Quest log is full!\n");
    }
}

void printQuests(){
    printf("\n---- Quest Log ----\n");
    if(questLog.count == 0) {
        printf("You have no active quests.\n");
    }else{
        for(int i = 0; i <questLog.count; i++) {
            printf("%s: %s\n",questLog.quests[i].name, questLog.quests[i].completed ? "Completed" : "In Progress");
            printf("%s\n",questLog.quests[i].description);
        }
    }
}

void explore(){
    printf("\nYou explore the area...\n");
    int event = rand() % 3;
    switch (event){
        case 0:
            printf("You find a wild Amogh!\n");
            addItem("Amoghus");
            break;
        case 1:
            printf("You encounter a weak enemy and defeat it!\n");
            player.experience += 10;
            printf("You gained 10 experience points.\n");
            break;
        case 2:
            printf("You find nothing of interest.\n");
            break;
    }
}

void gameLoop(){
    char input[20];
    while(42){
        printf("\nWhat would you like to do? (status/inventory/quests/explore/quit): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input,"\n")] = 0;

        if(strcmp(input, "status") == 0){
            printStatus();
        }
        else if(strcmp(input,"inventory") == 0){
            printInventory();
        }else if(strcmp(input, "quests") == 0){
            printQuests();
        }else if(strcmp(input, "explore") == 0){
            explore();
        }else if(strcmp(input, "quit") == 0){
            printf("Thanks for playing! Goodbye.\n");
            break;
        }else{
            printf("Please enter a valid command\n");
        }
}
    }


int main() {
    srand(time(NULL));
    initCharacter();
    addQuest("Survive JIIT", "Defeat the dark wizard who can't be named and save JIIT.");
    printf("Welcome, %s, to the land of JIIT!\n",player.name);
    gameLoop();
    return 0;
}
