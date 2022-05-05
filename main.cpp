#include<iostream>
#include"Generator.h"

using namespace std;

int main()
{
	string file, field, sortby;
	//take input file name; if file does not exist the constructor would print out a message and the program finished.
	cout << "Graph Coronavirus Data" << endl;
	cout << "Enter the file with data "<< endl;
	getline(cin, file);
	Generator g = Generator(file);
	
	//take user input on a specific field for graphing; if any user input is wrong the program would inidcate the error and return to here (menu)
	menu:
		cout << "Which field do you want to graph?"<< endl;
		cout << "\"nc\" = new confirmed" << endl;
		cout << "\"nd\" = new deaths" << endl;
		cout << "\"nr\" = new recovered" << endl;
		cout << "\"tc\" = total confirmed" << endl;
		cout << "\"td\" = total deaths" << endl;
		cout << "\"tr\" = total recovered" << endl;
		getline(cin, field);
		
		cout << "In ascending order or descending order?" << endl;
		cout << "\"a\" = ascending" << endl;
		cout << "\"d\" = descending" << endl;
		getline(cin, sortby);
	
	if((field!="nc"&&field!="nd"&&field!="nr"&&field!="tc"&&field!="td"&&field!="tr")||(sortby!="a"&&sortby!="d"))
	{
		cout << "Input Error" << endl;
		goto menu;
	}
	else
	{
		g.graph(field, sortby);
	}

	return 0;
}