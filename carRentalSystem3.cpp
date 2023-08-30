#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <stdexcept>
using namespace std;
class total
{
public:
    static int totalUsers;
    static int totalDrivers;
    static int totalCars;
    static int totalRentedCars;
};
class admin
{
protected:
    string userName;
    string password; // default user name and password
public:
    void setUserName(string name)
    {
        userName = name;
    }
    void setPassword(string newPassword)
    {
        password = newPassword;
    }
    string getAdminName()
    {
        return userName;
    }
    string getAdminPassword()
    {
        return password;
    }
};
class userInfo
{
protected:
    string name;
    string cnic;
    string phoneNo;
    string address;

public:
    bool isValidNumber(const string &Number)
    {
        for (char c : Number)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    void setName()
    {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
    }
    void setCnic()
    {
        cout << "Enter your cnic: ";
        cin >> cnic;
        while (!isValidNumber(cnic))
        {
            cout << "Invalid input, Please enter a valid cnic number: ";
            cin >> cnic;
        }
    }
    void setPhone()
    {
        cout << "Enter your phone No: ";
        cin >> phoneNo;
        while (!isValidNumber(phoneNo))
        {
            cout << "Invalid input, Please enter a valid phone number: ";
            cin >> phoneNo;
        }
    }
    void setAddress()
    {
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
    }

    // Getters
    string getName()
    {
        return name;
    }
    string getCnic()
    {
        return cnic;
    }
    string getAddress()
    {
        return address;
    }
    string getPhone()
    {
        return phoneNo;
    }
};
class Car : public total
{
private:
    int carId;
    string carClass;
    string model;
    int year;
    string maker;
    string available;

public:
    void getCarData(ifstream &input, Car tCars[])
    {
        int i = 1;
        while (input >> tCars[i].carId >> ws && getline(input, tCars[i].carClass) >> ws && getline(input, tCars[i].model) >> tCars[i].year >> ws && getline(input, tCars[i].maker) >> ws && getline(input, tCars[i].available))
        {
            if (tCars[i].carId == (totalCars - 1))
            {
                break;
            }
            i++;
        }
    }
    void deleteCarData(Car tCars[], int id)
    {
        ifstream input;
        ofstream carFile, emp;

        carFile.open("./Files/temp.txt");
        input.open("./Files/carsData.txt");
        emp.open("./Files/carNo.txt");

        int i = 1;
        int newId = 1;
        while (input >> tCars[i].carId >> ws && getline(input, tCars[i].carClass) >> ws && getline(input, tCars[i].model) >> tCars[i].year >> ws && getline(input, tCars[i].maker) >> ws && getline(input, tCars[i].available))
        {
            if (tCars[i].carId == id)
            {
                continue;
            }
            tCars[i].carId = newId;
            carFile << tCars[i].getId() << endl;
            carFile << tCars[i].getClass() << endl;
            carFile << tCars[i].getModel() << endl;
            carFile << tCars[i].getYear() << endl;
            carFile << tCars[i].getMaker() << endl;
            carFile << tCars[i].getAvailable() << endl;
            i++;
            newId++;
        }
        tCars[1].totalCars--;
        emp << tCars[1].totalCars;
        emp.close();
        input.close();
        carFile.close();
        remove("./Files/carsData.txt");
        rename("./Files/temp.txt", "./Files/carsData.txt");
    }
    void setAvailable()
    {
    again:
        cout << "Enter 1 for Available or 2 for Not available";
        int choice;
        if (choice < 1 || choice > 2)
        {
            goto again;
        }
        switch (choice)
        {
        case 1:
            available = "It is available";
            break;
        case 2:
            available = "It is not available";
        }
    }
    void setAvailable(string temp)
    {
        available = temp;
    }
    void setId()
    {
        carId = totalCars;
    }
    void setCarClass()
    {
        int choice;
        cout << "1: Hatchback" << endl
             << "2: Sedan" << endl
             << "3: Suv" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        if (choice < 1 || choice > 3)
        {
            while (choice < 1 || choice > 3)
            {
                cout << "Invalid Input, Try again: ";
                cin >> choice;
            }
        }
        switch (choice)
        {
        case 1:
            carClass = "Hatchback";
            break;
        case 2:
            carClass = "Sedan";
            break;
        case 3:
            carClass = "Suv";
            break;
        }
    }
    void setModel()
    {
        cout << "Enter model: ";
        cin >> model;
    }
    void setYear()
    {
        cout << "Enter manufactured year of the car: ";
        while (true)
        {
            try
            {
                cin >> year;
                if (cin.fail())
                {
                    throw runtime_error("Invalid Input");
                }
                break;
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters until newline

                cout << "Invalid input, Please Enter again: ";
            }
        }
    }
    void setMaker()
    {
        cout << "Who manufactured the car: ";
        cin >> maker;
    }
    // Getters
    int getId()
    {
        return carId;
    }
    string getClass()
    {
        return carClass;
    }
    string getModel()
    {
        return model;
    }
    int getYear()
    {
        return year;
    }
    string getMaker()
    {
        return maker;
    }
    string getAvailable()
    {
        return available;
    }
};
class Users : public userInfo, public total
{
private:
    int userId;
    string email;
    string userPassword;

public:
    void setId()
    {
        userId = totalUsers;
    }
    void setEmail(string E)
    {
        email = E;
    }
    void setuserPassword(string P)
    {
        userPassword = P;
    }
    void readUsersData(ifstream &input, Users tUsers[])
    {
        int i = 1;
        while (input >> tUsers[i].userId >> ws && getline(input, tUsers[i].name) >> ws && getline(input, tUsers[i].address) >> tUsers[i].cnic >> tUsers[i].phoneNo >> ws && getline(input, tUsers[i].email) >> ws && getline(input, tUsers[i].userPassword))
        {
            if (tUsers[i].userId == (totalUsers - 1))
            {
                break;
            }
            i++;
        }
    }
    void deleteUserData(Users tUsers[], int id)
    {
        ifstream input;
        ofstream userFile, emp;

        userFile.open("./Files/temp.txt");
        input.open("./Files/userData.txt");
        emp.open("./Files/userNo.txt");

        int i = 1;
        int newId = 1;
        while (input >> tUsers[i].userId >> ws && getline(input, tUsers[i].name) >> ws && getline(input, tUsers[i].address) >> tUsers[i].cnic >> tUsers[i].phoneNo >> ws && getline(input, tUsers[i].email) >> ws && getline(input, tUsers[i].userPassword))
        {
            if (tUsers[i].userId == id)
            {
                continue;
            }
            tUsers[i].userId = newId;
            userFile << tUsers[i].getId() << endl;
            userFile << tUsers[i].getName() << endl;
            userFile << tUsers[i].getAddress() << endl;
            userFile << tUsers[i].getCnic() << endl;
            userFile << tUsers[i].getPhone() << endl;
            userFile << tUsers[i].getEmail() << endl;
            userFile << tUsers[i].getuserPassword() << endl;
            i++;
        }
        tUsers[1].totalUsers--;
        emp << tUsers[1].totalUsers;
        emp.close();
        input.close();
        userFile.close();
        remove("./Files/userData.txt");
        rename("./Files/temp.txt", "./Files/userData.txt");
    }
    // Getters
    int getId()
    {
        return userId;
    }
    string getEmail()
    {
        return email;
    }
    string getuserPassword()
    {
        return userPassword;
    }
};
class rentedCars : public Car
{
protected:
    int realId;
    string sMonth;
    string sDay;
    string lMonth;
    string lDay;
    string sDate;
    string lDate;
    string driver;
    string tEmail;
    int rentedId;
    int day;
    int rent;
    string carModel;
    int carYear;

public:
    void getRentedCarData(ifstream &input, rentedCars rCars[])
    {
        int i = 1;
        while (input >> rCars[i].realId >> rCars[i].rentedId >> ws && getline(input, rCars[i].sDate) >> ws && getline(input, rCars[i].lDate) >> rCars[i].day >> ws && getline(input, rCars[i].sMonth) >> ws && getline(input, rCars[i].carModel) >> rCars[i].carYear >> rCars[i].rent >> rCars[i].tEmail)
        {
            if (rCars[i].realId == (totalRentedCars - 1))
            {
                break;
            }
            i++;
        }
    }
    void setId(int i)
    {
        rentedId = i;
    }
    void setRealId()
    {
        realId = totalRentedCars;
    }
    void setSMonth()
    {
        cout << "Enter starting month:  ";
        cin >> sMonth;
    }
    void setLMonth()
    {
        cout << "Enter the the ending month:  ";
        cin >> lMonth;
    }
    void setTEmail(string t)
    {
        tEmail = t;
    }
    void setSDay()
    {
        cout << "Enter starting date: ";
        while (true)
        {
            try
            {
                cin >> sDay;
                if (cin.fail())
                {
                    throw runtime_error("Invalid Input");
                }
                break;
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters until newline

                cout << "Invalid input, Please Enter again: ";
            }
        }
    }
    void setLDay()
    {
        cout << "Enter Last Date: ";
        while (true)
        {
            try
            {
                cin >> lDay;
                if (cin.fail())
                {
                    throw runtime_error("Invalid Input");
                }
                break;
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters until newline

                cout << "Invalid input, Please Enter again: ";
            }
        }
    }
    void setDate()
    {
        sDate = sDay + "-" + sMonth;
        lDate = lDay + "-" + lMonth;
    }
    void setRent(int r)
    {
        rent = r;
    }
    void setDays()
    {
        cout << "Note: Enter the days according to your starting and ending date, entering false value will result in ban" << endl;
        cout << "Enter How many days do you want the car for: " << endl;
        cin >> day;
    }

    // Getters
    int getRealId()
    {
        return realId;
    }
    string getCarModel()
    {
        return carModel;
    }
    int getCarYear()
    {
        return carYear;
    }
    string getSMonth()
    {
        return sMonth;
    }
    int getRentedId()
    {
        return rentedId;
    }
    int getRent()
    {
        return rent;
    }
    string getSDate()
    {
        return sDate;
    }
    string getLDate()
    {
        return lDate;
    }
    string getDriver()
    {
        return driver;
    }
    int getDay()
    {
        return day;
    }
    string getTEmail()
    {
        return tEmail;
    }
};
class Driver : public userInfo, public total
{
private:
    int driverId;
    string drivingLicense;
    string driverAvailable;

public:
    void getDriverData(ifstream &input, Driver drivers[])
    {
        int i = 1;
        while (input >> drivers[i].driverId >> ws && getline(input, drivers[i].name) >> ws && getline(input, drivers[i].cnic) >> drivers[i].drivingLicense >> ws && getline(input, drivers[i].driverAvailable))
        {
            if (drivers[i].driverId == (totalDrivers - 1))
            {
                break;
            }
            i++;
        }
    }
    void deleteDriverData(Driver drivers[], int id)
    {
        ifstream input;
        ofstream driverFile, emp;

        driverFile.open("./Files/temp.txt");
        input.open("./Files/driverData.txt");
        emp.open("./Files/driverNo.txt");

        int i = 1;
        int newId = 1;
        while (input >> drivers[i].driverId >> ws && getline(input, drivers[i].name) >> ws && getline(input, drivers[i].cnic) >> drivers[i].drivingLicense >> ws && getline(input, drivers[i].driverAvailable))
        {
            if (drivers[i].driverId == id)
            {
                continue;
            }
            drivers[i].driverId = newId;
            driverFile << drivers[i].getDriverId() << endl;
            driverFile << drivers[i].getName() << endl;
            driverFile << drivers[i].getCnic() << endl;
            driverFile << drivers[i].getDrivingLicense() << endl;
            driverFile << drivers[i].getAvailable() << endl;
            i++;
            newId++;
        }
        drivers[1].totalDrivers--;
        emp << drivers[1].totalDrivers;
        emp.close();
        input.close();
        driverFile.close();
        remove("./Files/driverData.txt");
        rename("./Files/temp.txt", "./Files/driverData.txt");
    }
    void setDrivingLicense()
    {
        cout << "Enter Driving License: ";
        cin >> drivingLicense;
    }
    void setDriverId()
    {
        driverId = totalDrivers;
    }
    void setAvailable()
    {
        cout << "Enter the status of driver: ";
        cin >> driverAvailable;
    }
    void setAvailable(string a)
    {
        driverAvailable = a;
    }

    string getDrivingLicense()
    {
        return drivingLicense;
    }
    int getDriverId()
    {
        return driverId;
    }
    string getAvailable()
    {
        return driverAvailable;
    }
};

int total::totalUsers = 0;
int total::totalDrivers = 0;
int total::totalCars = 0;
int total::totalRentedCars = 0;

// Functions for Everything
void welcome(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials);
void userLogin(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[]);
void userMenu(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], string &tempEmail, Driver drivers[]);
void userRegister(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[]);
void carRent(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], string &tempEmail, Driver drivers[]);
void adminLogin(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials);
void addCar(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials);
void addDriver(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials);
void editNamePassword(admin &credentials);
void editDriver(total &obj, Driver drivers[]);
void editCar(total &obj, Car tCars[]);
void viewUsers(total &obj, Users tUsers[]);
void viewCar(total &obj, Car tCars[]);
void viewDrivers(total &obj, Driver drivers[]);
void deleteCar(Car tCars[]);
void deleteDriver(Driver drivers[]);
void income(total &obj, rentedCars rCars[]);
void deleteUser(Users tUsers[]);

int main()
{
    total inc;
    ifstream fin;
    admin obj;
    string tempE, tempP;
    Driver drivers[50];
    Users tUsers[100];
    Car tCars[100];
    rentedCars rCars[100];

    fin.open("./Files/userData.txt");
    tUsers[1].readUsersData(fin, tUsers);
    fin.close();

    fin.open("./Files/carsData.txt");
    tCars[1].getCarData(fin, tCars);
    fin.close();

    fin.open("./Files/driverData.txt");
    drivers[1].getDriverData(fin, drivers);
    fin.close();

    fin.open("./Files/rentedCars.txt");
    rCars[1].getRentedCarData(fin, rCars);
    fin.close();
    cout << rCars[1].getCarModel();

    fin.open("./Files/userNo.txt");
    fin >> inc.totalUsers;
    fin.close();

    fin.open("./Files/adminName.txt");
    fin >> tempE;
    fin.close();

    fin.open("./Files/adminPassword.txt");
    fin >> tempP;
    fin.close();

    obj.setUserName(tempE);
    obj.setPassword(tempP);

    fin.open("./Files/carNo.txt");
    fin >> inc.totalCars;
    fin.close();

    fin.open("./Files/driverNo.txt");
    fin >> inc.totalDrivers;
    fin.close();

    fin.open("./Files/rentedNo.txt");
    fin >> inc.totalRentedCars;
    fin.close();

    welcome(inc, tUsers, tCars, rCars, drivers, obj);
}
void welcome(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials)
{
    cout << setw(80) << "Welcome to Car Rental System" << endl;
again:
    cout << "What are you: " << endl
         << "1: User" << endl
         << "2: Admin" << endl;
    int choice;
    cout << "Enter choice: ";
    while (true)
    {
        try
        {
            cin >> choice;
            if (cin.fail())
            {
                throw runtime_error("Invalid Input");
            }
            break;
        }
        catch (const runtime_error &e)
        {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters until newline

            cout << "Invalid input, Please Enter again: ";
        }
    }
    // cin >> choice;
    if (choice < 1 || choice > 2)
    {
        cout << "Invalid choice" << endl;
        goto again;
    }
    switch (choice)
    {
    case 1:
        cout << endl
             << endl;
        userLogin(obj, tUsers, tCars, rCars, drivers);
        break;
    case 2:
        cout << endl
             << endl;
        string tempName, tempPassword;
    again2:
        cout << "Enter User Name: ";
        cin >> tempName;
        cout << "Enter Password: ";
        cin >> tempPassword;
        if (tempName == credentials.getAdminName() && tempPassword == credentials.getAdminPassword())
        {
            cout << endl
                 << endl;
            adminLogin(obj, tUsers, tCars, rCars, drivers, credentials);
        }
        else
        {
            goto again2;
        }
        break;
    }
}
void userLogin(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[])
{

    for (int i = 1; i < 50; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(54) << "User Login" << endl;
again2:
    cout << "Login or Register" << endl;
    int choice;
    cout << "Enter 1 for login or 2 for Register: ";
    cin >> choice;
    if (choice < 1 || choice > 2)
    {
        cout << "Invalid choice" << endl;
        goto again2;
    }
    switch (choice)
    {
    case 1:
    {
        string temporaryEmail, temp2;
        bool validCredentials = false;

        while (validCredentials == false)
        {
            cout << "Enter your email: ";
            cin >> temporaryEmail;
            cout << "Enter your password: ";
            cin >> temp2;

            for (int i = 1; i < obj.totalUsers; i++)
            {
                if (temporaryEmail == tUsers[i].getEmail() && temp2 == tUsers[i].getuserPassword())
                {
                    cout << endl
                         << endl;
                    userMenu(obj, tUsers, tCars, rCars, temporaryEmail, drivers);
                    validCredentials = true; // Exit the loop if credentials are valid
                    break;
                }
            }

            if (validCredentials == false)
            {
                int choice2;
                cout << "Wrong password or email" << endl;
            again:
                cout << "1: Try Again" << endl;
                cout << "2: Register" << endl;
                cout << "Enter your choice: ";
                cin >> choice2;

                if (choice2 == 1)
                {
                    // Continue to the next iteration of the while loop to try again
                }
                else if (choice2 == 2)
                {
                    cout << endl
                         << endl;
                    userRegister(obj, tUsers, tCars, rCars, drivers);
                    break; // Exit the loop after registration
                }
                else
                {
                    cout << "Invalid choice" << endl;
                    goto again; // This will only ask again for choice2,
                }
            }
        }
    }
    break;

    case 2:
        cout << endl
             << endl;
        userRegister(obj, tUsers, tCars, rCars, drivers);
        break;
    }
}
void userRegister(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[])
{
    string tempEmail, tempPassword;
    for (int i = 1; i < 50; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(54) << "User Register" << endl;
    tUsers[obj.totalUsers].setId();
    tUsers[obj.totalUsers].setName();
    tUsers[obj.totalUsers].setCnic();
    tUsers[obj.totalUsers].setPhone();
    tUsers[obj.totalUsers].setAddress();

    bool isOk = false;
    while (isOk == false)
    {
        cout << "Enter Email: ";
        cin >> tempEmail;
        cout << "Enter Password: ";
        cin >> tempPassword;
        if (tUsers[1].getEmail() == "")
        {
            tUsers[obj.totalUsers].setEmail(tempEmail);
            tUsers[obj.totalUsers].setuserPassword(tempPassword);
            ofstream fout;
            fout.open("./Files/userData.txt", ios::app);

            fout << tUsers[obj.totalUsers].getId() << endl;
            fout << tUsers[obj.totalUsers].getName() << endl;
            fout << tUsers[obj.totalUsers].getAddress() << endl;
            fout << tUsers[obj.totalUsers].getCnic() << endl;
            fout << tUsers[obj.totalUsers].getPhone() << endl;
            fout << tUsers[obj.totalUsers].getEmail() << endl;
            fout << tUsers[obj.totalUsers].getuserPassword() << endl;
            fout.close();

            fout.open("./Files/userNo.txt");
            obj.totalUsers++;
            fout << obj.totalUsers;
            fout.close();
            cout << endl
                 << endl;
            userLogin(obj, tUsers, tCars, rCars, drivers);
        }
        for (int i = 1; i < obj.totalUsers; i++)
        {
            if (tempEmail == tUsers[i].getEmail() || tempPassword == tUsers[i].getuserPassword())
            {
                cout << "This email or password is already in use, please Enter again: " << endl;
            }
            else
            {
                isOk = true;
                tUsers[obj.totalUsers].setEmail(tempEmail);
                tUsers[obj.totalUsers].setuserPassword(tempPassword);
                break;
            }
        }
    }
    ofstream fout;
    fout.open("./Files/userData.txt", ios::app);

    fout << tUsers[obj.totalUsers].getId() << endl;
    fout << tUsers[obj.totalUsers].getName() << endl;
    fout << tUsers[obj.totalUsers].getAddress() << endl;
    fout << tUsers[obj.totalUsers].getCnic() << endl;
    fout << tUsers[obj.totalUsers].getPhone() << endl;
    fout << tUsers[obj.totalUsers].getEmail() << endl;
    fout << tUsers[obj.totalUsers].getuserPassword() << endl;
    fout.close();

    fout.open("./Files/userNo.txt");
    obj.totalUsers++;
    fout << obj.totalUsers;
    fout.close();
    cout << endl
         << endl;
    userLogin(obj, tUsers, tCars, rCars, drivers);
}
void userMenu(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], string &tempEmail, Driver drivers[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "User Menu" << endl
         << endl;
    cout << "Welcome What would you like to do" << endl;
    cout << "1: Rent a Car" << endl;
    cout << "2: Quit" << endl;
    int choice;
again:
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice < 1 || choice > 2)
    {
        goto again;
    }
    switch (choice)
    {
    case 1:
        cout << endl
             << endl;
        carRent(obj, tUsers, tCars, rCars, tempEmail, drivers);
        break;
    case 2:
        break;
    }
}
void carRent(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], string &tempEmail, Driver drivers[])
{
start:
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "Rent a Car" << endl;
restart:
    cout << "Which class do you want?" << endl;
    int choice;
    cout << "1: Hatchback" << endl
         << "2: Sedan" << endl
         << "3: Suv" << endl
         << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    if (choice < 1 || choice > 3)
    {
        while (choice < 1 || choice > 3)
        {
            cout << "Invalid Input, Try again: ";
            cin >> choice;
        }
    }
    int sedanCount = 0;     // Initialize a variable to count the number of sedan cars
    int hatchBackCount = 0; // Initialize a variable to count the number of sedan cars
    int suvCount = 0;       // Initialize a variable to count the number of sedan cars
    switch (choice)
    {
    case 1:
        for (int i = 1; i < obj.totalCars; i++)
        {
            if (tCars[i].getClass() == "Hatchback")
            {
                if (tCars[i].getAvailable() == "It is available")
                {
                    cout << "Car Id: " << tCars[i].getId() << endl
                         << "Car Class: " << tCars[i].getClass() << endl
                         << "Car model: " << tCars[i].getModel() << endl
                         << "Car year: " << tCars[i].getYear() << endl
                         << "Car maker: " << tCars[i].getMaker() << endl
                         << "Car Availability: " << tCars[i].getAvailable() << endl;
                    hatchBackCount++;
                }
            }
            cout << endl;
        }
        if (hatchBackCount == 0)
        {
            cout << "There is no hatchBackCar" << endl;
            goto start;
        }

        break;
    case 2:

        // Loop through all cars to find sedan cars that are available
        for (int i = 1; i < obj.totalCars; i++)
        {
            if (tCars[i].getClass() == "Sedan" && tCars[i].getAvailable() == "It is available")
            {
                cout << "Car Id: " << tCars[i].getId() << endl
                     << "Car Class: " << tCars[i].getClass() << endl
                     << "Car model: " << tCars[i].getModel() << endl
                     << "Car year: " << tCars[i].getYear() << endl
                     << "Car maker: " << tCars[i].getMaker() << endl
                     << "Car Availability: " << tCars[i].getAvailable() << endl;

                sedanCount++; // Increment the sedan count
            }
            cout << endl;
        }
        // Check if there are no sedan cars available
        if (sedanCount == 0)
        {
            cout << "There is no sedan car" << endl;
            goto start;
        }
        break;
    case 3:
        for (int i = 1; i < obj.totalCars; i++)
        {
            if (tCars[i].getClass() == "Suv")
            {
                if (tCars[i].getAvailable() == "It is available")
                {
                    cout << "Car Id: " << tCars[i].getId() << endl
                         << "Car Class: " << tCars[i].getClass() << endl
                         << "Car model: " << tCars[i].getModel() << endl
                         << "Car year: " << tCars[i].getYear() << endl
                         << "Car maker: " << tCars[i].getMaker() << endl
                         << "Car Availability: " << tCars[i].getAvailable() << endl;
                    suvCount++;
                }
            }
            cout << endl;
        }
        if (suvCount == 0)
        {
            cout << "There is no suv car" << endl;
            goto start;
        }
        break;
    }
    cout << "Enter the id of the car you want to rent: ";
    int choice2;
    cin >> choice2;
    if (choice2 < 1 || choice2 >= obj.totalCars)
    {
        while (choice2 < 1 || choice2 >= obj.totalCars)
        {
            cout << "Enter again: ";
            cin >> choice2;
        }
    }
    rCars[obj.totalRentedCars].setRealId();
    rCars[obj.totalRentedCars].setSDay();
    rCars[obj.totalRentedCars].setSMonth();
    rCars[obj.totalRentedCars].setLDay();
    rCars[obj.totalRentedCars].setLMonth();
    rCars[obj.totalRentedCars].setDate();
    rCars[obj.totalRentedCars].setDays();
    rCars[obj.totalRentedCars].setId(choice2);
    rCars[obj.totalRentedCars].setTEmail(tempEmail);

    int idChoice;
    string driverChoice;
again:
    cout << "Do you want a driver? (Y/N)" << endl;
    cin >> driverChoice;
    if (driverChoice == "N")
    {
        int tempRent;
        tempRent = rCars[obj.totalRentedCars].getDay() * 5000;
        rCars[obj.totalRentedCars].setRent(tempRent);
        cout << "Do you want to make any changes? ";
        string changeChoice;
        cin >> changeChoice;
        if (changeChoice == "Y")
        {
            goto restart;
        }
        else if (changeChoice == "N")
        {
            ofstream fout, rentedCarNo, carFile;
            rentedCarNo.open("./Files/rentedNo.txt");
            fout.open("./Files/rentedCars.txt", ios::app);
            carFile.open("./Files/carsData.txt");

            fout << rCars[obj.totalRentedCars].getRealId() << endl;
            fout << rCars[obj.totalRentedCars].getRentedId() << endl;
            fout << rCars[obj.totalRentedCars].getSDate() << endl;
            fout << rCars[obj.totalRentedCars].getLDate() << endl;
            fout << rCars[obj.totalRentedCars].getDay() << endl;
            fout << rCars[obj.totalRentedCars].getSMonth() << endl;
            fout << tCars[choice2].getModel() << endl;
            fout << tCars[choice2].getYear() << endl;
            fout << rCars[obj.totalRentedCars].getRent() << endl;
            fout << rCars[obj.totalRentedCars].getTEmail() << endl;

            tCars[choice2].setAvailable("It is not available");
            for (int i = 1; i < obj.totalCars; i++)
            {
                carFile << tCars[i].getId() << endl;
                carFile << tCars[i].getClass() << endl;
                carFile << tCars[i].getModel() << endl;
                carFile << tCars[i].getYear() << endl;
                carFile << tCars[i].getMaker() << endl;
                carFile << tCars[i].getAvailable() << endl;
            }
            obj.totalRentedCars++;
            rentedCarNo << obj.totalRentedCars;
            rentedCarNo.close();
            fout.close();
            carFile.close();
            userMenu(obj, tUsers, tCars, rCars, tempEmail, drivers);
        }
    }
    if (driverChoice == "Y")
    {
        for (int i = 1; i < obj.totalDrivers; i++)
        {
            cout << "Driver Id: " << drivers[i].getDriverId() << endl;
            cout << "Driver Name: " << drivers[i].getName() << endl
                 << endl;
        }
        cout << endl;
    enterAgain:
        cout << "Enter the id of the driver you want to hire: ";
        cin >> idChoice;
        if (idChoice >= obj.totalDrivers)
        {
            goto enterAgain;
        }
        else if (drivers[idChoice].getAvailable() == "It is not available")
        {
            cout << "This driver is already booked, please enter again" << endl;
            goto enterAgain;
        }
    }
    int tempRent;
    tempRent = rCars[obj.totalRentedCars].getDay() * 8000;
    rCars[obj.totalRentedCars].setRent(tempRent);
    cout << "Do you want to make any changes? ";
    string changeChoice;
    cin >> changeChoice;
    if (changeChoice == "Y")
    {
        goto restart;
    }
    else if (changeChoice == "N")
    {
        drivers[idChoice].setAvailable("It is not available");
        ofstream fout, driverFile, rentedCarNo, carFile;
        rentedCarNo.open("./Files/rentedNo.txt");
        fout.open("./Files/rentedCars.txt", ios::app);
        driverFile.open("./Files/driverData.txt");
        carFile.open("./Files/carsData.txt");

        for (int i = 1; i < obj.totalDrivers; i++)
        {
            driverFile << drivers[i].getDriverId() << endl;
            driverFile << drivers[i].getName() << endl;
            driverFile << drivers[i].getCnic() << endl;
            driverFile << drivers[i].getDrivingLicense() << endl;
            driverFile << drivers[i].getAvailable() << endl;
        }
        fout << rCars[obj.totalRentedCars].getRealId() << endl;
        fout << rCars[obj.totalRentedCars].getRentedId() << endl;
        fout << rCars[obj.totalRentedCars].getSDate() << endl;
        fout << rCars[obj.totalRentedCars].getLDate() << endl;
        fout << rCars[obj.totalRentedCars].getDay() << endl;
        fout << rCars[obj.totalRentedCars].getSMonth() << endl;
        fout << tCars[choice2].getModel() << endl;
        fout << tCars[choice2].getYear() << endl;
        fout << rCars[obj.totalRentedCars].getRent() << endl;
        fout << rCars[obj.totalRentedCars].getTEmail() << endl;

        tCars[choice2].setAvailable("It is not available");
        for (int i = 1; i < obj.totalCars; i++)
        {
            carFile << tCars[i].getId() << endl;
            carFile << tCars[i].getClass() << endl;
            carFile << tCars[i].getModel() << endl;
            carFile << tCars[i].getYear() << endl;
            carFile << tCars[i].getMaker() << endl;
            carFile << tCars[i].getAvailable() << endl;
        }
        obj.totalRentedCars++;
        rentedCarNo << obj.totalRentedCars;
        rentedCarNo.close();
        fout.close();
        carFile.close();
        driverFile.close();
        userMenu(obj, tUsers, tCars, rCars, tempEmail, drivers);
    }
}
void adminLogin(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials)
{
    cout << "Welcome to admin panel, What would you like to do?" << endl;
    cout << "1: Add a car" << endl;
    cout << "2: Add a driver" << endl;
    cout << "3: Change user name or password" << endl;
    cout << "4: Edit Driver" << endl;
    cout << "5: Edit Car" << endl;
    cout << "6: View Users" << endl;
    cout << "7: View Cars" << endl;
    cout << "8: View Drivers" << endl;
    cout << "9: Delete Car" << endl;
    cout << "10: Delete Driver" << endl;
    cout << "11: View Income" << endl;
    cout << "12: Delete User" << endl;
    int choice;
    while (choice < 1 || choice > 12)
    {
        cout << "Enter your choice: ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        cout << endl
             << endl;
        addCar(obj, tUsers, tCars, rCars, drivers, credentials);
        break;
    case 2:
        cout << endl
             << endl;
        addDriver(obj, tUsers, tCars, rCars, drivers, credentials);
        break;
    case 3:
        cout << endl
             << endl;
        editNamePassword(credentials);
        break;
    case 4:
        cout << endl
             << endl;
        editDriver(obj, drivers);
        break;
    case 5:
        cout << endl
             << endl;
        editCar(obj, tCars);
        break;
    case 6:
        cout << endl
             << endl;
        viewUsers(obj, tUsers);
        break;
    case 7:
        cout << endl
             << endl;
        viewCar(obj, tCars);
        break;
    case 8:
        cout << endl
             << endl;
        viewDrivers(obj, drivers);
        break;
    case 9:
        cout << endl
             << endl;
        deleteCar(tCars);
        break;
    case 10:
        cout << endl
             << endl;
        deleteDriver(drivers);
        break;
    case 11:
        cout << endl
             << endl;
        income(obj, rCars);
        break;
    case 12:
        cout << endl
             << endl;
        deleteUser(tUsers);
        break;
    }
    cout << endl
         << endl;
    adminLogin(obj, tUsers, tCars, rCars, drivers, credentials);
}
void addCar(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials)
{
    ofstream carFile, carNo;
    carFile.open("./Files/carsData.txt", ios::app);
    carNo.open("./Files/carNo.txt");
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(45) << "Add a car" << endl;
    cout << "Enter data of car " << obj.totalCars << endl
         << endl;

    tCars[obj.totalCars].setId();
    tCars[obj.totalCars].setModel();
    tCars[obj.totalCars].setCarClass();
    tCars[obj.totalCars].setMaker();
    tCars[obj.totalCars].setYear();
    tCars[obj.totalCars].setAvailable("It is available");

    carFile << tCars[obj.totalCars].getId() << endl;
    carFile << tCars[obj.totalCars].getClass() << endl;
    carFile << tCars[obj.totalCars].getModel() << endl;
    carFile << tCars[obj.totalCars].getYear() << endl;
    carFile << tCars[obj.totalCars].getMaker() << endl;
    carFile << tCars[obj.totalCars].getAvailable() << endl;
    carFile.close();

    obj.totalCars++;
    carNo << obj.totalCars;
    carNo.close();
}
void addDriver(total &obj, Users tUsers[], Car tCars[], rentedCars rCars[], Driver drivers[], admin &credentials)
{
    ofstream driverFile, driverNo;
    driverFile.open("./Files/driverData.txt", ios::app);
    driverNo.open("./Files/driverNo.txt");
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(45) << "Add Driver" << endl;
    cout << "Enter data of driver " << obj.totalDrivers << endl
         << endl;

    drivers[obj.totalDrivers].setDriverId();
    drivers[obj.totalDrivers].setName();
    drivers[obj.totalDrivers].setCnic();
    drivers[obj.totalDrivers].setDrivingLicense();
    drivers[obj.totalDrivers].setAvailable("It is available");

    driverFile << drivers[obj.totalDrivers].getDriverId() << endl;
    driverFile << drivers[obj.totalDrivers].getName() << endl;
    driverFile << drivers[obj.totalDrivers].getCnic() << endl;
    driverFile << drivers[obj.totalDrivers].getDrivingLicense() << endl;
    driverFile << drivers[obj.totalDrivers].getAvailable() << endl;

    obj.totalDrivers++;
    driverNo << obj.totalDrivers;
    driverFile.close();
    driverNo.close();
}
void editNamePassword(admin &credentials)
{
    string tempN, tempP; // for new user name and password
    ofstream fout;
    cout << "Enter 1 For user name or 2 for password";
    int editChoice;
    cin >> editChoice;
    switch (editChoice)
    {
    case 1:
        fout.open("./Files/adminName.txt");
        cout << "Enter your new user name: ";
        cin >> tempN;
        credentials.setUserName(tempN);
        fout << credentials.getAdminName() << endl;
        fout.close();
        break;
    case 2:
        fout.open("./Files/adminPassword.txt");
        cout << "Enter your new password: ";
        cin >> tempP;
        credentials.setPassword(tempP);
        fout << credentials.getAdminPassword() << endl;
        fout.close();
        break;
    }
}
void editDriver(total &obj, Driver drivers[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "Edit a Driver" << endl;
    cout << "Enter the id of the driver you want to edit: " << endl;
    int editChoice;
    cin >> editChoice;
    while (editChoice >= obj.totalDrivers)
    {
        cout << "Enter again: ";
        cin >> editChoice;
    }

    cout << "1) Driver Name: " << drivers[editChoice].getName() << endl;
    cout << "2) Driver Cnic: " << drivers[editChoice].getCnic() << endl;
    cout << "3) Driving License: " << drivers[editChoice].getDrivingLicense() << endl;
    cout << "4) Available: " << drivers[editChoice].getAvailable() << endl
         << endl;

    int fieldChoice;
    cout << "Enter the field no you want to edit: ";
    cin >> fieldChoice;
    while (fieldChoice < 1 || fieldChoice > 4)
    {
        cout << "Invalid Number, Enter again: ";
        cin >> fieldChoice;
    }
    switch (fieldChoice)
    {
    case 1:
        cout << endl;
        drivers[editChoice].setName();
        break;
    case 2:
        cout << endl;
        drivers[editChoice].setCnic();
        break;
    case 3:
        cout << endl;
        drivers[editChoice].setDrivingLicense();
        break;
    case 4:
        cout << endl;
        if (drivers[editChoice].getAvailable() == "It is available")
        {
            drivers[editChoice].setAvailable("It is not available");
        }
        else
        {
            drivers[editChoice].setAvailable("It is available");
        }
        break;
    }
    ofstream driverFile;
    driverFile.open("./Files/driverData.txt");
    for (int i = 1; i < obj.totalDrivers; i++)
    {
        driverFile << drivers[i].getDriverId() << endl;
        driverFile << drivers[i].getName() << endl;
        driverFile << drivers[i].getCnic() << endl;
        driverFile << drivers[i].getDrivingLicense() << endl;
        driverFile << drivers[i].getAvailable() << endl;
    }
    driverFile.close();
}
void editCar(total &obj, Car tCars[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "Edit a Car" << endl;
    cout << "Enter the id of the car you want to edit: " << endl;
    int editChoice;
    cin >> editChoice;
    while (editChoice >= obj.totalCars)
    {
        cout << "Enter again: ";
        cin >> editChoice;
    }
    cout << "1) Car Class: " << tCars[editChoice].getClass() << endl
         << "2) Car model: " << tCars[editChoice].getModel() << endl
         << "3) Car year: " << tCars[editChoice].getYear() << endl
         << "4) Car maker: " << tCars[editChoice].getMaker() << endl
         << "5) Car Availability: " << tCars[editChoice].getAvailable() << endl
         << endl;
    int fieldChoice;
    cout << "Enter the field no you want to edit: ";
    cin >> fieldChoice;
    while (fieldChoice < 1 || fieldChoice > 4)
    {
        cout << "Invalid Number, Enter again: ";
        cin >> fieldChoice;
    }
    switch (fieldChoice)
    {
    case 1:
        cout << endl;
        tCars[fieldChoice].setCarClass();
        break;
    case 2:
        cout << endl;
        tCars[fieldChoice].setModel();
        break;
    case 3:
        cout << endl;
        tCars[fieldChoice].setYear();
        break;
    case 4:
        cout << endl;
        tCars[fieldChoice].setMaker();
        break;
    case 5:
        cout << endl;
        if (tCars[editChoice].getAvailable() == "It is available")
        {
            tCars[editChoice].setAvailable("It is not available");
        }
        else
        {
            tCars[editChoice].setAvailable("It is available");
        }
        break;
    }
    ofstream carFile;
    carFile.open("./Files/carsData.txt");
    for (int i = 1; i < obj.totalCars; i++)
    {
        carFile << tCars[i].getId() << endl;
        carFile << tCars[i].getClass() << endl;
        carFile << tCars[i].getModel() << endl;
        carFile << tCars[i].getYear() << endl;
        carFile << tCars[i].getMaker() << endl;
        carFile << tCars[i].getAvailable() << endl;
    }
    carFile.close();
}
void viewUsers(total &obj, Users tUsers[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "View Users" << endl;
    cout << "Do you want to view all users or a specific user (1 or 2): " << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "Enter again: ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        cout << "Enter the id of the user: ";
        int idChoice;
        cin >> idChoice;
        cout << endl
             << endl;
        cout << "User Id:" << tUsers[idChoice].getId() << endl;
        cout << "User Name:" << tUsers[idChoice].getName() << endl;
        cout << "User Address:" << tUsers[idChoice].getAddress() << endl;
        cout << "User Cnic:" << tUsers[idChoice].getCnic() << endl;
        cout << "User Phone No:" << tUsers[idChoice].getPhone() << endl;
        cout << "User Email:" << tUsers[idChoice].getEmail() << endl;
        cout << "User Password:" << tUsers[idChoice].getuserPassword() << endl;
        break;
    case 2:
        for (int i = 1; i < obj.totalUsers; i++)
        {
            cout << endl
                 << endl;
            cout << "User Id:" << tUsers[i].getId() << endl;
            cout << "User Name:" << tUsers[i].getName() << endl;
            cout << "User Address:" << tUsers[i].getAddress() << endl;
            cout << "User Cnic:" << tUsers[i].getCnic() << endl;
            cout << "User Phone No:" << tUsers[i].getPhone() << endl;
            cout << "User Email:" << tUsers[i].getEmail() << endl;
            cout << "User Password:" << tUsers[i].getuserPassword() << endl;
        }
        break;
    }
}
void viewCar(total &obj, Car tCars[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "View Cars" << endl;
    cout << "Do you want to view all Cars or a specific Car or a car of specific class (1,2,3): " << endl;
    int choice2;
    cin >> choice2;
    while (choice2 < 1 || choice2 > 3)
    {
        cout << "Enter again: ";
        cin >> choice2;
    }
    switch (choice2)
    {
    case 1:
        cout << "Enter the id of the car: ";
        int idChoice;
        cin >> idChoice;
        cout << endl
             << endl;
        cout << "Car Id: " << tCars[idChoice].getId() << endl;
        cout << " Car Class: " << tCars[idChoice].getClass() << endl
             << " Car model: " << tCars[idChoice].getModel() << endl
             << " Car year: " << tCars[idChoice].getYear() << endl
             << " Car maker: " << tCars[idChoice].getMaker() << endl
             << " Car Availability: " << tCars[idChoice].getAvailable() << endl
             << endl;
        break;
    case 2:
        for (int i = 1; i < obj.totalCars; i++)
        {
            cout << "Car Id: " << tCars[i].getId() << endl
                 << "Car Class: " << tCars[i].getClass() << endl
                 << "Car model: " << tCars[i].getModel() << endl
                 << "Car year: " << tCars[i].getYear() << endl
                 << "Car maker: " << tCars[i].getMaker() << endl
                 << "Car Availability: " << tCars[i].getAvailable() << endl;
        }
        break;
    case 3:
        cout << "Which class do you want?" << endl;
        int choice;
        cout << "1: Hatchback" << endl
             << "2: Sedan" << endl
             << "3: Suv" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        if (choice < 1 || choice > 3)
        {
            while (choice < 1 || choice > 3)
            {
                cout << "Invalid Input, Try again: ";
                cin >> choice;
            }
        }
        switch (choice)
        {
        case 1:
            for (int i = 1; i < obj.totalCars; i++)
            {
                if (tCars[i].getClass() == "Hatchback")
                {
                    cout << "Car Id: " << tCars[i].getId() << endl
                         << "Car Class: " << tCars[i].getClass() << endl
                         << "Car model: " << tCars[i].getModel() << endl
                         << "Car year: " << tCars[i].getYear() << endl
                         << "Car maker: " << tCars[i].getMaker() << endl
                         << "Car Availability: " << tCars[i].getAvailable() << endl
                         << endl;
                }
                else if (tCars[i].getClass() != "Hatchback")
                {
                    cout << "There are no cars with class Hatchback" << endl;
                    break;
                }
            }
            break;
        case 2:
            for (int i = 1; i < obj.totalCars; i++)
            {
                if (tCars[i].getClass() == "Sedan")
                {
                    cout << "Car Id: " << tCars[i].getId() << endl
                         << "Car Class: " << tCars[i].getClass() << endl
                         << "Car model: " << tCars[i].getModel() << endl
                         << "Car year: " << tCars[i].getYear() << endl
                         << "Car maker: " << tCars[i].getMaker() << endl
                         << "Car Availability: " << tCars[i].getAvailable() << endl;
                }

                cout << endl;
            }
            break;
        case 3:
            for (int i = 1; i < obj.totalCars; i++)
            {
                if (tCars[i].getClass() == "Suv")
                {
                    cout << "Car Id: " << tCars[i].getId() << endl
                         << "Car Class: " << tCars[i].getClass() << endl
                         << "Car model: " << tCars[i].getModel() << endl
                         << "Car year: " << tCars[i].getYear() << endl
                         << "Car maker: " << tCars[i].getMaker() << endl
                         << "Car Availability: " << tCars[i].getAvailable() << endl;
                }
                cout << endl;
            }
            break;
        }
        break;
    }
}
void viewDrivers(total &obj, Driver drivers[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "View Driver " << endl;
    cout << "Do you want to view a specific driver or all drivers (1 or 2): " << endl;
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "Enter again: ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        cout << "Enter the id of the driver: ";
        int idChoice;
        cin >> idChoice;
        cout << "Driver Id: " << drivers[idChoice].getDriverId() << endl;
        cout << "1) Driver Name: " << drivers[idChoice].getName() << endl;
        cout << "2) Driver Cnic: " << drivers[idChoice].getCnic() << endl;
        cout << "3) Driving License: " << drivers[idChoice].getDrivingLicense() << endl;
        cout << "4) Available: " << drivers[idChoice].getAvailable() << endl
             << endl;
        break;
    case 2:
        for (int i = 1; i < obj.totalDrivers; i++)
        {
            cout << "Driver Id: " << drivers[idChoice].getDriverId() << endl;
            cout << "1) Driver Name: " << drivers[idChoice].getName() << endl;
            cout << "2) Driver Cnic: " << drivers[idChoice].getCnic() << endl;
            cout << "3) Driving License: " << drivers[idChoice].getDrivingLicense() << endl;
            cout << "4) Available: " << drivers[idChoice].getAvailable() << endl
                 << endl;
        }
        break;
    }
}
void deleteCar(Car tCars[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "Delete Car " << endl;
    cout << "Enter the id of the Car you want to delete: ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice >= tCars[1].totalDrivers)
    {
        cout << "Enter again: ";
        cin >> choice;
    }
    tCars[1].deleteCarData(tCars, choice);
}
void deleteDriver(Driver drivers[])
{
    for (int i = 1; i < 100; i++)
    {
        cout << "*";
    }
    cout << endl;
    cout << setw(50) << "Delete Driver " << endl;
    cout << "Enter the id of the Car you want to delete: ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice >= drivers[1].totalDrivers)
    {
        cout << "Enter again: ";
        cin >> choice;
    }
    drivers[1].deleteDriverData(drivers, choice);
}
void income(total &obj, rentedCars rCars[])
{
    for (int i = 1; i < 200; i++)
    {
        cout << "*";
    }
    int income = 0;
    cout << endl;
    cout << setw(50) << "View Income " << endl;
    int choice;
    cout << "Enter 1 for all income or Enter 2 for a specific month income: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        for (int i = 1; i < obj.totalRentedCars; i++)
        {
            income = income + rCars[i].getRent();
        }
        cout << "The total you have earned is: " << income << endl;
        break;
    case 2:
        cout << "Enter the specific month : ";
        string month;
        cin >> month;
        for (int i = 1; i < obj.totalRentedCars; i++)
        {
            if (rCars[i].getSMonth() == month)
            {
                income = income + rCars[i].getRent();
            }
        }
        cout << "The total you have earned in your specific month is: " << income << endl;
        break;
    }
}
void deleteUser(Users tUsers[])
{
    cout << endl
         << endl;
    cout << "Enter id: ";
    int choice;
    cin >> choice;
    tUsers[1].deleteUserData(tUsers, choice);
}
