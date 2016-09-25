// tests/load_data.cpp
// Test using DCMTK to load multiframe DICOM files.

// INCLUDES

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


// HELPERS

// Value Representation (VR) table




short shortFromLittleEndian ( char* data )
{
    return ( data[1] << 8 ) | data[0];
}

short readLittleEndianShort ( ifstream& file ) {
    char* data = new char[2];
    file.read( data, 2 );
    return shortFromLittleEndian( data );
}

void printHexShort ( short i ) {
    cout << setfill( '0' ) << setw( sizeof( short ) * 2 ) << hex << i;
}


// MAIN

int main ( int argc, char* argv[] )
{

    string dicomPath = "/Users/max/Documents/git/radroom/conversion/test/imagesAB/IMAGES/BRAINSAG";
    ifstream dicomFile ( dicomPath, ios::in | ios::binary );

    string dicomHeader ( "DICM" );
    
    char* data;
    
    short curGroup;
    short curElement;
    short curVR;

    if ( dicomFile.is_open() )
    {
        cout << "File opened!\n";
        
        // DICOMs start with 128 blanks
        dicomFile.seekg( 128, ios::beg );

        // Check DICOM magic number
        data = new char[4];
        dicomFile.read( data, 4 );
        if ( dicomHeader.compare( string( data ) ) != 0 )
        {
            cout << "DICOM prefix does not match!\n";
            return 1;
        }

        cout << to_string( sizeof( int ) ) << "\n";

        // Iterate over data elements
        bool readFinished = false;

        while ( !readFinished ) {

            // Get group, element, and VR
            curGroup        = readLittleEndianShort( dicomFile );
            curElement      = readLittleEndianShort( dicomFile );
            // curVR           = readLittleEndianInt( dicomFile );

            printHexShort( curGroup );
            cout << ":";
            printHexShort( curElement );
            cout << "\n";

            readFinished = true;

        }
        
        dicomFile.close();
    }
    else {
        cout << "Could not open file!\n";
    }

    return 0;

}
