// tandt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include <vector>
#include <cstring>

using namespace std;

class Employee;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;
class Waiter;
class Bill;

class Room
{
public:
	char roomType[20];
	int noOfBeds;
	double rent;
	int roomNo;
	int status;
	static int noOfrooms;
public:

	Room(string roomT, int noOfBeds, double rent, int roomNo)
	{
		for (int i = 0; i < roomT.size(); i++) {
			roomType[i] = roomT[i];
		}
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
			cout << " Status :: Currently Occupied \n";
		else
			cout << "Status :: Vacant \n";
	}

	void vacateRoom(int rno)
	{
		Room r;
		fstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Room))) {
			if (r.roomNo == rno) {
				r.status = 0;
				file.seekp(-int(sizeof(Room)), ios::cur);
				file.write((char*)&r, sizeof(Room));
			}
		}
		file.close();
	}
	//display all or only available rooms
	void displayAvailable()
	{
		Room r;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Room))) {
			if (r.status == 0) {
				r.display_roomDetail();
			}
		}
		file.close();
	}

	void displayAll() {
		Room r;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Room))) {
			r.display_roomDetail();
		}
		file.close();
	}

};
int Room::noOfrooms = 0;

class Dish
{
public:
	char dishName[100];
	double price;
	char dishType[100];
	static int noOfdishes;

public:
	Dish(string dishName, double price, string dishType)
	{
		for (int i = 0; i < dishName.size(); i++) {
			this->dishName[i] = dishName[i];
		}
		this->price = price;
		for (int i = 0; i < dishType.size(); i++) {
			this->dishType[i] = dishType[i];
		}
	}
	Dish() {}

	void setData() {

		cout << "Enter Dish Name : "; cin >> this->dishName;
		cout << "Enter Dish Price: "; cin >> this->price;
		cout << "Enter Dish Type : "; cin >> this->dishType;

	}


	void displayDish()
	{

		cout << "Name :" << this->dishName << endl;
		cout << " Price :" << this->price << endl;
		cout << "Dish type: " << this->dishType << endl;

	}
};
int Dish::noOfdishes = 0;

class Restaurant
{

public:
	void addDish()
	{

		ofstream menu;
		menu.open("Menu.bin", ios::app | ios::binary);

		Dish a;
		a.setData();
		menu.write((char*)&a, sizeof(Dish));

		menu.close();
	}


	void displayMenu()
	{
		vector <Dish> dish;
		ifstream menu;
		Dish a;
		menu.open("Menu.bin", ios::in | ios::binary);

		while (menu.read((char*)&a, sizeof(Dish))) { dish.push_back(a); }

		menu.close();
		for (int i = 0; i < dish.size(); i++)
		{
			dish[i].displayDish();
		}

	}

};



class Customer
{
public:

	char custName[50];
	char custAddress[100];
	int custID;
	long int custPhone;
	char checkInTime[50];
public:
	static int noOfcustomers;
	static int n;



	Customer()
	{
		time_t c = time(0);
		//string dt = ctime(&c);
		noOfcustomers++;

	}

	void setData()
	{
		time_t now = time(0);
		//string dt = ctime(&now);
		/*for (int i = 0; i < dt.size(); i++) {
			checkInTime[i] = dt[i];
		}*/
		custID = n++;

		cout << "Enter your Name :\n";
		cin >> this->custName;

		cout << "Enter your Address :\n";
		cin >> this->custAddress;

		cout << "Enter your Phone number :\n";
		cin >> this->custPhone;



	}

	/*int selectChoice()
	{
		int ch;
		cout << " Hello!\n";
		cout << "Enter \n1. Accomodation \n 2. Dine\n ";
		cin >> ch;
		return ch;
	}*/



	virtual void display_Custinfo()
	{
		cout << "Name :: " << this->custName << endl;
		cout << "Address :: " << this->custAddress << endl;
		cout << "ID :: " << custID << endl;
		cout << "Phone Number :: " << custPhone << endl;
		cout << "Check-In Time ::" << this->checkInTime << endl;

	}
	virtual void view_bill() {
	}

	virtual void checkOut() {
	}
};
int Customer::noOfcustomers = 0;
int Customer::n = 999;



class RoomCustomer : public Customer
{
public:
	int room_no;
	int days;
	double rbill;
	Room r;

	RoomCustomer() {}

	RoomCustomer(int rn, int d)
	{
		room_no = rn;
		days = d;

		Room s;
		ifstream file("Rooms.bin", ios::in | ios::binary);


		while (file.read((char*)&s, sizeof(Room))) {
			if (s.roomNo == rn) r = s;
		}

		file.close();
	}

	void view_bill()
	{
		rbill = r.rent * days;
		cout << "Room Bill =" << rbill;
	}

	void bookRoom()
	{
		//r1.displayAvailable();  //send this to where ur booking


		Room temp;
		vector <Room> s;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&temp, sizeof(Room))) {
			s.push_back(temp);
		}
		file.close();

		/*bool st = r.checkstatus(r);
		cout << st;*/

		if (r.status == 0) {
			for (int i = 0; i < s.size(); i++) {
				if (s[i].roomNo == r.roomNo) {
					s[i].status = 1;
				}
			}

			ofstream file1("Rooms.bin", ios::out | ios::binary);
			for (int i = 0; i < s.size(); i++) {
				Room sss = s[i];
				file1.write((char*)&sss, sizeof(Room));
			}
			file1.close();
		}

		else {
			cout << "Room already booked!" << endl;
		}

	}

	void cancelRoom() {

		r.vacateRoom(r.roomNo);
	}

	void display_Custinfo()
	{

		Customer::display_Custinfo();
		cout << "Check-In Time :: " << checkInTime << endl;
		cout << "Room type :: " << r.roomType << endl;
		cout << "Room Number :: " << r.roomNo << endl;

	}

	void checkOut();

	void addRoomCustomer() {
		ofstream customer;
		customer.open("RoomCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RoomCustomer));
		customer.close();
	}

	friend Bill operator +(RoomCustomer& r, RestaurantCustomer& m);
};

class RestaurantCustomer :public Customer
{
public:
	double dbill = 0;
	vector <const char*> dishes;
	vector <Dish> menu;
public:
	//order dish
	void Order_dish(char a[])
	{
		dishes.push_back(a);

	}

	//items that has bought by customer
	void print_itemlist()
	{
		ifstream file("Menu.bin", ios::binary | ios::in);
		Dish d;

		while (file.read((char*)&d, sizeof(Dish))) {
			menu.push_back(d);
		}

		file.close();

		cout << "You have ordered:\n";
		cout << "dish\tPrice\n";

		int k = 1;
		for (int j = 0; j < dishes.size(); j++) {
			for (int i = 0; i < menu.size(); i++)
			{
				if (strcmp(menu[i].dishName, dishes[j]) == 0)
				{
					cout << k++ << ". " << menu[i].dishName << "\t" << menu[i].price << endl;
				}
			}
		}
	}

	void view_bill();

	RestaurantCustomer() {}

	void addRestaurantCustomer() {
		ofstream customer;
		customer.open("RestaurantCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RestaurantCustomer));
		customer.close();
	}

	friend Bill operator +(RoomCustomer& r, RestaurantCustomer& m);

};


class Bill {
	static int bill_id;
	double tbill = 0;

public:



	Bill() { bill_id++; }

	void roomcustomer_print_bill(RoomCustomer c)
	{


		vector <RestaurantCustomer> rs;

		RestaurantCustomer temp2;

		ifstream file1("RestaurantCustomer.bin", ios::in | ios::binary);
		while (file1.read((char*)&temp2, sizeof(RestaurantCustomer))) {
			rs.push_back(temp2);
		}
		file1.close();


		Bill t;
		
		for (int j = 0; j < rs.size(); j++) {
			if (c.custName == rs[j].custName && c.custPhone == rs[j].custPhone) {
				 t = c + rs[j];
			}
		}

		cout << "Your total bill during your stay is " << t.tbill << "/-" << endl;
		cout << "Thank You! Visit Again.\n" << endl;


	}

	void restaurantcustomer_print_bill(double p) {
		cout << "Bill = " << p;
	}


	friend Bill operator +(RoomCustomer& r, RestaurantCustomer& m);

};
int Bill::bill_id = 999;

Bill operator +(RoomCustomer& r, RestaurantCustomer& m) {
	Bill b;
	b.tbill = r.rbill + m.dbill;
	cout << b.tbill;
	return b;
}

void RoomCustomer::checkOut()
{
	Bill b;
	b.roomcustomer_print_bill(*this);
	r.vacateRoom(r.roomNo);
}

void RestaurantCustomer::view_bill()
{

	for (int j = 0; j < dishes.size(); j++) {
		for (int i = 0; i < menu.size(); i++)
		{
			if (strcmp(menu[i].dishName, dishes[j]) == 0)
			{
				dbill += menu[i].price;

			}
		}
	}


	Bill b;
	b.restaurantcustomer_print_bill(dbill);
}

class Employee {
protected:
	int employeeid;
	char name[20];

public:
	static int noofemployees;
	static int x;

	Employee() {}

	Employee(string n) {
		for (int i = 0; i < n.size(); i++) {
			name[i] = n[i];
		}
		employeeid = x++;
	}

	virtual void perform_duty() = 0;
	virtual ~Employee() {
	}
	void display() {
		cout << name << endl;
		cout << employeeid << endl;

	}
	void displayAvailable(Employee& r)
	{
		//Room r;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Employee))) {
			r.display();
		}
		file.close();
	}

	friend class Administrator;
};

int Employee::noofemployees = 0;
int Employee::x = 999;

class RoomService : public Employee {

public:
	RoomService() {}

	RoomService(string name) : Employee(name) {}

	void perform_duty() {
		cout << "Cleaning room ....  " << endl << "Cleaning done!" << endl;
	}
};

class Waiter : public Employee {

public:
	Waiter() {}

	Waiter(string name) : Employee(name) {}

	void perform_duty() {
		cout << "Serving food .... " << endl << "Food is served!" << endl;
	}
};


class Administrator : public Employee {

public:

	void addRoom() {

		Room r;
		r.setRoom();

		ofstream file("Rooms.bin", ios::app | ios::binary);
		file.write((char*)&r, sizeof(Room));
		file.close();
	}
	void removeRoom() {

		vector <Room> r;
		int number;

		cout << "All Rooms currently in the Hotel :" << endl;
		Room test;
		test.displayAll();

		cout << "Enter the room number: ";
		cin >> number;

		Room s;
		ifstream file("Rooms.bin", ios::in | ios::binary);


		while (file.read((char*)&s, sizeof(Room))) {
			r.push_back(s);
		}

		file.close();

		int flag = 0;
		for (int i = 0; i < r.size(); i++) {
			if (r[i].roomNo == number) {
				r.erase(r.begin() + i);
				flag = 0;
				break;
			}
			else flag = 1;
		}

		if (flag == 1) cout << "No such employee was found!" << endl;

		ofstream file1;
		file1.open("Rooms.bin", ios::out | ios::binary);
		for (int i = 0; i < r.size(); i++) {
			Room rrr = r[i];
			file1.write((char*)&rrr, sizeof(Room));

		}
		file1.close();

	}

	void addEmployee() {
		char ename[20];
		int choice;

		cout << "Enter employee name :"; cin >> ename;
		cout << "Enter 1 if employee is a room service employee and 2 for waiter employee: "; cin >> choice;

		switch (choice) {
		case 1:
		{RoomService r(ename);
		fstream file("Roomservice.bin", ios::app | ios::binary);
		file.write((char*)&r, sizeof(RoomService));
		file.close();
		break; }

		case 2:
		{Waiter w(ename);
		fstream file("Waiter.bin", ios::app | ios::binary);
		file.write((char*)&w, sizeof(Waiter));
		file.close();
		break; }
		}
	}

	void removeEmployee() {
		char ename[20];
		int type;
		vector <RoomService> r;
		vector <Waiter> w;


		//
		cout << "Enter the employee's name: ";
		cin >> ename;
		cout << "Enter the appropriate number for employee type: [1] Room Service   [2] Waiter" << endl;
		cin >> type;

		RoomService s;
		ifstream file("Roomservice.bin", ios::in | ios::binary);


		while (file.read((char*)&s, sizeof(RoomService))) {
			r.push_back(s);
		}

		file.close();

		cout << "\n" << r.size() << endl;

		int flag = 0;
		for (int i = 0; i < r.size(); i++) {
			if (r[i].name == ename) {
				r.erase(r.begin() + i);
				flag = 0;
				break;
			}
			else flag = 1;
		}

		if (flag == 1) cout << "No such employee was found!" << endl;

		ofstream file1;
		file1.open("Roomservice.bin", ios::out | ios::binary);
		for (int i = 0; i < r.size(); i++) {
			RoomService rrr = r[i];
			file1.write((char*)&rrr, sizeof(RoomService));

		}
		file1.close();

		Waiter t;
		ifstream file2("Waiter.bin", ios::in | ios::binary);


		while (file2.read((char*)&t, sizeof(Waiter))) {
			w.push_back(t);
		}

		file2.close();

		cout << "\n" << w.size() << endl;

		int flag1 = 0;
		for (int i = 0; i < w.size(); i++) {
			if (w[i].name == ename) {
				w.erase(w.begin() + i);
				flag1 = 0;
				break;
			}
			else flag1 = 1;
		}

		if (flag1 == 1) cout << "No such employee was found!" << endl;

		ofstream file3;
		file3.open("Waiter.bin", ios::out | ios::binary);
		for (int i = 0; i < w.size(); i++) {
			Waiter www = w[i];
			file3.write((char*)&www, sizeof(Waiter));

		}
		file3.close();
	}

	void perform_duty() {
		int choice;
		cout << "Enter the appropriate number to execute a function of your choice: " << endl << "1. Add Room" << endl << "2. Remove Room" << endl << "3. Add Employee" << endl << "4. Remove Employee" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			addRoom();
			break;

		case 2:
			removeRoom();
			break;

		case 3:
			addEmployee();
			break;

		case 4:
			removeEmployee();
			break;
		}
	}


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

int main()
{
	int no;
	Administrator a;
	a.addRoom();
	Room o;
	o.displayAvailable();

	cout << "Room";
	cin >> no;
	RoomCustomer r(no, 4);
	r.addRoomCustomer();
	r.setData();
	r.bookRoom();
	r.display_Custinfo();
	r.view_bill();
	Restaurant rt;
	rt.addDish();
	rt.displayMenu();

	RestaurantCustomer c;
	c.setData();
	char s[100]; cin >> s;
	c.Order_dish(s);
	c.print_itemlist();
	c.addRestaurantCustomer();
	c.view_bill();

	r.checkOut();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
