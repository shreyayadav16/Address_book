/*
Name    : Shreya Rahul Yadav
Date    : 
Batch Id: 

  Address Book Management System
  ------------------------------
  This is a menu-driven C program that helps manage and organize contact details.
  It allows users to create, search, edit, delete, view, and save contacts in a
  structured and user-friendly way.

  Project Highlights:
    - Each contact consists of three fields: Name, Phone Number, and Email ID.
    - Data is stored in memory while the program is running.
    - File handling ensures that contacts are saved into a CSV file and reloaded
      when the program is executed again.
    - Input validation guarantees correct data entry:
        * Name must contain only alphabets/spaces.
        * Phone number must have exactly 10 digits.
        * Email should follow a valid format and end with ".com".
    - Duplicate phone numbers and emails are restricted.

  Core Features:
    1. Add Contact       : Insert a new contact after input validation.
    2. Search Contact    : Locate a contact by Name, Phone, or Email.
    3. Edit Contact      : Modify existing contact information.
    4. Delete Contact    : Permanently remove a contact.
    5. List All Contacts : Display all stored contacts with sorting options
                           (by Name, Phone, or Email).
    6. Save Contacts     : Write all current contacts to a CSV file.
    7. Exit Program      : Exit safely, with the option to save changes.

  Working Mechanism:
    - On startup, the program loads contacts from the CSV file (if available).
    - The user navigates through a simple menu interface.
    - Any changes (add, edit, delete) remain in memory until explicitly saved.
    - The "Save" option permanently writes data to the CSV file.
    - Ensures persistence across program runs.

  File Organization:
    - main.c       : Contains the main menu and user interaction logic.
    - contact.c/h  : Handles add, search, edit, delete, validation, and display.
    - file.c/h     : Handles reading and writing of the "contacts.csv" file.

  Scalability:
    - Modular design makes it easy to add new fields like address, birthday, or notes.
    - Can be extended to include features like import/export, grouping contacts,
      or even a GUI-based interface in the future.

*/


#include <stdio.h>
#include "contact.h"
#include<stdio_ext.h>

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf(" Exiting...\n");
              //  saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                __fpurge(stdin);
        }
    } while (choice != 6);
    
       return 0;
}
