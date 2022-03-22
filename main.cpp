
#include "bank.h"
#include <iostream>
#include <string>

using namespace std;

void test(const string &bankFile) {
  Bank m;
  cout << "*** Open " << bankFile << endl;
  if (!m.processTransactionFile(bankFile)) {
    cout << "Failed to load " << bankFile << endl;
    return;
  }
}

int main(int argc, char *argv[]) {

  // Note that tests were done in BankTransIn.txt
  for (int i = 1; i < argc; ++i) {
    cout << "The command line argument(s) was " << argv[i] << std::endl;
    string fileName = argv[i];
    test(fileName);
  }
  cout << "Done!" << endl;
  return 0;
}