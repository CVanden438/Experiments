// OOP in C++ course project
// Program to store experiments from keyboard or file and to print 
// them to console or file, allowing some manipulation to be done
// Author: Chris Vanden


// Includes
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<stdlib.h>
#include "Experiment.h"
using namespace std;


// -----Experiment containers and iterators-----
vector<base*> base_vector;
map<const string, base*> mymap;
map<const string, base*>::iterator it;
map<const string, base*>::iterator saveit;
// Pointer to store saved experiment
base* save = new experiment();

// -----Function to print list of stored experiments-----
void listexperiments(){
	cout << "List of stored experiments:" << endl;
	// Iterates through map of experiments
	for (it = mymap.begin(); it != mymap.end(); ++it)
	{
		// Prints out the name of each experiment
		cout << "Experiment name: " << it->first << endl;
	}

}

int main(){
	// -----Variables used in main program loop-----
	// String to hold name of experiment
	string name;
	// Checks used throughout loop
	// Flag to exit loop if user exits program
	int flag(0);
	// Integer to keep track of latest element of base vector
	int z(0);
	// Check to only allow user into load option if an experiment is saved
	int savecheck(0);
	// -----Main loop of program-----
	while (flag != 1){
		// Giving the user their options
		cout << "----------Options----------" << endl;
		cout << "1. Add experiment data from keyboard" << endl <<
			"2. Add experiment data from file" << endl <<
			"3. Add additional data to experiment" << endl <<
			"4. Save an experiment" << endl <<
			"5. Load an experiment" << endl <<
			"6. Sort data in experiment" << endl <<
			"7. Delete an experiment" << endl <<
			"8. Print experiment to console" << endl <<
			"9. Output experiment to file" << endl <<
			"10. Exit program" << endl <<
			"---------------------------" << endl;
		int choice;
		cin >> choice;
		// Making sure user inputs one of the available options
		while (cin.fail() || choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice !=7 && choice != 8 && choice != 9 && choice != 10){
			cout << "Please enter a valid choice" << endl;
			// Used to get rid of any bad inputs stored in cin
			cin.clear();
			cin.ignore(80, '\n');
			cin >> choice;
		}
		if (choice == 1){
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Enter name of experiment: ";
			cin >> name;
			// Searches through experiments to see if experiment already exists with the inputed name
			// This is to stop the previous key linked to that experiment from being overriden
			it = mymap.find(name);
			// If iterator reaches the end then it means no experiment exists with that name
			if (it != mymap.end()){
				cout << "Sorry, there is already an experiment with that name, please choose another" << endl;
			}
			else
			{
				// Adds a new experiment to the vector of base class pointers
				base_vector.push_back(new experiment(name));
				// Pairs the experiment with its given name and stores it in the map container
				mymap[name] = base_vector[z];
				// Increases z by one so next time an experiment is added it knows which element it is added to
				z++;
				// Calls on function to set the data for the experiment
				mymap.find(name)->second->setdatakeyboard();
			}
		}
		else if (choice == 2){
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Enter name of experiment: ";
			cin >> name;
			// Same check as with adding from keyboard
			it = mymap.find(name);
			if (it != mymap.end()){
				cout << "Sorry, there is already an experiment with that name, please choose another" << endl;
			}
			else
			{
				// Adds experiment in same way as from keyboard
				base_vector.push_back(new experiment(name));
				mymap[name] = base_vector[z];
				z++;
				// Exception which will throw if either the file can not be opened or if a line can not be read in
				try{
					mymap.find(name)->second->setdatafile();
				}
				// If either of the above, program deletes the last experiment entry to prevent having an experiment allocated with nothing in
				catch(int errorFlag){
					if (errorFlag == -1){
						// Destroys map entry
						mymap.erase(name);
						z--;
						// Deletes experiment from the base vector
						delete base_vector[z];
					}
				}
			}
		}
		else if (choice == 3){
			cin.clear();
			cin.ignore(80, '\n');
			// Calls function to print experiment list
			listexperiments();
			cout << "Which experiment do you want to add data to?" << endl;
			cin >> name;
			// If experiment exists, calls on funciton to add data to it
			it = mymap.find(name);
			if (it != mymap.end()){
				it->second->adddata();
			}
			else
			{
				cout << "Sorry, experiment " << name <<
					" is not in database" << endl;
			}
		}
		else if (choice == 4){
			cin.clear();
			cin.ignore(80, '\n');
			// Calls function to print expeirment list
			listexperiments();
			cout << "Saving an experiment will over-ride any current save, do you wish to continue? (y/n)" << endl;
			char choice;
			cin >> choice;
			// Checks for valid input
			while (choice != 'y' && choice != 'n'){
				cin.clear();
				cin.ignore(80, '\n');
				cout << "Please enter either (y) or (n)" << endl;
				cin >> choice;
			}
			if (choice == 'y'){
				cout << "Enter name of experiment to save: " << endl;
				cin >> name;
				// Checks experiment is in database
				it = mymap.find(name);
				if (it != mymap.end()){
					cout << "Saving data for:  " << name << endl;
					// Creates copy of chosen experiment to save
					base* savetemp = it->second->clone();
					// Points save iterator to location of saved experiment so program known where to load experiment to
					saveit = mymap.find(name);
					// Moves the copied experiment to the save pointer
					save = move(savetemp);
					// This allows the load option to be used
					savecheck = 1;
				}
				else
				{
					cout << "Sorry, experiment " << name <<
						" is not in database" << endl;
				}
			}
		}
		else if (choice == 5){
			cin.clear();
			cin.ignore(80, '\n');
			// If there is no saved experiment then will go back to main loop
			if (savecheck == 0){
				cout << "There is currently no saved experiment" << endl;
			}
			else{
				// Prints out names of saved experiments
				cout << "The current saved experiment is : " << save->getname() <<
					endl << "Do you want to load this save? It will undo any changes made sinse (y/n)" << endl;
				char choice;
				cin >> choice;
				// Checks for valid input
				while (choice != 'y' && choice != 'n'){
					cin.clear();
					cin.ignore(80, '\n');
					cout << "Please enter either (y) or (n)" << endl;
					cin >> choice;
				}
				// Moves the saved experiment to the location it was saved from, this will revert any changed made to that experiment sinse it was saved
				if (choice == 'y'){
					saveit->second = move(save);
					// Once experiment has been loaded, stops user from being able to load again without a new save
					savecheck = 0;
				}

			}
		}
		else if (choice == 6){
			cin.clear();
			cin.ignore(80, '\n');
			// Prints out names of saved experiments
			listexperiments();
			cout << "Which experiment do you want to sort?" << endl;
			cin >> name;
			// Calls function to order data based on measurement number in ascending order
			it = mymap.find(name);
			if (it != mymap.end()){
				it->second->sortdata();
			}
			else
			{
				cout << "Sorry, experiment " << name <<
					" is not in database" << endl;
			}
		}
		else if (choice == 7){
			cin.clear();
			cin.ignore(80, '\n');
			// Prints out names of saved experiments
			listexperiments();
			cout << "Which experiment do you want to delete?" << endl;
			cin >> name;
			it = mymap.find(name);
			// Destroys the map containing the expeirment and deletes the corresponding measurement pointer
			if (it != mymap.end()){
				cout << "Deleting experiment: " << name << endl;
				delete it->second;
				mymap.erase(it);
			}
			else
			{
				cout << "Sorry, experiment " << name <<
					" is not in database" << endl;
			}
		}
		else if (choice == 8){
			cin.clear();
			cin.ignore(80, '\n');
			// Prints out names of saved experiments
			listexperiments();
			cout << "Enter name of experiment to print: " << endl;
			cin >> name;
			it = mymap.find(name);
			if (it != mymap.end()){
				it->second->printdata();
			}
			else
			{
				cout << "Sorry, experiment " << name <<
					" is not in database" << endl;
			}
		}
		else if (choice == 9){
			cin.clear();
			cin.ignore(80, '\n');
			// Outputs the data for an experiment to file
			listexperiments();
			cout << "Enter name of experiment to output to file: " << endl;
			cin >> name;
			it = mymap.find(name);
			if (it != mymap.end()){
				cout << "Outputting data for: " << name << " to file" << endl;
				it->second->printdatafile();
			}
			else
			{
				cout << "Sorry, experiment " << name <<
					" is not in database" << endl;
			}
		}
		else if (choice == 10){
			// Sets flag to 1 to exit main loop and end program
			flag = 1;
		}
		cout << '\n';
	}
	// Cleans up by deleting the memory used for the experiments
	for (auto base_vectorit = base_vector.begin(); base_vectorit<base_vector.end();
		++base_vectorit) delete *base_vectorit;
	base_vector.clear();
	return 0;
}