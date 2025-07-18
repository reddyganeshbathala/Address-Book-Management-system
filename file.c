#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
 FILE *fp;
 fp = fopen("contact.csv","w");
 if(fp == NULL)
 {
   perror("Error");
   return;
 } 
 int i;
 for(i=0;i<addressBook->contactCount;i++)
 {
   fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
 }
 fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook)
{
 FILE *fp;
 fp = fopen("contact.csv","r");
 if(fp == NULL)
 {
   perror("Error");
   return;
 }
 fscanf(fp,"#%d\n",&addressBook->contactCount);
 int i;
 for(i=0;i<addressBook->contactCount;i++)
 {
    fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
 }
 fclose(fp);   
}


