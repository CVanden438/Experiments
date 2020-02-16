// Makes sure header will only be defined once
#ifndef MY_CLASS_H
#define MY_CLASS_H
#include<vector>
#include<string>
#include<list>
#include<algorithm>
using namespace std;

// -----Abstract base class used as interface-----
class base
{
public:
	// Virtual functions which will be overriden in experiment class
	virtual ~base(){}
	virtual base* clone() const = 0;
	virtual void setdatakeyboard() = 0;
	virtual void printdata() = 0;
	virtual void setdatafile() = 0;
	virtual void printdatafile() = 0;
	virtual string getname() = 0;
	virtual void adddata() = 0;
	virtual double getmean() = 0;
	virtual double geterr() = 0;
	virtual void sortdata() = 0;
};

// -----Experiment class to store and manipulate the experiments-----
class experiment : public base
{
protected:
	// -----Container to store experiment data-----
	vector < vector<double> > mdata;
	// String to store name of experiment
	string name;
public:
	// Default constructor
	experiment(){ name = "null"; }
	// Parametised constructor
	experiment(string name1) : name(name1) {}
	// Clone function to use as a copy constructor
	virtual experiment *clone() const { return new experiment(*this); }
	// Prototypes of member functions
	void setdatakeyboard();
	void printdata();
	void setdatafile();
	void printdatafile();
	string getname();
	void adddata();
	double getmean();
	double geterr();
	void sortdata();
	~experiment(){};
};
#endif
