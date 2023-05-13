
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

class Employee;
class Exception;
class Dish;
class RestaurantCustomer;
class Restaurant;
class Hotel;
class Room;
class RoomService;
class Waiter;

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
	char roomType[20];
	int noOfBeds;
	double rent;
	int roomNo;
	int status;
	static int noOfrooms;
public:
	Room()
	{}
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
		while (file.read((char*)&r, sizeof(Room)))
		{
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

class Restaurant
{
public:
	vector <Dish> dish;

public:
	void addDish()
	{
		string dtype, dname;
		double dprice;

		ofstream menu;
		menu.open("Menu.bin", ios::app | ios::binary);

		cout << "Enter Dish Name : "; cin >> dname;
		cout << "Enter Dish Price: "; cin >> dprice;
		cout << "Enter Dish Type : "; cin >> dtype;

		Dish a(dname, dprice, dtype);

		menu.write((char*)&a, sizeof(Dish));

		menu.close();
	}


	Dish getDish(string dnam)
	{
		for (int i = 0; i < dish.size(); i++)
		{

			if (dish[i].dishName == dnam)

			{
				return dish[i];
			}
		}
	}


	void displayMenu()
	{
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
	long int custID;
	long int custPhone;
	char checkInTime[50];
public:
	static int noOfcustomers;
	static long int n;



	Customer()
	{
		time_t c = time(0);
		string dt = ctime(&c);
		noOfcustomers++;

	}

	void setData()
	{
		time_t now = time(0);
		string dt = ctime(&now);
		for (int i = 0; i < dt.size(); i++) {
			checkInTime[i] = dt[i];
		}
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
	RoomService rs;
	int room_no;
	int days;
	double rbill;
	Room r;

	RoomCustomer() {}

	RoomCustomer(int rn, int d)
	{
		room_no = rn;
		days = d;
	}

	void viewbill()
	{
		rbill = r.rent * days;
		cout << "Bill =" << rbill;
	}

	void bookRoom(Room& r1)
	{
		//r1.displayAvailable();  //send this to where ur booking
		this->r = r1;

		Room temp;
		vector <Room> s;
		ifstream file("Rooms.bin", ios::in | ios::binary);
		while (file.read((char*)&temp, sizeof(Room))) {
			s.push_back(temp);
		}
		file.close();

		int st = r1.checkstatus(r1);

		if (st == 0) {
			for (int i = 0; i < s.size(); i++) {
				if (s[i].roomNo == r1.roomNo) {
					s[i].status == 1;
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

	void order_roomservice()
	{
		rs.perform_duty();
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

	void checkOut()
	{
		Bill b;
		RoomCustomer rc;
		//b.roomcustomer_print_bill(*this);
		b.roomcustomer_print_bill(rc);
		r.vacateRoom(r.roomNo);
	}

	void addRoomCustomer() {
		ofstream customer;
		customer.open("RoomCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RoomCustomer));
		customer.close();
	}

	friend void operator +(RoomCustomer& r, vector<RestaurantCustomer> m);
};

class RestaurantCustomer :public Customer
{
public:
	double dbill;
	vector <string> dishes;
public:
	//order dish
	void Order_dish(string a)
	{
		dishes.push_back(a);

	}

	//items that has bought by customer
	void print_itemlist(vector<Dish> d)
	{
		cout << "You have ordered:\n";
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

	void addRestaurantCustomer() {
		ofstream customer;
		customer.open("RestaurantCustomer.bin", ios::app | ios::binary);
		customer.write((char*)&(*this), sizeof(RestaurantCustomer));
		customer.close();
	}

	friend void operator +(RoomCustomer& r, vector<RestaurantCustomer> m);

};

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
		char roomType[10];
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
		{RoomService r();
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


class Bill {
	static int bill_id;
	double tbill;

public:



	Bill() { bill_id++; }

	void roomcustomer_print_bill(RoomCustomer& c)
	{


		//RoomCustomer r;
		vector <RestaurantCustomer> rs;

		/*RoomCustomer temp;

		ifstream file("RoomCustomer.bin", ios::in | ios::binary);
		while (file.read((char*)&temp, sizeof(RoomCustomer))) {
			if (temp.custName == c.custName && temp.custPhone == c.custPhone) {
				r = temp;
			}
		}
		file.close();*/

		RestaurantCustomer temp2;

		ifstream file1("RestaurantCustomer.bin", ios::in | ios::binary);
		while (file1.read((char*)&temp2, sizeof(RestaurantCustomer))) {
			rs.push_back(temp2);
		}
		file1.close();

		vector <RestaurantCustomer> forbill;


		for (int j = 0; j < rs.size(); j++) {
			if (c.custName == rs[j].custName && c.custPhone == rs[j].custPhone) {
				forbill.push_back(rs[j]);
			}
		}
		c + forbill;



	}

	void restaurantcustomer_print_bill(double p) {
		cout << "Bill = " << p;
	}


	friend void operator +(RoomCustomer& r, vector<RestaurantCustomer> m);

};
int Bill::bill_id = 999;

void operator +(RoomCustomer& r, vector<RestaurantCustomer> m) {
	Bill b;
	b.tbill = r.rbill;
	for (int i = 0; i < m.size(); i++) {
		b.tbill += m[i].dbill;
	}

	cout << "Your total bill during your stay is " << b.tbill << "/-" << endl;
	cout << "Thank You! Visit Again.\n" << endl;
}




class Hotel
{
private:
	static Hotel* instanceHotel;
	string hotelName;
	string hotelAddress;
public:
	Employee* employee[5];
	Restaurant restuarant;
	Administrator admin;
	RoomCustomer roomcus;

	Room room[6], r2;
	Customer* customer[5];
	Bill bill;


	void display_availableRooms()
	{
		r2.displayAvailable();
	}


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
	void room_service()
	{
		roomcus.order_roomservice();
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

	void cancelRoom() {


		r2.vacateRoom(r2.roomNo);
	}

	void RoomCustomer_checkOut()
	{
		Bill b;
		RoomCustomer rc1;
		b.roomcustomer_print_bill(rc1);
		r2.vacateRoom(r2.roomNo);
	}

	void RestCustomer_checkout()
	{
		Bill b1;
		b1.restaurantcustomer_print_bill(1238743);

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

	void add_dish()
	{
		restuarant.addDish();
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
	void employee_login()
	{
		system("cls");
		cout << "\n\t\t\t-------LOGIN FORM-------";
		char array[3][20], pass[20], user[20], sign_name[20], sign_pass[20], ch, c;
		int result_name, result_pass, option;
		FILE* fptr;

		cout << "\n\n\t\t\tSelect a number:\n";
		cout << "\n\t\t\t 1. Register\n";
		cout << "\n\t\t\t 2. Sign in\n";
		cout << "\n\t\t\tYour choice: ";
		cin >> option;

		//REGISTRATION
		if (option == 1) {
			//checking if a user exists
			fptr = fopen("Signin_details.txt", "r+");
			if (fptr != NULL && (ch = getc(fptr)) != EOF) {
				printf("\n\t\t\tA user already exists. Please sign in to the system with your username.\n");
				printf("\n\t\t\tPress any key to continue ... ");
				getch();
				fclose(fptr);
				//login();
			}

			else {
				fptr = fopen("Signin_details.txt", "w+");
				printf("\t\t\tUsername: ");
				fflush(stdin);
				fgets(user, 30, stdin);
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

				//bus();//calling bus function to input some bus data on the first registration
			}


		}

		if (option == 2) {

			//SIGN-IN
			fptr = fopen("Signin_details.txt", "r+");
			if ((ch = getc(fptr)) == EOF) {
				printf("\n\t\t\tPlease register yourself first\n");
				printf("\n\t\t\tPress any key to continue...");
				getch();
				//login();
			}
			else {
				printf("\n\t\t\tUsername: ");
				fflush(stdin);//refresh
				fgets(sign_name, 20, stdin);
				printf("\n\t\t\tPassword: ");
				fflush(stdin);

				int a = 0;
				int count;
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
					//login();
				}

				else if (result_name == 0 && result_pass == 0) printf("\n\t\t\tWelcome user %s", array[0]);
				getch();
			}
		}
		fclose(fptr);
	}
};
Hotel* Hotel::instanceHotel = 0;




int main()
{
	//do login then admin menu
	char user;
	system("COLOR F8");
	cout << "\n\t\t\t-----WELCOME TO HOTEL-----";//add name
	cout << "\n\n\tPress 'A' if you are the hotel administrator and 'C' if you are a customer : ";
	cin >> user;
	system("cls");

	switch (user) {
	case 'a':
	case 'A':
		//login();
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
	Hotel r("Second Wife", "JINNAH AVANUE,MODEL COLONY,MALIR, Karachi, Pakistan ");

	do {
		cout << "\n\n\n\t\tPlease press the corresponding number to select one of the following options:\n";
		cout << "\n\t\t[1] Add Room\n";
		cout << "\n\t\t[2] Remove Room\n";
		cout << "\n\t\t[3] Add Employee\n";
		cout << "\n\t\t[4] Remove Employee\n";
		cout << "\n\t\t[5] Add Dish\n";
		cout << "\n\t\t[6] View All Rooms\n";
		cout << "\n\t\t[7] Exit ";
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
			r.add_dish();
		case 6:
			r.display_allrooms();
			break;

		default: printf("Wrong option");
		}
	} while (choice != 7);

}

void customer() {
	int choice, option;
	Hotel r1("Pearl Continental", "Club Rd، opposite PIDC, Civil Lines, Karachi, Karachi City, Sindh");


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

			switch (choice) {
			case 1:
				r1.display_availableRooms();
				break;
			case 2:
				r1.bookRoom(4);
				break;
			case 3:
				r1.cancelRoom();
				break;
			case 4:
				r1.room_service();
				break;
			case 5:
				r1.RoomCustomer_checkOut();
				break;

			default: printf("Wrong option");

			}
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

			switch (choice) {
			case 1:
				r1.displayMenu();
				break;
			case 2:
				r1.takeOrder("Pizza");
				break;
			case 3:
				r1.RestCustomer_checkout();
				exit(0);
				break;

			default: printf("Wrong option");

			}
		} while (choice != 3);
		break;
	}
}

