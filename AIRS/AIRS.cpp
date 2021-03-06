/*
Airline Reservation System
Date: 08/12/2017
Author: @Ayush Agrawal, @Rajat Agarwal, @Pavan Bykampadi
*/
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <process.h>
#include <string.h>

using namespace std;

int main();
void admin();
struct Date {
	int day,
	month,
	year;
};

struct Flight {
	char num[6],
	al[20],
	src[4],
	dst[4];

	int price,
	seats,
	etdh,				//etd hour
	etah;          //eta hour

	Date etd;
} flight[20];


struct User {
	char name[20],
	pwd[20];

	int booked[10],
	bcount,
	type;  					//0 - user, 1 - airline

} user[10];




/*
Functions for AIRS Flights
Date: 19/12/2017
Author: @Ayush Agrawal, @Rajat Agarwal
*/


int n = 4, upos = 0; 											//number of flights, user logged in

void preset_vals(){													//hardcoded value presets

	//Users
	strcpy(user[0].name, "ayush");
	strcpy(user[1].name, "rajat");
	strcpy(user[2].name, "pavan");
	strcpy(user[3].name, "airline");

	strcpy(user[0].pwd, "ayush");
	strcpy(user[1].pwd, "rajat");
	strcpy(user[2].pwd, "pavan");
	strcpy(user[3].pwd, "airline");

	user[0].bcount = 0;
	user[1].bcount = 0;
	user[2].bcount = 0;
	user[3].bcount = 0;

	user[0].type = 0;
	user[1].type = 0;
	user[2].type = 0;
	user[3].type = 1;

	//Flights
	flight[0].price=20000;
	flight[0].seats=150;
	flight[0].etdh=1200;
	flight[0].etah=1400;
	flight[0].etd.day=6;
	flight[0].etd.month=9;
	flight[0].etd.year=2018;

	flight[1].price=25000;
	flight[1].seats=150;
	flight[1].etdh=1100;
	flight[1].etah=1500;
	flight[1].etd.day=6;
	flight[1].etd.month=9;
	flight[1].etd.year=2018;

	flight[2].price=27000;
	flight[2].seats=150;
	flight[2].etdh=1000;
	flight[2].etah=1400;
	flight[2].etd.day=8;
	flight[2].etd.month=10;
	flight[2].etd.year=2018;

	flight[3].price=30000;
	flight[3].seats=180;
	flight[3].etdh=2000;
	flight[3].etah=2350;
	flight[3].etd.day=6;
	flight[3].etd.month=9;
	flight[3].etd.year=2018;

	strcpy(flight[0].al,"Emirates");
	strcpy(flight[0].src,"blr");
	strcpy(flight[0].dst,"dxb");
	strcpy(flight[0].num,"em469");

	strcpy(flight[1].al,"Emirates");
	strcpy(flight[1].src,"dxb");
	strcpy(flight[1].dst,"gnv");
	strcpy(flight[1].num,"em369");

	strcpy(flight[2].al,"Air France");
	strcpy(flight[2].src,"blr");
	strcpy(flight[2].dst,"cdg");
	strcpy(flight[2].num,"ai489");

	strcpy(flight[3].al,"Ethihad");
	strcpy(flight[3].src,"blr");
	strcpy(flight[3].dst,"dbx");
	strcpy(flight[3].num,"et420");
}



void password(char pass[])
{

	cout << "\nPassword: \n";

	for(int i = 0; i < 20 ; i++) {
		pass[i]=getch();

		if(pass[i] !=8) {								//8 = ASCII for backspace
			cout << "*";
			if(pass[i] == '\r')							//If user presses enter
				break;
		}
		else if(pass[i] == 8 && i > 0) {
			i-=2;
			cout << "\b\b";
		}
	}
	pass[i]='\0';
}


void login(){
	char userName[20], pass[20];
	int loginAttempt = 0, flag = 0;

	while (loginAttempt < 5   &&   !flag)
	{
		if (loginAttempt > 0)
			cout << "Incorrect username or password \n\n";

		cout << "\nUser name: ";
		cin >> userName;

		password(pass);

		for(int i = 0; i < 10; i++)
		{
			if(strcmp(userName, user[i].name) == 0    &&    strcmp(pass, user[i].pwd) == 0)
			{
				if (user[i].type == 0)
					userf();
				else
					admin();

				loginAttempt = 0;
				upos = i;
				flag = 1;

				break;
			}
		}
	}

	if (loginAttempt == 5)
		cout << "\nToo many login attempts! The program will now terminate.";
}


void drawline(){
	cout << "\n________________________________________________________________________________\n";
}

void header(){

	clrscr();

	cout << setw(80) << "Logged in as: " << user[upos].name;

	drawline();
	cout << "Airplane Reservation System";
	drawline();
}

void table_line(int i, int sl){

	cout << '\n' << setw(5) << sl << setw(6) << flight[i].num << setw(20) << flight[i].al;
	cout << setw(4) << flight[i].etd.day << '/' << setw(2) << flight[i].etd.month << '/' << setw(4) << flight[i].etd.year << setw(6) << flight[i].etdh;
	cout << setw(8) << flight[i].etah << setw(8) << flight[i].price
}



void display_flights() {

	header();

	cout << '\n' << setw(5) << "Sl" << setw(6) << "Flight" << setw(20) << "Airline" << setw(18) << "Departure" << setw(8) << "Arrival" << setw(8) << "Price";

	drawline();

	for(int i=0; i<n; i++)
		table_line(i, i+1);
}



void add_flight() {

	header();

	char fno[6];
	int i;
	//enter airline
	cout << "\nEnter Airline:";
	cin >> flight[n].al;

	//input flight time
	cout << "\n\nEnter Date of Departure: (DD MM YYYY): " << endl;
	cin >> flight[n].etd.day >> flight[n].etd.month >> flight[n].etd.year;

	cout << "\n\nEnter Estimated time of Departure (24 hour):" << endl;
	cin >> flight[n].etdh;

	cout << "\n\nEnter Estimated time of Arrival (24 hour):" << endl;
	cin >> flight[n].etah;

	//generates flight number (eg AI250 etc)
	for (i = 0; i < 2; i++)
		fno[i] = flight[n].al[i];

	for (; i < 5; i++)
		fno[i] = rand() % 10 + 49;

	fno[6]='\0';

	strcpy(flight[n].num, fno);

	//input destination and source
	cout << "\nEnter Source Airport: " << endl;
	cin >> flight[n].src;

	cout << "\n\nEnter Destination Airport: " << endl;
	cin >> flight[n].dst;

	cout << "\nenter cost per seat :";
	cin >> flight[n].price;

	n++;

	//continue
	cout << "\nEnter any key to continue";
	getch();

}



void del_flight()
{

	display_flights();

	cout << "\nEnter sl no of flight to be deleted :";
	int pos;

	cin >> pos;

	for (int i = pos - 1; i <= n; i++)
		flight[i] = flight[i+1];

	n--;
}



void status()
{
	int cpos, sl = 1, fpos, bcount;
	char ch, conf;

	bcount = user[upos].bcount;

	for(int i=0; i<n; i++)
	{
		for(int j = 0; j <= bcount; j++)
		{
			if(user[upos].booked[j] == i) {

				table_line(i, sl);
				sl++;
				break;
			}
		}
	}

	header();

	cout << "\nPress R to return to main menu";
	cout << "\nPress C to cancel a booking";

	getch(ch);
	do{
		if(ch=='C' || ch=='c') {
			cout << "\nenter serial number of flight to cancel: ";
			cin >> cpos;

			fpos = user[upos].booked[cpos-1];					//index of flight as stored in the Flights array

			cout << "\nCancel flight from "<<flight[fpos].src<<" to "<<flight[fpos].dst<<"?\nPress C to confirm :";
			cin >> conf;

			if(conf=='C' || conf=='c')
			{
				user[upos].bcount--;
				bcount--;

				//deleting entry
				for (int i = cpos-1; i < bcount; i++)
					user[upos].booked[i] = user[upos].booked[i+1];

			}
		} else if (ch != 'r' && ch != 'R') {
			cout << "\nPlease enter valid input";
		}
	} while (ch != 'c' && ch != 'C' && ch != 'r' && ch != 'R');
}



void pay(int pos)
{
	header();

	int CVV, bcount, card_no[16];

	cout << "\nenter card no. :";
	for(int i = 0; i < 16; i++)
		cin >> card_no[i];

	cout << "\n\nenter CVV :";
	cin >> CVV;

	cout << "\nproccessing payment...";
	for (double i = 0; i < 500000000; i++) {}			//delay timer

	bcount = user[upos].bcount;

	user[upos].booked[bcount] = pos;
	user[upos].bcount++;
}



void confirmation(int pos)
{
	header();

	int seats;

	cout << "\nenter no. of seats :";
	cin >> seats;

	cout << "\nPrice payable :" << flight[pos].price * seats;

	cout << "\n\n" << "press any key to continue to payment page";
	getch();
	pay(pos);
}



void search()
{
	header();

	char src[4], des[4];
	int day, month, year;

	cout << "\nenter source airport code :";

	cin >> src;
	cout << "\nenter destination airport code :";
	cin >> des;

	cout << "\nenter date of departure : (DD MM YYYY) :";
	cin >> day >> month >> year;

	int sl = 0, result[10], j = 0, bpos;			//result stores the search results with user friendly indices - j
	//bpos is sl no of flight to be booked
	for(int i=0; i<n; i++)
	{

		if ( strcmpi(src,flight[i].src) == 0   &&   strcmpi(des,flight[i].dst) == 0   &&   flight[i].etd.day == day   &&   flight[i].etd.month == month &&   flight[i].etd.year == year)
		{
			result[j] = i;
			j++;
			sl++;

			table_line(i, sl)
		}
	}

	if(sl != 0) {
		cout << "\nEnter serial no of flight to book :";
		cin >> bpos;
		confirmation(result[bpos-1]);					//result[bpos-1] gives corresponding index of flight as stored in Flights array
	} else
		cout << "\nSorry!No flights match your request";

}


void userf()
{

	int flag = 1, bcount, ch = 1;
	bcount = user[upos].bcount;

	do
	{
		if(ch > 3 || ch < 1)
			cout << "Please enter value between 1 and 3";

		cout << "\n1: Search for flights\n2: View current booking\n3: Exit";
		cout << "\n\noption: ";

		cin >> ch;

		switch(ch){
			case 1:
				search();
				break;
			case 2:
				status();
				break;
			case 3:
				cout << "\nThank you for using our services!!";
				flag=0;
				break;
		}
	} while(flag && (ch > 3 || ch < 1));			//checks for correct input and exit
}


void admin()
{
	header();

	int flag = 1, ch = 1;

	do {

		if (ch > 3 || ch < 1)
			cout << "\nEnter valid option";

		cout << "\n1. Add flight\n2. Delete flight\n3. Logout";
		cout << "\n\nOption :";

		cin >> ch;
		switch(ch)
		{
			case 1:
				add_flight();
				break;
			case 2:
				del_flight();
				break;
			case 3:
				flag = 0;
				break;
		}
	} while (flag && (ch > 3 || ch < 1));
}


int main()
{
	drawline();
	cout << "AIRLINE RESERVATION SYSTEM";
	drawline();

	preset_vals();
	login();

	cout << "\nHave a good day!!\n";
	return 0;
}
