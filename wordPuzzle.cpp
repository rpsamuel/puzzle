//David Samuel, dms4gt, wordPuzzle.cpp Travis 
//runtime is n^4 because of the 4 nested for loops
#include "hashTable.h"
#include "timer.h"
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAXROWS 500
#define MAXCOLS 500

timer tim;
char table[MAXROWS][MAXCOLS];

bool readInGrid (string filename, int &rows, int &cols);
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols);

int main(int argc, char ** argv){
  string diction = argv[1];
	
  ifstream file(diction.c_str());
  string t;
  int sizeOf=0;
  while(getline(file,t)){
    sizeOf++; 
	   cout<<"SizeOF is:" << sizeOf<< "\n";
  }
 cout<<"SizeOF end :" << sizeOf<< "\n";
  hashTable *wordpuz= new hashTable((sizeOf));
  file.close();
  file.open(diction.c_str());
  while(getline(file,t)){
   
	  if(t.length()>2){
      wordpuz->insert(t); //error is occuring here, wrong address. Can't find issue. 
	    
    }}
	
  file.close();

  string words = argv[2];
  file.open(words.c_str());
  int rows;
  int cols;

  readInGrid(words.c_str(), rows, cols);
  int numWords=0;
  string k;
  tim.start();
  for(int r= 0; r<rows;r++){
    for(int c=0; c<cols; c++){
      for(int d=0; d<8; d++){
	for(int l= 3; l<23; l++){
	  string word(getWordInGrid(r,c,d,l,rows,cols));
	  if(l>word.length()){
	    break;}
	  if(wordpuz->contains(word)){
	    numWords+=1;
	    if(d==0){
	      k="N (";
	    }
	    else if(d==1){
	      k="NE (";
	    }
	     if(d==2){
	      k="E (";
	    }
	    else if(d==3){
	      k="SE (";
	    } if(d==4){
	      k="S (";
	    }
	    else if(d==5){
	      k="SW (";
	    } if(d==6){
	      k="W (";
	    }
	    else if(d==7){
	      k="NW (";
	    }
     cout<< k<<r<<", "<< c<< "):\t"<<word<< endl;
	  }
	}
      }
    }
  }
  tim.stop();
  int totTime= tim.getTime()*1000;
  cout<< numWords<<" words found"<< endl;
  cout<< totTime<< endl;
  return 0;
}
  
  

/** This function will read in a grid file, as per the format in the
 * CS 2150 lab 6 document, into a global grid[][] array.  It uses C++
 * file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columnss as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
bool readInGrid (string filename, int &rows, int &cols) {
    // a C++ string to hold the line of data that is read in
    string line;
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream file(filename.c_str());
    // upon an error, return false
    if ( !file.is_open() )
        return false;
    // the first line is the number of rows: read it in
    file >> rows;
    cout << "There are " << rows << " rows." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the second line is the number of cols: read it in and parse it
    file >> cols;
    cout << "There are " << cols << " cols." << endl;
    getline (file,line); // eats up the return at the end of the line
    // the third and last line is the data: read it in
    getline (file,line);
    // close the file
    file.close();
    // convert the string read in to the 2-D grid format into the
    // grid[][] array.  In the process, we'll print the grid to the
    // screen as well.
    int pos = 0; // the current position in the input data
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            table[r][c] = line[pos++];
            cout << table[r][c];
        }
        cout << endl;
    }
    // return success!
    return true;
}



/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static char[][] variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A char* containing the letters in the provided direction
 *         (NOTE: it is returned in a static char array).
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
char* getWordInGrid (int startRow, int startCol, int dir, int len,
                     int numRows, int numCols) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocataion.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static char output[256];
    // make sure the length is not greater than the array size.
    if ( len >= 255 )
        len = 255;
    // the position in the output array, the current row, and the
    // current column
    int pos = 0, r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output[pos++] = table[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // set the next character to zero (end-of-string)
    output[pos] = 0;
    // return the string (a C-style char* string, not a C++ string
    // object)
    return output;
}
