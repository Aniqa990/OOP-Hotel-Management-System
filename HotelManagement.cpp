
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<stdbool.h>
#include <iomanip>
#include<fstream>



class Exception;
class Customer;
using namespace std;
class RoomCustomer;
class Employee;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;

class Exception
{
public:
	int errNo;
	string msg;

public:
	Exception(int errNo, string msg)
	{
		this->errNo = errNo;
		this->msg = msg;
	}

	void what()
	{
		cout << "\t\t" << errNo << " :: " << msg << endl;
	}
};

class Room
{
public:
	string roomType;
	int noOfBeds;
	double rent;
	int roomNo;
	int status;
	int noOfrooms;
public:

	Room(string roomType, int noOfBeds, double rent, int roomNo)
	{
		this->roomType = roomType;
		this->noOfBeds = noOfBeds;
		this->rent = rent;
		this->roomNo = roomNo;
		this->status = 0;

	}
	void setRoom()
	{
		cout << "Enter Room Type, No of beds, Rent, RoomNo\n";
		cin >> this->roomType;
		cin >> this->noOfBeds;
		cin >> this->rent;
		cin >> this->roomNo;
		status = 0;

	}

	Room()
	{
	}




	bool checkstatus(Room r)
	{
		if (r.status == 1)
			return false;
		else
			return true;
	}

	void display_roomDetail()
	{

		cout << "Room Type :: " << this->roomType << endl;
		cout << "Number of Beds :: " << this->noOfBeds << endl;
		cout << "Rent :: " << this->rent << endl;
		cout << "Room Number ::" << this->roomNo << endl;
		if (status == 1)
			cout << " Occupied \n";
		else
			cout << "Vacant \n";
	}

	void vacateRoom(int rno)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (this->roomNo == rno)
				this->status = 0;
		}
	}
	//display all or only available rooms
	void displayAvailable(Room r[6])
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (r[i].status == 0)
				r[i].display_roomDetail();
		}
	}

};

class Dish
{
public:
	string dishName;
	double price;
	string dishType;
	int noOfdishes;

public:
	Dish(string dishName, double price, string dishType)
	{
		this->dishName = dishName;
		this->price = price;
		this->dishType = dishType;
	}
	Dish()
	{

	}
	void displayDish()
	{
		cout << "Name :" << dishName << endl;
		cout << " Price :" << price << endl;
		cout << "Dish type: " << dishType << endl;

	}
};

class Customer
{
protected:

	string custName;
	string custAddress;
	string custID;
	long int custPhone;
	string checkInTime;
public:
	static int noOcustomers;



	Customer()
	{
		time_t c = time(0);
		string dt = ctime(&c);
		this->custName = " ";
		this->custAddress = " ";
		this->custID = " ";
		this->custPhone = 0L;
		this->checkInTime = dt;

	}

	void setData()
	{
		time_t now = time(0);
		string dt = ctime(&now);
		this->checkInTime = dt;
		ofstream customer;
		customer.open("Customer.txt", ios::ate);
		cout << "Enter your Name :\n";
		cin >> this->custName;
		customer << "Name ::" << this->custName << "\n";

		cout << "Enter your Address :\n";
		cin >> this->custAddress;
		customer << "Address ::" << this->custAddress << "\n";

		cout << "Enter your Phone number :\n";
		cin >> this->custPhone;
		customer << "Phone ::" << this->custPhone << "\n";


		customer.close();

	}

	int selectChoice()
	{
		int ch;
		cout << " Hello!\n";
		cout << "Enter \n1. Accomodation \n 2. Dine\n ";
		cin >> ch;
		return ch;
	}



	virtual void display_Custinfo()
	{
		cout << "Name :: " << this->custName << endl;
		cout << "Address :: " << this->custAddress << endl;
		cout << "ID :: " << custID << endl;
		cout << "Phone Number :: " << custPhone << endl;
		cout << "Check-In Time ::" << this->checkInTime << endl;

	}
	virtual void viewBill() {
	}

	virtual void checkout() {
	}
};

class RoomCustomer : public Customer
{
public:
	int room_no;
	int days;
	double rbill;
	Room r;
public:
	RoomCustomer() {}

	//parameters error
	RoomCustomer(double b, int r, int d)
	{
		room_no = b;
		days = d;
		rbill = r;
	}
	void viewbill()
	{
		cout << "Bill =" << rbill;
	}

	void bookRoom(Room r1)
	{
		this->r = r1;
	}

	void display_Custinfo()
	{

		Customer::display_Custinfo();
		cout << "Check-In Time :: " << checkInTime << endl;
		cout << "Room type :: " << r.roomType << endl;
		cout << "Room Number :: " << r.roomNo << endl;

	}

	void checkOut()
	{
		cout << "Your bill is " << this->rbill << "/-" << endl;
		this->rbill = 0;
		cout << "Thank You! Visit Again.\n" << endl;
	}


};

int main()
{
    
}

