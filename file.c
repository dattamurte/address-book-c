#include <stdio.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
{ 
  FILE *fp;
  fp = fopen("contacts.txt", "w");
  
  if(fp==NULL)
  {
    printf("Error. Couldn't open file foer writing\n");
    return;
  }

  fprintf(fp, "%d\n", addressBook -> contactCount);

  for(int i=0; i<addressBook -> contactCount; i++)
  {
    fprintf(fp, "%s,%s,%s\n", addressBook -> contacts[i].name, addressBook ->contacts[i].phone, addressBook -> contacts[i].email);
  }

  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
  FILE *fp;
  fp= fopen("contacts.txt", "r");

  if(fp==NULL)
  {
    printf("Files not found. Starting empty with address book\n");
    addressBook -> contactCount=0;
    return;
  }


  fscanf(fp, "%d\n", &addressBook -> contactCount);
  
  if(addressBook -> contactCount > MAX_CONTACTS)
  {
    addressBook -> contactCount = MAX_CONTACTS;
  }

  for(int i=0; i<addressBook -> contactCount; i++)
  {
    fscanf(fp, "%[^,],%[^,],%[^\n]\n", addressBook -> contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
  }
    
  fclose(fp);
}  