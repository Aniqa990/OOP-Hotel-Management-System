// Hotel Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include<conio.h>
#include<cstdio>
#include<cstring>
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <vector>
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
	double rent; //per night
	int roomNo;
	int status;
	static int noOfrooms;
public:

	Room(string roomType, int noOfBeds, double rent, int roomNo)
	{
		this->roomType = roomType;
		this->noOfBeds = noOfBeds;
		this->rent = rent;
		this->roomNo = roomNo;
		this->status = 0;
		noOfrooms++;

	}
	void setRoom()
	{
		cout << "Enter Room Type, No of beds, Rent, RoomNo\n";
		cin >> this->roomType;
		cin >> this->noOfBeds;
		cin >> this->rent;
		cin >> this->roomNo;
		status = 0;
		noOfrooms++;

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
	void displayAvailable(Room& r)
	{
		//Room r;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&r, sizeof(Room))) {
			if (r.status == 0) {
				r.display_roomDetail();
			}
		}
		file.close();
	}

};
int Room::noOfrooms = 0;

class Dish
{
public:
	string dishName;
	double price;
	string dishType;
	static int noOfdishes;

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
int Dish::noOfdishes = 0;


class Customer
{
protected:

	
	long int custID;
	string checkInTime;
public:
	static int noOfcustomers;
	static long int n;
        string custName;
	string custAddress;
        long int custPhone;

	Customer()
	{
		time_t c = time(0);
		string dt = ctime(&c);
		this->custName = " ";
		this->custAddress = " ";
		this->custID = 0;
		this->custPhone = 0L;
		this->checkInTime = dt;

	}

	void setData()
	{
		time_t now = time(0);
		string dt = ctime(&now);
		this->checkInTime = dt;
		custID = n++;
		ofstream customer;
		customer.open("Customer.txt", ios::ate);
		cout << "Enter your Name :\n";
		cin >> this->custName;

		cout << "Enter your Address :\n";
		cin >> this->custAddress;

		cout << "Enter your Phone number :\n";
		cin >> this->custPhone;

		customer.write((char*)&(*this), sizeof(Customer));


		customer.close();

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
	virtual void viewBill() {
	}

	virtual void checkout() {
	}
};
int Customer::noOfcustomers = 0;
long int Customer::n = 99999;



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
	RoomCustomer(int r, int d):Customer()
	{
		room_no = r;
		days = d;
	}

	void viewbill()
	{
		rbill = r.rent*days;
		cout << "Bill =" << rbill;
	}

	void bookRoom(Room r1)
	{
		r1.displayAvailable(r1);
		this->r = r1;

		//open rooms file and update status
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
		dishes.push_back(a);

	}

	//items that has bought by customer
	void print_itemlist(vector<Dish> d)
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
	static int x;

	Employee() {}

	Employee(string n) :name(n) {
		employeeid = x++;
	}

	virtual void perform_duty() = 0;
	virtual ~Employee() {
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
		cout << "Executing ordered room service ....  " << endl << "Room Service Executed!" << endl;
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
		string roomType;
		int noOfBeds, roomNo;
		double rent;

		cout << "Enter Room Type, No of beds, Rent, RoomNo\n";
		cin >> roomType;
		cin >> noOfBeds;
		cin >> rent;
		cin >> roomNo;

		Room r(roomType, noOfBeds, rent, roomNo);

		ofstream file("Rooms.bin", ios::app | ios::binary);
		file.write((char*)&r, sizeof(Room));
		file.close();
	}
	void removeRoom() {
		//int number;
		////display all rooms
		//cout << "Enter the room number: ";
		//cin >> number;

		//Room r;
		//fstream file("Rooms.bin", ios::in | ios::binary);
		//fstream file1("temp.bin", ios::app | ios::binary);

		//while (file.read((char*)&r, sizeof(Room))) {
		//	if (r.roomNo != number) {
		//		file1.write((char*)&r, sizeof(Room));
		//	}
		//}

		//remove("Rooms.bin");
		//rename("temp.bin", "Rooms.bin");

		vector <Room> r;
		int number;
		//display all rooms
		cout << "Enter the room number: ";
		cin >> number;

		Room s;
		ifstream file("Rooms.bin", ios::in | ios::binary);

		for (int i = 0; i < Room::noOfrooms; i++) {
			file.read((char*)&s, sizeof(Room));
			r.push_back(s);
		}
		file.close();

		for (int i = 0; i < r.size(); i++) {
			if (r[i].roomNo == number) {
				r.erase(r.begin() + i);
				i--;
			}
		}

		ofstream file1;
		file1.open("Rooms.bin", ios::out | ios::binary);
		for (int i = 0; i < r.size(); i++) {
			file1.write((char*)&r[i], sizeof(Room)); //not working
		}
		file1.close();

	}

	void addEmployee() {
		string ename;
		int choice;

		cout << "Enter employee name :"; cin >> ename;
		cout << "Enter 1 if employee is a room service employee and 2 for waiter employee: "; cin >> choice;

		switch (choice) {
		case 1:
		{RoomService r(ename);
		fstream file("Employees.bin", ios::app | ios::binary);
		file.write((char*)&r, sizeof(RoomService));
		file.close();
		break; }

		case 2:
		{Waiter w(ename);
		fstream file("Employees.bin", ios::app | ios::binary);
		file.write((char*)&w, sizeof(Waiter));
		file.close();
		break; }
		}
	}

	void removeEmployee() {
		string ename;
		Employee** e = new Employee * [2];

		RoomService r;
		Waiter w;
		e[0] = &w;
		e[1] = &r;

		cout << "Enter employee name :"; cin >> ename;

		fstream file("Rooms.bin", ios::in | ios::binary);
		fstream file1("temp.bin", ios::app | ios::binary);

		for (int i = 0; i < 2; i++) {
			while (file.read((char*)&(*e[i]), sizeof(Employee))) {
				if (ename != e[i]->name) {
					file1.write((char*)&(*e[i]), sizeof(Employee));
				}
			}
		}

		remove("Employees.bin");
		rename("temp.bin", "Employees.bin");
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



class Bill {
	int bill_id;

public:



	Bill() {}

	void print_bill()
	{


	}
};

class Hotel
{
private:
	static Hotel* instanceHotel;
	string hotelName;
	string hotelAddress;
public:
	Employee* employee[5];
	Restaurant restuarant;

	Room room[6];
	Customer* customer[5];
	Bill bill;
private:


	Hotel(string hname, string add)
	{
		this->hotelName = hname;
		this->hotelAddress = add;
	}
public:
	static Hotel* getHotel()
	{
		if (!instanceHotel)
			instanceHotel = new Hotel("RENNAISSANCE", "HUBLI");
		return instanceHotel;
	}

	void setHotel(Restaurant r, Room rs[6])
	{
		int i;

		for (i = 0; i < 6; i++)
		{
			this->room[i] = rs[i];
		}
		for (i = 0; i < 8; i++)
			this->restuarant.dish[i] = r.dish[i];

	}

	//extra
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
		int i;
		cout << "\n\n----------------------------------------------Room Details----------------------------------------------\n\n";
		cout << setw(25) << "Room Type" << setw(25) << "Number of Beds" << setw(25) << "Rent" << setw(25) << "Room Number\n";
		for (i = 0; i < 6; i++)
		{
			if (room[i].status == 0)
			{
				cout << setw(25) << room[i].roomType;
				cout << setw(25) << room[i].noOfBeds;
				cout << setw(25) << room[i].rent;
				cout << setw(25) << room[i].roomNo << "\n";
			}
		}
		cout << "\n\n";
	}

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

	//extra
	void askFeedback()
	{
		int f;
		string cname;
		ofstream feedback;
		feedback.open("feedback.txt", ios::app);
		feedback << "Customer Name\t : ";
		cout << "Enter your Name\n";
		cin >> cname;
		feedback << cname << "\t\t\t";
		cout << " Thanks for your time! \n How likely are you to recommend Hotel Rennaisance to a Friend or Colleague? \n Rate on a scale of 1-10\n";
		cin >> f;
		feedback << "Feedback\t: ";
		feedback << f << "\n";
		feedback.close();
		cout << " Thanks for your valuable feedback!" << endl;
	}
	//extra
	void getCustomerData(Customer* c)
	{
		cout << " Name :: " << c->custName << endl;
		cout << " Address :: " << c->custAddress << endl;
		cout << " Phone :: " << c->custPhone << endl;

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

	void show_bill()
	{
		bill.print_bill();
	}
	void add_dish()
	{
		restuarant.addDishes();
	}

	void remove_rooms()
	{

	}

	void add_rooms() {

	}

	void add_employees()
	{

	}

	void remove_employees()
	{

	}
	void employee_login()
	{
		system("cls");
		cout<<"\n\t\t\t-------LOGIN FORM-------";
		char array[3][20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c;
		int result_name, result_pass, option;
		FILE* fptr;

	    cout<<"\n\n\t\t\tSelect a number:\n";
		cout<<"\n\t\t\t 1. Register\n";
		cout<<"\n\t\t\t 2. Sign in\n";
		cout<<"\n\t\t\tYour choice: ";
		cin>>option;

		//REGISTRATION
		if (option == 1) {
			//checking if a user exists
			fptr = fopen("Signin_details.txt", "r+");
			if (fptr != NULL && (ch = getc(fptr)) != EOF) {
				printf("\n\t\t\tA user already exists. Please sign in to the system with your username.\n");
				printf("\n\t\t\tPress any key to continue ... ");
				getch();
				fclose(fptr);
				login();
			}

			else {
				fptr = fopen("Signin_details.txt", "w+");
				printf("\t\t\tUsername: ");
				fflush(stdin);
				gets(user);
				printf("\t\t\tPassword: ");
				fflush(stdin);
				//taking password in sterics

				int i = 0;
				while (i < 20)
				{
					pass[i] = getch();
					c = pass[i];
					if (c == 13) break;
					else printf("*");
					i++;
				}
				pass[i] = '\0';

				printf("\n\t\t\t\tYou have successfully registered!");
				fprintf(fptr, "%s\n%s\n", user, pass);
				fclose(fptr);

				printf("\n\t\t\tPress any key to continue ... ");
				getch();

				bus();//calling bus function to input some bus data on the first registration
			}


		}

		if (option == 2) {

			//SIGN-IN
			fptr = fopen("Signin_details.txt", "r+");
			if ((ch = getc(fptr)) == EOF) {
				printf("\n\t\t\tPlease register yourself first\n");
				printf("\n\t\t\tPress any key to continue...");
				getch();
				login();
			}
			else {
				printf("\n\t\t\tUsername: ");
				fflush(stdin);//refresh
				gets(sign_name);
				printf("\n\t\t\tPassword: ");
				fflush(stdin);

				int a = 0;
				while (a < 20)
				{
					sign_pass[a] = getch();
					c = sign_pass[a];
					if (c == 13) break;
					else printf("*");
					a++;
				}
				sign_pass[a] = '\0';

				int i = 0;
				rewind(fptr);
				while (!feof(fptr)) {
					fgets(array[i], sizeof(array[i]), fptr);
					i++;
				}
				strcat(sign_name, "\n"); //fgets takes null character in string too
				strcat(sign_pass, "\n");


				result_name = strcmp(array[0], sign_name);
				result_pass = strcmp(array[1], sign_pass);


				if (result_pass != 0 || result_name != 0) {
					count++;
					if (count == 3) {
						printf("\n\t\t\t3 wrong attempts on credentials.");
						exit(0);
					}
					printf("\n\t\t\tWrong attempts on credentials.");
					getch();
					login();
				}

				else if (result_name == 0 && result_pass == 0) printf("\n\t\t\tWelcome user %s", array[0]);
				getch();
			}
		}
		fclose(fptr);
	}
};
Hotel* Hotel::instanceHotel = 0;



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
	//do login then admin menu
	char user;
	system("COLOR F8");
	cout<<"\n\t\t\t-----WELCOME TO HOTEL-----";//add name
	cout<<"\n\n\tPress 'A' if you are the hotel administrator and 'C' if you are a customer : ";
	cin >> user;
	system("cls");

	switch (user) {
	case 'a':
	case 'A':
		login();
		system("cls");
		admin();
		break;


	case 'c':
	case 'C':
		customer();
		break;
	}


	return 0;
}

void admin() {
	int choice;
	
	do {
		cout<<"\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
		cout<<"\n\t\t[1] Add Room\n";
		cout<<"\n\t\t[2] Remove Room\n";
		cout<<"\n\t\t[3] Add Employee\n";
		cout<<"\n\t\t[4] Remove Employee\n";
		cout << "\n\t\t[5] Add Dish\n";
		cout << "\n\t\t[6] View All Rooms\n";
		cout<<"\n\t\t[7] Exit ";
		cout<<"\n\n\t\t";
		cin>>choice;
		system("cls");

		/*switch (choice) {
		case 1: bus();
			break;
		case 2: record();
			break;
		case 3: delete_record();
			break;
		case 4: update_pass();
			break;
		case 5: exit();
		default: printf("Wrong option");
		}*/
	} while (choice != 7);

}

void customer() {
	int choice, option;

	cout << "Press [1] for options related to hotel rooms or [2] for dining in the restaurant\n";
	cin >> option;

	switch (option) {
	case 1:
		do {
			cout << "\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
			cout << "\n\t\t[1] View All Available Rooms\n";
			cout << "\n\t\t[2] Room Reservation\n";
			cout << "\n\t\t[3] Cancel Reservation\n";
			cout << "\n\t\t[4] Order Room Service\n";
			cout << "\n\t\t[5] Check Out\n"; //here you will have to exit afterwards
			cout << "\n\t\t[6] Exit ";
			cout << "\n\n\t\t";
			cin >> choice;
			system("cls");

			/*switch (choice) {
			case 1: record();
				break;
			case 2: reservation();
				break;
			case 3: cancel();
				break;
			case 4: exit();
				break;
			default: printf("Wrong option");

			}*/
		} while (choice != 6);
		break;

	case 2:
		do {
			cout << "\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
			cout << "\n\t\t[1] See Menu\n";
			cout << "\n\t\t[2] Place Order\n";
			cout << "\n\t\t[3] Checkout ";
			cout << "\n\n\t\t";
			cin >> choice;
			system("cls");

			/*switch (choice) {
			case 1: record();
				break;
			case 2: reservation();
				break;
			case 3: cancel();
				break;
			case 4: exit();
				break;
			default: printf("Wrong option");

			}*/
		} while (choice != 3);
		break;
	}
}
