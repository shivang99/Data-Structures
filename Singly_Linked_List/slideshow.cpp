//--------------------------------------------------------------------
//
//  slideshow.cpp
//
//  (Shell) Slide show program
// Name: Shivang Trivedi
// Date: Feb 19, 2019
// Description: This program reads slides from a text file and prints it out on screen.
//--------------------------------------------------------------------



#include <ctime>
#include <conio.h> // For function getch()
#include <cstdlib> // For several general-purpose functions
#include <fstream> // For file handling
#include <iomanip> // For formatted output
#include <iostream> // For cin, cout, and system
#include <string> // For string data type
#include <set>  //For sets

using namespace std;

#include "ListLinked.cpp"


//--------------------------------------------------------------------

// This is a very ugly way to wait for a specified amount of time.
// It is ugly because it runs the CPU the whole time, instead of
// just suspending the process for the required time period.
// However, it is also very portable.  This function should work on
// all platforms that support ANSI C++.  Feel free to replace this
// with something nicer (such as sleep or usleep) if you so choose.
void wait(int secs) 
{
    int start=clock();

    while (clock() < start + secs * CLOCKS_PER_SEC);
}

//--------------------------------------------------------------------

class Slide
{
  public:
    static const int HEIGHT = 10,		// Slide dimensions
                     WIDTH  = 36;

    void display () const;			// Display slide and pause

  private:

    char image [HEIGHT][WIDTH];  	   // Slide image
    int pause;				   // Seconds to pause after
   					   //  displaying slide

    friend istream& operator>> (istream& in, Slide& slide);
    friend ostream& operator<< (ostream& out, const Slide& slide);
};

//--------------------------------------------------------------------

int main()
{
	List<Slide> slideShow;    	    // Slide show
	Slide currSlide;                // Slide
	char filename[81];              // Name of slide show file

	// Read the slide show from the specified file.

	cout << endl << "Enter the name of the slide show file : ";
	cin >> filename;

	ifstream slideFile(filename);

	if (!slideFile)
	{
		cout << "Error opening file " << filename << endl;
	}
	else
	{
		//read from file until end of file is reached
		while (!slideFile.eof()) {
				//get slide from file
				slideFile >> currSlide;
				//insert the current slide into the list
				slideShow.insert(currSlide);
				//print current slide
				currSlide.display();
		}

		// Close the file. 
		slideFile.close();
		// Display the slide show slide-by-slide. (Your code below)

	}
    return 0;
}

//--------------------------------------------------------------------

istream& operator>> (istream& inFile, Slide& slide)

// Read a slide from inFile.
{
	inFile >> slide.pause;
    // Read a slide from inFile.
	for (int x = 0; x < slide.HEIGHT; x++) {
		for (int y = 0; y < slide.WIDTH; y++) {
			inFile.get(slide.image[x][y]);
		}
	}
	return inFile;
}

//--------------------------------------------------------------------

ostream& operator<< (ostream& out, const Slide& slide)

{
	//print the 2D array
	for (int x = 0; x < slide.HEIGHT; x++) {
		for (int y = 0; y < slide.WIDTH; y++) {
			out << slide.image[x][y];
		}
	}
	//return the ostream
	return out;


}


void Slide:: display () const

{
    //This should compile and run on both Windows and Unix
    //Feel free to change this if you want to do something nicer.
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Display a slide and pause.
		//output current slide. wait function for pause
		cout << (*this);
		wait(this->pause);

}
