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

// this variable is used as a sentinel card
const double sentinel = 1e+7;

// this function is used to display the array elements at any point of time, *numbers - represents the array of numbers and the size represents
// the size of the array
void displayArray(double *numbers , int size){

     cout << "The elements of the array are as follows -: " << endl;

     for(int i = 0 ; i < size ; ++i)
             cout << numbers[ i ] << " ";

     cout << endl;
}

// this function is used to perform the merge operation which is used to merge the 2 sorted subarrays
int doMerge( double *numbers , int startIndex , int midIndex , int endIndex ){

    // as the merge procedure relies on auxiliary arrays we first need to evaluate the size of these auxiliary arrays
    int numbersOneSize = midIndex - startIndex + 1;
    int numbersTwoSize = endIndex - midIndex;

    // these are the 2 sorted subarrays that need to be merged, a 1 has been added to the size to place the sentinel card
    double left[ numbersOneSize + 1 ] , right[ numbersTwoSize + 1 ] ;

    // assign sentinels to last locations
    left[ numbersOneSize ] = right[ numbersTwoSize ] = sentinel;

    // form the 2 subarrays
    for(int i = 0 ; i < numbersOneSize ; ++i)
            left[ i ] = numbers[ startIndex + i ];

    for(int i = 0 ; i < numbersTwoSize ; ++i)
            right[ i ] = numbers[ midIndex + i + 1 ];


    // pointers used in traversing the two sorted subarrays
    int i = 0 , j = 0 ;

    for(int k = startIndex ; k <= endIndex ; ++k){

            if( left[ i ] <= right[ j ] ){
                numbers[ k ] = left[ i ];
                ++i;
            }

            else{
                 numbers[ k ] = right[ j ];
                 ++j;
            }
    }
}

// this function is used to execute the MergeSort algorithm
int doMergeSort( double *numbers , int startIndex , int endIndex ){

    // we only sort the numbers when the starting index is less than or equal to ending index
    if( startIndex < endIndex ){

        // this variable is used to calculate the mid-point of the array
        int midIndex = ( startIndex + endIndex )/2;

        // these 2 calls are the recursive calls in the merge sort algorithm
        doMergeSort( numbers , startIndex , midIndex );
        doMergeSort( numbers , midIndex + 1 , endIndex);

        // this call to doMerge actually arranges the 2 sorted subarrays into a single sorted array
        doMerge( numbers , startIndex , midIndex , endIndex );
    }

    return 0;
}

int main(){

    // this variable stores the number of numbers we will have in our array to sort
    int num;

    cout << "Please enter the size of the array that you want to sort : ";
    cin >> num;

    // this is the array that is used to store the numbers to be sorted, for the sake of simplicity we assume the numbers to be of type "double"
    double numbers[ num ];

    // enter the numbers that constitute the array
    cout << "\nPlease start entering the numbers that constitute the array!!!" << endl;

    for(int i = 0 ; i < num ; ++i){
            cout << "Please enter element number " << i+1 << " : ";
            cin >> numbers[ i ];
    }

    // display the array entered by the user
    displayArray( numbers , num );

    // call the merge sort procedure to sort the array
    doMergeSort( numbers , 0 , num - 1 );

    cout << "After Sorting ";
    // after calling merge sort display the array in sorted order
    displayArray( numbers , num );

    getchar();

    return 0;
}
