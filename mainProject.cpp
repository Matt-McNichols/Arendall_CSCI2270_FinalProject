#include <iostream>
#include "MovieTree.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <json/json.h>
#include <vector>

using namespace std;

void displayMainMenu();
void displayPathMenu();
void displayFinalMenu();
int getFileSize(char * fileName);
void easyTree(MovieTree * mt);
void mediumTree(MovieTree * mt);
void hardTree(MovieTree * mt);
bool checkSameVal(int array[], int val, int arrLength);

int main(int argc, char*argv[])
{
    int input;
	int score = 0;
    // Create a new communication network
    //MovieTree *mt = new MovieTree();
	MovieNode * Matched = new MovieNode;
	MovieNode * current = new MovieNode;
    // Flag used for exiting menu
    bool quit = false;
    bool tryAgain = false;
	bool flagWon = false;
    // Used for input
    //int in_key;
	while(!tryAgain || !quit)
	{
		MovieTree *mt = new MovieTree();
		tryAgain = false;
		quit = false;
		displayMainMenu();
		cin >> input;
		//clear out cin
		cin.clear();
		cin.ignore(10000,'\n');


		while(1)
		{
			// Easy
			if(input == 1){
				easyTree(mt);
				current = mt->chooseCurrent();
				Matched = mt->chooseMatch();
				cout<< "Your key is: "<< Matched->key<<endl;
				cout<< "You are currently at: "<< current->key<<endl;
				break;
			}
			// Medium
			else if(input == 2){
				mediumTree(mt);
				current = mt->chooseCurrent();
				Matched = mt->chooseMatch();
				cout<< "Your key is: "<< Matched->key<<endl;
				cout<< "You are currently at: "<< current->key<<endl;
				break;
			}
			// Hard
			else if(input == 3){
				hardTree(mt);
				current = mt->chooseCurrent();
				Matched = mt->chooseMatch();
				cout<< "Your key is: "<< Matched->key<<endl;
				cout<< "You are currently at: "<< current->key<<endl;
				break;
			}
			// Quit
			else if(input == 4){
				cout<<"Goodbye!"<<endl;
				quit = true;
				tryAgain = true;
				return 0;
			}
			// Invalid Input
			else{
				cout << "Invalid Input" << endl;
				cin.clear();
				cin.ignore(10000,'\n');
			}
		}
		while(tryAgain != true)
		{
			displayPathMenu();
			cin >> input;

			//clear out cin
			cin.clear();
			cin.ignore(10000,'\n');

			switch (input)
			{
				// Move Left
				case 1:
					current = current->leftChild;
					cout<<current->key<<endl;
					score++;
					if(!mt->checkNIL(current) && current->key == Matched->key){
						cout<<"You found: "<<current->key<<endl;
						cout<<"YOU WIN!!!"<<endl;
						flagWon = true;
						tryAgain = true;
					}
					else if(mt->checkNIL(current)){
						cout<<"Dead END"<<endl;
						current = mt->chooseCurrent();
						cout<<"Restart at root: "<<current->key<<endl;
					}
					else{
						cout<<"You found: "<<current->key<<endl;
					}
					break;
				// Move Right
				case 2:
					current = current->rightChild;
					cout<<current->key<<endl;
					score++;
					if(!mt->checkNIL(current) && current->key == Matched->key){
						cout<<"You found: "<<current->key<<endl;
						cout<<"YOU WIN!!!"<<endl;
						tryAgain = true;
					}
					else if(mt->checkNIL(current)){
						cout<<"Dead END"<<endl;
						current = mt->chooseCurrent();
						cout<<"Restart at root: "<<current->key<<endl;
					}
					else{
						cout<<"You found: "<<current->key<<endl;
					}
					break;
				// Move Back
				case 3:
					current = current->parent;
					cout<<current->key<<endl;
					score++;
					if(!mt->checkNIL(current) && current->key == Matched->key){
						cout<<"You found: "<<current->key<<endl;
						cout<<"YOU WIN!!!"<<endl;
						tryAgain = true;
					}
					else if(mt->checkNIL(current)){
						cout<<"Dead END"<<endl;
						current = mt->chooseCurrent();
						cout<<"Restart at root: "<<current->key<<endl;
					}
					else{
						cout<<"You found: "<<current->key<<endl;
					}
					break;
				// Give Up
				case 4:
					cout << "You Gave Up!" << endl;
					tryAgain = true;
					break;
				// This is a hidden test to check if the tree is valid. For testing purposes. 
				case 5: 
					if (mt->isValid())
						cout << "Tree is valid\n";
					else
						cout << "Tree is not valid\n";
					break;
				// invalid input
				default:
					cout << "Invalid Input" << endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
			}
		}
		tryAgain = false;
		while(tryAgain != true)
		{
			displayFinalMenu();
			cin >> input;

			//clear out cin
			cin.clear();
			cin.ignore(10000,'\n');

			switch (input)
			{
				// Calculate Score
				case 1:
					mt->calculateScore(score, flagWon);
					break;
				// Print Tree Maze
				case 2:
					mt->printMovieInventory();
					break;
				// Try Again
				case 3:
					// Free memory and return
					delete mt;
					flagWon = false;
					tryAgain = true;
					//cout<<quit<<endl;
					break;
				// Quit
				case 4:
					cout << "Goodbye!" << endl;
					delete mt;
					flagWon = false;
					quit = true;
					tryAgain = true;
					break;
				// This is a hidden test to check if the tree is valid. For testing purposes. 
				case 5: 
					if (mt->isValid())
						cout << "Tree is valid\n";
					else
						cout << "Tree is not valid\n";
					break;
				// invalid input
				default:
					cout << "Invalid Input" << endl;
					cin.clear();
					cin.ignore(10000,'\n');
					break;
			}
		}
	}
	
	
    // Free memory and return
    //delete mt;

    return 0;
}

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayPathMenu()
{
    cout << "======Choose Direction=====" << endl;
    cout << "1. Left" << endl;
    cout << "2. Right" << endl;
    cout << "3. Back" << endl;
    cout << "4. Give Up" << endl;
    return;
}

void displayMainMenu()
{
    cout << "======Maze Wizard=====" << endl;
    cout << "Choose a Difficulty" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Quit" << endl;
    return;
}

void displayFinalMenu()
{
	cout << "======Maze Wizard Results=====" << endl;
	cout << "1. Show Score" << endl;
    cout << "2. Print Tree Maze" << endl;
    cout << "3. Try Again" << endl;
    cout << "4. Quit" << endl;
    return;
}

/* reads file into tree */
void easyTree(MovieTree * mt)
{
	int arrayCheck[5];
	for(int i=0; i<5; i++){
		arrayCheck[i] = 0;
	}
	for(int i=0; i < 5; i++)
	{
		int val = rand()%100 + 1; // random # 1-100;
		if(!checkSameVal(arrayCheck, val, 5)){
			//cout<<val<<endl;
			arrayCheck[i] = val;
			mt->addMovieNode(val);
		}
		else
			i--;
	}
}
void mediumTree(MovieTree * mt)
{
	int arrayCheck[10];
	for(int i=0; i<10; i++){
		arrayCheck[i] = 0;
	}
	for(int i=0; i < 10; i++)
	{
		int val = rand()%100 + 1; // random # 1-100;
		if(!checkSameVal(arrayCheck, val, 10)){
			//cout<<val<<endl;
			mt->addMovieNode(val);
			arrayCheck[i] = val;
		}
		else
			i--;
	}
}
void hardTree(MovieTree * mt)
{
	int arrayCheck[20];
	for(int i=0; i<20; i++){
		arrayCheck[i] = 0;
	}
	for(int i=0; i < 20; i++)
	{
		int val = rand()%100 + 1; // random # 1-100;
		if(!checkSameVal(arrayCheck, val, 20)){
			//cout<<val<<endl;
			mt->addMovieNode(val);
			arrayCheck[i] = val;
		}
		else
			i--;
	}
}

bool checkSameVal(int array[], int val, int arrLength){
	for(int i=0; i<arrLength; i++)
	{
		if(array[i] == val)
			return true;
	}
	return false;
}

