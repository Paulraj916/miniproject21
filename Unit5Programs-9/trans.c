#include <stdio.h>
#include <stdlib.h>
// clientData structure definition
struct clientData {
  unsigned int acctNum; // account number
  char lastName[15];    // account last name
  char firstName[10];   // account first name
  double balance;       // account balance
};                      // end structure clientData

// prototypes
unsigned int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord_and_delete(FILE *fPtr,int);
void deleteRecord(FILE *fPtr);
void amounttransfer(FILE *fPtr);
void displaytext(FILE *fptr);

int main(int argc, char *argv[]) {
  FILE *cfPtr;         // credit.dat file pointer
  unsigned int choice;
  int new=0; // user's choice

  // fopen opens the file; exits if file cannot be opened
  if ((cfPtr = fopen("credit.dat", "rb+")) == NULL) {
    printf("%s: File could not be opened.\n", argv[0]);
    exit(-1);
  }
  // enable user to specify action
  while ((choice = enterChoice()) != 6) {
    switch (choice) {
    // create text file from record file
    case 1:
      displaytext(cfPtr); break;
    // update record
    case 2:
      updateRecord(cfPtr); break;
    // create record
    case 3:
      new=1;newRecord_and_delete(cfPtr,new); break;
    // delete existing record
    case 4:
      new=2;newRecord_and_delete(cfPtr,new); break;
    case 5:
      amounttransfer(cfPtr); break;
    // display if user does not select valid choice
    default:
      puts("Incorrect choice"); break;
    } // end switch
    textFile(cfPtr);
  } // end while

  fclose(cfPtr); // fclose closes the file
} // end main

// create formatted text file for printing
void textFile(FILE *readPtr) {
  FILE *writePtr; // accounts.txt file pointer
  int result;     // used to test whether fread read any bytes
  // create clientData with default information
  struct clientData client = {0, "", "", 0.0};

  // fopen opens the file; exits if file cannot be opened
  if ((writePtr = fopen("accounts.txt", "w")) == NULL) {
    puts("File could not be opened.");
  } // end if
  else {
    rewind(readPtr); // sets pointer to beginning of file
    fprintf(writePtr, "%-10s%-20s%-15s%15s\n", "Acct", "Last Name",
		    "First Name", "Balance");

    // copy all records from random-access file into text file
    while (!feof(readPtr)) {
      result = fread(&client, sizeof(struct clientData), 1, readPtr);

      // write single record to text file
      if (result != 0 && client.acctNum != 0) {
        fprintf(writePtr, "%-10d%-20s%-15s%15.2f\n", client.acctNum,
                client.lastName, client.firstName, client.balance);
      } // end if
    }   // end while

    fclose(writePtr); // fclose closes the file
  }                   // end else
} // end function textFile

void amt_update_transfer(FILE *kPtr,unsigned int account,double transaction,int uptrec){
  // move file pointer to correct record in file
  struct clientData client = {0, "", "", 0.0};
  fseek(kPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
  // read record from file
  fread(&client, sizeof(struct clientData), 1, kPtr);
  // display error if account does not exist
  if (client.acctNum == 0) {
    printf("Account #%d has no information.\n", account);
  } else { // update record
    
    if(uptrec==1){
      printf("%-6d%-16s%-11s%10.2f\n\n", client.acctNum, client.lastName,
           client.firstName, client.balance);
      // request transaction amount from user
      printf("%s", "Enter charge ( + ) or payment ( - ): ");
      scanf("%lf", &transaction);
      client.balance += transaction; // update record balance
    }
    if(uptrec==2){
      client.balance += transaction; 
    }
    printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName,
           client.firstName, client.balance);
    
    // move file pointer to correct record in file
    // move back by 1 record length
    fseek(kPtr, -sizeof(struct clientData), SEEK_CUR);
    // write updated record over old record in file
    fwrite(&client, sizeof(struct clientData), 1, kPtr);
  } // end else
}

// update balance in record
void updateRecord(FILE *fPtr) {
  unsigned int account; // account number
  double transaction;   // transaction amount
  int uptrec = 1;
  // create clientData with no information
  // obtain number of account to update
  printf("%s", "Enter account to update ( 1 - 100 ): ");
  scanf("%d", &account);
  amt_update_transfer(fPtr,account,transaction,uptrec);
} // end function updateRecord
// create and insert record
void newRecord_and_delete(FILE *fPtr,int new) {
  // create clientData with default information
  struct clientData client = {0, "", "", 0.0};
  struct clientData blankClient;
  unsigned int accountNum; // account number

  // obtain number of account to create
  printf("%s", "Enter new account number ( 1 - 100 ): ");
  scanf("%d", &accountNum);

  // move file pointer to correct record in file
  fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);
  // read record from file
  //if new == 1 then new record if n== 2 then delete record
  //this is for new record
  if(new==1){
    fread(&client, sizeof(struct clientData), 1, fPtr);
    // display error if account already exists
    if (client.acctNum != 0) {
      printf("Account #%d already contains information.\n", client.acctNum);
    } // end if
    else { // create record
      // user enters last name, first name and balance
      printf("%s", "Enter lastname, firstname, balance\n? ");
      scanf("%14s%9s%lf", client.lastName, client.firstName, &client.balance);

      client.acctNum = accountNum;
      // move file pointer to correct record in file
      fseek(fPtr, (client.acctNum - 1) * sizeof(struct clientData), SEEK_SET);
      // insert record in file
      fwrite(&client, sizeof(struct clientData), 1, fPtr);
  }
  } // end else
  //this is for delete record
  if(new==2){
    fread(&blankClient, sizeof(struct clientData), 1, fPtr);
    // display error if record does not exist
    if (blankClient.acctNum == 0) {
      printf("Account %d does not exist.\n", accountNum);
    }      // end if
    else { // delete record
      // move file pointer to correct record in file
      fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);
      // replace existing record with blank record
      fwrite(&client, sizeof(struct clientData), 1, fPtr);
    } // end else
  }
} 

void amounttransfer(FILE *fPtr){
  unsigned int account1; // account number 1
  unsigned int account2; // account number 2
  double transaction;
  int uptrec = 2;
  printf("%s", "Enter the amount transfer from account-1 to account-2 : ");
  scanf("%lf", &transaction);
  printf("%s", "Enter account-1 of which amount to be send : ");
  scanf("%d", &account1);
  amt_update_transfer(fPtr,account1,(transaction-(transaction*2)),uptrec);
  printf("%s", "Enter account-2 of which amount to be received: ");
  scanf("%d", &account2);
  amt_update_transfer(fPtr,account2,transaction,uptrec);
}

void displaytext(FILE *fptr){
  char s;
  fptr=fopen("accounts.txt","r");
  while((s=fgetc(fptr))!=EOF) {
      printf("%c",s);
  }
  fclose(fptr);
}

// enable user to input menu choice
unsigned int enterChoice(void) {
  unsigned int menuChoice; // variable to store user's choice
  // display available options
  printf("%s", "\nEnter your choice\n"
               "1 - Display all account details\n"
               "2 - update an account\n"
               "3 - add a new account\n"
               "4 - delete an account\n"
               "5 - money transfer\n"
               "6 - end program\n? ");

  scanf("%u", &menuChoice); // receive choice from user
  return menuChoice;
} // end function enterChoice
