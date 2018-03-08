#include <iostream>
#include <fstream>
#include <string>
void readFile();
using namespace std;

int main() {
	readFile();
	return 0;
}

void readFile() {

	const int NUM = 100;
	int itemNumber[100];
	string productName[100];
	double cost[100];
	int qty[100];

	ifstream inFile;
	inFile.open("ProductData.csv");

	string itemNum;
	getline(inFile, itemNum, ',');
	string pName;
	getline(inFile, pName, ',');
	string itemCost;
	getline(inFile, itemCost, ',');
	string quantity;
	inFile >> quantity;

	for (int i = 0; i < NUM; i++) {
		getline(inFile, itemNumber[i], ',');
		getline(inFile, productName[i], ',');
		getline(inFile, cost[i], ',');
		inFile >> qty[i];

	}



}