#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"

 void sortContacts(AddressBook *addressBook, int sortCriteria)
{
  for(int i=0; i<addressBook ->contactCount-1; i++)
  {
    for(int j=i+1; j<addressBook-> contactCount; j++)
    {
      int cmp=0;
      if(sortCriteria==1)
      {
        cmp = strcmp(addressBook -> contacts[i].name, addressBook -> contacts[j].name);
      }

      if(sortCriteria==2)
      {
        cmp = strcmp(addressBook -> contacts[i].phone, addressBook ->contacts[j].phone);
      }
      if(sortCriteria==3)
      {
        cmp = strcmp(addressBook -> contacts[i].email, addressBook ->contacts[j].email);
      }

      if(cmp>0)
      {
        Contact temp= addressBook ->contacts[i];
        addressBook -> contacts[i]=addressBook ->contacts[j];
        addressBook -> contacts[j]= temp;
      }
    }
  }

}


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    //Sort contacts based on the chosen criteria

    if(sortCriteria >=1 && sortCriteria <=3)
    {
      sortContacts(addressBook, sortCriteria);
    }
    
    printf("\n%-5s %-20s %-15s %-30s\n", "No", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------------------\n");

    for(int i=0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n", i, addressBook->contacts[i].name, addressBook-> contacts[i].phone, addressBook->contacts[i].email);
    }
      printf("--------------------------------------------------------------------------\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}




void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int check_ph(char *phone)
{
   int len= strlen(phone);
   if(len==10)
   {
    return 1; 
   }
   return 0;
}

int check_phone(char *phone, AddressBook *addressBook)
{

  for(int i=0; i< addressBook-> contactCount; i++)
  {
    if(strcmp(phone, addressBook -> contacts[i].phone)==0)
    {
       return 1;
    }
  }

  return 0;

}

int check_email_format(char *email)
{
  if(strchr(email, '@')==NULL)
  {
    return 0;
  }

  if(strstr(email, ".com")==NULL)
  {
    return 0;
  }

  return 1;
}

int check_email(char *email, AddressBook *addressBook)
{

  for(int i=0; i<addressBook -> contactCount; i++)
  {
    if(strcmp(email, addressBook -> contacts[i].email)==0)
    {
      return 1;
    }
  }

  return 0;

}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
  char name[20], phone[20], email[20];
  int res, result, ret, valid;

  printf("Enter the name: ");
  scanf(" %19[^\n]", name);

  
  do
  { 
      printf("Enter the phone number: ");
      scanf(" %19[^\n]", phone);
     
    ret = check_ph(phone);
     if(ret==0)
     {
      printf("Invalid input. Phone number must be 10 digits\n");
     }
     res= check_phone(phone, addressBook);

     if(res==1)
    {
       printf("The phone number is already present\n");
    }
     
  } while(res==1 || ret==0);

  do
  {
    printf("Enter the email id: ");
    scanf(" %19[^\n]", email);
    
    valid=check_email_format(email);

    if(!valid)
    {
      printf("Invalid email.\n");
    }
    result= check_email(email, addressBook);
    if(result==1)
    {
      printf("The email id is already present\n");
    }
  }while(!valid || result==1);

  strcpy(addressBook -> contacts[addressBook ->contactCount].name, name);
  strcpy(addressBook -> contacts[addressBook ->contactCount].phone, phone);
  strcpy(addressBook -> contacts[addressBook ->contactCount].email, email);
  
  addressBook -> contactCount++;

}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char name[50];
    char phone_no[20];
    char email_id[50];

    int option;
    int flag=0;

    printf("1. search by name\n2. search by ph no.\n3. search by email id\n");
    printf("Enter the option : ");
    scanf("%d", &option);

    switch(option)
    {
        case 1: printf("Enter the name: ");
        scanf(" %49[^\n]", name);

        for(int i=0; i<addressBook->contactCount; i++)
        {

          if(strcmp(name, addressBook -> contacts[i].name)==0)
          { 
            printf("%s %s %s", addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
            flag=1;
          }
        }
          if(flag==0)
          {
           printf("name is not present\n");
          }
         break;

         case 2: printf("Enter the phone no: ");
          scanf(" %19[^\n]", phone_no);

         for(int i=0; i<addressBook->contactCount; i++)
         {

           if(strcmp(phone_no, addressBook -> contacts[i].phone)==0)
           { 
             printf("%s %s %s", addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
             flag=1;
           }
        }
          if(flag==0)
          {
           printf("phone no is not present\n");
          }
          break;

          case 3: printf("Enter the email id: ");
          scanf(" %49[^\n]", email_id);

        for(int i=0; i<addressBook->contactCount; i++)
        {

          if(strcmp(email_id, addressBook -> contacts[i].email)==0)
          { 
            printf("%s %s %s", addressBook ->contacts[i]. name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
            flag=1;
          }
        }
          if(flag==0)
          {
           printf("email id is not present\n");
          }
          break;

          default: 
          printf("Invalid choice. Please try again\n");
          break;
   }
}



void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
  int option, index=-1;
  int choice;
  char name[20];
  char phone_no[20];
  char email_id[20];

  printf("1. select by name\n2. select by ph no\n3. select by email id\n");
  printf("Enter the option: ");
  scanf("%d", &option);  

  switch(option)
  {
    case 1 : 
            printf("Enter the name: ");
            scanf(" %19[^\n]", name);

          for(int i=0; i<addressBook->contactCount; i++)
          {
             if(strcmp(name, addressBook -> contacts[i].name)==0)
            {
              printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
            }
          }

        printf("Enter the index: ");
        scanf("%d", &index);
        
        if(index !=-1)
        {
          printf("1.Edit name\n2.Edit ph no\n3.Edit email id\n4.Edit all details\n");
          printf("Enter the choice: ");
          scanf("%d", &choice);

          switch(choice)
          {
             case 1 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);

                    strcpy(addressBook -> contacts[index].name, name);
                    break;
            case 2 : 
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);

                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    break;
            case 3 : 
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);

                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
            case 4 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);


                    strcpy(addressBook -> contacts[index].name, name);
                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
          }
        }
        break;


        case 2 : 
            printf("Enter the ph no: ");
            scanf(" %19[^\n]", phone_no);

           for(int i=0; i<addressBook->contactCount; i++)
          {
              if(strcmp(phone_no, addressBook -> contacts[i].phone)==0)
             {
              printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
             }
          }

        printf("Enter the index: ");
        scanf("%d", &index);
        
        if(index !=-1)
        {
          printf("1.Edit name\n2.Edit ph no\n3.Edit email id\n4.Edit all details\n");
          printf("Enter the choice: ");
          scanf("%d", &choice);

          switch(choice)
          {
             case 1 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);

                    strcpy(addressBook -> contacts[index].name, name);
                    break;
            case 2 : 
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);

                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    break;
            case 3 : 
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);

                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
            case 4 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);


                    strcpy(addressBook -> contacts[index].name, name);
                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
          }
        }
        break;


        case 3 : 
            printf("Enter the email id: ");
            scanf(" %19[^\n]", email_id);

          for(int i=0; i<addressBook->contactCount; i++)
          {
           if(strcmp(email_id, addressBook -> contacts[i].email)==0)
           {
              printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
           
           }
        }

        printf("Enter the index: ");
        scanf("%d", &index);
        
        if(index !=-1)
        {
          printf("1.Edit name\n2.Edit ph no\n3.Edit email id\n4.Edit all details\n");
          printf("Enter the choice: ");
          scanf("%d", &choice);

          switch(choice)
          {
             case 1 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);

                    strcpy(addressBook -> contacts[index].name, name);
                    break;
            case 2 : 
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);

                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    break;
            case 3 : 
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);

                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
            case 4 : 
                    printf("Enter the new name : ");
                    scanf(" %19[^\n]", name);
                    printf("Enter the new ph no : ");
                    scanf(" %19[^\n]", phone_no);
                    printf("Enter the new email id : ");
                    scanf(" %19[^\n]", email_id);

                    strcpy(addressBook -> contacts[index].name, name);
                    strcpy(addressBook -> contacts[index].phone, phone_no);
                    strcpy(addressBook -> contacts[index].email, email_id);
                    break;
          }
        }

        break;
  } 
   
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for delete contact */
   int option, index=-1;
  char name[50];
  char phone_no[20];
  char email_id[50];
  int found = 0;

  printf("1. select by name\n2. select by ph no\n3. select by email id\n");
  printf("Enter the option: ");
  scanf("%d", &option);  

  switch(option)
  {
    case 1 : 
            printf("Enter the name: ");
            scanf(" %49[^\n]", name);

          for(int i=0; i<addressBook->contactCount; i++)
          {
             if(strcmp(name, addressBook -> contacts[i].name)==0)
             {
               printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
               found = 1;
             }
          }

          if(!found)
          {
            printf("No contact was found with that name\n");
            return;
          }

        printf("Enter the index: ");
        scanf("%d", &index);
        
       if(index > 0 && index < addressBook -> contactCount)
        {
          for(int i=index; i< addressBook-> contactCount; i++)
          {
            addressBook -> contacts[i]= addressBook -> contacts[i+1];
       
          }

          (addressBook -> contactCount)--;
        }

       
      break;

      case 2 : 
            printf("Enter the phone no: ");
            scanf(" %19[^\n]", phone_no);

          for(int i=0; i<addressBook->contactCount; i++)
          {
             if(strcmp(phone_no, addressBook -> contacts[i].phone)==0)
            {
              printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
              found =1;
           
            }
          }

          if(!found)
          {
            printf("No contact was found with that phone no\n");
            return;
          }


        printf("Enter the index: ");
        scanf("%d", &index);
        
        if(index > 0 && index < addressBook -> contactCount)
        {
          for(int i=index; i< addressBook-> contactCount; i++)
          {
            addressBook -> contacts[i]= addressBook -> contacts[i+1];
       
          }
          (addressBook -> contactCount)--;
        }

        
      break;

      case 3 : 
            printf("Enter the email id: ");
            scanf(" %49[^\n]", email_id);

          for(int i=0; i<addressBook->contactCount; i++)
          {
            if(strcmp(email_id, addressBook -> contacts[i].email)==0)
            {
              printf("%d %s %s %s\n", i, addressBook ->contacts[i].name, addressBook -> contacts[i].phone, addressBook -> contacts[i].email);
              found =1;
           
            }
         }

         if(!found)
          {
            printf("No contact was found with that email id\n");
            return;
          }


        printf("Enter the index: ");
        scanf("%d", &index);
        
         if(index > 0  && index < addressBook -> contactCount)
           {
          for(int i=index; i< addressBook-> contactCount; i++)
          {
            addressBook -> contacts[i]= addressBook -> contacts[i+1];
       
          }
          (addressBook -> contactCount)--;
        }

        
      break;
      
      default:
           printf("Invalid option\n");
           return;
      

  }      
}














