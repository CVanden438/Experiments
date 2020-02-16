#include<iostream>
#include<string>
#include<fstream>
#include<numeric>
#include<list>
#include<iomanip>
#include "Experiment.h"
using namespace std;

// -----Function to set experiment data from kayboard-----
void experiment::setdatakeyboard()
{
	// Variables the inputs are asigned to
	double datestamp;
	double data, rerror, serror;
	vector<double> temp;
	// Flag to allow loop to keep looping till user exits
	char setflag = 0;
	cout << "Setting data for experiment: " << name << endl;
	while (setflag != 'n')
	{
		cout << "Enter the datestamp of the measurement in the form day/month\n";
		cin >> datestamp;
		// Checks for a valid input
		while (cin.fail() || datestamp < 0 || datestamp > 3112){
			cout << "Please enter a valid date\n";
			// Clears cin of any bad input
			cin.clear();
			cin.ignore(80, '\n');
			cin >> datestamp;
		}
		// Adds each part of the measurement to temp vector
		temp.push_back(datestamp);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the measurement\n";
		cin >> data;
		while (cin.fail()){
			cout << "Please enter valid data\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> data;
		}
		temp.push_back(data);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the random error\n";
		cin >> rerror;
		while (cin.fail()){
			cout << "Please enter a valid random error\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> rerror;
		}
		temp.push_back(rerror);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the systematic error (enter 0 if none)\n";
		cin >> serror;
		while (cin.fail()){
			cout << "Please enter a valid systematic error error\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> serror;
		}
		temp.push_back(serror);
		// Adds the temp vector comtaining full measurement to overall vector containing multiple measurements
		mdata.push_back(temp);
		temp.clear();
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Do you want to add another measurement? (y/n)\n";
		cin >> setflag;
		// Asks if user wants to finish inputting or add another experiment
		while (setflag != 'y' && setflag != 'n'){
			cout << "Please enter either (y) or (n)" << endl;
			cin.clear();
			cin.ignore(80, '\n');
			cin >> setflag;
		}
	}
	cin.clear();
	cin.ignore(80, '\n');
}
// -----Function to print the data to console-----
void experiment::printdata()
{
	// Asks the user to set the precision they want the output to be in
	int precision;
	cout << "What precision do you want to output the data to?" << endl;
	cin >> precision;
	// Makes sure user inputs a reasonable precision
	while (cin.fail() || precision > 15){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Please enter a valid precision" << endl;
		cin >> precision;
	}
	// Outputs the data to console
	cout << "Report for experiment : " << name << endl;
	cout << "|Date|-----------|Measurement|\n";
	// Loops through the measurements, outputting each one
	for (int j = 0; j < mdata.size(); j++){
		cout << setprecision(4) << mdata[j][0] << "	         " << setprecision(precision) << mdata[j][1] << "+-" << mdata[j][2] << "+-" << mdata[j][3] << endl;
	};
	// Also outpts the mean and standard error for the experiment
	cout << "The mean value of the measurements is : " << getmean() << endl;
	cout << "The standard error on the mean is : " << geterr() << endl;
	cin.clear();
	cin.ignore(80, '\n');
}
// -----Function to output experiment to file-----
void experiment::setdatafile()
{
	string filename;
	cout << "Input name of file to set data from: ";
	cin >> filename;
	ifstream file(filename);
	// Checks if file can be opened
	if (file.is_open()){
		cout << "File successfully opened" << endl;
		vector<double> tempfile;
		double t;
		// Will only be successful if there are 4 numbers delimited by white space on each line
		while (!file.eof()){
			// Adds each element of each line to temp vector
			for (int i = 0; i < 4; i++){
				file >> t;
				tempfile.push_back(t);
			}
			// Pushes back each line to the vector containing multiple measurements
			mdata.push_back(tempfile);
			tempfile.clear();
			// If there isnt 4 numbers on each line or something which isnt a number then gives and error and throws exception
			if (file.fail()){
				cerr << "Error: One of the lines in the file could not be read in, please try again" << endl;
				file.clear();
				file.ignore(1000, '\n');
				const int lineflag(-1);
				throw lineflag;
			}
		}
		}
	// Gets here if file could not be opened and throws an error
	else{
		cout << "Could not open file" << endl;
		const int textflag(-1);
		throw textflag;
	}
	cin.clear();
	cin.ignore(80, '\n');
}
// -----Function to output the data to a file
void experiment::printdatafile()
{
	// Sets name of output file
	ofstream myfile("output.txt");
	int precision;
	// Asks the user what precision to output the data to
	cout << "What precision do you want to output the data to?" << endl;
	cin >> precision;
	// Makes sure user inputs a reasonable precision
	while (cin.fail() || precision > 15){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Please enter a valid precision" << endl;
		cin >> precision;
	}
	// Once file is open, writes a report to it
	if (myfile.is_open())
	{
		myfile << "|Date|-----------|Measurement|\n";
		for (int j = 0; j < mdata.size(); j++){
			myfile << setprecision(4) << mdata[j][0] << "	         " << setprecision(precision) << mdata[j][1] << "+-" << mdata[j][2] << "+-" << mdata[j][3] << endl;
		};
		// Also writes the mean and standard error to the file
		myfile << "The mean value of the measurements is : " << getmean() << endl;
		myfile << "The standard error on the mean is : " << geterr() << endl;
		myfile.close();
	}
	cin.clear();
	cin.ignore(80, '\n');
}
// -----Function to get name of experiment-----
string experiment::getname()
{
	return name;
}
// -----Function to add data to an existing experiment
void experiment::adddata()
{
	// Variables the inputs are asigned to
	double datestamp;
	double data, rerror, serror;
	vector<double> temp;
	// Flag to allow loop to keep looping till user exits
	char addflag = 0;
	cout << "Adding data to experiment: " << name << endl;
	while (addflag != 'n')
	{
		cout << "Enter the datestamp of the measurement in the form day/month\n";
		cin >> datestamp;
		// Checks for a valid input
		while (cin.fail() || datestamp < 0 || datestamp > 3112){
			cout << "Please enter a valid date\n";
			// Clears cin of any bad input
			cin.clear();
			cin.ignore(80, '\n');
			cin >> datestamp;
		}
		// Adds each part of the measurement to temp vector
		temp.push_back(datestamp);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the measurement\n";
		cin >> data;
		while (cin.fail()){
			cout << "Please enter valid data\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> data;
		}
		temp.push_back(data);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the random error\n";
		cin >> rerror;
		while (cin.fail()){
			cout << "Please enter a valid random error\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> rerror;
		}
		temp.push_back(rerror);
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Enter the systematic error (enter 0 if none)\n";
		cin >> serror;
		while (cin.fail()){
			cout << "Please enter a valid systematic error error\n";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> serror;
		}
		temp.push_back(serror);
		// Adds the temp vector comtaining full measurement to overall vector containing multiple measurements
		mdata.push_back(temp);
		temp.clear();
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Do you want to add another measurement? (y/n)\n";
		cin >> addflag;
		// Asks if user wants to finish inputting or add another experiment
		while (addflag != 'y' && addflag != 'n'){
			cout << "Please enter either (y) or (n)" << endl;
			cin.clear();
			cin.ignore(80, '\n');
			cin >> addflag;
		}
	}
	cin.clear();
	cin.ignore(80, '\n');
}
// -----Function to calculate the mean of the measurements for an experiment-----
double experiment::getmean()
{
	double sum(0.);
	double mean;
	int n = mdata.size();
	// Loops over the measurements and calculates a sum
	for (int i = 0; i < n; i++){
		sum = sum + mdata[i][1];
	}
	// Divides by total number to get mean
	mean = sum / n;
	return mean;
}
double experiment::geterr()
{
	double mean = getmean();
	double sum = 0.;
	int size = mdata.size();
	// If experiment only contains 1 measurement then combines both errors in quadrature
	if (size == 1){
		double se = pow(mdata[0][2] * mdata[0][2] + mdata[0][3] * mdata[0][3], 0.5);
		return se;
	}
	else{
		// Calculates the sum of each measurment minus the mean squared
		for (int i = 0; i < size; i++){
			sum += pow((mdata[i][1] - mean), 2);
		}
	// Calculations to find the standard error on the mean
	double var = sum / (size - 1);
	double sd = pow(var, 0.5);
	double se = sd / pow(size, 0.5);
	return se;
	}
}
// -----Function to sort data for an experiment-----
void experiment::sortdata()
{
	// Looks at the second element of each element of the data to compare them
	sort(mdata.begin(), mdata.end(), [](const vector<double>& a, const vector<double>& b) {
		// This will sort them in ascending order
		return a[1] < b[1];
	});
}