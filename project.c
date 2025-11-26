#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define NAME 50
#define ADDR 100
#define FILE_NAME "citizens.dat"

typedef struct {
    int id;
    char name[NAME];
    int age;
    char address[ADDR];
    char phone[20];
} Citizen;

Citizen list[MAX];
int count = 0, nextId = 1;

void save() {
    FILE *f = fopen(FILE_NAME, "wb");
    if (!f) { printf("Error saving!\n"); return; }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(&nextId, sizeof(int), 1, f);
    fwrite(list, sizeof(Citizen), count, f);
    fclose(f);
    printf("Data saved.\n");
}

void load() {
    FILE *f = fopen(FILE_NAME, "rb");
    if (!f) return;
    fread(&count, sizeof(int), 1, f);
    fread(&nextId, sizeof(int), 1, f);
    fread(list, sizeof(Citizen), count, f);
    fclose(f);
}

void addCitizen() {
    if (count >= MAX) { printf("Storage full!\n"); return; }
    Citizen c;
    c.id = nextId++;

    printf("Enter name: ");
    fgets(c.name, NAME, stdin);
    c.name[strcspn(c.name, "\n")] = 0;

    printf("Enter age: ");
    scanf("%d", &c.age); while(getchar()!='\n');

    printf("Enter address: ");
    fgets(c.address, ADDR, stdin);
    c.address[strcspn(c.address, "\n")] = 0;

    printf("Enter phone: ");
    fgets(c.phone, 20, stdin);
    c.phone[strcspn(c.phone, "\n")] = 0;

    list[count++] = c;
    printf("Citizen added with ID %d\n", c.id);
}

void listCitizens() {
    if (count == 0) { printf("No records.\n"); return; }
    printf("\nID  Name               Age  Phone\n--------------------------------------\n");
    for (int i=0; i<count; i++)
        printf("%-3d %-18s %-4d %s\n",
               list[i].id, list[i].name, list[i].age, list[i].phone);
}

int findIndex(int id) {
    for (int i=0; i<count; i++)
        if (list[i].id == id) return i;
    return -1;
}

void viewCitizen() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id); while(getchar()!='\n');

    int i = findIndex(id);
    if (i < 0) { printf("Not found!\n"); return; }

    Citizen c = list[i];
    printf("\nID: %d\nName: %s\nAge: %d\nAddress: %s\nPhone: %s\n",
           c.id, c.name, c.age, c.address, c.phone);
}

void deleteCitizen() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id); while(getchar()!='\n');

    int i = findIndex(id);
    if (i < 0) { printf("Not found!\n"); return; }

    for (int j=i; j<count-1; j++)
        list[j] = list[j+1];
    count--;

    printf("Record deleted.\n");
}

void searchCitizen() {
    char key[NAME];
    printf("Enter name keyword: ");
    fgets(key, NAME, stdin);
    key[strcspn(key, "\n")] = 0;

    int found = 0;
    printf("\nResults:\n");
    for (int i=0; i<count; i++) {
        if (strstr(list[i].name, key)) {
            printf("%d - %s (%d)\n", list[i].id, list[i].name, list[i].age);
            found = 1;
        }
    }
    if (!found) printf("No match found.\n");
}

int main() {
    load();
    while (1) {
        int ch;
        printf("\n--- Citizen Records System ---\n");
        printf("1. Add\n2. List\n3. View\n4. Search\n5. Delete\n6. Save\n0. Exit\nChoice: ");
        scanf("%d", &ch); while(getchar()!='\n');

        switch(ch) {
            case 1: addCitizen(); break;
            case 2: listCitizens(); break;
            case 3: viewCitizen(); break;
            case 4: searchCitizen(); break;
            case 5: deleteCitizen(); break;
            case 6: save(); break;
            case 0: save(); printf("Bye!\n"); return 0;
            default: printf("Invalid!\n");
        }
    }
}
