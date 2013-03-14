// I/O Includes

#include<new>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<strstream>

// Data Structure Includes

#include<map>
#include<set>
#include<list>
#include<stack>
#include<deque>
#include<queue>
#include<vector>
#include<bitset>
#include<string>
#include<iterator>
#include<algorithm>

// Standard Namespace Inclusion

using namespace std;

// Supporting Macros

#define SZ( C )                 ( ( int ) ( ( C ).size() ) )
#define ALL( C )                ( C ).begin() , ( C ).end()
#define TR( C , it )            for( typeof( ( C ).begin() ) it = ( C ).begin(); it != ( C ).end() ; ++it )
#define LN( STRING )            ( ( int ) ( STRING ).length() )
#define SPRESENT( C , x )       ( ( ( C ).find( x ) ) != ( C ).end() )
#define CPRESENT( C , x )       ( find( ALL( C ) , x ) != ( C ).end() )
#define PB                      push_back

// Typedefed Versions of Data Types

typedef vector< int > VI;
typedef vector< VI > VVI;
typedef vector< string > VS;
typedef pair< int ,int > PII;
typedef long long LL;
typedef unsigned long long ULL;

int main(){

    // this file is used to scan the input for the algorithm
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 1/Programming Assignment 6/HashInt.txt" , "rb" ,stdin);

    // this file is used to dump the output of the algorithm
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 1/Programming Assignment 6/HashIntAnswer.txt" , "wb" ,stdout);

    // we maintain a set of elements so that there is no repetition
    set< long > elements;

    // this temporary long variable is used to scan the elements from the file
    long temp;

    while( scanf("%ld" , &temp) != -1 )
        elements.insert( temp );

    // this is a vector that is used to hold the elements in the set without repetition
    vector< long > setElements( ALL( elements ) );

    // sort all the elements of the vector
    sort( ALL( setElements ) );

    // this variable is used to store the number of target values
    int nTargetValues = 0;

    for(int i = 2500 ; i <= 4000 ; ++i){

        // a carful analysis of the sorted data set yields us this result
        for(int j = 0 ; j <= 203 ; ++j){

            if( binary_search( setElements.begin() + j + 1 , setElements.begin() + 203 , i - setElements[ j ] ) ){
                ++nTargetValues;
                break;
            }
        }
    }

    cout << "The number of target values are : " << nTargetValues << endl;

    return 0;
}
