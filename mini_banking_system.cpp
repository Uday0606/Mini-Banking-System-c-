#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Account
{
    private:
    int ac_number;
    string name;
    double balance;
    static int next_acnumber;// to auto-generate ac_number;

    public:
    //constructor
    Account(string ac_name)
    {
        name=ac_name;
        balance=1000.0;
        ac_number=next_acnumber++;
    }
    //getters
    int get_account_number()
    {
        return ac_number;
    }
    string get_name()
    {
        return name;
    }
    double get_balance()
    {
        return balance;
    }

    //Deposit method
    void deposit(double amount)
    {
        if(amount>0)
        {
            balance+=amount;
            cout<<"Deposited: "<<amount<<" successfully"<<endl;
        }
        else
        {
            cout<<"Invalid deposit amount"<<endl;
        }
    }

    //Withdraw method
    void withdraw(double amount)
    {
        if(amount>0 && amount<=balance)
        {
            balance-=amount;
            cout<<"Withdrew: "<<amount<<" successfully"<<endl;
        }
        else if(amount<=0)
        {
            cout<<"Invaild amount"<<endl;
        }
        else
        {
            cout<<"Insufficient funds"<<endl;
        }
    }

    //transfer
    void transfer(Account &to, double amount)
    {
        if(amount>0 && amount<=balance)
        {
            balance-=amount;
            to.balance+=amount;
            cout<<"Transfer successfully"<<endl;
        }
        else
        {
            cout<<"Invalid or Insufficient funds for transfer"<<endl;
        }
    }

    //display account details
    void display()
    {
        cout<<"\nAccount number: "<<ac_number;
        cout<<"\nName: "<<name;
        cout<<"\nBalance: "<<balance<<"\n";
    }

};
//Initialize static member
int Account::next_acnumber=1001;
void print_menu()
{
    cout<<endl;
    cout<<"    -- Mini Banking system---  "<<endl;
    cout<<"1.Create account"<<endl;
    cout<<"2.Deposit"<<endl;
    cout<<"3.Withdraw"<<endl;
    cout<<"4.Transfer"<<endl;
    cout<<"5.Check balance"<<endl;
    cout<<"6.Exit"<<endl;
    cout<<endl;

}
int main()
{
    vector<Account>accounts;
    int choice;
    while(1)
    {
        print_menu();
        cout<<"Enter your choice"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1: //crate account
            {
                string name;
                cout<<"Enter account holder name: ";
                cin.ignore();
                getline(cin,name);
                accounts.push_back(Account(name));
                accounts.back().display();
                cout<<"Account created successfully!"<<endl;
                break;
            }
            case 2://deposit amount
            {
            int ac_num;
            double amount;
            cout<<"Enter account number: ";
            cin>>ac_num;
            cout<<"Enter deposit amount: ";
            cin>>amount;

            bool found=false;
            for(int i=0;i<accounts.size();i++ )
            {
                if(accounts[i].get_account_number()==ac_num)
                {
                    accounts[i].deposit(amount);
                    found=true;
                    break;
                }
            }
            if(!found)
            cout<<"Account not found"<<endl; 
            break;
            }  
            
            case 3://withdraw amount
            {
                int ac_num;
                double amount;
                cout<<"Enter account number: ";
                cin>>ac_num;
                cout<<"Enter withdrawal amount: ";
                cin>>amount;

                bool found=false;
                for(int i=0;i<accounts.size();i++)
                {
                    if(accounts[i].get_account_number()==ac_num)
                    {
                        accounts[i].withdraw(amount);
                        found =true;
                        break;
                    }
                    
                } 
                if(!found)
                cout<<"Account not found"<<endl;
                break;
                
            }
            case 4://Transfer
            {
                int from_ac_num,to_ac_num;
                double amount;
                cout<<"Enter sender account number: ";
                cin>>from_ac_num;
                cout<<"Enter receiver account number: ";
                cin>>to_ac_num;
                cout<<"Enter amount to transfer: ";
                cin>>amount;

                Account *from_ac=nullptr,*to_ac=nullptr;

                //find accounts 
                for(int i=0;i<accounts.size();i++)
                {
                    if(accounts[i].get_account_number()==from_ac_num)
                    {
                        from_ac=&accounts[i];
                    }
                    if(accounts[i].get_account_number()==to_ac_num)
                    {
                        to_ac=&accounts[i];
                    }
                }
                if(from_ac!=nullptr && to_ac!=nullptr)
                {
                    from_ac->transfer(*to_ac,amount);
                }
                else
                {
                    cout<<"one or both account numbers are invalid"<<endl;
        
                }
                break;
            }
            case 5://check balance
            {
                int ac_num;
                cout<<"Enter account number: ";
                cin>>ac_num;

                bool found=false;
                for(int i=0;i<accounts.size();i++)
                {
                    if(accounts[i].get_account_number()==ac_num)
                    {
                        accounts[i].display();
                        found=true;
                        break;
                    }
                }
                if(!found)
                {
                    cout<<"Account not found"<<endl;
                }
                break;
            }


            case 6: //Exit
           cout <<"Thank you for banking with us! Have a great day!"<<endl;
            return 0;
            

            default://user entered other than in menu
            cout<<"Invalid choice!Please Try again"<<endl;

        }
    }
    return 0;
}