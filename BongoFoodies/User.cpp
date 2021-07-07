#include "User.h"

vector<User> Users_database;
int User::ID=0;

User::User()
{
    ID++;
    time_t tt;
    time (&tt);
    DOR=localtime(&tt);
}

User::~User()
{
    //dtor
}

void User:: Register()
{
    cout<<"\n\t **** Registration ****"<<endl;
    string pass;
    User u;

    cout<<"Name:";
    cin>>u.Name;

email_duplication_flag:
    cout<<"Email:";
    cin>>u.Email;
    for(unsigned int i=0; i<Users_database.size(); i++)
    {
        if(Users_database.at(i).Email==u.Email)
        {
            cout<<"This email is already in use!\n";
            goto email_duplication_flag;
        }
    }

    cout<<"Password:";
    cin>>pass;
    u.Password=pass;

    Users_database.push_back(u);
    cout<<"\n\nRegistration successful!\n"<<endl;

    Login();
}

void User::Login()
{
    cout<<"\n\t **** Login ****"<<endl;
    string email, pass;

email_nonexistent_flag:
    cout<<"Email:";
    cin>>email;
    for(unsigned int i=0; i<Users_database.size(); i++)
    {
        if(Users_database.at(i).Email==email)
        {

password_incorrect_flag:
            cout<<"Password:";
            cin>>pass;
            if(Users_database.at(i).Password!=pass)
            {
                cout<<"Incorrect password!\n";
                goto password_incorrect_flag;
            }

            cout<<"\n\nLogin successful!\n"<<endl;

            cout<<" (1)Do something\n (2)Logout\n\n";
            int choice;
            cout<<"Choice: ";
            cin>>choice;
            switch(choice)
            {
            case 1:
                cout<<"Doing something\n";
                exit(1);
            case 2:
                login_interface();
            }
        }
    }
    cout<<"User not found!\n";
    goto email_nonexistent_flag;

}

void login_interface()
{
    cout<<"\n\n1.New User\n2.Existing User\n\n";
    int choice;
    cout<<"Choice: ";
    cin>>choice;

    User user;
    switch(choice)
    {
    case 1:
        user.Register();
        break;
    case 2:
        user.Login();
        break;
    }
}
