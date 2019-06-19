#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
class mobile {
	char mobname[15], comname[15];
	long price;
public:
	mobile();
	~mobile();
	void addMob();
	void modifyMob();
	void deleteMob();
	int searchMob();
	void displayMob();
	void search_mobname();
	void search_comname();
	void search_mobname_comname();
};

void searchMenu();
void exit();
void display();
void main(){
	mobile mob;

	int choice;
	do{
		clrscr();
		cout << "\nWelcome to Mobile Management System";
		cout << "\n===================================\n";
		cout << "\nMain Menu";
		cout << "\n=========";
		cout << "\n1. Add Mobile";
		cout << "\n2. Modify Mobile";
		cout << "\n3. Delete Mobile";
		cout << "\n4. Display Mobiles";
		cout << "\n5. Search";
		cout << "\n   ==> By Mobile Name";
		cout << "\n   ==> By Company Name";
		cout << "\n   ==> By Mobile Name and Company Name";
		cout << "\n0. Exit";
		cout << "\n\nEnter Choice [0-5]: ";
		cin >> choice;

		switch (choice){
			case 1: mob.addMob(); break;
			case 2: mob.modifyMob(); break;
			case 3: mob.deleteMob(); break;
			case 4: display(); break;
			case 5: searchMenu(); break;
			case 0: exit(); break;
			default: cout << "\nInvalid choice\n"; getch();
		}
	} while (choice != 0);
}
void searchMenu() {
	int choice;
	mobile mob;

	do{
		clrscr();
		cout << "\nSearch Menu";
		cout << "\n==========";
		cout << "\n1. Mobile Name";
		cout << "\n2. Company Name";
		cout << "\n3. Mobile Name and Company Name";
		cout << "\n0. Exit";
		cout << "\n\nEnter Choice [0-3]: ";
		cin >> choice;
		cin.ignore();
		switch (choice){
			case 1: mob.search_mobname(); break;
			case 2: mob.search_comname(); break;
			case 3: mob.search_mobname_comname(); break;
			case 0: break;
			default: cout << "\nInvalid choice\n"; getch();
		}
	} while (choice != 0);
}
void exit() {
	cout << "\nThanks for using Mobile Management System\n";
	getch();
}
mobile :: mobile() {
	strcpy (mobname, "");
	strcpy (comname, "");
	price = 0;
}
mobile :: ~mobile() {
	strcpy (mobname, "");
	strcpy (comname, "");
	price = 0;
}
void mobile :: addMob() {
	ofstream fout ("mobile.dat", ios :: app | ios :: binary);

	if (!fout){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	mobile mob;

	cout << "\nMobile Addition Screen";
	cout << "\n======================\n";

	cout << "\nMobile Name : "; gets(mob.mobname);
	strupr(mob.mobname);

	int flag = mob.searchMob();

	if (flag == 1){
		cout << "\nDuplicate mobiles are not allowed\n";
	}
	else if (flag == -1){
		cout << "\nFile error\n";
	}
	else {
		cout << "\nCompany Name : "; gets(mob.comname);
		strupr(mob.comname);
		cout << "\nPrice          : "; cin >> mob.price;

		fout.write((char *)&mob, sizeof(mob)) ;

		fout.close();

		cout << "\nRecord inserted successfully\n";
	}
	fout.close();
	cout << "\n\nPress any key to continue .....";
	getch();
}
void mobile :: modifyMob() {
	ifstream fin ("mobile.dat", ios :: binary);
	ofstream fout ("temp.dat", ios :: binary);

	if (!fin || !fout){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	mobile mob;

	cout << "\nMobile Modification Screen";
	cout << "\n==========================\n";

	char mobname[15];
	int flag = 0;

	cout << "\nMobile Name to modify : "; gets(mobname);

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.mobname,mobname)!=0) {
			fout.write((char *)&mob, sizeof(mob));
		}
		else {
			flag = 1;
			mob.displayMob();

			cout << "\nEnter New Values: \n";

			cout << "\nMobile Name        : "; gets(mob.mobname);
			strupr(mob.mobname);
			cout << "\nCompany Name   : "; gets(mob.comname);
			strupr(mob.comname);
			cout << "\nPrice          : "; cin >> mob.price;

			fout.write((char *)&mob, sizeof(mob));
		}
	}

	fin.close();
	fout.close();

	remove ("mobile.dat");
	rename ("temp.dat", "mobile.dat");

	if (flag == 1){
		cout << "\nRecord modified successfully\n";
	}
	else {
		cout << "\nInvalid Mobile Name : " << mobname << endl;
	}
	cout << "\nPress any key to continue .....";
	getch();
}
void mobile	:: deleteMob() {
	ifstream fin ("mobile.dat", ios :: binary);
	ofstream fout ("temp.dat", ios :: binary);

	if (!fin || !fout){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	mobile mob;

	cout << "\nMobile Deletion Screen";
	cout << "\n======================\n";

	char mobname[15] ;
	int flag = 0;

	cout << "\nEnter Mobile Name to delete : "; gets(mobname);

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.mobname,mobname)!=0) {
			fout.write((char *)&mob, sizeof(mob));
		}
		else {
			flag = 1;
			mob.displayMob();
		}
	}

	fin.close();
	fout.close();

	remove ("mobile.dat");
	rename ("temp.dat", "mobile.dat");

	if (flag == 1){
		cout << "\nRecord deleted successfully\n";
	}
	else {
		cout << "\nInvalid Mobile Name : " << mobname << endl;
	}
	cout << "\nPress any key to continue .....";
	getch();
}
int mobile :: searchMob() {
	ifstream fin ("mobile.dat", ios :: binary);

	if (!fin){
		cout << "\nFile not opened\n";
		return -1;
	}

	mobile mob;

	int flag = 0;

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.mobname,mobname)==0) {
			flag = 1;
			break;
		}
	}

	fin.close();

	return flag;
}
void mobile	:: displayMob() {
	cout << "\nMobile Name        : " << mobname << endl;
	cout << "\nCompamny Name   : " << comname << endl;
	cout << "\nPrice          : " << price << endl;
}
void mobile	:: search_mobname() {
	ifstream fin ("mobile.dat", ios :: binary);

	if (!fin){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	cout << "\nMobile Searching Screen";
	cout << "\n=======================\n";

	mobile mob;

	char mobname[15];
	int flag = 0;

	cout << "\nEnter Mobile Name to search : "; gets(mobname);

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.mobname, mobname)==0) {
			flag = 1;
			mob.displayMob();
			cout << "\n\nPress any key to continue .....\n";
			getch();
		}
	}

	if (flag == 0){
		cout << "\nInvalid Mobile Name : " << mobname << endl;
		cout << "\nPress any key to continue .....";
		getch();
	}
	fin.close();
}
void mobile	:: search_comname() {
	ifstream fin ("mobile.dat", ios :: binary);

	if (!fin){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	cout << "\nMobile Searching Screen";
	cout << "\n=======================\n";

	mobile mob;

	char comname[15];
	int flag = 0;

	cout << "\nEnter Company Name to search : "; gets(comname);

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.comname, comname)==0) {
			flag = 1;
			mob.displayMob();
			cout << "\n\nPress any key to continue .....";
			getch();
		}
	}

	if (flag == 0){
		cout << "\nInvalid Company Name : " << comname << endl;
		cout << "\n\nPress any key to continue .....";
		getch();
	}
	fin.close();
}
void mobile:: search_mobname_comname() {
	ifstream fin ("mobile.dat", ios :: binary);

	if (!fin){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	cout << "\nMobile Searching Screen";
	cout << "\n=======================\n";

       mobile mob;

	char mobname[15], comname[15];
	int flag = 0;

	cout << "\nEnter Mobile Name  to search      : "; gets(mobname);
	cout << "\nEnter Company Name to search : "; gets(comname);

	while (fin.read((char *)&mob, sizeof(mob)))	{
		if (strcmpi(mob.mobname, mobname)==0 && strcmpi(mob.comname, comname)==0) {
			flag = 1;
			mob.displayMob();
			cout << "\n\nPress any key to continue .....";
			getch();
		}
	}

	if (flag == 0){
		cout << "\nInvalid Mobile" << endl;
		cout << "\n\nPress any key to continue .....";
		getch();
	}
	fin.close();
}
void display() {
	ifstream fin ("mobile.dat", ios :: binary);

	if (!fin){
		cout << "\nFile not opened\n";
		getch();
		return;
	}

	mobile mob;

	cout << "\nDetails of mobiles";
	cout << "\n==================\n";

	while (fin.read((char *)&mob, sizeof(mob))) {
		mob.displayMob();
		cout << "\nPress any key to continue .....\n";
		getch();
	}

	fin.close();
}