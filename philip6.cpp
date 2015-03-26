/*
 * Homework 6 Program, Stn Channels
 * Goal: Learning how to use classes and their associates concepts of scope, 
 * privacy and encapulation
 * Author: Luke Philip Ogweno
 * 24 March 2015
 * Github account: https://github.com/PhilipOgweno/HMWORK7.git
 */
 //******************************************************************************
// External Libraries

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <fstream>
#include <iomanip>
#include <locale>
#include <ctype.h>
#include <stdlib.h>
#include "earthquake.h"
#include "Station_Info.h"

using namespace std;

// Global Variables

string iFileName, oFilename = "philip.out", logfilename = "philip.log", message;
int flag;

// Defining Classes

//// Defining Enumerators

enum Months {January = 1, February, March, April, May, June,
     July, August, September, October, November, December};
enum Mag_type {ML, Ms, Mb, Mw };
enum Network_Code {CE, CI, FA, NP, WR };
enum Band_Type {longperiod, shortperiod, broadband };
enum Inst_Type {highgain, lowgain, accelerometer };
    string uppercase ( string );
    string Mag_type2string ( Mag_type );
    Mag_type string2_Mag_type ( string );
//******************************************************************************

void open_input ( ifstream & );
void open_file ( string, ofstream & );
void print_file ( string, ofstream & );
void print_file ( int, ofstream & );
void Date_check ( string, ofstream & );
void Month_check ( int, ofstream & );
void Day_check ( int, ofstream & );
void Year_check ( int, ofstream & );
void Time_check ( string, ofstream & );
void Time_Zone_check ( string, ofstream & );
void Mag_Type_check ( string, ofstream & );
void Mag_size_check ( float, ofstream & );
void Signals ( ofstream &, string, string, string, string, string, string );
void Network_Code_check ( int, string, ofstream & );
void Stn_code_check ( int, string, ofstream & );
void Band_Type_check ( int, string , ofstream & );
void Inst_Type_check ( int, string, ofstream & );


string Network_Code_to_string ( Network_Code );
Network_Code string2_Network_Code ( string );
string Band_Type2string ( Band_Type );
Band_Type string2_Band_Type ( string );
string Inst_Type2string ( Inst_Type );
Inst_Type string2_Inst_Type ( string );

// Main Program starts here

int main ()

{
    // Defining Variables' Type

    string EqkName1, day, Month, year;
    string Temp, h1, h2, h3, h4, h5;
    int Numb_of_valid_entries = 0, Numb_of_input = 0, Val = 0, Numb_of_signal = 0;
    Months Month_name;

    Station_Info Station_Info_Arr [ 300 ];
    Station_Info Station_Info_Temp;
    earthquake header;

    // Prompt User for Input File Name.

    ifstream iFile;
    open_input ( iFile );

    // Preparing log file

    ofstream logfile;
    open_file ( logfilename, logfile );

    message = "Opening file: philip.in";
    print_file ( message, logfile );
    print_file ( "\n", logfile );
    message = "Processing input ...";
    print_file ( message, logfile );
    print_file ( "\n", logfile );

    // Reading and Checking the Header

    iFile >> header.Event_ID;
    iFile >> header.Date;   
    Date_check ( header.Date, logfile );

    // Finding and Checking the Validity of the Month

    Temp       =  Temp.append ( header.Date.begin (), header.Date.begin () + 2 );
    Val        = atoi(Temp.c_str());
    Month_check ( Val, logfile );
    Month_name = Months(Val);
    Month      = MonthStrng ( Month_name );

    // Finding and Checking the Validity of the day

    h1 =  h1.append ( header.Date.begin () + 4, header.Date.begin () + 5 );
    Val   = atoi(h1.c_str());
    Day_check ( Val, logfile );

    // Getting and Checking  Validity of the year

    h2 =  h2.append ( header.Date.begin () + 6, header.Date.end () );
    Val   = atoi(h2.c_str());
    Year_check ( Val, logfile );

    iFile >> header.Time;
    Time_check ( header.Time, logfile );
    iFile >> header.Time_Zone;
    Time_Zone_check ( header.Time_Zone, logfile );
    iFile >> header.EqkName;
    getline(iFile, EqkName1);
    header.EqkName.append ( EqkName1 ); 

    // Getting Epicenter Location

    iFile >> header.Lon;
    iFile >> header.Lat; 
    iFile >> header.depth;

    // Getting Mag Information

    iFile >> header.Mag_type_string;
    Mag_Type_check ( header.Mag_type_string, logfile );
    iFile >> header.Mag_size;
    Mag_size_check ( header.Mag_size, logfile );
    message = "Header read correctly!";
    print_file ( message, logfile );
    print_file ( "\n\n", logfile );

    // Preparing output files

    ofstream oFile;
    open_file ( oFilename, oFile );
    oFile    << "#"   << day.append( header.Date.begin () + 3, 
             header.Date.begin () + 5 ) 
             << " "   << Month << " "    << year.append( header.Date.begin () + 6,
             header.Date.end () );
    oFile    << " "   << header.Time     << " "    <<  header.Time_Zone << " " 
             << Mag_type2string ( string2_Mag_type ( header.Mag_type_string)) 
             << " "   << header.Mag_size << " "    << header.EqkName << " ";
    oFile    << "["   << header.Event_ID << "]  (" << header.Lon << ", " 
             << header.Lat << ", " << header.depth << ")" << endl;

    // Reading the input Entries

    while (( iFile >> Station_Info_Temp.Network_Code ) && ( Numb_of_valid_entries < 300)) 
    {
        flag = 0;
        Numb_of_input = Numb_of_input + 1;
        
        // Checking the following

        Network_Code_check ( Numb_of_input, Station_Info_Temp.Network_Code, logfile );
        iFile >> Station_Info_Temp.Stn_code;
        Stn_code_check ( Numb_of_input, Station_Info_Temp.Stn_code, logfile );
        iFile >> Station_Info_Temp.Band_Type;
        Band_Type_check ( Numb_of_input, Station_Info_Temp.Band_Type, logfile );
        iFile >> Station_Info_Temp.Inst_Type;
        Inst_Type_check ( Numb_of_input, Station_Info_Temp.Inst_Type, logfile );

       // Getting and Checking for Orientation

        h3 = "";
        h4 = "";
        h5 = "";
        iFile >> Station_Info_Temp.Orient;
        if (( Station_Info_Temp.Orient.length() < 1 ) || 
           ( Station_Info_Temp.Orient.length() > 3)) 
        {
            flag = 5;
        }
        else 
        {
            h1 = Station_Info_Temp.Orient[0];
            if (( h1 != "1" ) && ( h1 != "2" ) && ( h1 != "3" )) 
            {
                if (( uppercase ( h1 ) != uppercase ( "N" )) 
                && ( uppercase ( h1 )   != uppercase ( "E" )) 
                && ( uppercase ( h1 )   != uppercase ( "Z" )) ) 
                { 
                    flag = 5;
                }
                else 
                {
                    if ( Station_Info_Temp.Orient.length() > 1 ) 
                    {
                        h2 = Station_Info_Temp.Orient[1];
                        if (( h2 != "N" ) && ( h2 != "E" ) && ( h2 != "Z" )) 
                        {
                            flag = 5;
                        }
                        else 
                        {
                            if ( Station_Info_Temp.Orient.length() > 2 ) 
                            {
                                h5 = Station_Info_Temp.Orient[2];
                                if (( h5 != "N" ) && ( h5 != "E" ) && ( h5 != "Z" )) 
                                {
                                    flag = 5;
                                }
                            }
                        }
                    }
                }
            }
            else {
                if ( Station_Info_Temp.Orient.length() > 1 ) 
                {
                    h2 = Station_Info_Temp.Orient[1];
                    if (( h2 != "1" ) && ( h2 != "2" ) && ( h2 != "3")) 
                    {
                        flag = 5;
                    }
                    else 
                    {
                        if ( Station_Info_Temp.Orient.length() > 2 ) 
                        {
                            h5 = Station_Info_Temp.Orient[2];
                            if (( h5 != "1" ) && ( h5 != "2" ) && ( h5 != "3")) 
                            {
                                flag = 5;
                            }
                        }
                    }
                }
            }
        }

       if ( flag == 5 ) 
       {
            print_file ( "Station_Info # ", logfile );
            print_file ( Numb_of_input, logfile );
            print_file ( " ignored. Invalid Orient. ", logfile ); 
            print_file ( "\n", logfile );  
        }
        if ( flag == 0 ) 
        {
            Numb_of_valid_entries = Numb_of_valid_entries + 1;
            Station_Info_Temp.Orient = h1;
            Station_Info_Arr [ Numb_of_signal ] = Station_Info_Temp;
            Numb_of_signal = Numb_of_signal + 1;
            if ( h2 != "" ) 
            {
                Station_Info_Temp.Orient = h2;
                Station_Info_Arr [ Numb_of_signal ] = Station_Info_Temp;
                Numb_of_signal = Numb_of_signal +1;
                if ( h5 != "" ) 
                {
                    Station_Info_Temp.Orient = h5;
                    Station_Info_Arr [ Numb_of_signal ] = Station_Info_Temp;
                    Numb_of_signal = Numb_of_signal +1;
                }
            }
        }
    }

    print_file ( "Total invalid entries ignored: ", logfile );
    print_file (( Numb_of_input - Numb_of_valid_entries ), logfile );
    print_file ( "\n", logfile );
    print_file ( "Total valid entries read: ", logfile );
    print_file ( Numb_of_valid_entries, logfile );
    print_file ( "\n", logfile );
    print_file ( "Total signal names produced: ", logfile );
    print_file ( Numb_of_signal, logfile );
    print_file ( "\n", logfile );
    print_file ( "Finished!", logfile );

    oFile << ( Numb_of_signal ) << endl;             // Printing Outputs
    for (int i = 0; i < ( Numb_of_signal ); i++) 
    {

        // Producing Signal

        Signals ( oFile, header.Event_ID, Network_Code_to_string 
        ( string2_Network_Code ( Station_Info_Arr[i].Network_Code)), 
        Station_Info_Arr[i].Stn_code, Band_Type2string ( string2_Band_Type 
        ( Station_Info_Arr[i].Band_Type)),  Inst_Type2string 
        ( string2_Inst_Type ( Station_Info_Arr[i].Inst_Type)), Station_Info_Arr[i].Orient );
    }
    return 0;
}            // End of main programm

//******************************************************************************
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

string uppercase ( string s )          // Converts all letters of input string to upper case.
{
    string result = s;
    for (int i=0; i < (int)s.size(); i++)
        result[i] = toupper(s[i]);
    return result;
}
//******************************************************************************
// Function to Check Network Code

void Network_Code_check ( int Numb_of_input, string code, ofstream & logfile ) 
{
    if (( code.length() != 2 ) || (( code != "CE" ) && ( code != "CI" ) 
    && ( code != "FA" ) 
    && ( code != "NP" ) && ( code != "WR")) ) 
    {
        flag = 1;
    }
    if ( flag == 1) 
    {
        print_file ( "Station_Info # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid network. ", logfile );
        print_file ( "\n", logfile );
    }
    return;
}
//******************************************************************************
// Function to Check Station Code

void Stn_code_check ( int Numb_of_input, string code, ofstream & logfile ) 
{
    if ( code.length() != 3 ) 
    {
        if ( code.length() != 5 ) 
        {
            flag = 2;
        }
        else 
        {
            if (( !isdigit ( code[0])) || ( !isdigit ( code[1])) 
            || ( !isdigit ( code[2]))   || ( !isdigit ( code[3])) 
            || ( !isdigit ( code[4])) ) 
            {
                flag = 2;
            }
        }
    }
    else 
    {
        if (( !isalpha ( code[0])) || ( !isalpha ( code[1])) 
        || ( !isalpha ( code[2])) ) 
        {
            flag = 2;
        }
        else {
            if ( uppercase ( code ) != code ) 
            {
                flag = 2;
            }    
        }
    }
    if ( flag == 2) 
    {
        print_file ( "Station_Info # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid Stn code. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return;
}
//******************************************************************************
// Function to Check Type of Band

void Band_Type_check ( int Numb_of_input, string band, ofstream & logfile ) 
{
    if (( uppercase ( band ) != uppercase ( "Long-period")) 
    && ( uppercase  ( band ) != uppercase ( "Short-period")) 
    && ( uppercase  ( band ) != uppercase ( "Broadband")) ) 
    {
        flag = 3;
    }
    if ( flag == 3 ) {
        print_file ( "Station_Info # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid type of band. ", logfile ); 
        print_file ( "\n", logfile );
    }
    return;
}    
//******************************************************************************
// Function to check instrument type
void Inst_Type_check ( int Numb_of_input, string instrument, ofstream & logfile ) 
{
    if (( uppercase ( instrument ) != uppercase ( "High-Gain")) 
    && ( uppercase ( instrument )  != uppercase ( "Low-Gain")) 
    && ( uppercase ( instrument )  != uppercase ( "Accelerometer")) ) 
    {
        flag = 4;
    }
    if ( flag == 4 ) 
    {
        print_file ( "Station_Info # ", logfile );
        print_file ( Numb_of_input, logfile );
        print_file ( " ignored. Invalid type of instrument. ", logfile ); 
        print_file ( "\n", logfile );
    }
}
//******************************************************************************

string Network_Code_to_string ( Network_Code MM )  // Function to Change Network Code to String
{
    switch ( MM ) 
    {
        case CE:
            return "CE";
        case CI:
            return "CI";
        case FA:
            return "FA";
        case NP:
            return "NP";
        case WR:
            return "WR";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Network_Code string2_Network_Code (string NN)  // Function to Change String to Network Code
{
    NN = uppercase (NN);
    if ( NN == "CE" ) 
    {
        return CE;
    }    
    if ( NN == "CI" ) 
    {
        return CI;
    }
    if ( NN == "FA" ) 
    {
        return FA;
    }
    if ( NN == "NP" ) 
    {
        return NP;
    }
    if ( NN == "WR" ) 
    {
        return WR;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
string Band_Type2string ( Band_Type MMM )  // Function to Change Band Type to String
{
    switch ( MMM ) 
    {
        case longperiod:
            return "L";
        case shortperiod:
            return "B";
        case broadband:
            return "H";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Band_Type string2_Band_Type (string NN)  // Function to Change String to Band Type
{
    NN = uppercase (NN);
    if ( NN == uppercase ( "Long-Period"))
    {
        return longperiod;
    }    
    if ( NN == uppercase ( "Short-Period"))
    {
        return shortperiod;
    }
    if ( NN == uppercase ( "Broadband"))
    {
        return broadband;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
// Function to Change Instrument Type to String

string Inst_Type2string ( Inst_Type MMMM )
{
    switch ( MMMM ) 
    {
        case highgain:
            return "H";
        case lowgain:
            return "L";
        case accelerometer:
            return "N";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Inst_Type string2_Inst_Type (string NN)   // Function to Change String to Instrument Type
{
    NN = uppercase (NN);
    if ( NN == uppercase ( "High-Gain"))
    {
        return highgain;
    }    
    if ( NN == uppercase ( "Low-Gain"))
    {
        return lowgain;
    }
    if ( NN == uppercase ( "Accelerometer"))
    {
        return accelerometer;
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************

