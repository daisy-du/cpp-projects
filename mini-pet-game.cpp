// HEADER FILE USED IN PROJECT

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// CLASS USED IN PROJECT

class pet {

	int pet_id;
	char name[50];
	int fullness;
	int friendliness;
	string type;

public:
	void create_pet();	// function to get pet data from user
	void show_pet() const;	// function to show pet data
	void modify();	// function to edit pet info
	void feed(int);	// function to feed the pet 
	void play();	// function to play with pet
	void report() const;	// function to show data in tabular format
	int retpet_id() const;	// function to return pet number
	int retfullness() const;	// function to return pet fullness
	int retfriendliness() const;	// function to return pet friendliness
	string rettype() const;	// function to return type of pet
};        

void pet::create_pet() {
	cout << "\n Enter The Pet No. : ";
	cin >> pet_id;
	cout << "\n Enter The Name of The Pet : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n Enter Type of The Pet (Fire/Water/Grass) : ";
	cin >> type;
	fullness = 50;
	friendliness = 0;
	cout << "\n\n Pet Created..";
}

void pet::show_pet() const {
	cout << "\n Pet No. : " << pet_id;
	cout << "\n Pet Name : " << name;
	cout << "\n Type of Pet : " << type;
	cout << "\n Fullness: " << fullness;
	cout << "\n Friendliness: " << friendliness;
}


void pet::modify() {
	cout << "\n Pet No. : " << pet_id;
	cout << "\n Modify Pet Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n Modify Type of Pet : ";
	cin >> type;
}

// x is the number of the treat
void pet::feed(int x) {
	fullness += x * 5;
	if (fullness > 100) {
		fullness = 100;
		cout << "\n " << name << " is very full!";
	}
}
	
void pet::play() {
	friendliness += 5;
	if (fullness > 100) {
		friendliness = 100;
		cout << "\n " << name << " really likes you!";
	}
}
	
void pet::report() const {
	cout << pet_id << setw(12) << " " << name << setw(10) << 
	" " << type << setw(10) << " " << fullness << setw(12) << " " << friendliness << endl;
}
	
int pet::retpet_id() const {
	return pet_id;
}

int pet::retfullness() const {
	return fullness;
}

int pet::retfriendliness() const {
	return friendliness;
}

string pet::rettype() const {
	return type;
}

// INTRODUCTION FUNCTION

void intro() {
	cout << "\n\t  Mini Pet Game";
	cout << "\n\n Developed by : Daisy (Yu) Du";
	cout << "\n";
	cin.get();
}

// function declaration

void write_pet();	// function to write record in binary file
void display_pet(int);	// function to display pet details given by user
void modify_pet(int);	// function to modify record of file
void delete_pet(int);	// function to delete record of file
void display_all();		// function to display all pet details
void feed_pet(int); // function to feed given pet
void play_with_pet(int); // function to play with given pet
void intro();	// function to show introductory message

// function to write pet in file

void write_pet() {
	pet p;
	ofstream outFile;
	outFile.open("pet.dat",ios::binary | ios::app);
	p.create_pet();
	outFile.write(reinterpret_cast<char *> (&p), sizeof(pet));
	outFile.close();
}

// function to read specific pet from file

void display_pet(int n) {
	pet p;
	bool exists = false;
	ifstream inFile;
	inFile.open("pet.dat",ios::binary);
	if (!inFile) {
		cout << "Pet file could not be open !! Press any Key...";
		return;
	}
	cout << "\n Pet Details \n";
    while (inFile.read(reinterpret_cast<char *> (&p), sizeof(pet))) {
		if (p.retpet_id() == n) {
			p.show_pet();
			exists = true;
		}
	}
    inFile.close();
	if (exists == false) 
		cout << "\n\n Pet number does not exist!";
}

// function to modify pet of file

void modify_pet(int n) {
	bool found = false;
	pet p;
	fstream File;
    File.open("pet.dat", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "Pet file could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char *> (&p), sizeof(pet));
		if (p.retpet_id() == n) {
			p.show_pet();
			cout << "\n\n Enter The New Details of pet" << endl;
			p.modify();
			int pos = (-1) * static_cast<int>(sizeof(pet));
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&p), sizeof(pet));
		    cout<<"\n\n Pet Updated";
		    found = true;
		  }
	}
	File.close();
	if (found == false)
		cout << "\n\n Pet Not Found ";
}

// function to display all pets

void display_all() {
	pet p;
	ifstream inFile;
	inFile.open("pet.dat",ios::binary);
	if (!inFile) {
		cout << "Pet file could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n Pet List\n\n";
	cout << "============================================================================\n";
	cout << "Pet No.      NAME         Type        Fullness      Friendliness    \n";
	cout << "============================================================================\n";
	while (inFile.read(reinterpret_cast<char *> (&p), sizeof(pet))) {
		p.report();
	}
	inFile.close();
}

// function to feed pet

void feed_pet(int n) {
	int treat;
	bool found = false;
	pet p;
	fstream File;
    File.open("pet.dat", ios::binary|ios::in|ios::out);

	if (!File) {
		cout << "Pet file could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char *> (&p), sizeof(pet));
		if (p.retpet_id() == n) {
			p.show_pet();
			
			cout << "\n\n To Feed the Pet";
			cout << "\n\n Enter The amount of treat: ";
			cin >> treat;
			p.feed(treat);

			int pos = (-1) * static_cast<int>(sizeof(p));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(pet));
			cout << "\n\n Pet is fed ";
			found = true;
	       }
         }
    File.close();
	if (found == false)
		cout<<"\n\n Pet Record Not Found";
}

// function to play with pet

void play_with_pet(int n) {

	bool found = false;
	pet p;
	fstream File;
    File.open("pet.dat", ios::binary|ios::in|ios::out);

	if (!File) {
		cout << "Pet file could not be open !! Press any Key...";
		return;
	}

	while (!File.eof() && found == false) {
		File.read(reinterpret_cast<char *> (&p), sizeof(pet));

		if (p.retpet_id() == n) {
			p.show_pet();
			p.play();
			int pos = (-1) * static_cast<int>(sizeof(p));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&p), sizeof(pet));
			cout << "\n\n Pet is entertained ";
			found = true;
	       }
         }
    File.close();
	if (found == false)
		cout<<"\n\n Pet Record Not Found";
}

// THE MAIN FUNCTION OF PROGRAM

int main() {

	char selection;
	int pet_id;

	intro();

	do {
		system("clear");

		cout << "\n\n  Main Menu";
		cout << "\n\n  01. Adopt New Pet";
		cout << "\n\n  02. Feed Pet";
		cout << "\n\n  03. Play with Pet";
		cout << "\n\n  04. Pet Status";
		cout << "\n\n  05. All Pet List";
		cout << "\n\n  06. Edit a Pet Info";
		cout << "\n\n  07. Exit Game";
		cout << "\n\n  Select Your Option (1-7) ";

		cin >> selection;
		system("clear");

		switch(selection) {
		case '1':
			write_pet();
			break;
		case '2':
			cout << "\n\n Enter The Pet No. : "; cin >> pet_id;
			feed_pet(pet_id);
			break;
		case '3':
			cout << "\n\n Enter The Pet No. : "; cin >> pet_id;
			play_with_pet(pet_id);
			break;
		case '4': 
			cout << "\n\n Enter The Pet No. : "; cin >> pet_id;
			display_pet(pet_id);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n Enter The Pet No. : "; cin >> pet_id;
			modify_pet(pet_id);
			break;
		case '7':
			cout << "\n\n Thanks for visiting your pets! We will see you next time!\n\n";
			break;
		    default :cout << "\a";
		}
		cin.ignore();
		cin.get();
    } while (selection != '7');
	return 0;
}

// END OF PROJECT