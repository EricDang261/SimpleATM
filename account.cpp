#include "account.h"
#include <iostream>
#include <string>
using namespace std;

// constructor
Account ::Account(int id, string name) : id{id}, name{move(name)} {
  // Identify fund type/set names for all fund types
  fundtype[0].name = " Money Market";
  fundtype[1].name = " Prime Money Market";
  fundtype[2].name = " Long-Term Bond";
  fundtype[3].name = " Short-Term Bond";
  fundtype[4].name = " 500 Index Fund";
  fundtype[5].name = " Capital Value Fund";
  fundtype[6].name = " Growth Equity Fund";
  fundtype[7].name = " Growth Index Fund";
  fundtype[8].name = " Value Fund";
  fundtype[9].name = " Value Stock Index";
}

// get account ID
int &Account::getID() { return id; }

// get account name
string Account::getName() { return name; }

// get how much money is in a type of fund
int Account::getFund(int fundID) { return fundtype[fundID].amount; }

// check if the fund has enough money
bool Account::isEnoughMoney(int fundID, int amount) {
  return getFund(fundID) >= amount;
}

// get name for fund
string Account::getFundName(int fundID) { return fundtype[fundID].name; }

// add money to a fund
bool Account::addFund(int fundID, int amount) {
  fundtype[fundID].amount += amount;
  return true;
}

// Remove money from a fund
bool Account::removeFund(int fundID, int amount) {
  fundtype[fundID].amount -= amount;
  return true;
}

// add transaction history to a fund
void Account::addHistory(string &history, int fundID) {
  fundtype[fundID].history << "\t" << history << endl;
}

// get history of transactions from a single fund or account
void Account::getHistory(int fundID) {
  if (fundID == -1) {
    cout << "Display transaction history for: " << getName() << " by fund"
         << endl;
    for (auto &i : fundtype) {
      cout << i.name << ": $" << i.amount << endl;
      cout << i.history.str(); // store history with a string container
    }
  } else {
    cout << fundtype[fundID].name << ": $" << fundtype[fundID].amount << endl;
    cout << fundtype[fundID]
                .history.str(); // store history with a string container
  }
}
