#include "account.h"

bankAccount::Person person;

void menuListNumber() {
  int number;
  std::cin >> number;
  switch (number) {
    case 1:
      person.createAccount();
      break;
    case 2:
      person.updateAccount();
      break;
    case 3:
      person.makeTransaction();
      break;
    case 4:
      person.accountDetails();
      break;
    case 5:
      person.removeAccount();
      break;
    case 6:
      person.customersLeft();
      break;
    case 7:
      person.exitToMenu();
      break;
  }
}

void bankAccount::Person::createAccount() {
  std::cout << "Write your first name\n"; 
  std::cin >> firstName;
  std::cout << "Write your last name\n";
  std::cin >> lastName;
  std::cout << "Write your birth day\n";
  std::cin >> birthDay;
  std::cout << "Write your birth month\n";
  std::cin >> birthMonth;
  std::cout << "Write your birth year\n";
  std::cin >> birthYear; 
  std::cout << "Write your account balance\n";
  std::cin >> accountBalance;
  std::cout << "Write the currency of your money\n";
  std::cin >> moneyCurrency;
  bool emptyFile=false;
  time_t curr_time;
	tm * curr_tm;
	time(&curr_time);
	curr_tm = localtime(&curr_time);
	strftime(registrationDate, 50, "%d/%m/%Y", curr_tm);
  std::ifstream json_openfile("accounts.json");
  if(json_openfile.peek() == std::ifstream::traits_type::eof() ) {
    std::ofstream json_writefile("accounts.json");
    json_writefile << "{\n}";
    json_writefile.close();
  }
  json j;
  json_openfile >> j;
  j["Accounts"]+={{"firstname", person.firstName},{"lastname", person.lastName}, {"birthday", person.birthDay}, {"birthmonth", person.birthMonth}, {"birthyear", person.birthYear}, {"balance", person.accountBalance}, {"currency", person.moneyCurrency}, {"registration", person.registrationDate}};
  json_openfile.close();
  std::ofstream json_writefile("accounts.json");
  json_writefile << std::setw(4) << j;
  json_writefile.close();
  menuListNumber();
}

void bankAccount::Person::updateAccount() {
  int option;
  int answer;
  std::cout << "Write the number of option from the list which information you want to change\n";
  std::cout << "1. Change your first name\n";
  std::cout << "2. Change your last name\n";
  std::cout << "5. Change your birth day\n";
  std::cout << "4. Change your birth month\n";
  std::cout << "3. Change your birth year\n";
  std::cin >> option;
  switch (option) {
    case 1:
      std::cout << "Write your first name\n"; 
      std::cin >> firstName;
      break;
    case 2:
      std::cout << "Write your last name\n";
      std::cin >> lastName;
      break;
    case 3:
      std::cout << "Write your birth day\n";
      std::cin >> birthDay;
      break;
    case 4:
      std::cout << "Write your birth month\n";
      std::cin >> birthMonth;
      break;
    case 5:
      std::cout << "Write your birth year\n";
      std::cin >> birthYear; 
      break;
  }
  std::ifstream json_openfile("accounts.json");
  json j;
  json_openfile >> j;
  int myAccount=j["Accounts"].size()-1;
  j["Accounts"][myAccount]["firstname"]=firstName;
  j["Accounts"][myAccount]["lastname"]=lastName;
  j["Accounts"][myAccount]["birthday"]=birthDay;
  j["Accounts"][myAccount]["birthmonth"]=birthMonth;
  j["Accounts"][myAccount]["birthyear"]=birthYear;
  json_openfile.close();
  std::ofstream json_file("accounts.json");
  json_file << std::setw(4) << j;
  json_file.close();
  std::cout << "Do you want to change something else?\n" << "Write 1 for YES and 2 for NO\n";
  std::cin >> answer;
  if(answer==1) {
    updateAccount();
  }
  else {
    menuListNumber();
  }
}

void bankAccount::Person::makeTransaction() {
  int answer;
  std::ifstream json_openfile("accounts.json");
  json j;
  json_openfile >> j;
  int existMoney;
  int moneyToTransfer;
  std::string fn;
  std::string ln;
  int by;
  std::cout << "Write customer first name\n";
  std::cin >> fn;
  std::cout << "Write customer last name\n";
  std::cin >> ln;
  std::cout << "Write customer birth year\n";
  std::cin >> by;
  int ra=0;
  bool customerExist=false;
  for (int i=0; i<j["Accounts"].size(); ++i) {
        if(j["Accounts"][i]["firstname"]==fn && j["Accounts"][i]["lastname"]==ln && j["Accounts"][i]["birthyear"]==by) {
          ra=i;
          customerExist=true;
        }
  }
  if(customerExist==true) {
    std::cout << "How much you want to transfer?\n";
    std::cin >> moneyToTransfer;
    int myAccount=j["Accounts"].size()-1;
    existMoney=j["Accounts"][myAccount]["balance"];
    j["Accounts"][myAccount]["balance"]=existMoney-moneyToTransfer;
    int recipientMoney = j["Accounts"][ra]["balance"];
    j["Accounts"][ra]["balance"]= recipientMoney+moneyToTransfer;
    json_openfile.close();
    std::ofstream json_file("accounts.json");
    json_file << std::setw(4) << j;
    json_file.close();
    std::cout << "Transfer successfully completed!\n";
  }
  else {
    std::cout << "Our bank don't have a customer with the same information that you provided." << std::endl;
  }
  std::cout << "Do you want to make another transaction?\n" << "Write 1 for YES and 2 for NO\n";
  std::cin >> answer;
  if(answer==1) {
    makeTransaction();
  }
  else {
    menuListNumber();
  }
}

void bankAccount::Person::accountDetails() {
  std::ifstream json_file("accounts.json");
  json j;
  json_file >> j;
  int a;
  for (int i=0; i<j["Accounts"].size(); i++) {
        if(j["Accounts"][i]["firstname"]==person.firstName) {
          a=i;
        }
  }
  std::cout << "Your first name is " << j["Accounts"][a]["firstname"].get<std::string>() << "\n"; 
  std::cout << "Your last name is " << j["Accounts"][a]["lastname"].get<std::string>() << "\n";
  std::cout << "Your birth date is " << j["Accounts"][a]["birthday"] << "/" << j["Accounts"][a]["birthmonth"] << "/"  << j["Accounts"][a]["birthyear"] << "\n";
  std::cout << "Your balance is " << j["Accounts"][a]["balance"] << " " << j["Accounts"][a]["currency"].get<std::string>() << "\n";
  std::cout << "You registered your account on " << j["Accounts"][a]["registration"].get<std::string>() << "\n";
  json_file.close();  
  menuListNumber();
}

void bankAccount::Person::removeAccount() {
  std::ifstream json_openfile("accounts.json");
  json j;
  json_openfile >> j;
  j["Accounts"].erase(j["Accounts"].end());
  json_openfile.close();
  std::ofstream json_file("accounts.json");
  json_file << std::setw(4) << j;
  json_file.close();
  menuListNumber();
}

void bankAccount::Person::customersLeft() {
  std::ifstream json_openfile("accounts.json");
  json j;
  json_openfile >> j;
  std::cout << j["Accounts"].size() << " " << "customers left in the system" << std::endl;
  json_openfile.close();
  menuListNumber();
}

void showMainMenu() {
  std::cout << "CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n";
  std::cout << "|||||| WELCOME TO THE MAIN MENU ||||||\n\n";
  std::cout << "1. Create new account\n";
  std::cout << "2. Update information of existing account\n";
  std::cout << "3. For transactions\n";
  std::cout << "4. Check the details of existing account\n";
  std::cout << "5. Removing existing account\n";
  std::cout << "6. View customers left\n";
  std::cout << "7. Exit\n";
  menuListNumber();
}

void bankAccount::Person::exitToMenu() {
  this->Person::~Person();
  system("clear");
  showMainMenu();
  menuListNumber();
}
