#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

int validate_Phonenumber(char *temp, AddressBook *addressBook);
int validate_Email(char *temp , AddressBook *addressBook);
void search_by_name(AddressBook *addressBook);
void search_by_phonenumber(AddressBook *addressBook);
void search_by_email(AddressBook *addressBook);

// Initialize the address book and load contacts from file
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); 
}

// List all contacts in the address book
void listContacts(AddressBook *addressBook)
{
 printf("\n═══════════════════════════════════════════════════════════════════════════════════\n");
 printf("   ID     Name                 Phone                 Email\n");
 printf("═══════════════════════════════════════════════════════════════════════════════════\n");

 for (int i = 0; i < addressBook->contactCount; i++)
 {
    printf("  %-6d %-20s %-20s %-30s\n",
           i + 1,
           addressBook->contacts[i].name,
           addressBook->contacts[i].phone,
   	   addressBook->contacts[i].email);
 }
 printf("═══════════════════════════════════════════════════════════════════════════════════\n\n");
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// Create a new contact in the address book
void createContact(AddressBook *addressBook)
{
    // Check if the address book is full
    if( addressBook->contactCount >= MAX_CONTACTS)
    {
      printf("Addressbook was full.");
      return ;
    }

    int index = addressBook->contactCount;                                       
    printf("\nEnter the contact name: "); // Read contact name
    scanf(" %[^\n]", addressBook->contacts[index].name);

    printf("Enter the phonenumber: "); // Read and validate phone number
    int validation1;
    char temp1[50];
    do
    {
     scanf(" %[^\n]", temp1);
     validation1 = validate_Phonenumber(temp1, addressBook);
     switch(validation1)
     {
      case 1:
       printf("Error: Phone number must contain exactly 10 digits.\n");
       break;
      case 2:
       printf("Error: Phone number must contain digits only.\n");
       break;
      case 3:
       printf("Error: This phone number is already present.\n");
       break;
      case 4:
       strcpy( addressBook->contacts[index].phone, temp1);

     }
    }while(validation1 != 4);

    printf("Enter the email: "); // Read and validate email
    int validation2;
    char temp2[50];
    do
    {
     scanf(" %[^\n]", temp2);
     validation2 = validate_Email(temp2, addressBook);
     switch(validation2)
     {
      case 1:
       printf("Error: Email is too short. It must be more than 5 characters.\n");
       break;
      case 2:
       printf("Error: Email must contain the '@' symbol.\n");
       break;
      case 3:
       printf("Error: Email must end with '.com'.\n");
       break;
      case 4:
       printf("Error: Email must contain only lowercase letters and digits.\n");
       break;
      case 5:
        printf("Error: This email already exists in the address book.\n");
        break;
      case 6:
       strcpy(addressBook->contacts[index].email, temp2);
       break;
     }
    }while(validation2 != 6);

    printf("\033[1;32m✓ Contact created successfully.\033[0m\n\n");
    
    addressBook->contactCount++ ; // Increase the contact count
 }

int validate_Phonenumber(char *temp, AddressBook *addressBook)
{
   int i;
 
   // Check if the phone number has exactly 10 digits
   if(strlen(temp) != 10)
   {
      return 1;
   }
   
   // Check if all characters are digits
   for (int i = 0; i < 10; i++) 
   {
        if(!isdigit(temp[i]))
        return 2; 
   }

   // Check for duplicates in the existing contact list
   if(addressBook->contactCount>0)
   {
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(temp, addressBook->contacts[i].phone) == 0)
        return 3; 
    }
    return 4;
   }
   return 4;
}
int validate_Email(char *temp, AddressBook *addressBook)
{
    int len = strlen(temp);

    // Check if the email has atleast 5 character
    if (len <= 5)
    {
        return 1; 
    }

    // Check if the email has '@' character
    if (strchr(temp, '@') == NULL)
    {
        return 2; 
    }
     
    // Check if the email has ".com"
    if (len < 4 || strcmp(&temp[len - 4], ".com") != 0)
    {
        return 3; 
    }

    // Check for invalid characters (only lowercase letters, digits, '.', '@' allowed)
    for (int i = 0; i < len; i++)
    {
      char ch = temp[i];
      if (!((ch >= 'a' && ch <= 'z') || isdigit(ch)|| ch=='.'|| ch =='@'))
      {
        return 4;
      } 
    }

    // Check for duplicate email in the address book
    if(addressBook->contactCount>0)
    {
       for (int i = 0; i < addressBook->contactCount; i++)
       {
        if(strcmp(temp, addressBook->contacts[i].email) == 0)
        return 5;
       }
      return 6;
    }
    return 6;
}

// Function to search contact by name, phone number, or email
void searchContact(AddressBook *addressBook) 
{
  int option;
  printf("Choose your option: \n  1.Search by name\n  2.Search by phonenumber\n  3.Search by emailid\n");
  printf("Select your option: ");
  scanf("%d", &option);

  // Call the appropriate search function based on user choice
  if(option == 1)
  {
    search_by_name(addressBook);
  }
  else if(option == 2)
  {
    search_by_phonenumber(addressBook);
  }
  else if(option == 3)
  {
    search_by_email(addressBook);
  }
  else
  {
    printf("Invalid option");
  }
}

// Function to search for a contact by name
void search_by_name(AddressBook *addressBook)
{
  char temp[50];
  int found=0;

  printf("Enter the name: ");

  // Loop through the contacts to find a match
  scanf(" %[^\n]", temp);
  for(int i=0;i<addressBook->contactCount;i++)
  {
      if(strcmp(addressBook->contacts[i].name, temp) == 0)
      {
	    printf("\n\033[0m---------------------------\033[0m\n");
            printf("\033[1;32mName :\033[0m  %s\n", addressBook->contacts[i].name);
            printf("\033[1;32mPhone:\033[0m  %s\n", addressBook->contacts[i].phone);
            printf("\033[1;32mEmail:\033[0m  %s\n", addressBook->contacts[i].email);
            printf("\033[0m---------------------------\033[0m\n\n");
	    found=1;
      } 
  }
  if(!found)
  {
    printf("\033[0;31m✗ Contact not Found\033[0m\n\n");
  }
}

// Function to search for a contact by phone number
void search_by_phonenumber(AddressBook *addressBook)
{
  char temp[50];
  int found=0;
  printf("Enter the phonenumber: ");
  scanf(" %[^\n]", temp);

  // Validate the entered phone number
  int res= validate_Phonenumber(temp, addressBook);
  if(res == 4 || res == 3  )
  {
   // Loop through contacts to find a matching phone number 
   for(int i=0;i<addressBook->contactCount;i++)
   {
      if(strcmp(addressBook->contacts[i].phone, temp) == 0)
      {
            printf("\n\033[0m---------------------------\033[0m\n");
            printf("\033[1;32mName :\033[0m  %s\n", addressBook->contacts[i].name);
            printf("\033[1;32mPhone:\033[0m  %s\n", addressBook->contacts[i].phone);
            printf("\033[1;32mEmail:\033[0m  %s\n", addressBook->contacts[i].email);
            printf("\033[0m---------------------------\033[0m\n\n");
	    found=1;
      }
   }
   if(!found)
   {
    printf("\033[0;31m✗ Contact not Found\033[0m\n\n");
   }
  }
  else
  {
    printf("Enter valid phonenumber.\n\n");
  }
}

// Function to search a contact by email in the address book
void search_by_email(AddressBook *addressBook)
{
  char temp[50];
  int found=0;
  printf("Enter the email: ");
  scanf(" %[^\n]", temp);

   // Validate the entered email format
  int res= validate_Email(temp, addressBook);
  if(res == 6)
  {
   // Compare input email with stored contact email
   for(int i=0;i<addressBook->contactCount;i++)
   {
      if(strcmp(addressBook->contacts[i].email, temp) == 0)
      {
            printf("\n\033[0m---------------------------\033[0m\n");
            printf("\033[1;32mName :\033[0m  %s\n", addressBook->contacts[i].name);
            printf("\033[1;32mPhone:\033[0m  %s\n", addressBook->contacts[i].phone);
            printf("\033[1;32mEmail:\033[0m  %s\n", addressBook->contacts[i].email);
            printf("\033[0m---------------------------\033[0m\n\n");
            found =1;
     }
   }
   if(!found)
   {
    printf("\033[0;31m✗ Contact not Found\033[0m\n\n");
   }
  }
  else
  {
    printf("Enter valid email.\n\n");
  }
}

// Function to edit a contact in the address book based on user's choice
void editContact(AddressBook *addressBook)
{
    int choice;
    char temp[50];
    int found = 0;

    printf("Edit contact by:\n");
    printf("1.Name\n");
    printf("2.Phone Number\n");
    printf("3.Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the name of the contact to edit: ");
            scanf(" %[^\n]", temp);
            break;
        case 2:
            printf("Enter the phone number of the contact to edit: ");
            scanf(" %[^\n]", temp);
            break;
        case 3:
            printf("Enter the email ID of the contact to edit: ");
            scanf(" %[^\n]", temp);
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    // Search for the contact based on selected field
    for (int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;

        if (choice == 1 && strcmp(addressBook->contacts[i].name, temp) == 0)
       	{
            match = 1;
        }
       	else if (choice == 2 && strcmp(addressBook->contacts[i].phone, temp) == 0)
       	{
            match = 1;
        }
       	else if (choice == 3 && strcmp(addressBook->contacts[i].email, temp) == 0)
       	{
            match = 1;
        }

	// If a matching contact is found
        if (match)
       	{
            found = 1;
            int option;
            printf("\nContact found: \n");
            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);

            printf("\nWhich field do you want to edit?\n");
            printf(" 1.Name\n");
            printf(" 2.Phone\n");
            printf(" 3.Email\n");
            printf(" 4.All\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) 
	    {
                case 1:
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[i].name);
                    break;
                case 2:
                    printf("Enter new phone: ");
                    scanf(" %[^\n]", addressBook->contacts[i].phone);
                    break;
                case 3:
                    printf("Enter new email: ");
                    scanf(" %[^\n]", addressBook->contacts[i].email);
                    break;
                case 4:
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[i].name);
                    printf("Enter new phone: ");
                    scanf(" %[^\n]", addressBook->contacts[i].phone);
                    printf("Enter new email: ");
                    scanf(" %[^\n]", addressBook->contacts[i].email);
                    break;
                default:
                    printf("Invalid choice.\n");
                    return;
            }

	    printf("\033[0;32m✓ Contact updated successfully!\033[0m\n\n");
            break;
        }
    }

    if (!found) 
    {
        printf("\033[0;31m✗ Contact not Found\033[0m\n\n");
    }
}

// Function to delete a contact from the address book based on user selection
void deleteContact(AddressBook *addressBook)
{
    int option;
    char temp[50];
    int found = 0;

    printf("Delete contact by:\n");
    printf(" 1.Name\n");
    printf(" 2.Phone Number\n");
    printf(" 3.Email\n");
    printf("Select your option: ");
    scanf("%d", &option);

    // Get corresponding input value based on chosen option
    switch (option) {
        case 1:
            printf("Enter name to delete: ");
            break;
        case 2:
            printf("Enter phone number to delete: ");
            break;
        case 3:
            printf("Enter email to delete: ");
            break;
        default:
            printf("Invalid option\n");
            return;
    }
    scanf(" %[^\n]", temp);
   
    // Search for the matching contact
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        int match = 0;

	// Match based on selected field
        if (option == 1 && strcmp(addressBook->contacts[i].name, temp) == 0)
            match = 1;
        else if (option == 2 && strcmp(addressBook->contacts[i].phone, temp) == 0)
            match = 1;
        else if (option == 3 && strcmp(addressBook->contacts[i].email, temp) == 0)
            match = 1;

	// If a matching contact is found
        if (match)
        {
            found = 1;

	    // Shift all contacts after the matched one to fill the gap
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

	    // Decrease the contact count
            addressBook->contactCount--;
            printf("\033[0;32m✓ Contact deleted successfully!\033[0m\n\n");
            break;
        }
    }

    if (!found)
    {
       printf("\033[0;31m✗ Contact not Found\033[0m\n\n");
    }
}



