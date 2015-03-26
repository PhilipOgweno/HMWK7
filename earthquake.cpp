// Earthquake class definition

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "earthquake.h"

using namespace std;
// Defining prototypes

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
//string uppercase ( string );
//string Mag_type2string ( Mag_type );
//Mag_type string2_Mag_type ( string );

string  message;
int flag;

void Date_check ( string Date, ofstream & logfile ) // function to checks validity of Date
{
    message = "Incorect Date !";
    if ( Date.length() != 10 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else 
    {
        if (( ( Date[2] != "-"[0] ) && ( Date[2] != "/"[0])) || 
        (( Date[5] != "-"[0] ) && ( Date[5] != "/"[0])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        else 
        {
            if (( !isdigit ( Date[0])) || ( !isdigit ( Date[1])) || 
            ( !isdigit ( Date[3])) || ( !isdigit ( Date[4])) ) 
            {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }  
            if (( !isdigit ( Date[6])) || ( !isdigit ( Date[7])) || 
            ( !isdigit ( Date[8])) || ( !isdigit ( Date[9])) ) 
            {
                print_file ( message, logfile );
                exit (EXIT_FAILURE);
            }
        }
    }
    return;
}
//******************************************************************************
void Month_check ( int Month, ofstream & logfile )  // function to check validity of Month 
{
    if (( Month > 12 ) || ( Month < 1))
    {
        message = "Incorect Month ! ";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Day_check ( int day, ofstream & logfile )    // function checks the validity of Day
{
    if (( day > 31 ) || ( day < 1))
    {
        message = "Incorect Day !.";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Year_check ( int year, ofstream & logfile )  // checking the validity of Year
{
    if ( year < 0 ) 
    {
        message = "Incorect Year !";
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Time_check ( string Time, ofstream & logfile )  // checking the validity of Time
{
    message = "Incorrect Time format !";
    if ( Time.length() != 12 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    else 

    {
        if (( Time[2] != ":"[0] ) || ( Time[5] != ":"[0] ) || 
           ( Time[8] != "."[0])) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        else 
        {
        if (( !isdigit ( Time[0])) || ( !isdigit ( Time[1])) || 
           ( !isdigit ( Time[3])) || ( !isdigit ( Time[4])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        if (( !isdigit ( Time[6])) || ( !isdigit ( Time[7])) || 
           ( !isdigit ( Time[9])) 
        || ( !isdigit ( Time[10])) || ( !isdigit ( Time[11])) ) 
        {
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        
                // Defining other Variables

        string temp0, h1, h2;
        double Val;

        temp0 =  temp0.append ( Time.begin (), Time.begin () + 2 ); // checking the validity of Hour
        Val = atoi(temp0.c_str());
        if (( Val < 0 ) || ( Val > 23)) 
        {
            message = "Incorrect Hour !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        h1 =  h1.append ( Time.begin () + 3, Time.begin () + 5 ); // checking the validity of Minutes
        Val = atoi(h1.c_str());
        if (( Val < 0 ) || ( Val > 59)) 
        {
            message = "Incorrect Minute !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }

        h2 =  h2.append ( Time.begin () + 6, Time.begin () + 8 ); // checking the validity of Seconds
        Val = atoi(h2.c_str());
        if (( Val < 0 ) || ( Val > 59)) 
        {
            message = "Incorrect Second !.";
            print_file ( message, logfile );
            exit (EXIT_FAILURE);
        }
        }
    }
    return;
}
//******************************************************************************
void Time_Zone_check ( string Time_Zone, ofstream & logfile ) // checking the validity of Time Zone
{
    message = "Incorrect Time_Zone format !.";
    if (( Time_Zone.length() != 3 ) || ( !isalpha ( Time_Zone[0])) || 
    ( !isalpha ( Time_Zone[1])) || ( !isalpha ( Time_Zone[2])) ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
void Mag_Type_check ( string Mag_type, ofstream & logfile ) // checking the validity of MagType
{
    message = "Incorrect Mag_type !.";
    string mt = uppercase ( Mag_type );
    if (( mt != uppercase ( "ml")) && ( mt != uppercase ( "ms")) 
    && ( mt != uppercase ( "mb")) && ( mt != uppercase ( "mw")) ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************
// Function to checks for validity of Mag size 

void Mag_size_check ( float Mag_size, ofstream & logfile ) 
{
    message = "Incorrect Magnitude size !";
    if ( Mag_size <= 0 ) 
    {
        print_file ( message, logfile );
        exit (EXIT_FAILURE);
    }
    return;
}
//******************************************************************************

string MonthStrng ( Months Month )   // Function to Convert "Month" to a String
{
    switch ( Month ) 
    {
        case January:
            return "January";
        case February:
            return "February";
        case March:
            return "March";
        case April:
            return "April";
        case May:
            return "May";
        case June:
            return "June";
        case July:
            return "July";
        case August:
            return "August";
        case September:
            return "September";
        case October:
            return "October";
        case November:
            return "November";
        case December:
            return "December";
        default:
            return "ILLEGAL";
    }
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
string Mag_type2string ( Mag_type M )         // Function to Change Mag Type to String
{
    switch ( M ) 
    {
        case ML:
            return "ML";
        case Ms:
            return "Ms";
        case Mb:
            return "Mb";
        case Mw:
            return "Mw";
    }
    exit(EXIT_FAILURE);
}
//******************************************************************************
Mag_type string2_Mag_type ( string NN )       // Function to Change String to Mag Type
{
    NN = uppercase ( NN );
    if ( NN == "ML" ) 
    {
        return ML;
    }    
    if ( NN == "MS" ) 
    {
        return Ms;
    }
    if ( NN == "MB" ) 
    {
        return Mb;
    }
    if ( NN == "MW" ) 
    {
        return Mw;
    }
    exit(EXIT_FAILURE);
}


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
