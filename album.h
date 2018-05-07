/* Author: Josh Herman
 * Filename: album.h
 * This file has the function declarations for the album class; album.cpp extends on this
 */
#ifndef ALBUM_H
#define ALBUM_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctype.h>
#include <fstream>
#include <ostream>
#include <iomanip>
#include "date.h"

const int MAX_NAME = 256;
const int MAX_TRACKS = 40;
//these are 512 because that is double what the artistName and albumTitle would be
const int MAX_NORMALIZED_NAME = 512;
const int MAX_UN_NORM_NAME = 512;

class Album{
private:
    int numTracks;
    Date releaseDate;
    char albumTitle[MAX_NAME];
    char artistName[MAX_NAME];
    char labelName[MAX_NAME];
    //R = rock; P = Pop; C = country; H = hip-hop; J = Jazz; S = classical; F = folk; G = reggae; B = R&B; L = Blues; E = Electronic; N = no genre
    char genre;
    char trackList[MAX_TRACKS][MAX_NAME];
    char normalizedName[MAX_NORMALIZED_NAME];
    void normalize_CString();
public:
    //ctors:
    Album();
    //set functions:
    void set_releaseDate(int year, int month, int day){releaseDate.setDate(year, month, day);}
    void set_albumTitle(const char title[MAX_NAME]);
    void set_artistName(const char name[MAX_NAME]);
    void set_labelName(const char lName[MAX_NAME]);
    void setGenre(char g);
    void addTrack(const char trackName[MAX_NAME]);
    void setNormName(){normalize_CString();}
    void setDateUtil(int y, int m, int d){releaseDate.setDate(y, m, d);}
    void setInputDate(const char inputDate[MAX_NAME]);
    //clear the tracks in the 2D array
    void clearTracks();
    //get functions:
    int get_numTracks(){return numTracks;}
    Date get_releaseDate(){return releaseDate;}
    string get_albumTitle() const;
    string get_artistname() const;
    string get_labelName() const;
    string get_track(int index);
	string get_normName();
    char getGenre(){return genre;}
	
	//read/write functions
	void readAlbum(ifstream& inputBin);
	void writeAlbum(ofstream& outTxt);
    void writeBinAlbum(ofstream& outBin);
    
	//overloaded functions
	Album operator=(const Album& copyA);
	
	//friend classes
    friend class Date;
    template<class T> friend class Position;
    template<class T> friend class BinarySearchTree;
    template<class T> friend class Node;
	
	//friend functions
	friend ostream& operator<<(ostream& outStream, const Album& a);
    friend bool operator< (const Album& compare1, const Album& compare2);
    friend bool operator==(const Album& compare1, const Album& compare2);
};
#endif