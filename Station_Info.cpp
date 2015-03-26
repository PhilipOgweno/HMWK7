// Station class definition
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Station_Info.h"

using namespace std;

string iFileName, oFilename = "philip.out", logfilename = "philip.log", message;
int flag;


void open_input ( ifstream & );
void open_file ( string, ofstream & );
void print_file ( string, ofstream & );
void print_file ( int, ofstream & );
void Network_Code_check ( int, string, ofstream & );
void Stn_code_check ( int, string, ofstream & );
void Band_Type_check ( int, string , ofstream & );
void Inst_Type_check ( int, string, ofstream & );


// Functions

void open_input ( ifstream & ifs )                  // open_input Function 
{
    cout << "Enter input file name: ";              // Prompt User for Input File Name.
    cin >> iFileName;                               // Input file

    ifs.open(iFileName.c_str());

    if ( !ifs.is_open() ) 
    {
        message = "Input file does not exist!";    // Check if the File Is Opened correctly

        ofstream logfile;                         // log to logfile if Error occurrs
        open_file ( logfilename, logfile );
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void open_file ( string filename, ofstream & ofs ) // open_file Function (open new file)
{
    ofs.open(filename.c_str());
    if ( !ofs.is_open() ) 
    {
        message = "File does not exist!";

        ofstream logfile;                         // log to logfile if Error occurrs
        open_file ( logfilename, logfile );
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void print_file ( string message, ofstream & ofs )  // Prints Messages on Files and Terminal
{
    ofs << message  << flush;                       // Flush output stream buffer
    cout << message << flush;
    return;
}
//******************************************************************************
void print_file ( int number, ofstream & ofs )     // Function to Prints numbers
{
    ofs << number  << flush;
    cout << number << flush;
    return;
}
//******************************************************************************
string uppercase ( string s )          // Converts all letters of input string to upper case.
{
    string result = s;
    for (int i=0; i < (int)s.size(); i++)
        result[i] = toupper(s[i]);
    return result;
}
//******************************************************************************
// Function to Produce Signal Name
        
void Signals ( ofstream & oFile, string Event_ID, string Network_Code, 
     string Stn_code, string Band_Type, string Inst_Type, string Orient ) 
{ 
    string temp= "";
    temp.append( Event_ID );
    temp.append( "." );
    temp.append( Network_Code );
    temp.append( "." );
    temp.append( Stn_code );
    temp.append( "." );
    temp.append( Band_Type );
    temp.append( Inst_Type );
    temp.append( Orient );
    oFile << temp << endl;
    return;
}

//******************************************************************************


