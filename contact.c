#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"
#include "file.h"
//#include <stdio_ext.h">

int indexArr[10];
int Index = 0;

void sortbyName(AddressBook *);
void sortbyPhone(AddressBook *);
void sortbyEmail(AddressBook *);
void print(AddressBook *);

void listContacts(AddressBook *addressBook)
{
	//list all the contacts..
    int ch;
    do
    {
        printf("Sorting Menu:\n");
        printf("1.Sort by Name\n");
        printf("2.Sort by Phone Number\n");
        printf("3.Sort by Email\n");
        printf("4.Print the Contacts\n");
        printf("5.Go to the Privious menu\n");
        printf("------------------------------------------------------\n");
        printf("Enter your Choice\n");
        scanf("%d", &ch);

        switch(ch)
        {
        case 1:
            sortbyName(addressBook);
            break;
        
        case 2:
            sortbyPhone(addressBook);
            break;   

        case 3:
            sortbyEmail(addressBook);
            break;    

        case 4:
            print(addressBook);
            break;

        case 5:
            return;

        default:
            printf("Invalid choice. Please try again.\n");
            __fpurge(stdin);        
        }

    } while (ch != 5);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization (After files)
    saveContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

 int ValidName(char *Name);
 int ValidContact(char *Contact);
 int ValidEmail(char *Email);
 int duplicate(char *str, char ch, AddressBook *addressBook);
 int findContact(AddressBook *addressBook, char *search);

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    
    char Name[30];
    char Contact[15];
    char Email[50];
    int flag, length;

    //name
    do
    {
        flag = 0;
        printf("Enter the name : ");
        scanf(" %[^\n]",Name);
        //printf("%s\n",Name);
        flag = ValidName(Name);
    }while(flag);
    strcpy(addressBook->contacts[addressBook->contactCount].name, Name);


    //NUMBER

    do
    {
        flag = 0;
        printf("Enter the Contact Number : ");
        getchar();
        scanf("%s",Contact);
        
        flag = ValidContact(Contact);
        if (flag == 0)                 // if valid format
        {
            flag = duplicate(Contact, 'C', addressBook); // now check duplicate

        }

    } while (flag);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, Contact);


    //EMAIL

    do
    {
        flag = 0;
            printf("Enter the Email id:");
            getchar();
            scanf("%s",Email);
            flag =ValidEmail(Email);

            if(flag==0)
            {
                flag = duplicate(Email,'E', addressBook);
            } 

    } while (flag);
     strcpy(addressBook->contacts[addressBook->contactCount].email, Email);
        
        addressBook->contactCount++;
}
void searchByName(AddressBook *addressbook);
void searchByContact(AddressBook *addressbook);
void searchByEmail(AddressBook *addressbook);

void searchContact(AddressBook *addressBook)
{
    /* Define the logic to search a Contacts */  
    int choice;
    do{
        printf("Searching Menu\n");
        printf("1.Search by Name\n");
        printf("2.Search by Phone");
        printf("3.Search by Email\n");
        printf("4.Go Back to Previous menu\n");
        printf("Enter Your Choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: 
                searchByName(addressBook);
                break;

            case 2:
                searchByContact(addressBook);
                break;

            case 3:
                searchByEmail(addressBook);
                break;

            case 4:
                return ;

            default:
            
                printf("Invalid choice! Please Enter valid Choice\n");
                __fpurge(stdin);

        }
    } while (choice !=4 );

}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    if(addressBook->contactCount == 0)
    {
        printf("No contacts available to edit.\n");
        return;
    }
    char search[50];
    printf("Enter Name/Phone/Email of the contact to edit: ");
    scanf(" %[^\n]", search);

    int indexArr[100]; //to store all matching indexes
    int matchCount = 0;

    //Find all matching contacts
    for(int i=0; i<addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0 ||
            strcmp(addressBook->contacts[i].phone, search) == 0 ||
            strcmp(addressBook->contacts[i].email, search) == 0)
        
        {
            indexArr[matchCount] = i;
            printf("%d) Name: %s | Phone: %s | Email: %s\n",
                   matchCount + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            matchCount++;
        }
    }
    if (matchCount == 0)
    {
        printf("Contact not found!\n");
        return;
    }
    int serialChoice;
    printf("Enter the Serial Number of the contact to edit: ");
    scanf("%d", &serialChoice);

    if (serialChoice <= 0 || serialChoice > matchCount)
    {
        printf("Invalid Serial Number!\n");
        return;
    }
    int index = indexArr[serialChoice - 1];  // actual index in contacts[]

    int choice, flag;
    char newValue[50];

    do
    {
        printf("\n--- Edit Menu ---\n");
        printf("1. Edit Name\n");
        printf("2. Edit Contact\n");
        printf("3. Edit Email\n");
        printf("4. Exit Editing\n");
        printf("Enter your choice");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1: // Edit Name
            do
            {
                flag = 0;
                printf("Enter new Name: ");
                scanf(" %[^\n]", newValue);
                flag = ValidName(newValue);
                if (flag == 0)
                    flag = duplicate(newValue, 'N', addressBook);
            } while (flag);
            strcpy(addressBook->contacts[index].name, newValue);
            printf("Name updated successfully!\n");
            break;

        case 2: // Edit Contact
            do
            {
                flag = 0;
                printf("Enter new Contact Number: ");
                scanf("%s", newValue);
                flag = ValidContact(newValue);
                if (flag == 0)
                    flag = duplicate(newValue, 'C', addressBook);
            } while (flag);
            strcpy(addressBook->contacts[index].phone, newValue);
            printf("Contact Number updated successfully!\n");
            break;

        case 3: // Edit Email
            do
            {
                flag = 0;
                printf("Enter new Email: ");
                scanf("%s", newValue);
                flag = ValidEmail(newValue);
                if (flag == 0)
                    flag = duplicate(newValue, 'E', addressBook);
            } while (flag);
            strcpy(addressBook->contacts[index].email, newValue);
            printf("Email updated successfully!\n");
            break;

        case 4:
            printf("Exiting edit menu.\n");
            break;
            default:
            printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);
}
    

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to delete.\n");
        return;
    }

    char search[50];
    printf("Enter Name/Phone/Email of the contact to delete: ");
    scanf(" %[^\n]", search);

    int deleteIndex = -1;

    // Find first match
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0 ||
            strcmp(addressBook->contacts[i].phone, search) == 0 ||
            strcmp(addressBook->contacts[i].email, search) == 0)
        {
            deleteIndex = i;
            break;  // stop at first match
        }
    }

    if (deleteIndex == -1)
    {
        printf("Contact not found!\n");
        return;
    }

    // Shift contacts left
    for (int j = deleteIndex; j < addressBook->contactCount - 1; j++)
    {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}


//Name Function
int ValidName(char *Name)
    {
        int i = 0;
        while(Name[i] != '\0')
        {
        if(!((Name[i] >= 'A' && Name[i] <= 'Z') ||  (Name[i] >= 'a' && Name[i] <= 'z') ||  (Name[i] == ' ')))
        {
            printf("Error : Enter the Valid Name\n");
            return 1;
        }
        i++;
    }
        return 0;

    }

    //Number Function 

    int ValidContact(char *Contact)
    {
        int i = 0, len = strlen(Contact);

        if (len != 10) // phone number should be 10 digits
        {
            printf("Error : Phone number must be 10 digits long\n");
            return 1;
        }

        while (Contact[i] != '\0')
        {
             if (!(Contact[i] >= '0' && Contact[i] <= '9'))
            {
                printf("Error : Phone number must contain only digits\n");
                return 1;
            }
            i++;
        }

        return 0; // valid
    }

    //EMAIL Funnction
int ValidEmail(char *Email)
{
    int i = 0, atPos = -1, dotPos = -1;
    int atCount = 0;

    while (Email[i] != '\0')
    {
        if (Email[i] == ' ')
        {
            printf("Error : Email must not contain spaces\n");
            return 1;
        }

        if (Email[i] == '@')
        {
            atCount++;
            atPos = i;
        }

        if (Email[i] == '.')
        {
            dotPos = i;
        }

        i++;
    }

    // must contain exactly one @
    if (atCount != 1)
    {
        printf("Error : Email must contain exactly one '@'\n");
        return 1;
    }

    // @ must not be first or last character
    if (atPos == 0 || atPos == i - 1)
    {
        printf("Error : Invalid position of '@'\n");
        return 1;
    }

    // there must be a dot after @
    if (dotPos == -1 || dotPos < atPos)
    {
        printf("Error : Email must contain a '.' after '@'\n");
        return 1;
    }

    // domain must be at least 2 characters after last dot
    if ((i - dotPos) < 3)
    {
        printf("Error : Domain must have at least 2 characters after '.'\n");
        return 1;
    }

    //  must end with ".com"
    if (i < 4 || strcmp(Email + i - 4, ".com") != 0)
    {
        printf("Error : Email must end with '.com'\n");
        return 1;
    }

    return 0; // valid
}


int duplicate(char *str, char ch, AddressBook *addressBook)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *field = NULL;

        if (ch == 'N')
            field = addressBook->contacts[i].name;
        else if (ch == 'C')
            field = addressBook->contacts[i].phone;
        else if (ch == 'E')
            field = addressBook->contacts[i].email;

        if (field != NULL && strcmp(field, str) == 0)
        {
            if (ch == 'N')
                printf("Error: Name is already present, please enter a unique Name.\n");
            else if (ch == 'C')
                printf("Error: Contact Number is already present, please enter a unique Contact Number.\n");
            else if (ch == 'E')
                printf("Error: Email is already present, please enter a unique Email.\n");

            return 1; // duplicate found
        }
    }

    return 0; // no duplicate
}

void sortbyName(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    // printf("contact count = %d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            // printf("ret =%d\n",ret);
            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}

void sortbyPhone(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    // printf("contact count = %d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);

            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}

void sortbyEmail(AddressBook *addressBook)
{
    Contact temp;
    int ret;
    // printf("contact count = %d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            ret = strcasecmp(addressBook->contacts[i].email, addressBook->contacts[j].email);

            if (ret > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
}
void print(AddressBook *addressBook)
{

    printf("Serial No");
    printf("                  Name             ");
    printf("       Contact Number        ");
    printf("            Email             ");
    printf("\n---------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d", i + 1);
        printf("%30s", addressBook->contacts[i].name);
        printf("%30s", addressBook->contacts[i].phone);
        printf("%30s", addressBook->contacts[i].email);
        printf("\n-------------------------------------------------------------------------------------------------\n");
    }
}


//Searching the name
void searchByName(AddressBook *addressBook)
{
    char name[30];
    int found = 0;

    printf("Enter Name to search: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            printf("Found Contact:\n");
            printf("Name: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
        printf("No contact found with Name: %s\n", name);
}

void searchByContact(AddressBook *addressBook)
{
    char phone[15];
    int found = 0;

    printf("Enter Phone to search: ");
    scanf("%s", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("Found Contact:\n");
            printf("Name: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
        printf("No contact found with Phone: %s\n", phone);
}

void searchByEmail(AddressBook *addressBook)
{
    char email[50];
    int found = 0;

    printf("Enter Email to search: ");
    scanf("%s", email);

    for (int i = 0; i < addressBook->contactCount; i++)
    
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("Found Contact:\n");
            printf("Name: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
        printf("No contact found with Email: %s\n", email);

        
}
// Edit Contact
int findContact(AddressBook *addressBook, char *search)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0 ||
            strcmp(addressBook->contacts[i].phone, search) == 0 ||
            strcmp(addressBook->contacts[i].email, search) == 0)
        {
            return i; // return index of found contact
        }
    }
    return -1; // not found
}


