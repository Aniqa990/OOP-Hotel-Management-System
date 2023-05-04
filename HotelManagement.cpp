
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include<ctime>
#include<stdbool.h>
#include <iomanip>
#include<fstream>

using namespace std;

class Exception;
class Customer;
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
int  Dish::noOfdishes = 0;


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
int Customer::noOcustomers = 0;
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

class RestaurantCustomer :public Customer
{
public:
	static double dbill;
	vector<string> dishes;
public:
	//order dish
	void Order_dish(string a)
	{
		dishes.push_back( a);

	}

	//items that has bought by customer
	void prin_itemlist(vector<Dish> d)
	{
		cout << "Dishes that Customer has ordered!\n";
		cout << "dish\tPrice\n";
		for (int i = 0; i < d.size(); i++)
		{
			if (d[i].dishName == dishes[i])
			{
				cout << 1 + i << ". " << d[i].dishName << "\t" << d[i].price << endl;
			}
		}
	}
	void view_bill(vector<Dish> d3)
	{
		for (int i = 0; i < d3.size(); i++)
		{
			if (d3[i].dishName == dishes[i])
			{
				dbill += d3[i].price;

			}
		}
		cout << "Bill = " << dbill;
	}

	RestaurantCustomer() {}

	RestaurantCustomer(double a)
	{
		dbill = a;
	}


};

double RestaurantCustomer::dbill = 0;



class Employee {
	int employeeid;
	string name;

public:
	static int noofemployees;

	Employee(){}

	virtual void perform_duty() = 0;
	virtual ~Employee() {
	}
};

int Employee::noofemployees = 0;

class Administrator : public Employee {

public:

	void addRoom() {}
	void removeRoom() {}
	void addEmployee(){}
	void removeEmployee(){}
	void perform_duty() {
		//all above functions in switch case
	}

};

class RoomService : public Employee {

public:

	void perform_duty(){}
};
class SelectEmployee {
	//protected:
	Employee* e;


public:
	SelectEmployee(Employee* e1)
	{
		e = e1;
	}

	void performDuty()
	{
		e->perform_duty();
	}

};


class Restaurant {

public:
	//Dish* dishes = new Dish[noofdishes];

	void addDishes(){}
	void displayMenu(){}

};

class Bill { //composition with customer
	int bill_id;

public:
	void print_bill() {
		//get customer, dish, and room details
		//add objects of order and roombooking
	 }
};

class Hotel {
	string hotelName;
	string hotelAddress;

public:
	Hotel(string hname, string add)
	{
		this->hotelName = hname;
		this->hotelAddress = add;
	}

	void display_allrooms(){}
	void displayMenu()
	{
		cout << "\n\n-----------------------------------------------Menu-------------------------------------------------\n\n ";
		int i;
		const int width = 8;
		cout << setw(25) << " Dish Name" << setw(25) << "Price" << setw(25) << "Dish Type" << endl;
		for (i = 0; i < 8; i++)
		{

			cout << setw(25) << restuarant.dish[i].dishName;
			cout << setw(25) << restuarant.dish[i].price;
			cout << setw(25) << restuarant.dish[i].dishType << "\n";
		}
		cout << "\n\n";
	}

	void bookRoom(int r)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (room[i].roomNo == r)
				room[i].status = 1;
		}
	}


	void getCustomerData(Customer* c)
	{
		cout << " Name :: " << c->custName << endl;
		cout << " Address :: " << c->custAddress << endl;
		cout << " Phone :: " << c->custPhone << endl;
		cout << " Email :: " << c->custEmail << endl;
		cout << " Check-In Time:: " << c->checkInTime << endl;
	}

	void vacateRoom(int rno)
	{
		int i, j = 0;
		for (i = 0; i < 6; i++)
		{

			if (room[i].roomNo == rno)
			{
				j = 1;
				room[i].status = 0;
				cout << "Thank You! Visit Again.\n" << endl;
			}
		}
		if (j == 0)
			throw Exception(8, "Sorry! Room Not Found, or occupied at the moment\n");

	}
	void takeOrder(string dnm)
	{
		int i, j = 0;;
		for (i = 0; i < 8; i++)
		{
			if (restuarant.dish[i].dishName == dnm)
			{
				j = 1;
				cout << "Order Successful\n" << endl;
			}
		}
		if (j == 0)
			throw Exception(9, "Sorry! Dish Not Found, Enter a valid entry");
	}
};



class Restaurant
{
public:
	Dish dish[8];

public:
	void addDishes()
	{
		ofstream menu;
		menu.open("Menu.txt", ios::ate);
		int i;
		for (i = 0; i < 8; i++)
		{
			cout << i + 1 << "] Enter Dish Name Price and Type\n";
			cin >> dish[i].dishName >> dish[i].price >> dish[i].dishType;
			menu << dish[i].dishName << "\t" << dish[i].price << "\t" << dish[i].dishType << "\n";
		}
		menu.close();
	}

	// I make it extra 
	Dish getDish(string dnam)
	{
		int i;
		for (i = 0; i < 8; i++)
		{

			if (dish[i].dishName == dnam)

			{
				return dish[i];
			}
		}
	}



	void displayDish(Dish d)
	{
		cout << " Dish Name :: " << d.dishName << endl;
		cout << " Price :: " << d.price << endl;
		cout << " Dish Type :: " << d.dishType;

	}

	void displayMenu()
	{
		int i;
		for (i = 0; i < 8; i++)
		{
			displayDish(dish[i]);
		}

	}

};


int main()
{
   
}

