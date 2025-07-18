
#include "contact.h"

int main() 
{
    int choice;

    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    printf("\033[0m╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("                                                               \033[0;32mAddress Book Menu    \n");
    printf("\033[0m╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");

    do 
    {  
	printf(" 1.Create contact\n");
	printf(" 2.Search contact\n");
	printf(" 3.Edit contact\n");
	printf(" 4.Delete contact\n");
	printf(" 5.List all contacts\n");
	printf(" 6.Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
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
		printf("\033[0;32mSaving \033[0mand \033[0;31mExiting...\n");
		saveContactsToFile(&addressBook);
		break;
	    default:
		printf("Invalid choice,please try again.\n");
	}
    } while (choice != 6);

    return 0;
}


