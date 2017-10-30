#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Entry {
    char lastName[31];
    char firstName[31];
    char pnoneNumber[12];
    struct Entry *next;
};
struct Entry *head, *tail;

void input();
void search();
void list();
void help();
void del(struct Entry **);
void store(struct Entry *i, struct Entry **head, struct Entry **tail);
void display(struct Entry *);
int  menu_select(); struct Entry *find(char *s);

int main()
{
    head = tail = NULL;
      for(;;)
      {
        switch(menu_select()) {
          case 1:  input();
            break;
          case 2: ; del(&head);
            break;
          case 3: ; list();
            break;
          case 4: ; search();
          break;
          case 5: return 0;
        }
      }
      return 0;
}

int  menu_select(void)
{
    int answer;
    printf(" \t\t\t Menu:\n");
    printf("\n1. Add contact\n");
    printf("2. Delete contact\n");
    printf("3. Display all entries\n");
    printf("4. Search entry\n");
    printf("5. Exit\n");
    do
    {
        printf("\nYour entered: ");
        answer = getchar() - '0';
    }
    while(answer < 0 || answer > 5);
    return answer;
}

void input()
{
    struct Entry *entry;
    for(;;) {
        entry = (struct Entry *)malloc(sizeof(struct Entry));
        if(!entry) {
            printf("\nError!");
            return;
        }
        if( (getchar()-'0') == 0) break;

        printf("Input last name: ");
        scanf("%s",entry->lastName);

        printf("Input first name: ");
        scanf("%s",entry->firstName);

        printf("Input phone number: ");
        scanf("%s",entry->pnoneNumber);

        printf("Press 0 for exit\n");
        int c = getchar() - '0';
        if (c == 0) break;

        store(entry, &head, &tail);
    }
}


void store(struct Entry *entry, struct Entry **head, struct Entry **tail)
{
    struct Entry *old, *current;
    current = *head;
    if(!*tail) {
        entry->next = NULL;
        *tail = entry;
        *head = entry;
        return;
    }

    old = NULL;
    while(current) {
        if(current->pnoneNumber < entry->pnoneNumber) {
            old = current;
            current = current->next;
        }
        else {
            if(old) {
                old->next = entry;
                entry->next = current;
                return;
            }
            entry->next = current;
            *head = entry;
            return;
        }
    }
    (*tail)->next = entry;
    entry->next = NULL;
    *tail = entry;
}

void del(struct Entry **head)
{
    struct Entry *entry;
    struct Entry *current=*head;

    char lastName[40];
    printf("Input last name: ");
    scanf("%s", lastName);
    entry = find(lastName);

    if (entry !=0 && entry!=*head) {
        while (current->next!=entry) {
            current=current->next;
        }
        current->next=entry->next;
        free(entry);
    }
    else if (entry==*head) {
        *head=(*head)->next;
        free(entry);
    }
    printf("Entry is deleted\n");
}

struct Entry *find(char *lastName)
{
    struct Entry *entry;
    printf("\nYour find phone number of: %s\n",lastName);
    entry = head;
    while(entry) {
        if( strcmp(lastName,entry->lastName) == 0)
            return entry;
        entry = entry->next;
    }
    printf("Phone number not found.\n\n");
    return NULL;
}

void list()
{
    struct Entry *entry;
    entry = head;
    printf("\t\tPhone entries:\n");
    while(entry) {
        display(entry);
        entry = entry->next;
    }
    printf("\n");
}

void display(struct Entry *entry)
{
    printf(" Last name: %s\n", entry->lastName);
    printf(" First name: %s\n", entry->firstName);
    printf(" Phone number: %s\n\n", entry->pnoneNumber);
}

void search()
{
  struct Entry *entry;
  char lastName[40];
  printf("Input last name: ");
  scanf("%s",lastName);
  entry = find(lastName);
  entry ? display(entry) : printf("Entry not found\n");
}
