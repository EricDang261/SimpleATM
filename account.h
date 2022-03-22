
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <sstream>
#include <string>
using namespace std;
 
class Account {

public:
 Account(int id, string name);                 // constructor for creating an account
 int& getID();                                 // get Account ID
 string getName();                             // get Account name
 int getFund(int fundID);                      // get an amount from a fund
 string getFundName(int fundID);               // get a fund name
 bool addFund(int fundID, int amount);         // add money to a fund
 void addHistory(string &history, int id);     // add transaction history to a fund
 void getHistory(int fundID);                  // get history from a single fund or account
 bool isEnoughMoney(int fundId, int amount);   // check if enough money in account
 bool removeFund(int fundID, int amount);      // remove oney from a fund

 
 private:
 struct FundType {
   //amount of money in a fund
   int amount{0};

   //to save transaction history
   stringstream history;

   // to identify name of fundtype.
   string name;
 };
 int id{0};             // int variable for ID
 string name;           // string variable for name of client
 FundType fundtype[10]; // array of fundtype structure
};
#endif // ACCOUNT_H

