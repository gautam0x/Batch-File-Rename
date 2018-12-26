/*--------------------------------------------------------------------------------------------------
This Program is licensed under Gautam http://github.com/gautam0x for Presonal use

Usage :
-->> This is file renaming program
-->> It can rename thousands of file in single click

Condition :
-->> File should be in the order of

	example : name1.jpg , name2.jpg , name3.jpg etc .
	and a file custom_name_list.txt contain new name for all the file-name line BY line in same directory

	lets begain code :)
---------------------------------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>

using namespace std ;

void exit_message(string , int) ;	// function to print message on exit condition
void clear_screen() ;				// function to clear screen on both linux and windows


int main()
{
	char choice ;	// universal choice variable in program

	/* --------------------------------------------------------

	variables :
	file prefix -->> the starting constant string
	file_suffix , file_starting_suffix , file_ending_suffix -->> the integer value for which represent numbering start and end
	total_file -->> variable which contains the nuber of file by substracting starting and ending suffix
	file_extension , file_extension_old -->> the variable which contains the extension of the file new and old

	------------------------------------------------------------*/

	string file_prefix , file_extension , file_extension_old , filename_old , filename_new ;
	int file_suffix , file_starting_suffix , file_ending_suffix , total_file ;





	/*	The Output acreen and input interface for the program	*/


	clear_screen() ;    // Clear the screen first

	cout<<"\n     Usage :      \n      Enter File Prefix , File Suffix , File Extension >> Step BY Step <<" ;
	cout<<"\n\n     Example :  \n" ;
	
	
	cout<<"                file_name 001 . jpg                       \n " ;
	cout<<"                 |        |      |                        \n " ;
	cout<<"                 |        |      |                        \n " ;
	cout<<"                 |        |      |_____ file extension    \n " ;
	cout<<"                 |        |                               \n " ;
	cout<<"                 |        |____________ file suffix       \n " ;
	cout<<"                 |                                        \n " ;
	cout<<"                 |_____________________ file prefix       \n " ;
	cout<<"\n\n\n";


	cout<<"     Steps : \n";
	cout<<endl<<"  1. Prefix of filename "<<endl<<"  --> ";
	getline(cin , file_prefix);

	cout<<endl<<"  2. Starting suffix [number]"<<endl<<"  --> ";
	cin>>file_starting_suffix ;

	cout<<endl<<"  3. Ending suffix [number]"<<endl<<"  --> ";
	cin>>file_ending_suffix ;

	cout<<endl<<"  4. File extension [without . ]" <<endl <<"  --> ";
	cin.ignore();    // use to clear input buffer
	getline(cin , file_extension_old);

	file_extension_old.length() > 0 ? file_extension_old = "." + file_extension_old : file_extension = ' ' ;

	cout<<endl<<endl<<"      Do you want to change file extension [Y / N ] : ";
	cin>>choice ;

	//////// Choice if users wants to change file extension

	if(choice == 'y' || choice == 'Y')
	{
		cout<<endl<<"  5. New file extension (without . )" <<endl <<" --> ";

		cin.ignore();    // use to clear input buffer
		getline(cin , file_extension);

		file_extension.length() > 0 ? file_extension = "." + file_extension : file_extension = ' ' ;
	}
	else
	{
		file_extension = file_extension_old;
	}

	//////// Count the total file in range

	total_file = file_ending_suffix - file_starting_suffix + 1 ;




	/* ----------- Perofrm file handling Operation ------- */

	ifstream file;
	file.open("custom_name_list.txt");

	string temp;
	int    number_of_lines = 0 ;


	// Count the total no of lines in the filename list
	while( getline(file,temp) )
	{
		number_of_lines++ ;
	}
	file.clear();                // reset the file pointer
	file.seekg(0 , ios::beg );   // change get file pointer to starting point of file

	if( number_of_lines != total_file )
	{
		exit_message("Number of files are different than no of lines" , 0) ;
		return 0 ;
	}

	// put some newlines before listing
	cout<<"\n\n";

	// perform renaming operation
	for(file_suffix = file_starting_suffix ; file_suffix <= file_ending_suffix ; file_suffix++)
	{
		stringstream temp;
		temp << file_suffix;       // convert int to sstream and ssstream to string

		filename_old = file_prefix + temp.str() + file_extension_old ;

		getline( file , filename_new ) ;
		filename_new = filename_new + file_extension ;

		if( !rename( filename_old.c_str() , filename_new.c_str() ) )
			cout<<"|  Ok   |  " <<filename_old <<" -->> "<<filename_new << endl;
		else
			cout<<"| Error |  "<<filename_old << " -->> " << endl;
	}


	file.close();

	exit_message("Program Executed " , 1 ) ;
	return 0;
}


/* Defining the function Exit Message */
void exit_message(string exit_message , int exit_code)
{
	if( exit_code == 0 )
	{
		clear_screen() ;
		cout<<"\n\n---------------------------------------------------------------------";
		cout<<"\n\n Error Occoured : \n\n *** " << exit_message << " *** \n\n";
		cout<<"---------------------------------------------------------------------\n";
	}
	else
	{
		cout<<"\n\n---------------------------------------------------------------------";
		cout<<"\n\n Sucess : \n\n *** "<< exit_message <<" *** \n\n";
		cout<<"---------------------------------------------------------------------\n";
	}
}

/* Defining The function of clear screen for both windows and linux */
void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system ("clear");
#endif
}

