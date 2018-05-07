/* Author: Josh Herman
 * Filename: album.cpp
 * This file is the function implementations for the album class; part of album.h
 */
#include "album.h"

/* default ctor
 *      sets all cstring to "default"
 *      sets num tracks to 0
 *      sets genre to N
 */
Album::Album(){
    char temp[20] = "Default";
    numTracks = 0;
    genre = 'N';
    strcpy(albumTitle, temp);
    strcpy(artistName, temp);
    strcpy(labelName, temp);
}

/* set_albumTitle: this function sets the album title
 * Parameter: title - the title to copy over
 * returns nothing
 * Post-condition: albumTitle is set
 */
void Album::set_albumTitle(const char title[MAX_NAME]){
    strcpy(albumTitle, title);
}

/* set_astistName: this function sets the artist name
 * Parameter: name - the name to copy over
 * returns nothing
 * Post-condition: artistName is set
 */
void Album::set_artistName(const char name[MAX_NAME]){
    strcpy(artistName, name);
}

/* set_labelName: this function sets the label name
 * Parameter: label - the label to copy over
 * returns nothing
 * Post-condition: labelName is set
 */
void Album::set_labelName(const char lName[MAX_NAME]){
    strcpy(labelName, lName);
}

/* setGenre: this function sets the genre
 * Parameter: g - the genre
 * returns nothing
 * Post-condition: genre is set
 */
void Album::setGenre(char g){
    genre = g;
}

/* addTrack: this function adds a track to the 2D array
 * Parameter: trackName - is the track name to copy over
 * returns nothing
 * Pre-condition: numTrack CANNOT be over 20
 * Post-condition: the trackName is copied over, and numTracks is incremented by one
 */
void Album::addTrack(const char trackName[MAX_NAME]){
    strcpy(trackList[numTracks], trackName);
    numTracks++;
}

/* get_albumTitle: this function returns the albumTitle
 * no parameters
 * returns: the album title in STRING FORMAT
 */
string Album::get_albumTitle() const{
    string r = albumTitle; //return
    return(r);
}

/* get_track: this function returns the tracks in the index of the 2D array
 * Paraemeter: index - the index of the 2D array 
 * returns: the track in STRING FORMAT
 */
string Album::get_track(int index){
    string r = trackList[index]; //return
    return(r);
}

/* get_artistName: this function returns the artistName
 * no parameters
 * returns: the artist name in STRING FORMAT
 */
string Album::get_artistname() const{
    string r = artistName; //return
    return(r);
}

/* get_labelName: this function returns the labelName
 * no parameters
 * returns: the label name in STRING FORMAT
 */
string Album::get_labelName() const{
    string r = labelName; //return
    return(r);
}

string Album::get_normName(){
	string r = normalizedName; //return
	return(r);
}

/* normalize_CString: this function takes the album name & artist name and normlizes them
 *      concatonates the strings and only takes alphanumeric values(all letters are changed to lower case)
 * No Parameters
 * Returns nothing
 * Pre-condition: albumName and artistName have something in them
 * Post-condition: normalizedName is filled
 */
void Album::normalize_CString(){
    char temp_unNorm[MAX_UN_NORM_NAME];
    char tempNorm[MAX_NORMALIZED_NAME];
    char c;
	int i, count = 0;	
    strcat(temp_unNorm, albumTitle);
    strcat(temp_unNorm, artistName);
    
    //gets the alphanum characters and puts it in tempNorm
    for(i = 0; temp_unNorm[i] != '\0'; i++){
        if(isalnum(temp_unNorm[i])){
            tempNorm[count] = temp_unNorm[i];
			count++;
        }
    }
	
	//set NULL character
	tempNorm[count] = '\0';
    
    //makes all letters lowercase
    for(int k = 0; k < strlen(tempNorm); k++){
		if(!isdigit(tempNorm[k])){
			c = tolower(tempNorm[k]);
			tempNorm[k] = c;
		}
    }
    strcpy(normalizedName, tempNorm);
}

/* clearTracks: this function clears the trackList array
 *      it goes through each of the indexes, sets the cstring to '\0' and decrements the numTracks counter
 * Returns nothing
 * Post-condition: trackList has been cleared
 */
void Album::clearTracks(){
    char clearS[1] = {'\0'};
    while(numTracks != 0){
        strcpy(trackList[numTracks], clearS);
        numTracks--;
    }
    strcpy(trackList[numTracks], clearS);
}

/* overloaded<: this function compares the normalized names in each album
 * Parameters:
 *      compare: the album to compare 'this' to
 * returns true if first is less than second, false otherwise
 * Pre-condition: normalized name must be set for BOTH albums
 */
bool operator< (const Album& compare1, const Album& compare2){
	if(strcmp(compare1.normalizedName, compare2.normalizedName) < 0){
		return true;
	} else {
		return false;
	}
}

/* overloaded==: this functions compares the two normalized names of the albums provided
 * Parameter:
 *      compare: the album to compare 'this' to
 * returns true if they are absoluetely equal, false otherwise
 * Pre-condition: normalized name must be set for BOTH albums
 */
bool operator==(const Album& compare1, const Album& compare2){
    if(strcmp(compare1.normalizedName, compare2.normalizedName) == 0){
        return true;
    } else {
        return false;
    }
}

/* readAlbum: this fucntion will read one album
 * Parameter: inputBin - this is the input file stream
 * returns nothing
 * 
 */
void Album::readAlbum(ifstream& inputBin){
	Album temp;
	inputBin.read((char*)&temp, sizeof(temp));
	*this = temp;
}

/* writeBinALbum: this function will write one album to a binary file
 * Parameters:
 *      outBin: the ofstream variable
 *      writeA: the album to write to the binary file
 * Pre-condition: the binary file to write to is opened and closed in the calling function
 * Post-condition: the album passed is written to the binary file
 */
void Album::writeBinAlbum(ofstream& outBin){
    Album temp;
    temp = *this;
    outBin.write((char*)&temp, sizeof(temp));
}

/* operator=: this function completes a deep copy on a album
 * Parameter: copyA: the album to copy
 * returns *this when it is finished being copied
 * Post-condition: this has a deep copy of copyA
 */
Album Album::operator=(const Album& copyA){
	this -> numTracks = copyA.numTracks;
    this -> setDateUtil(copyA.releaseDate.getYear(), copyA.releaseDate.getMonth(), copyA.releaseDate.getDay());
	//this -> releaseDate.setDate(copyA.releaseDate.getYear(), copyA.releaseDate.getMonth(), copyA.releaseDate.getDay());
	strcpy(this -> albumTitle, copyA.albumTitle);
	strcpy(this -> artistName, copyA.artistName);
	strcpy(this -> labelName, copyA.labelName);
	this -> genre = copyA.genre;
	for(int i = 0; i < copyA.numTracks; i++){
		strcpy(this -> trackList[i], copyA.trackList[i]);
	}
	strcpy(this -> normalizedName, copyA.normalizedName);
	
	return *this;
}

/* operator<<: this fucntion prints out an Album in a pretty way
 * Parameters:
 *      outStream - the 'cout' stream
 *      a - the album to print out
 * Returns: outStream once its done
 */
ostream& operator<<(ostream& outStream, const Album& a){
	outStream<<setw(20)<<left<<a.albumTitle;
    outStream<<setw(20)<<left<<a.artistName;
    outStream<<setw(15)<<left<<a.labelName;
    outStream<<setw(10)<<a.releaseDate;
    outStream<<setw(10)<<a.genre<<endl;
	for(int i = 0; i < a.numTracks; i++){
		outStream<<"\t"<<a.trackList[i]<<endl;
	}
	return outStream;
}

/* setInputDate: this function takes a cstring and sets the release date of an album from that
 * Paramter:
 *      the cstring of the date in mm/dd/yyyy format
 * returns nothing
 * Post-condition: the album now has a release date
 */
void Album::setInputDate(const char inputDate[MAX_NAME]){
    int tempYear = 0, tempMonth = 0, tempDay = 0;
    
    string inDate = inputDate;
    int positionCheck = inDate.find('/');
    
    string tempSub = inDate.substr(0, positionCheck);
    tempMonth = atoi(tempSub.c_str());
    inDate.erase(0, positionCheck + 1);
        
    positionCheck = inDate.find('/');
    tempSub = inDate.substr(0, positionCheck);
    tempDay = atoi(tempSub.c_str());
    inDate.erase(0, positionCheck + 1);
        
    tempYear = atoi(inDate.c_str());
    
    releaseDate.setDate(tempYear, tempMonth, tempDay);
    
}