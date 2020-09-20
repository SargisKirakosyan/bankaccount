#pragma once

#include "json.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>

using json = nlohmann::json;

void showMainMenu();
void menuListNumber();

namespace bankAccount {
  class Person {
    public:
      std::string firstName;
      std::string lastName;
      int birthDay;
      int birthMonth;
      int birthYear;
      int accountBalance;
      std::string moneyCurrency;
      char registrationDate[50];
      void createAccount();
      void updateAccount();
      void makeTransaction();
      void accountDetails();
      void removeAccount();
      void customersLeft();
      void exitToMenu();
  };
}
