#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<string>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

class account
{
    int acno;
    int loanID;
    char type;
    char name[50];
    char phoneNo[15];
    double balance;
    double loanAmt;
    char transHistory[1000];
    char timeCreated[25];
    char* loanType;
public:
    void create_account(int);	//function to initialize a new account form
    void show_account() const;	//function to show an account's data on screen
    void modify();	//function to modify an individual account (admin)
    void addTrans(char*); //function to add to an individual account's transaction history
    void dep(double);	//function to accept amount and add to balance
    void draw(double);	//function to accept amount and subtract from balance
    void Wloan(double); //function to subtract loan input from loan amount
    void Dloan(double);//function to add loan input to loan amount
    void report() const;	//function to aid in displaying data for all accounts
    void reportTrans() const; //function to show transaction history
    int retacno() const;	//function to return account number
    int retloanID() const; // function to return load id
    string retacname () const; //function to return account name
    string retDate () const; // function to return date
    double retdeposit() const;	//function to return balance amount
    void displayLoans() const; //function to display current loans
    void changeType(int); // Function to change account's loan type
    void chargeInt(); // Function to charge interest on a loan
};


void account::create_account(int latest)
{

    char choice;
    bool validate;
    static int count=10001;
    static int Lcount=20001;
    int counter=0;

    if (latest != 0)
    {
        count = latest + 1;
        Lcount = count + 10000;
    }
    cout << "latest is " << latest;

    acno = count++;
    loanID = Lcount++;
    cout << "\n\nYour account number is: " << acno << endl;
    cout << "Your Loan ID is: " <<loanID;

    do {
        validate = false;
        cout<<"\n\nEnter The Name of The account Holder : ";
        cin.ignore();
        cin.getline(name,50);

        for (int i=0; i < strlen(name); i++)
        {
            if (isdigit(name[i]))
                validate = true;
        }
        if (validate)
        {
            cout << "#Error#\nThere is a number in your account name...";
        }
    } while (validate);

    do {
        validate = false;
        cout << "Enter a 10 digit phone number for your account: ";
        cin.ignore();
        cin.clear();
        cin.getline(phoneNo, 15);

        for (int i=0; i < strlen(phoneNo); i++)
        {
            if(!(isdigit(phoneNo[i])))
            {
                validate = true;
                cout << "\n#Error#\nThere is should be no character in your input...";
            }
        }
        if (strlen(phoneNo) != 9)
        {
            cout << "\n#Error#\nThere should be exactly 9 digits in your input...";
            validate = true;
        }
    } while (validate);

    type = 'C';
    do
    {
        validate = false;
        cout<<"Enter the account type (C/S) : ";
        cin.get(type);
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        else
            type=toupper(type);
        if (type != 'C' && type != 'S')
            validate = true;
    } while (validate);

    do
    {
        validate = false;
        cout << "Enter The Initial deposit: ";

        string char_array;
        cin>>char_array;

        for (int i=0; i < char_array.length(); i++)
        {
            if ((!isdigit(char_array[i])) && char_array[i] != '.')
                validate = true;
        }

        if (validate)
            cout << "Please enter a number without a character in it\n";
        else
            balance = atof(char_array.c_str());

    } while (validate);




    cout<<"would you like to take out a loan? (y/n)";
    cin >> choice;
    choice = toupper(choice);

    while (choice != 'N' && choice != 'Y')
    {
        cout << "please enter a valid input (y/n): ";
        cin >> choice;
        choice = toupper(choice);
    }

    if (choice == 'Y')
    {
        validate = true;

        cout << "\nwhat kind of loan is this?\n";
        cout << "01.Car(interest rate: 5.27% for 60 months)\n";
        cout << "02.Home(interest rate: 3.04% for 30 years)\n";
        cout << "03.Student(interest rate: 4.33% FOREVER)\nENTER: ";
        cin >> choice;
        switch (choice)
        {
            case '1':
                loanType = "Car";
                break;
            case '2':
                loanType = "Home";
                break;
            case '3':
                loanType = "Student";
                break;
            default:
                cout << "\nPlease input a valid entry";
                break;
        }
        cout << "You have chosen " << loanType;

        do
        {
            validate = false;
            cout<<"\n\nEnter a quantity for the loan: ";

            string char_array;
            cin >> char_array;

            for (int i=0; i < char_array.length(); i++)
            {
                if((!isdigit(char_array[i])) && char_array[i] != '.')
                    validate = true;
            }

            if (validate)
                cout << "ERROR#Please enter a number without a character in it\n";
            else
                loanAmt = atof(char_array.c_str());

        } while (validate);

        dep(loanAmt);
        cout << loanAmt << " Has been deposited into your account.\n\n";
    }
    if (!validate)
    {
        loanAmt = 0;
    }

    do
    {
        validate = false;
        cout << "Finally, Please enter today's date (Mo/da/Year)";
        if(counter ==0)
        {
            cin.ignore();
            counter++;
        }
        cin.getline(timeCreated, 12);

        if (timeCreated[2] != '/' || timeCreated[5] != '/')
        {
            validate = true;
            cout << "ERROR#\nEnsure the date is formatted correctly (xx/xx/xxxx)...\n";
            cout << timeCreated[2] << " " << timeCreated[5] << endl;
        }
        if (!isdigit(timeCreated[0]) || !isdigit(timeCreated[1]) ||!isdigit(timeCreated[0]) || !isdigit(timeCreated[3]) ||
            !isdigit(timeCreated[4]) || !isdigit(timeCreated[6]) || !isdigit(timeCreated[7]) || !isdigit(timeCreated[8]) || !isdigit(timeCreated[9]))
        {
            validate = true;
            cout << "ERROR#\nEnsure you are using NUMBERS for your dates...\n";
        }

    } while (validate);

    cout<<"\nYour account has been created, " << name;
    cout << ", on " << timeCreated;
}

void account::show_account() const
{
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nAccount Loan ID: "<<loanID;
    cout<<"\nAccount Holder Name : "<<name;
    cout<<"\nAccount Holder Phone Number : "<<phoneNo;
    cout <<"\nThis account was created on: "<<timeCreated;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance amount : "<<balance;
    cout <<"\nYou currently owe: "<<loanAmt;
    if (loanAmt > 0)
        cout <<"\nFor the following loan: "<< loanType;

    cout << endl;
}

void account::modify()
{
    show_account();
    cout<<"\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance amount : ";
    cin>>balance;
}

void account::addTrans(char* add)
{
    strcat(transHistory, add);
}
void account::dep(double x)
{
    balance+=x;
}

void account::draw(double x)
{
    balance-=x;
}

void account::Wloan(double x)
{
    loanAmt -= x;
}

void account::Dloan(double x)
{
    loanAmt += x;
}

void account::report() const
{
    cout<<acno<<"\t\t"<<left<<setw(10)<<name<<setw(13)<<type<<setw(10)<<balance<<setw(15)<<loanAmt<<endl;
}
void account::reportTrans() const
{
    cout <<"  Transaction history (Please disregard the first line)\n";
    cout <<"========================================================\n";
    cout << transHistory;
}

int account::retacno() const
{
    return acno;
}

int account::retloanID() const
{
    return loanID;
}

string account::retacname() const
{
    string str(name);
    return str;
}

string account::retDate() const
{
    string str(timeCreated);
    return str;
}
double account::retdeposit() const
{
    return balance;
}

void account::displayLoans() const
{
    cout << "\nLoan type: " << loanType << "\nLoan amount: " << loanAmt;
}

void account::changeType(int cH)
{
    if (cH == 1)
        loanType = "Car";
    else if (cH == 2)
        loanType = "Home";
    else if (cH == 3)
        loanType = "Student";
}

void account::chargeInt()
{
    if (loanType == "Car")
        loanAmt *= (1.0527);
    if (loanType == "Home")
        loanAmt *= (1.0304);
    if (loanType == "Student")
        loanAmt *= (1.0433);
}
//==========================PROTOTYPES==========================

void write_account(int);	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all(string);		//function to display all account details
void deposit_withdraw(int, int, string&); // function to deposit/withdraw amount for given account
void loans(int, string&); //function to show outstanding loans
void transfer(int, int, string&); // function to transfer funds from an account to another
void search(); //Search for an account via Ac number, loan id, date, or account owner's name
void intro();	//introductory screen function


//=========================MAIN FUNCTION==========================

int main()
{
    int ch;
    int max=0;
    vector<int>accountNums;
    char choice;
    int num, num2;
    string allTrans;

    intro();


    cout << setprecision(2) << fixed;

    //Empty files (If desired)
    cout << "Would you like to start a new session (Y for yes; Enter for no)";
    cin.get(choice);
    choice = toupper(choice);
    if (choice == 'Y')
        remove ("account.dat");


    do
    {
        //test if prior session and set first ac No and loan ID accordingly
        account ac;
        ifstream inFile;
        inFile.open("account.dat",ios::binary);
        if(inFile)
        {
            while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
            {
                accountNums.push_back(ac.retacno());
            }
            max = *max_element(accountNums.begin(), accountNums.end());
        }


        cout << "Please choose from the options below: ";
        cout<<"\n    MAIN MENU";
        cout<<"\n01. NEW ACCOUNT";
        cout<<"\n02. DEPOSIT AMOUNT";
        cout<<"\n03. WITHDRAW AMOUNT";
        cout<<"\n04. DISPLAY ACCOUNT INFORMATION";
        cout<<"\n05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n06. DELETE AN ACCOUNT";
        cout<<"\n07. MODIFY AN ACCOUNT";
        cout<<"\n08. OPEN LOAN MENU FOR AN ACCOUNT";
        cout<<"\n09. TRANSFER FUNDS FROM ONE ACCOUNT TO ANOTHER";
        cout<<"\n10. SEARCH MENU";
        cout<<"\n11. EXIT THE PROGRAM";
        cout<<"\nSelect Your Option (1-11): ";
        cin>>ch;
        //system("cls");
        switch(ch)
        {
            case 1:
                write_account(max);
                break;
            case 2:
                cout<<"\n\tEnter The account No. : ";
                cin>>num;
                deposit_withdraw(num, 1, allTrans);
                break;
            case 3:
                cout<<"\n\tEnter The account No. : ";
                cin>>num;
                deposit_withdraw(num, 2, allTrans);
                break;
            case 4:
                cout<<"\n\tEnter The account No. : ";
                cin>>num;
                display_sp(num);
                break;
            case 5:
                display_all(allTrans);
                break;
            case 6:
                cout<<"\n\tEnter The account No. : ";
                cin>>num;
                delete_account(num);
                break;
            case 7:
                cout<<"\n\tEnter The account No. : ";
                cin>>num;
                modify_account(num);
                break;
            case 8:
                cout <<"\n\tEnter The Account No. : ";
                cin >>num;
                loans(num, allTrans);
                break;
            case 9:
                cout << "\n\tEnter YOUR account No. :";
                cin >>num;
                cout << "\n\tEnter the account No. for the receiver: ";
                cin >>num2;
                cin.clear();
                cin.ignore();
                transfer(num, num2, allTrans);
                break;
            case 10:
                search();
                break;
            case 11:
                cout<<"\nTHANK YOU FOR TRYING COMMONWEALTH BANKING!";
                break;
            default :
                cout<<"\a";
                //break;
        }

        cin.ignore();
        cin.get();


    }while(ch!=11);
    return 0;
}


//==========================WRITE INTO MAIN FILE==========================


void write_account(int a)
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account(a);
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

//==========================RETURN SPECIFIC ACCOUNT INFO==========================

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            ac.reportTrans();
            flag=true;
        }
    }
    inFile.close();
    if(!flag)
        cout<<"\n\nAccount number does not exist";
}


//==========================MODIFY AN ACCOUNT==========================

void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(!found)
        cout<<"\n\n Record Not Found ";
}

//==========================DELETE AN ACCOUNT==========================



void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted ..";
}

//==========================DISPLAY ALL ACCOUNT INFORMATION==========================

void display_all(string allTrans)
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"A/c no."<<left<<setw(10)<<" \tNAME"<<setw(13)<<"Type"<<setw(10)<<" Balance"<<setw(15)<<" Total Loans Due"<<endl;
    cout<<"==================================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();

    cout << "-----All Transactions-----\n";
    cout <<allTrans;

}

//==========================DEPOSIT/WITHDRAW==========================


void deposit_withdraw(int n, int option, string &allTrans)
{
    double amt;
    bool found=false;
    string transaction, transaction2;
    string alltra;
    string amount;
    bool validate;

    //current time
    time_t now = time(0);
    char* date_time = ctime(&now);



    account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);

    if(!File)
    {

        cout<<"File could not be open !! Press any Key...";
        return;
    }

    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO Deposit AMOUNT ";

                do
                {
                    validate = false;
                    cout<<"\n\nEnter The amount to be deposited: ";

                    string char_array;
                    cin >> char_array;

                    for (int i=0; i < char_array.length(); i++)
                    {
                        if((!isdigit(char_array[i])) && char_array[i] != '.')
                            validate = true;
                    }

                    if (validate)
                        cout << "ERROR#Please enter a number without a character in it\n";
                    else
                        amt = atof(char_array.c_str());

                } while (validate);

                stringstream ss;
                ss << amt;
                ss >> amount;

                transaction =  "*" + amount + " Dollars have been deposited at " + date_time;
                transaction2 =  "\n"+ amount + " Dollars have been deposited at " + date_time + "\n";
                char* char_array;
                char_array = &transaction2[0];

                ac.dep(amt);
                ac.addTrans(char_array);
                ac.show_account();
                ac.reportTrans();

                alltra = transaction + " into Ac No. " + to_string(n) + "\n";
                allTrans += alltra;
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                do
                {
                    validate = false;
                    cout<<"\n\nEnter The amount to be withdrawn: ";

                    string char_array;
                    cin >> char_array;

                    for (int i=0; i < char_array.length(); i++)
                    {
                        if((!isdigit(char_array[i])) && char_array[i] != '.')
                            validate = true;
                    }

                    if (validate)
                        cout << "ERROR#Please enter a number without a character in it\n";
                    else
                        amt = atof(char_array.c_str());

                } while (validate);

                transaction = to_string(amt) + " Dollars have been withdrawn at " + date_time;
                transaction2 = "\n" + to_string(amt) + " Dollars have been withdrawn at " + date_time + "\n";

                char* char_array;
                char_array = &transaction2[0];

                ac.draw(amt);
                ac.addTrans(char_array);
                ac.show_account();
                ac.reportTrans();

                alltra = "*" + transaction + " From Ac No. " + to_string(n) + "\n";
                allTrans += alltra;
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));

            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));

            cout<<"\n\tRecord Updated";
            found=true;
        }
    }
    File.close();
    if(!found)
        cout<<"\n\n Record Not Found ";
}

//==========================LOAN MENU==========================


void loans(int n, string &allTrans)
{
    double amt;
    char choice;
    bool found=false, validate;
    string update, transaction2;
    account ac;
    fstream File;

    time_t now = time(0);
    char* date_time = ctime(&now);

    File.open("account.dat", ios::binary|ios::in|ios::out);

    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));

        if(ac.retacno()==n)
        {
            ac.show_account();

            cout << "\n\nWelcome to the loan menu!\nWhat would you like to do?\n";
            cout << "\n01. Make a payment on a loan\n";
            cout << "02. Borrow more money\n";
            cout << "03. Change your loan type\n";
            cout << "04. Calculate interest paid on the loan\n";
            cin >> choice;

            if (choice == '1')
            {
                cout << "Please review your current loan:\n";
                ac.displayLoans();

                do
                {
                    validate = false;
                    cout<<"\n\nEnter amount to pay off: ";

                    string char_array;
                    cin >> char_array;

                    for (int i=0; i < char_array.length(); i++)
                    {
                        if((!isdigit(char_array[i])) && char_array[i] != '.')
                            validate = true;
                    }

                    if (validate)
                        cout << "ERROR#Please enter a number without a character in it\n";
                    else
                        amt = atof(char_array.c_str());

                } while (validate);

                ac.draw(amt);
                ac.Wloan(amt);


                double bal=ac.retdeposit()-amt;
                cout <<"\n Your new current balance is " << bal << endl;

                update = "*" + to_string(amt) + " Has been paid off from a loan belonging to Acc No. " + to_string(n) + " at " + date_time + "\n";
                allTrans += update;


                transaction2 = to_string(amt) + " Dollars have been paid off from your loan at " + date_time + "\n";
                char* char_array;
                char_array = &transaction2[0];

                ac.addTrans(char_array);


            }
            else if (choice == '2')
            {
                cout << "Please review your current loans:\n";
                ac.displayLoans();

                do
                {
                    validate = false;
                    cout<<"\n\nHow much more would you like to borrow: ";

                    string char_array;
                    cin >> char_array;

                    for (int i=0; i < char_array.length(); i++)
                    {
                        if((!isdigit(char_array[i])) && char_array[i] != '.')
                            validate = true;
                    }

                    if (validate)
                        cout << "ERROR#Please enter a number without a character in it\n";
                    else
                        amt = atof(char_array.c_str());

                } while (validate);


                ac.Dloan(amt);


                update = "*" + to_string(amt) + " Has been added to the loan belonging to Acc No. " + to_string(n) + " at " + date_time +"\n";
                allTrans += update;

                transaction2 = to_string(amt) + " Has been added to your loan." + " at " + date_time + "\n";
                char* char_array;
                char_array = &transaction2[0];

                ac.dep(amt);
                ac.addTrans(char_array);
            }
            else if (choice == '3')
            {
                cout << "\nWhat kind of loan would you like to switch to?\n";
                cout << "01.Car(interest rate: 5.27% for 60 months)\n";
                cout << "02.Home(interest rate: 3.04% for 30 years)\n";
                cout << "03.Student(interest rate: 4.33% FOREVER)\nENTER: ";
                cin >> choice;
                switch (choice)
                {
                    case '1':
                        ac.changeType(1);
                        break;
                    case '2':
                        ac.changeType(2);
                        break;
                    case '3':
                        ac.changeType(3);
                        break;
                    default:
                        cout << "\nPlease input a valid entry";
                        break;
                }
            }
            else if (choice == '4')
            {
                cout << "Please review your current loan:\n";
                ac.displayLoans();
                cout << "\n\nWould you like to apply it's respective interest rate?\n";
                cout << "INTEREST RATES:\n";
                cout << "01.Car(interest rate: 5.27% for 60 months)\n";
                cout << "02.Home(interest rate: 3.04% for 30 years)\n";
                cout << "03.Student(interest rate: 4.33% FOREVER)\nENTER (y/n): ";
                cin >> choice;

                choice = toupper(choice);
                if (choice == 'Y')
                    ac.chargeInt();
                else
                    cout << "Entry invalid\n";

                cout << "Your new current loan:\n";
                ac.displayLoans();
            }

            int pos=(-1)*static_cast<int>(sizeof(ac));

            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));

            cout<<"\n\tRecord Updated";
            found=true;
        }
    }
    File.close();
    if(!found)
        cout<<"\n\n Record Not Found ";
}

//==========================TRANSFER MENU==========================

void transfer(int n, int m, string &allTrans)
{
    double amt;
    string update, transaction2;
    bool found=false, validate;

    time_t now = time(0);
    char* date_time = ctime(&now);


    account ac;
    fstream File;

    File.open("account.dat", ios::binary|ios::in|ios::out);

    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }

    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));

        if(ac.retacno()==n)
        {
            ac.show_account();

            do
            {
                validate = false;
                cout<<"\n\nEnter amount to transfer: ";

                string char_array;
                cin >> char_array;

                for (int i=0; i < char_array.length(); i++)
                {
                    if((!isdigit(char_array[i])) && char_array[i] != '.')
                        validate = true;
                }

                if (validate)
                    cout << "ERROR#Please enter a number without a character in it\n";
                else
                    amt = atof(char_array.c_str());

            } while (validate);

            double bal = ac.retdeposit() - amt;

            cout << "\n current balance is " << bal << endl;


            ac.draw(amt);


            transaction2 = "\n" + to_string(amt) + " Dollars have been transferred from your account to Acc No." + to_string(m) + " at " + date_time + "\n";
            char* char_array;
            char_array = &transaction2[0];
            ac.addTrans(char_array);

            int pos = (-1) * static_cast<int>(sizeof(ac));

            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            found = true;

        }

    }
    File.close();
    File.open("account.dat", ios::binary|ios::in|ios::out);

    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }

    found = false;

    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));

        if (ac.retacno()==m)
        {
            ac.dep(amt);

            int pos = (-1) * static_cast<int>(sizeof(ac));

            transaction2 = "\n"+to_string(amt) + " Dollars have been transferred to your account from Acc No." + to_string(m) + " at " + date_time +"\n";
            char* char_array;
            char_array = &transaction2[0];
            ac.addTrans(char_array);

            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));


            cout << "\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if(!found)
        cout<<"\n\n Record Not Found ";
    else
    {
        update = "*" + to_string(amt) + " has been transferred from Acc. No " + to_string(n) + " To Acc. No " + to_string(m) + " at " + date_time + "\n";
        allTrans += update;
    }
}

//==========================SEARCH MENU==========================

void search()
{
    int option;

    int aCno;
    int lOanID;
    string nAme;
    string tImeCreated;

    int counter = 0;

    cout << "Welcome to the search menu\n";

    cout << "How would you like to find your account?"
         << "\n(1) Account Number\n(2) Account Name\n"
         << "(3) Account date of creation\n"
         << "(4) Account Loan ID\nEnter: ";
    cin >> option;
    if (option == 1)
    {
        bool found=false;

        account ac;
        fstream File;

        File.open("account.dat", ios::binary|ios::in|ios::out);

        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }

        cout << "Enter account Number: ";
        cin >> aCno;

        while(!File.eof() && !found)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));

            if (ac.retacno() == aCno)
            {
                cout << "The following is your account...\n";
                ac.show_account();

                int pos = (-1) * static_cast<int>(sizeof(ac));
                File.seekp(pos, ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                File.close();
            }
            else
                cout << "NOTHING FOUND";
        }
    }

    else if (option == 2)
    {
        bool found=false;

        account ac;
        fstream File;

        File.open("account.dat", ios::binary|ios::in|ios::out);

        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }

        cout << "Enter account name: ";
        cin >> nAme;

        while(!File.eof() && !found)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));

            if (ac.retacname() == nAme)
            {
                counter++;
                ac.show_account();
            }
        }
        if (counter > 0)
            cout << "\nA total of " << counter-1 << " accounts were found with the name: " << nAme;
        else
            cout << "No accounts were found with the name " << nAme;

        counter = 0;
        int pos = (-1) * static_cast<int>(sizeof(ac));
        File.seekp(pos, ios::cur);
        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
        File.close();
    }

    else if (option == 3)
    {
        bool found=false;

        account ac;
        fstream File;

        File.open("account.dat", ios::binary|ios::in|ios::out);

        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }

        cout << "Enter account Date of creation (Mo/Da/Year): ";
        cin >> tImeCreated;

        while(!File.eof() && !found)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));

            if (ac.retDate() == tImeCreated)
            {
                counter++;
                ac.show_account();
            }
        }
        if (counter > 0)
            cout << "\nA total of " << counter-1 << " accounts were found with the date: " << tImeCreated;
        else
            cout << "\nNo accounts were found with the date: " << tImeCreated;
        int pos = (-1) * static_cast<int>(sizeof(ac));
        File.seekp(pos, ios::cur);
        File.write(reinterpret_cast<char *> (&ac), sizeof(account));
        File.close();
    }

    if (option == 4)
    {
        bool found=false;

        account ac;
        fstream File;

        File.open("account.dat", ios::binary|ios::in|ios::out);

        if(!File)
        {
            cout<<"File could not be open !! Press any Key...";
            return;
        }

        cout << "Enter Loan ID: ";
        cin >> lOanID;

        while(!File.eof() && !found)
        {
            File.read(reinterpret_cast<char *> (&ac), sizeof(account));

            if (ac.retloanID() == lOanID)
            {
                cout << "The following is your account...\n";
                ac.show_account();

                int pos = (-1) * static_cast<int>(sizeof(ac));
                File.seekp(pos, ios::cur);
                File.write(reinterpret_cast<char *> (&ac), sizeof(account));
                File.close();
            }
            else
                cout << "NOTHING FOUND";
        }
    }
}

//==========================INTRODUCTION==========================

void intro()
{
    cout << "**************************************\n";
    cout << "|   WELCOME TO COMMONWEALTH BANKING  |\n";
    cout << "|                                    |\n";
    cout << "|       an intuitive and friendly    |\n";
    cout << "|       banking experience!          |\n";
    cout << "|          By Ernesto Enriquez       |\n";
    cout << "=====================================\n";
    //cin.get();
}


////this is a test