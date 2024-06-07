#include <iostream>
#include<fstream>
#include <vector>
#include <cstring>
#include <ctime>
#include<chrono>
#include<conio.h>
#include <string>
#include <stdexcept> // include the <stdexcept> library for using exceptions
#include <Windows.h>

using namespace std;

class Exception;
class Employee;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;
class Waiter;
class Bill;

void SetColor(int ForgC)
{
	WORD wColor;
	//This handle is needed to get the current background attribute

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//csbi is used for wAttributes word

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//To mask out all but the background attribute, and to add the color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

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
protected:
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
		cin.ignore();
		cin.getline(roomType, 20);
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
		vector <Room> rm;
		Room r;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Room))) {
			rm.push_back(r);
		}
		file.close();

		for (int i = 0; i < rm.size(); i++) {
			if (rm[i].roomNo == rno) {
				rm[i].status = 0;
			}
		}

		ofstream file1("Rooms.bin", ios::out | ios::binary);
		for (int i = 0; i < rm.size(); i++) {
			Room rrr = rm[i];
			file1.write((char*)&rrr, sizeof(Room));
		}
		file1.close();
	}
	//display all or only available rooms
	void displayAvailable()
	{
		Room r;
		SetColor(20);
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
			cout << endl << endl;
		}
		file.close();
	}

	friend class RoomCustomer;
	friend class Administrator;
	friend class Hotel;

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
		int i;
		for (i = 0; i < dishName.size(); i++) {
			this->dishName[i] = dishName[i];
		}
		this->dishName[i] = '\0';
		this->price = price;
		int j;
		for (int j = 0; j < dishType.size(); j++) {
			this->dishType[j] = dishType[j];
		}
		this->dishType[j] = '\0';
	}
	Dish() {}

	void setData() {

		cout << "Enter Dish Name : ";
		cin.ignore();
		cin.getline(dishName, 100);
		cout << "Enter Dish Type : ";
		//cin.ignore();
		cin.getline(dishType, 100);
		cout << "Enter Dish Price: ";
		cin >> this->price;

	}


	void displayDish()
	{
		SetColor(35);
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

		Dish a; Dish dummy;
		a.setData();

		ifstream file("Menu.bin", ios::in | ios::binary);
		while (file.read((char*)&dummy, sizeof(Dish))) {
			while (strcmp(dummy.dishName, a.dishName) == 0) {
				cout << "Dish already exists. Please add another dish.";
				a.setData();
			}
		}

		ofstream menu;
		menu.open("Menu.bin", ios::app | ios::binary);

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
	int custID;//see
	long int custPhone;
public:
	static int noOfcustomers;
	static int x;



	Customer()
	{
		noOfcustomers++;

	}

	void setData()
	{



		custID = x++;

		cout << "Enter your Name :\n";
		cin.ignore();
		cin.getline(custName, 50);

		cout << "Enter your Address :\n";
		//cin.ignore();
		cin.getline(custAddress, 100);

		cout << "Enter your Phone number :\n";
		cin >> this->custPhone;



	}




	virtual void display_Custinfo()
	{
		SetColor(40);
		cout << "Name :: " << this->custName << endl;
		cout << "Address :: " << this->custAddress << endl;
		cout << "ID :: " << custID << endl;
		cout << "Phone Number :: " << custPhone << endl;

	}
	void bill() {
	}

	void checkOut() {
	}
};
int Customer::noOfcustomers = 0;
int Customer::x = 999;



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

	void bill()
	{
		rbill = r.rent * days;
	}

	void bookRoom()
	{


		Room temp;
		vector <Room> s;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&temp, sizeof(Room))) {
			s.push_back(temp);
		}
		file.close();


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

			addRoomCustomer();
		}

		else {
			cout << "Room already booked!" << endl;
		}

	}

	void cancelRoom(int x) {

		Room o;
		o.vacateRoom(x);
		removeroomcust(x);

	}

	void display_Custinfo()
	{

		Customer::display_Custinfo();
		cout << "Room type :: " << r.roomType << endl;
		cout << "Room Number :: " << r.roomNo << endl;
		cout << "Number of days for stay :: " << days << endl;

	}

	void checkOut();

	void addRoomCustomer() {
		ofstream customer;
		customer.open("RoomCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RoomCustomer));
		customer.close();
	}

	void removeroomcust(int no) {
		vector <RoomCustomer> r;


		RoomCustomer s;
		ifstream file("RoomCustomer.bin", ios::in | ios::binary);


		while (file.read((char*)&s, sizeof(RoomCustomer))) {
			r.push_back(s);
		}

		file.close();

		int flag = 0;
		for (int i = 0; i < r.size(); i++) {
			if (r[i].room_no == no) {
				r.erase(r.begin() + i);
				flag = 0;
				break;
			}
			else flag = 1;
		}

		if (flag == 1) cout << "No such room was found!" << endl;

		ofstream file1;
		file1.open("RoomCustomer.bin", ios::out | ios::binary);
		for (int i = 0; i < r.size(); i++) {
			RoomCustomer rrr = r[i];
			file1.write((char*)&rrr, sizeof(RoomCustomer));

		}
		file1.close();
	}

	void displayroomcust() {
		RoomCustomer f;
		ifstream file("RoomCustomer.bin", ios::in | ios::binary);
		while (file.read((char*)&f, sizeof(RoomCustomer))) {
			f.display_Custinfo();
		}

	}

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

		cout << "You have ordered:\n";
		cout << "Dish\t\t\tPrice\n";

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

	void bill();

	RestaurantCustomer() {
		ifstream file("Menu.bin", ios::binary | ios::in);
		Dish d;

		while (file.read((char*)&d, sizeof(Dish))) {
			menu.push_back(d);
		}

		file.close();
	}

	void addRestaurantCustomer() {
		ofstream customer;
		customer.open("RestaurantCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RestaurantCustomer));
		customer.close();
	}


};


class Bill {
	static int bill_id;
	double tbill = 0;

public:



	Bill() { bill_id++; }

	void roomcustomer_print_bill(double c)
	{
		SetColor(50);
		char v;
		cout << "Your total bill during your stay is " << c << "/-" << endl;
		cout << "Thank You! Visit Again.\n" << endl;
		cin >> v;

	}

	void restaurantcustomer_print_bill(double p) {

		cout << "Bill = " << p;
	}


};
int Bill::bill_id = 999;



void RoomCustomer::checkOut()
{
	Bill b;
	bill();
	b.roomcustomer_print_bill(rbill);
	r.vacateRoom(r.roomNo);
	removeroomcust(r.roomNo);

}

void RestaurantCustomer::bill()
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

		int j = 0;
		for (j = 0; j < n.size(); j++) {
			name[j] = n[j];
		}
		name[j] = '\0';
		employeeid = x++;
	}

	virtual void perform_duty() = 0;
	virtual ~Employee() {
	}
	void display() {
		cout << name << endl;
		cout << employeeid << endl;

	}
	void displayallworkers() {}

	friend class Administrator;
};

int Employee::noofemployees = 0;
int Employee::x = 999;

class RoomService : public Employee {

public:
	RoomService() {}

	RoomService(string name) : Employee(name) {}

	void perform_duty() {
		SetColor(30);
		cout << "Cleaning room ....  " << endl << "Cleaning done!" << endl;
	}

	void displayallworkers() {
		RoomService r;
		ifstream file("RoomService.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(RoomService))) {
			r.display();
		}
		file.close();
	}
};

class Waiter : public Employee {

public:
	Waiter() {}

	Waiter(string name) : Employee(name) {}

	void perform_duty() {
		SetColor(30);
		cout << "Serving food .... " << endl << "Food is served!" << endl;
	}

	void displayallworkers() {
		Waiter w;
		ifstream file("Waiter.bin", ios::in | ios::binary);
		while (file.read((char*)&w, sizeof(Waiter))) {
			w.display();
		}
		file.close();
	}
};


class Administrator : public Employee {

public:

	void addRoom() {


		Room r; Room dummy;
		r.setRoom();


		ifstream file1("Rooms.bin", ios::in | ios::binary);
		while (file1.read((char*)&dummy, sizeof(Room))) {
			while (r.roomNo == dummy.roomNo) {
				cout << "Room already exists. Enter another room number." << endl;
				r.setRoom();
			}
		}
		file1.close();

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

		if (flag == 1) cout << "No such room was found!" << endl;

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
		SetColor(100);

		cout << "Enter employee name :";
		cin.ignore();
		cin.getline(ename, 20);
		cout << "Enter 1 if employee is a room service employee and 2 for waiter employee: "; cin >> choice;

		while (choice != 1 && choice != 2) {
			cout << "Please select a valid option!";
			cin >> choice;
		}

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

		RoomService s;
		Waiter t;

		s.displayallworkers();
		t.displayallworkers();

		SetColor(10);

		cout << "Enter the employee's name: ";
		cin.ignore();
		cin.getline(ename, 20);
		cout << "Enter the appropriate number for employee type: [1] Room Service   [2] Waiter" << endl;
		cin >> type;

		while (type != 1 && type != 2) {
			cout << "Please select a valid option!";
			cin >> type;
		}

		if (type == 1) {
			ifstream file("Roomservice.bin", ios::in | ios::binary);


			while (file.read((char*)&s, sizeof(RoomService))) {
				r.push_back(s);
			}

			file.close();


			int flag = 0;
			for (int i = 0; i < r.size(); i++) {
				if (strcmp(r[i].name, ename) == 0) {
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
		}
		else {

			ifstream file2("Waiter.bin", ios::in | ios::binary);


			while (file2.read((char*)&t, sizeof(Waiter))) {
				w.push_back(t);
			}

			file2.close();

			int flag1 = 0;
			for (int i = 0; i < w.size(); i++) {
				if (strcmp(w[i].name, ename) == 0) {
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

class Hotel
{
private:
	string hotelName;
	string hotelAddress;
public:


	vector <Employee>emp;
	Restaurant restaurant;
	Administrator admin;
	RoomCustomer roomcus;
	RoomCustomer* r = new RoomCustomer();
	RestaurantCustomer* rc = new RestaurantCustomer();
	vector<Dish>dishes;
	vector<Room>room;
	Room r2;
	vector<Customer>customer;
	Bill bill;


	string getHotel_name() {
		return hotelName;
	}

	void display_availableRooms()
	{
		r2.displayAvailable();
	}


	Hotel(string hname, string add)
	{
		this->hotelName = hname;
		this->hotelAddress = add;
	}

	Hotel() {}
public:


	void setHotel()
	{
		system("cls");

		cout << "Setting restaurant menu...." << endl << endl;

		cout << "Enter dish details :" << endl << endl;
		for (int i = 0; i < 3; i++) {

			restaurant.addDish();
		}

		cout << "Adding employee information and room information: " << endl;
		for (int i = 0; i < 3; i++) {
			admin.addRoom();
		}
		for (int i = 0; i < 3; i++) {
			admin.addEmployee();
		}


	}

	void room_service()
	{
		RoomService rs;
		ifstream file("RoomService.bin", ios::in | ios::binary);
		file.seekg(0);
		file.read((char*)&rs, sizeof(RoomService));
		file.close();


		if (!file) {
			cout << "Failed to read object from file." << endl;
			return;
		}


		SelectEmployee s(&rs);
		s.performDuty();
	}

	void waiter() {
		Waiter w;
		ifstream file("Waiter.bin", ios::in | ios::binary);
		file.seekg(0);
		file.read((char*)&w, sizeof(Waiter));
		file.close();

		if (!file) {
			cout << "Failed to read Waiter object from file." << endl;
			return;
		}

		SelectEmployee s(&w);
		s.performDuty();

	}

	Room getRoom(int rno)
	{
		int i;
		for (i = 0; i < 6; i++)
		{
			if (room[i].roomNo == rno)
				return room[i];
		}
	}
	void display_allrooms()
	{

		cout << "********************************************************************************************\n";
		cout << "---------------------************************************************------------------------\n";
		cout << "\n--------------------------------------Room Details------------------------------------------\n";
		cout << "***********************************************************************************************\n";
		cout << "---------------------************************************************-------------------------\n\n\n";
		r2.displayAll();
	}

	void displayMenu()
	{
		cout << "********************************************************************************************\n";
		cout << "---------------------************************************************------------------------\n";
		cout << "\n\n-------------------------------------------Menu------------------------------------------\n ";
		cout << "***********************************************************************************************\n";
		cout << "---------------------************************************************---------------------------\n\n\n";
		restaurant.displayMenu();
	}

	void bookRoom()
	{
		int days, rno;
		system("cls");
		SetColor(20);
		cout << "All Available Rooms:\n";
		r2.displayAvailable();
		cout << "Enter the number of days you will stay :";
		cin >> days;
		cout << "Enter the room number you wish to book :";
		cin >> rno;


		Room dummy;
		int flag = 0;

		while (flag == 0) {

			ifstream file("Rooms.bin", ios::in | ios::binary);
			while (file.read((char*)&dummy, sizeof(Room))) {
				if (dummy.roomNo == rno) flag = 1;
			}

			if (flag == 0) {
				cout << "Room does not exist! Enter another room number: ";
				cin >> rno;
			}
		}
		if (r == NULL) {
			r = new RoomCustomer(rno, days);
			r->setData();
		}
		else {
			delete r;
			r = new RoomCustomer(rno, days);
			r->setData();
		}
		r->bookRoom();
		cout << "Room booked!" << endl;

	}


	void askFeedback()
	{
		int f;
		string cname;
		ofstream feedback;
		feedback.open("feedback.txt", ios::app);
		feedback << "Customer Name\t : ";
		cout << "*****************************************************************************\n";
		cout << "\t\t------------ How did you find your experience? ------------------";
		cout << "*****************************************************************************\n";
		cout << "Enter your Name\n";
		cin.ignore();
		getline(cin, cname);
		feedback << cname << "\t\t\t";
		cout << " Thanks for your time! \n How likely are you to recommend Hotel Rennaisance to a Friend or Colleague? \n Rate on a scale of 1-10\n";
		cin >> f;

		while (f < 1 || f>10) {
			cout << "Please rate on a scale of 1-10\n";
			cin >> f;
		}

		feedback << "Feedback\t: ";
		feedback << f << "\n";
		feedback.close();
		cout << " Thanks for your valuable feedback!" << endl;
	}

	void getCustomerData(Customer* c)
	{
		cout << " Name :: " << c->custName << endl;
		cout << " Address :: " << c->custAddress << endl;
		cout << " Phone :: " << c->custPhone << endl;

	}

	void viewRoomCust() {

		RoomCustomer c;

		ifstream file("RoomCustomer.bin", ios::in | ios::binary);
		while (file.read((char*)&c, sizeof(RoomCustomer))) {
			c.display_Custinfo();
			cout << endl << endl;
		}
	}


	void cancel_room() {
		int rno;
		char name[50];
		RoomCustomer temp;

		cout << "Please enter the room number you booked: ";
		cin >> rno;
		cout << "Please enter your name: ";
		cin.ignore();
		cin.getline(name, 50);

		int flag = 0;
		ifstream file("RoomCustomer.bin", ios::binary | ios::in);
		while (file.read((char*)&temp, sizeof(RoomCustomer))) {
			if (strcmp(temp.custName, name) == 0 && temp.room_no == rno) {
				temp.cancelRoom(rno);
				cout << "Room booking cancelled." << endl;
				flag = 1;
			}
		}

		if (flag == 0) { cout << "Room does not exist!" << endl; }
	}

	void RoomCustomer_checkOut()
	{
		int rno;
		char name[50];
		RoomCustomer temp;

		cout << "Please enter the room number you booked: ";
		cin >> rno;
		cout << "Please enter your name: ";
		cin.ignore();
		cin.getline(name, 50);

		ifstream file("RoomCustomer.bin", ios::binary | ios::in);
		while (file.read((char*)&temp, sizeof(RoomCustomer))) {
			if (strcmp(temp.custName, name) == 0 && temp.room_no == rno) {
				temp.checkOut();
			}
		}
	}

	void displayWorkers() {
		RoomService r;
		Waiter w;

		r.displayallworkers();
		w.displayallworkers();
	}

	void takeOrder()
	{
		int no;
		char dish[100];

		rc->setData();
		rc->addRestaurantCustomer();


		displayMenu();
		cout << "How many dishes would you like to order? ";
		cin >> no;


		int j = 0;
		cin.ignore();
		for (int i = 0; i < no; i++)
		{
			cout << "Enter dish name: ";
			fflush(stdin);
			cin.getline(dish, 100);
			rc->Order_dish(dish);

		}

		system("cls");

		//waiter();
		cout << "\n\t\tThank you for placing the order!" << endl;
		rc->print_itemlist();
		rc->bill();

	}

	void displaycustomers() {
		RoomCustomer d;
		d.displayroomcust();
	}

	void add_dish()
	{
		restaurant.addDish();
	}

	void remove_rooms()
	{
		admin.removeRoom();
	}

	void add_rooms() {
		admin.addRoom();
	}

	void add_employees()
	{
		admin.addEmployee();
	}

	void remove_employees()
	{
		admin.removeEmployee();
	}

	bool empty(std::ifstream& pFile)
	{
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	void admin_login()
	{
		system("cls");
		SetColor(84);
		cout << "\n\t\t\t-------LOGIN FORM-------";
		char array1[20], array2[20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c, v;
		int result_name, result_pass, option;

		cout << "\n\n\t\t\tSelect a number:\n";
		cout << "\n\t\t\t 1. Register\n";
		cout << "\n\t\t\t 2. Sign in\n";
		cout << "\n\t\t\tYour choice: ";
		cin >> option;
		while (option != 1 && option != 2) {
			cout << "Wrong option!";
			cin >> option;
		}

		//REGISTRATION
		if (option == 1) {
			//checking if a user exists
			ifstream file("Username.txt", ios::in);
			if (!empty(file)) {
				cout << "\n\t\t\tA user already exists. Please sign in to the system with your username.\n";
				cout << "\n\t\t\tPress any key to continue ... ";
				cin >> v;
				file.close();
				admin_login();
			}

			else {
				ofstream file1("Username.txt", ios::out);
				cout << "\t\t\tUsername: ";
				fflush(stdin);
				cin >> user;
				file1 << user;
				file1.close();
				ofstream file2("Password.txt", ios::out);
				cout << "\t\t\tPassword: ";
				fflush(stdin);
				//taking password in sterics

				int i = 0;
				while (i < 20)
				{
					fflush(stdin);
					pass[i] = _getch();
					c = pass[i];
					if (c == 13) break;
					else printf("*");
					i++;
				}
				pass[i] = '\0';

				cout << "\n\t\t\t\tYou have successfully registered!";
				file2 << pass;
				file2.close();

				printf("\n\t\t\tPress any key to continue ... ");
				cin >> v;

				setHotel();
			}


		}

		if (option == 2) {

			//SIGN-IN
			ifstream file3;
			file3.open("Username.txt", ios::in);
			if (empty(file3)) {
				cout << "\n\t\t\tPlease register yourself first\n";
				cout << "\n\t\t\tPress any key to continue...";
				cin >> v;
				admin_login();
			}
			else {
				cout << "\n\t\t\tUsername: ";
				fflush(stdin);//refresh
				cin >> sign_name;
				printf("\n\t\t\tPassword: ");
				fflush(stdin);

				char v;
				int a = 0;
				int count = 0;
				while (a < 20)
				{
					fflush(stdin);
					sign_pass[a] = _getch();
					c = sign_pass[a];
					if (c == 13) break;
					else printf("*");
					a++;
				}
				sign_pass[a] = '\0';

				ifstream file4("Username.txt", ios::in);
				file4 >> array1;
				file4.close();

				ifstream file5("Password.txt", ios::in);
				file5 >> array2;
				file5.close();

				result_name = strcmp(array1, sign_name);
				result_pass = strcmp(array2, sign_pass);


				if (result_pass != 0 || result_name != 0) {
					count++;
					if (count == 3) {
						cout << "\n\t\t\t3 wrong attempts on credentials.";
						exit(0);
					}
					cout << "\n\t\t\tWrong attempts on credentials.";
					cin >> v;
					admin_login();
				}

				else if (result_name == 0 && result_pass == 0) cout << "\n\t\t\tWelcome user " << array1;
				cin >> v;
			}
		}
	}
};


void admin(Hotel& r) {
	int choice;


	do {
		SetColor(74);
		cout << "*****************************************************************************\n";
		cout << "Please press the corresponding number to select one of the following options:\n";
		cout << "*****************************************************************************\n";
		cout << "\n\t\t[1] Add Room\n";
		cout << "\n\t\t[2] Remove Room\n";
		cout << "\n\t\t[3] Add Employee\n";
		cout << "\n\t\t[4] Remove Employee\n";
		cout << "\n\t\t[5] See Menu\n";
		cout << "\n\t\t[6] Add Dish\n";
		cout << "\n\t\t[7] View All Rooms\n";
		cout << "\n\t\t[8] Display All Workers\n";
		cout << "\n\t\t[9] See All Room Customers\n";
		cout << "\n\t\t[10] Exit ";
		cout << "\n\n\t\t";
		cin >> choice;
		system("cls");

		switch (choice) {
		case 1:
			r.add_rooms();
			break;
		case 2:
			r.remove_rooms();
			break;
		case 3:
			r.add_employees();
			break;
		case 4:
			r.remove_employees();
			break;
		case 5:
			r.displayMenu();
			break;
		case 6:
			r.add_dish();
		case 7:
			r.display_allrooms();
			break;
		case 8:
			r.displayWorkers();
			break;
		case 9:
			r.displaycustomers();
			break;
		case 10:
			exit(0);

		default:
			Exception obj(1, "Invalid option!");
			obj.what();
		}
	} while (choice != 10);

}

void Exit() {
	system("cls");
	Hotel h;
	h.askFeedback();
	SetColor(44);
	cout << "*****************************************************************************\n";
	printf("               Thank you for using the Hotel Management System!\n");
	cout << "*****************************************************************************\n";
	exit(0);
}

void customer(Hotel& r1) {
	int choice, option;
	SetColor(14);
	cout << "********************************************************************************\n";
	cout << "Press [1] for options related to hotel rooms or [2] for dining in the restaurant\n";
	cout << "*********************************************************************************\n";
	cin >> option;

	while (option != 1 && option != 2) {
		cout << "Invalid option!";
		cin >> option;
	}

	switch (option) {

	case 1:
		do {
			SetColor(54);
			cout << "\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
			cout << "\n\t\t[1] View All Available Rooms\n";
			cout << "\n\t\t[2] Room Reservation\n";
			cout << "\n\t\t[3] Cancel Reservation\n";
			cout << "\n\t\t[4] Order Room Service\n";
			cout << "\n\t\t[5] Check Out\n";
			cout << "\n\t\t[6] Exit ";
			cout << "\n\n\t\t";
			cin >> choice;
			system("cls");

			switch (choice) {
			case 1:
				r1.display_availableRooms();
				break;
			case 2:
				r1.bookRoom();
				break;
			case 3:
				r1.cancel_room();
				break;
			case 4:
				r1.room_service();
				break;
			case 5:
				r1.RoomCustomer_checkOut();
				Exit();
				break;
			case 6:
				Exit();

			default:
				Exception obj(1, "Invalid option!");
				obj.what();

			}
		} while (choice != 6);
		break;

	case 2:
		do {
			SetColor(54);
			cout << "\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
			cout << "\n\t\t[1] See Menu\n";
			cout << "\n\t\t[2] Place Order and Checkout";
			cout << "\n\n\t\t";
			cin >> choice;
			system("cls");

			switch (choice) {
			case 1:
				r1.displayMenu();
				break;
			case 2:
				char v;
				r1.takeOrder();
				cout << "\n\t\t\tPress any key to continue...";
				cin >> v;
				Exit();
				break;

			default:
				Exception obj(1, "Invalid option!");
				obj.what();

			}
		} while (choice != 2);
		break;
	}
}



int main()
{

	char user;
	SetColor(34);
	Hotel r1("Rennaisance", "Club Rd، opposite PIDC, Civil Lines, Karachi, Karachi City, Sindh");
	cout << "---------------------************************************************-------------------------\n";
	cout << "********************************************************************************************\n";
	cout << "                    -----WELCOME TO HOTEL " << r1.getHotel_name() << "------ \n";
	cout << "********************************************************************************************\n";
	cout << "---------------------************************************************-------------------------\n\n\n";
	SetColor(24);
	cout << "********************************************************************************************\n";
	cout << "        Press 'A' if you are the hotel administrator and 'C' if you are a customer : \n";
	cout << "********************************************************************************************\n";

	cin >> user;
	system("cls");

	switch (user) {
	case 'a':
	case 'A':
		r1.admin_login();
		system("cls");
		admin(r1);
		break;


	case 'c':
	case 'C':
		customer(r1);
		break;

	default:
		throw std::invalid_argument("Invalid option selected.");
		// throw an invalid_argument exception if the user entered an invalid option
	}



	return 0;
}
