
#ifndef BANK_H
#define BANK_H
#include "account.h"
#include "bstree.h"
#include <queue>
#include <string>

using namespace std;
class Bank {
public:

//input transactions into a queue and process them in order
 void processTransactions(queue<string> transactions);

 //process input file
bool processTransactionFile(const string &fileName); 

//open an account
 bool openAccount(string name, int id);

//deposit money into a specific fund of an account
 bool depositMoney(int id, int amount, int fundType, string& history);

 //withdraw money from a specific fund of an account
 bool withdrawMoney(int id, int amount, int fundType, string& history);

//auto transfer money to the fund you are trying to withdraw from
 bool autoTrans(Account *&source, Account *&target, int amount,
                     int fundtype1, int fundtype2);

 //transfer money between accounts or funds
 bool transferMoney(int sourceID, int fundType1, int amount, int targetId, int fundType2, string& history1, string& history2);

 //count how many digits are in the ID input
  int countNums(int id);
 
 
 //displays the transaction history of one account fund
 void displayHistory(int id, int fundType);

 //displays transaction history of one account
 void displayHistory(int id);
private:
 //BSTree accounts;
 BSTree account;
 //queue as container to store all of the transactions 
 queue <string> transactions;
};
#endif // BANK_H
