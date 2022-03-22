
#include "bank.h"
#include "bstree.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// process input file
bool Bank::processTransactionFile(const string &fileName) {
  ifstream inFile;
  inFile.open(fileName);
  if (inFile.fail()) {
    cerr << "Unable to open file: " << fileName << endl;
    return false;
  }
  // inFile.ignore(INT_MAX, '\n');
  string trans;
  while (!inFile.eof()) {
    getline(inFile, trans);
    transactions.push(trans);
  }
  processTransactions(transactions);
  inFile.close();
  return true;
}

// input transactions into a queue and process them in order
void Bank::processTransactions(queue<string> transactions) {
  while (transactions.size() > 1) {
    string singleTrans = transactions.front();
    vector<string> split;
    stringstream ss(singleTrans);
    string token;
    while (getline(ss, token, ' ')) {
      split.push_back(token);
    }
    transactions.pop();
    string t = split[0];
    char temp = t[0];
    switch (temp) {
    case 'O': {
      string name;
      name = split[1] + " " + split[2];
      int id = stoi(split[3]);
      openAccount(name, id);
      break;
    }
    case 'D': {
      string history = "D " + split[1] + " " + split[2];
      int id = stoi(split[1]) / 10;
      int fundType = stoi(split[1]) % 10;
      int amount = stoi(split[2]);
      depositMoney(id, amount, fundType, history);
      break;
    }
    case 'W': {
      string history = "W " + split[1] + " " + split[2];
      int id = stoi(split[1]) / 10;
      int fundType = stoi(split[1]) % 10;
      int amount = stoi(split[2]);
      withdrawMoney(id, amount, fundType, history);
      break;
    }
    case 'H': {
      int id = stoi(split[1]);
      int numDigits = countNums(id);
      if (numDigits == 4) {
        displayHistory(id);
      } else {
        id = stoi(split[1]) / 10;
        int fundType = stoi(split[1]) % 10;
        displayHistory(id, fundType);
      }
      break;
    }

    case 'T': {
      string history1 = "T " + split[1] + " " + split[2] + " " + split[3];
      string history2 = "D " + split[3] + " " + split[2];
      int sourceID = stoi(split[1]) / 10;
      int sourceFund = stoi(split[1]) % 10;
      int amount = stoi(split[2]);
      int targetID = stoi(split[3]) / 10;
      int targetFund = stoi(split[3]) % 10;
      transferMoney(sourceID, sourceFund, amount, targetID, targetFund,
                    history1, history2);
      break;
    }
    default: { break; }
    }
  }
  cout << "Processing Done. Final Balances." << endl;
  // display all final balances of open accounts
  account.display();
}

// open an account
bool Bank::openAccount(string name, int id) {
  Account *temp = new Account(id, move(name));
  // insert into tree
  if (account.insert(temp)) {
    return true;
  }
  delete temp;
  return false;
}

// deposit money into an specific account fund
bool Bank::depositMoney(int id, int amount, int fundType, string &history) {
  Account *temp = nullptr;
  if (!account.retrieve(id, temp)) {
    return false;
  }
  temp->addFund(fundType, amount);
  temp->addHistory(history, fundType);
  return true;
}

// withdraw money from a specific fund
bool Bank::withdrawMoney(int id, int amount, int fundType, string &history) {
  Account *temp = nullptr;
  // don't have account to widthdraw money
  if (account.retrieve(id, temp)) {
    // widthdraw money fromm temp
    // temp has enough money
    if (temp->isEnoughMoney(fundType, amount)) {
      temp->removeFund(fundType, amount);
      temp->addHistory(history, fundType);

      return true;
    }

    // if there's not enough money in fund, see if you can cover the aount from
    // another fund
    switch (fundType) {
    case 0:
      return autoTrans(temp, temp, amount, 1, 0);
    case 1:
      return autoTrans(temp, temp, amount, 0, 1);
    case 2:
      return autoTrans(temp, temp, amount, 3, 2);
    case 3:
      return autoTrans(temp, temp, amount, 2, 3);
    default:
      cout << "Error! Cannot widthdraw money from " << id << fundType << " $"
           << amount << temp->getFundName(fundType) << endl;
      string str1 = "W " + to_string(id) + to_string(fundType) + " " +
                    to_string(amount) + "(fail)";
      temp->addHistory(str1, fundType);
      break;
    }
    return false;
  }
  cout << " Account " << id << fundType << " doesnt exist to withdraw " << endl;
  return false;
}

// auto transfer money to the fund you are trying to withdraw from
bool Bank::autoTrans(Account *&source, Account *&target, int amount,
                     int fundtype1, int fundtype2) {
  int fund1 = source->getFund(fundtype1);
  int remain = amount - fund1;
  if (target->getFund(fundtype2) >= remain) {
    source->removeFund(fundtype1, fund1);
    target->removeFund(fundtype2, remain);
    string str1 = "W " + to_string(source->getID()) + to_string(fundtype1) +
                  " " + to_string(amount);
    string str2 = "T " + to_string(target->getID()) + to_string(fundtype2) +
                  " " + to_string(remain) + " " + to_string(source->getID()) +
                  to_string(fundtype1);
    source->addHistory(str1, fundtype1);
    target->addHistory(str2, fundtype2);
    return true;
  }
  string str1 = "W " + to_string(source->getID()) + to_string(fundtype1) + " " +
                to_string(amount) + "(fail)";
  source->addHistory(str1, fundtype1);
  cout << "Cannot widthdraw from " << source->getID() << fundtype1 << endl;
  return false;
}

// transfer one one account/fund to another
bool Bank::transferMoney(int sourceID, int fundType1, int amount, int targetID,
                         int fundType2, string &history1, string &history2) {

  Account *temp = nullptr;
  Account *temp2 = nullptr;
  if (!account.retrieve(sourceID, temp) || !account.retrieve(targetID, temp2)) {
    cout << "Account: " << sourceID << " or " << targetID << " does not exist"
         << endl;
    return false;
  }
  if (temp->getFund(fundType1) < amount) {
    cout << "Insufficient funds " << sourceID << fundType1 << endl;
    history1 += "(fail)";
    temp->addHistory(history1, fundType1);
    return false;
  }
  temp->removeFund(fundType1, amount);
  temp2->addFund(fundType2, amount);
  temp->addHistory(history1, fundType1);
  temp2->addHistory(history2, fundType2);
  return true;
}

// display single fund or account
void Bank::displayHistory(int id, int fundType) {
  Account *temp = nullptr;
  if (!account.retrieve(id, temp)) {
    cout << "cannot print out history" << endl;
    return;
  }
  temp->getHistory(fundType);
}

// display history of an account
void Bank::displayHistory(int id) {
  Account *temp = nullptr;
  if (!account.retrieve(id, temp)) {
    cout << "cannot print out history" << endl;
    return;
  }
  // print out all history
  temp->getHistory(-1);
}

// count how many digits are in the ID input
int Bank::countNums(int id) {
  int count = 0;
  while (id != 0) {
    id = id / 10;
    count++;
  }
  return count;
}
