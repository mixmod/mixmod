/***************************************************************************
                             EXAMPLES/main.cpp  description
    copyright            : (C) MIXMOD Team - 2001-2016
    email                : contact@mixmod.org
 ***************************************************************************/

/***************************************************************************
    This file is part of MIXMOD
    
    MIXMOD is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MIXMOD is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

    All informations available on : http://www.mixmod.org                                                                                               
***************************************************************************/
#include <map>
#include <iostream>
#include <mixmod.h>

using namespace std;

// print program usage
void showExamplesHelp() {
    cout << "Usage: './example_exe <function_name_shortcut>' where shortcuts are defined as follow.\n";
    cout << "    cX --> clustering_X_example with X in (integer) range [1,14]\n";
    cout << "    daX --> discriminant_analysis_X_example with X in (integer) range [1,5]\n";
}

// (example) function type
typedef void ( *Function ) ();

// key-value type for a map of functions
typedef pair<string,Function> StrToFunc;

// declare all functions to avoid compiler warnings
void clustering_1_example();
void clustering_2_example();
void clustering_3_example();
void clustering_4_example();
void clustering_5_example();
void clustering_6_example();
void clustering_7_example();
void clustering_8_example();
void clustering_9_example();
void clustering_10_example();
void clustering_11_example();
void clustering_12_example();
void clustering_13_example();
void clustering_14_example();
void discriminant_analysis_1_example();
void discriminant_analysis_2_example();
void discriminant_analysis_3_example();
void discriminant_analysis_4_example();
void discriminant_analysis_5_example();

// main entry point for clustering or DA EXAMPLES
// call: ./example XY where X is either 'c' or 'da',
//       and Y is the example number
int main ( int argc, char* argv[] ) {

    // create map: example function names --> example functions
    map<string,Function> functions;
    functions.insert ( StrToFunc ( "c1",clustering_1_example ) );
    functions.insert ( StrToFunc ( "c2",clustering_2_example ) );
    functions.insert ( StrToFunc ( "c3",clustering_3_example ) );
    functions.insert ( StrToFunc ( "c4",clustering_4_example ) );
    functions.insert ( StrToFunc ( "c5",clustering_5_example ) );
    functions.insert ( StrToFunc ( "c6",clustering_6_example ) );
    functions.insert ( StrToFunc ( "c7",clustering_7_example ) );
    functions.insert ( StrToFunc ( "c8",clustering_8_example ) );
    functions.insert ( StrToFunc ( "c9",clustering_9_example ) );
    functions.insert ( StrToFunc ( "c10",clustering_10_example ) );
    functions.insert ( StrToFunc ( "c11",clustering_11_example ) );
    functions.insert ( StrToFunc ( "c12",clustering_12_example ) );
    functions.insert ( StrToFunc ( "c13",clustering_13_example ) );
    functions.insert ( StrToFunc ( "c14",clustering_14_example ) );
    functions.insert ( StrToFunc ( "da1",discriminant_analysis_1_example ) );
    functions.insert ( StrToFunc ( "da2",discriminant_analysis_2_example ) );
    functions.insert ( StrToFunc ( "da3",discriminant_analysis_3_example ) );
    functions.insert ( StrToFunc ( "da4",discriminant_analysis_4_example ) );
    functions.insert ( StrToFunc ( "da5",discriminant_analysis_5_example ) );

    // match user input with a function name

    if ( argc != 2 || functions.find ( argv[1] ) == functions.end() ) {
        showExamplesHelp();
        return 0;
    }
    map<string,Function>::iterator it = functions.find ( argv[1] );
    //map<string,Function>::iterator it = functions.find ( "c10");
    Function example = it->second;

    // call example asked by user
    try {
        example();
    }
    catch (const XEM::Exception & e) {
        e.run();
        return 1;
    }
    return 0;
}
