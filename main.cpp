/* Author: Josh Herman(for all files)
 * This application models a database of musical albums like Spotify or iTunes
 * Date Started: 28.11.17
 * Date Due: 7.12.17
 */
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ostream>
#include <iomanip>
#include "album.h"
#include "binarysearch.h"
#include "date.h"
#include "node.h"
#include "position.h"

using namespace std;

const int MAX_STR_LENGTH = 256;

int checkFile(ifstream &input);
int readBin(BinarySearchTree<Album>& tree, ifstream& input);
void printMenu();

int main(int argc, char **argv){
    ifstream input;
	ofstream txtOut;
	ofstream binOut;
    char fileName[MAX_STR_LENGTH] = {"albums.bin"};
    BinarySearchTree<Album> dataBaseTree;
    int albumCount = 0;
	char userInput;
    
    input.open(fileName, ifstream::binary);
    
    int checkBinFile = checkFile(input);
    if(checkBinFile == -1){ //if file does not exist
        cout<<"'"<<fileName<<"'"<<" does not exist\n";
        input.close();
        return(0);
    } else if(checkBinFile == 0){ //file exists and has data in it
        albumCount = readBin(dataBaseTree, input);
		input.close();
    } 
	cout<<"Welcome to PSCC music database! Please select an option:\n";
	printMenu();
	userInput = getc(stdin);
	while(getc(stdin) != '\n');
	while(userInput != '5'){
		switch (userInput){
			case '1':
				findAlbum(dataBaseTree);
				break;
			case '2':
                deleteAlbum(dataBaseTree);
				break;
			case '3':
                addAlbum(dataBaseTree);
				break;
			case '4':
                txtOut.open("albums.log");
                dataBaseTree.preOrderTxtFile(txtOut, dataBaseTree.root());
                txtOut.close();
				break;
			default:
				cout<<"Invalid selection: "<<userInput<<endl;
		}
        cout<<"Select an option: \n";
		printMenu();
		userInput = getc(stdin);
		while(getc(stdin) != '\n');
	}
    
    binOut.open(fileName, ofstream::binary);
    dataBaseTree.preOrderBinFile(binOut, dataBaseTree.root());
    binOut.close();
    cout<<"Thank you for using PSCC Music Library\n";
    return (0);
    
	
    //THIS IS MY MAKING A BIN FILE NOT USED IN ACTUAL LAB
	/*string tempMain;
	string tempSub;
	int positionCheck = 0;
    int day = 0;
    int month = 0; 
    int year = 0;
    char tempGenre = '\0';
	
    char junk;
    
	Album temp;
	
    
    
	ifstream inputTxt;
	ofstream outBin;
	inputTxt.open("3Songs.txt");
	outBin.open("3Songs.bin", ofstream::binary);
	
	checkFile(inputTxt, "3Songs.txt");
	
    //getline(inputTxt, tempMain);
    inputTxt.get(junk);
    inputTxt.get(junk);
    inputTxt.get(junk);
	while(!inputTxt.eof()){
        getline(inputTxt, tempMain);
		positionCheck = tempMain.find(';');
		tempSub = tempMain.substr(0, positionCheck);
		temp.set_albumTitle(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
        cout<<temp.albumTitle<<" ";
        
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        temp.set_artistName(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
        cout<<temp.artistName<<" ";
        temp.setNormName();
        cout<<temp.normalizedName<<" ";
        
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        temp.set_labelName(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
        cout<<temp.labelName<<" ";
        
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        month = atoi(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
        
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        day = atoi(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
        
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        year = atoi(tempSub.c_str());
        tempMain.erase(0, positionCheck + 1);
    
        temp.setDateUtil(year, month, day);
        cout<<temp.releaseDate.day<<"/"<<temp.releaseDate.month<<"/"<<temp.releaseDate.year<<" ";
    
        positionCheck = tempMain.find(';');
        tempSub = tempMain.substr(0, positionCheck);
        tempGenre = tempSub[0];
        temp.setGenre(tempGenre);
        tempMain.erase(0, positionCheck + 1);
        cout<<temp.genre<<" "<<endl;
        //temp.numTracks = 0;
        
        //cout<<tempMain<<endl;
        while(tempMain != ""){
            positionCheck = tempMain.find(';');
            if(positionCheck != -1 ){
                tempSub = tempMain.substr(0, positionCheck);
                temp.addTrack(tempSub.c_str());
                tempMain.erase(0, positionCheck + 1);
                //cout<<tempMain<<endl;
            }else if(positionCheck == -1){
                temp.addTrack(tempMain.c_str());
                tempMain = "";
                //cout<<tempMain<<"\t got here"<<endl;
            }
            cout<<"\t"<<temp.trackList[temp.numTracks - 1]<<endl;
            
            positionCheck = tempMain.find(';');
        }
		cout<<temp.numTracks<<endl;
        outBin.write((char*)&temp, sizeof(temp));
        temp.clearTracks();
        //getline(inputTxt, tempMain);
        //OutFile.write( (char*)&my_double, sizeof(double));
	}
    
    cout<<"END OF READING IN\n";
	cout<<endl;
	cout<<endl;
	cout<<endl;
    outBin.close();
    ifstream inBin;
    inBin.open("3Songs.bin", ifstream::binary);
    inBin.read((char*)&temp, sizeof(temp));
    while(!inBin.eof()){
        cout<<temp.albumTitle<<" ";cout<<temp.artistName<<" ";cout<<temp.normalizedName<<" ";cout<<temp.labelName<<" ";
        cout<<temp.releaseDate.day<<"/"<<temp.releaseDate.month<<"/"<<temp.releaseDate.year<<" ";
        cout<<temp.genre<<" "<<endl;
        for(int i = 0; i < temp.numTracks; i++){
            cout<<"\t"<<temp.trackList[i]<<endl;
        }
		cout<<temp.numTracks<<endl;
        inBin.read((char*)&temp, sizeof(temp));
    }
	
    inBin.close();
	inputTxt.close();
	return 0;*/
}


/* printMenu: this function prints out the main menu for the user
 * No paramters
 * Returns nothing
 */
void printMenu(){
	cout<<"\t 1. Find an album\n";
	cout<<"\t 2. Delete an album\n";
	cout<<"\t 3. Add an album\n";
	cout<<"\t 4. Print log\n";
	cout<<"\t 5. Exit\n";
	cout<<"Option> ";
}

/*
 * Parameters:
 * 		ifstream &input: input file varible
 * checkFile - checks to see if the file exists and is not empty
 * Returns - -1 if the file does not exist, 1 if the file is empty, and 0 if the file exists and has data in it
 * Pre-condition - the file is opened/closed in calling function
*/

int checkFile(ifstream &input){
	char c;
	
	//if file does not exist
	if(!input.good()){
	//cout<<"Non-existant file: "<<fileName<<endl;
		return (-1);
	} else if(input.good()){ //if file exists
		input.get(c);
		
		if(!input.eof()){ //if file is not empty
			input.putback(c);
			return (0);
		}
		
		else { //if file is empty
			//cout<<"File exists but is empty: "<<fileName<<endl;
			return (1);
		}
	}
	return false;
}

/* readBin: this file reads the binary file for the albums
 * Parameters:
 * 		tree: the tree to insert the albums into
 * 		input: the file stream variable
 * returns: the number of albums in the file(also stored in the tree 'numNodes')
 *      this is mostly used for testing purposes
 * Pre-condition: the tree is initialized
 *      Also: the input file must be opened & closed in calling function
 * Post-condition: the file is read in and the tree has data in it
 */
int readBin(BinarySearchTree<Album>& tree, ifstream& input){
    Album temp;
    int count = 0;
    temp.readAlbum(input);
    while(!input.eof()){ //while not the end of file
        tree.insert(temp);
        count++;
        temp.readAlbum(input);
    }
    return count;
}