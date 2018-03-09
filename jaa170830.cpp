#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


int searchArray(itemData *ptr);

struct itemData {
	string productName;
	string cost;
	string itemNumber;
	string quantity;
};


int main()
{
	//I chose to use seperate arrays (rather than multidimensional arrays)
	//to sort through the variables. Notice how I declared the size of each array by
	//NUM which is a global constant variable I declared because I know that there will
	//always be 100 items that the customer can choose from.
	
	

	
	


	//Because I'm reading from the file I need to use ifStream. 
	//File.open() is the function that opens the file and ProductData.csv
	//is the excel file that the program is reading from
	ifstream file;
	file.open("ProductData.csv");

	itemData *ptr;
	string NUM;
	getline(file, NUM, ',');
	int numProd = stoi(NUM);
	itemData *ptr = new itemData[numProd];

	for (int i = 0; i < numProd; i++) {
		
		getline(file, ptr[i].productName, ',');

		
		getline(file, ptr[i].cost, ',');

		
		getline(file, ptr[i].itemNumber, ',');

		
		getline(file, ptr[i].quantity, ',');

	}



/*
	//When searching through each row in excel you 
	//search through each line and seperate each column
	//by having the program look for a comma aka the end of 
	//an excel cell.
	string nameOfProd;
	getline(file, nameOfProd, ',');

	string costOfProd;
	getline(file, costOfProd, ',');

	string itemNum;
	getline(file, itemNum, ',');

	string qty;
	file >> qty;

	*/
	//this for loop sorts through each file up to 100 or NUM
	for (int x = 0; x < NUM; x++)
	{
		getline(file, itemNumber[x], ',');
		getline(file, productName[x], ',');
		getline(file, cost[x], ',');
		file >> quantity[x];
	}
	//now that we are done storing all the data from the file we can
	//now close it 
	file.close();
	string product[NUM];
	int items[NUM][2];
	int counter = 0;
	//Now its time to loop through and actually search for the numbers that 
	//the customers give us. I used a two dimensional array for this with one
	//array being the rows and the other one being the columns.
	for (int x = 0; x < NUM; x++)
	{
		
		cout << "What product would you like? (Enter 0 when done choosing products)" << endl;
		cin >> product[x];

		if (product[x] == "0")
		{
			break;
		}
		items[x][0] = searchArray(itemNumber, product, productName, cost, x);// incorperating my search function
		if (items[x][0] == -1)//nothing should be in the 0th column
		{
			cout << "That product isn't in the database" << endl;
			x--;
		}
		else
		{
			cout << "How many of the product would you like?  ";
			cin >> items[x][1];
			if (items[x][1] > stoi(quantity[items[x][0]]))
			{
				while (items[x][1] > stoi(quantity[items[x][0]]))//customer enters a number greater than the quantity
				{
					cout << "There are not enough of it in stock." << endl;
					if (items[x][1] == 0)
					{
						cout << "We are out of stock! Sorry:(" << endl;//if the quantity is 0 then the product is out of stock
						break;
					}
					//even if they enter a wrong quantity we still need to ask them again rather than giving up on them;)
						cout << "How many of the product would you like?";
					cin >> items[x][1];
				}
			}
			counter++;
		}
	}
	string customerName;
	string street;
	string location;

	//due to the customers name being more than a first name we ask them to 
	//enter a period so that our getline function knows what to look for
	//in regards to the end of their name. This is also applied for the 
	//address and area they are from.
	cout << "Please enter your name. (Enter a period at the end)" << endl;
	getline(cin, customerName, '.');

	cout << "Please enter your street address. (Enter a period at the end)" << endl;
	getline(cin, street, '.');

	cout << "Please enter your City, State Zip code. (Enter a period at the end)" << endl;
	getline(cin, location, '.');

	cout << endl;

	//now its time to create a text file to store all the data in.
	//Ofstream is used to write to a file and output.open() is a 
	//function to open up the file.
	ofstream output;
	output.open("invoice.txt");
	//Throughout the rest of the output you will notice my use
	//of "output <<" and "cout <<". This is because I want to show 
	//output in both the terminal and the file so it stores the data
	//in two spots to make adding corrections easier rather than having to 
	//open up the text file after every run.
	cout << "Customer Name: " << customerName << endl;

	output << "Customer Name: " << customerName << endl;

	cout << "Customer Address: " << street << location << endl;

	output << "Customer Address: " << street << location << endl;

	cout << endl;

	output << endl;

	cout << itemNum << setw(8) << "" << nameOfProd << setw(8) << "" << qty << setw(4) << "" << 
	costOfProd << setw(5) << "" << "Total" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << endl << endl;

	output << itemNum << setw(8) << "" << nameOfProd << setw(8) << "" << qty << setw(5) << " " <<
	costOfProd << setw(5) << "" << "Total" << endl;
	cout << endl << endl;


	int caseA = 0;
	int caseB = 0;
	cout << fixed << setprecision(2);//we are only using currency so there is no need for more than 2 decimal spots.
	output << fixed << setprecision(2);
	double total = 0;
	//Time to whip out the big guns and print out everything at the end of their shopping.
	//You might be looking at this wondering "why did this idiot have so many cases" well 
	//you can thank my setw skills for that one. In order for it to print out nicely on the 
	//page I needed to have every number accounted for in regards to the quantity that 
	//the customer chooses and the product number... I'm sorry.
	for(int t = 0; t < counter; t++)
	{
		caseA = items[t][0];
		caseB = items[t][1];
		if (t < 10 && caseB <= 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(5)
				<< "" << caseB << left << setw(5) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(5) 
			<< "" << caseB << left << setw(5) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}
		if (t < 10 && caseB > 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(4)
			<< "" << caseB << left << setw(5) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(4)
			<< "" << caseB << left << setw(5) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}
		if (t > 10 && t < 98 && caseB <= 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(2) 
			<< "" << caseB << left << setw(4) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(2) 
			<< "" << caseB << left << setw(4) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}
		if (t > 10 && t < 98 && caseB > 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(3) 
			<< "" << caseB << left << setw(4) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(3) 
			<< "" << caseB << left << setw(4) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}
		if (t > 98 && caseB > 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(2)
				<< "" << caseB << left << setw(2) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(2) 
			<< "" << caseB << left << setw(2) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}
		if (t > 98 && caseB <= 10)
		{
			cout << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(1) 
			<< "" << caseB << left << setw(2) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
			cout << "----------------------------------------------------" << endl << endl;

			output << "Item Number " << t + 1 << left << setw(5) << "" << productName[caseA] << left << setw(1)
				<< "" << caseB << left << setw(2) << "" << cost[caseA] << left << setw(5) << "" << (stod(cost[caseA])*(caseB)) << endl << endl;
		}

		total += (stod(cost[caseA])*(caseB));
	}
	//
	cout << left << setw(47) << "Total: " << total << endl;
	output << left << setw(47) << "Total: " << total << endl;
	output.close();
	system("pause");
	return 0;
}
//This is the first function to help search for the product that the customer is looking for
int searchArray(itemData *ptr)
{
	//this for loop loops through all the numbers in the item number list and sees
	//if the item number that the customer entered was in the database
	for (int i = 0; i < NUM; i++)
	{
		//due to the use of an excel fill I had to convert all the 
		//variables to strings in order for c++ to read them but unfortunatly
		//not all the variables in the database were strings so professor 
		//McMahan told us to use stoi() in order to change the string back to 
		//an integer data type.
		if (stoi(productNum[count]) == stoi(ar[i]))
		{
			cout << prodName[i] << setw(4) << " " << itemCost[i] << endl;
			return i;
		}
	}
	return -1;
}