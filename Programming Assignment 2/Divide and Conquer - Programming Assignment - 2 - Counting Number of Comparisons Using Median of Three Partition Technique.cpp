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
#include<list>Ķ
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

// Supporting Macro

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

// this variable stores the number of comparisons that happen while the execution of the quick sort
// routine
int quickSortComparisons = 0;

// this function is used to display the array elements at any point of time, *numbers - represents the array of numbers and the size represents
// the size of the array
void displayArray(double *numbers , int size){

     cout << "The elements of the array are as follows -: " << endl;

     for(int i = 0 ; i < size ; ++i)
             cout << numbers[ i ] << endl;

     cout << endl;
}

// this function implements the partition routine used by quick sort to put the pivot element
// in its rightful position, we pass the left and the right indices of the array which
// delineate the boundaries of the array, this will return the index i which is the rightful
// position of the pivot element so that we can sort the 2 subarrays recursively namely
// 0 to i-1 and i+1 to n
int partitionArray(double *numbers , int leftIndex , int rightIndex){

    // as a pre-processing step we need to choose the median element of the array as the pivot
    // element

    // this variable stores the length of the subarray that we need to partition
    int length = rightIndex - leftIndex + 1;

    // make a vector of pairs to store the 3 elements, which stores pairs of the form
    // < number , index >
    vector< pair< double , int > > elems;

    elems.PB( make_pair( numbers[ leftIndex ] , leftIndex ) );

    if( length % 2 != 0 )
        elems.PB( make_pair( numbers[ leftIndex + length/2 ] , leftIndex + length/2 ) );
    else
        elems.PB( make_pair( numbers[ leftIndex + (length/2 - 1) ] , leftIndex + (length/2 - 1) ) );

    elems.PB( make_pair( numbers[ rightIndex ] , rightIndex ) );

    // sort the vector of pairs to obtain the sandwiched item value
    sort( ALL( elems ) );

    // swap the respective values
    swap( numbers[ leftIndex ] , numbers[ elems[ 1 ].second ] );

    elems.clear();

    // using the simplest pivot choosing technique we choose the first element of the array
    // as the pivot element
    double pivot = numbers[ leftIndex ];

    // now we choose 2 pointers that help in partitioning  the array, i - will keep track of the
    // correct position where the pivot element will be stored and j is used for scanning through
    // the array
    int i , j;

    // assign i to one position more than the pivot index
    i = leftIndex + 1;

    for(j = leftIndex + 1 ; j <= rightIndex ; ++j){

        // we only swap the elements of the array if the element is less than the pivot
        if( numbers[ j ] < pivot ){
            swap( numbers[ i ] , numbers[ j ] );
            ++i;
        }
    }

    // now swap the pivot element with the first element
    if( i != leftIndex + 1 )
        swap( numbers[ leftIndex ] , numbers[ i - 1 ] );

    return i - 1;
}

// this is the quick sort procedure used to sort the array of double numbers we pass the size of
// the array as a parameter to th function
int quickSort(double *numbers , int leftIndex , int pivotIndex , int rightIndex){

    if( leftIndex >= rightIndex )
        return 0;

    // this variable stores the index where the pivot element will be stored after the partitioning
    // takes place
    int tempPivotIndex = partitionArray(numbers , leftIndex , rightIndex);

    quickSortComparisons += ( tempPivotIndex - 1 - leftIndex ) + ( rightIndex - tempPivotIndex + 1 );

    // recursively sort the 2 subarrays
    quickSort(numbers , leftIndex , leftIndex , tempPivotIndex - 1);
    quickSort(numbers , tempPivotIndex + 1 , tempPivotIndex + 1 , rightIndex);

}

int main(){

    // this file is used to scan the numbers to be sorted
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 1/Programming Assignment 2/QuickSort.txt" , "rb", stdin);

    // this file is used to dump the output in sorted order
    freopen("/home/ankit/Desktop/Coursera Courses/Design and Analysis of Algorithms - Part 1/Programming Assignment 2/QuickSortAnswer3.txt" , "wb", stdout);

    // this is the array that is used to store the numbers to be sorted, for the sake of simplicity we assume the numbers to be of type "double"
    int num = 10000;
    double numbers[ num ];

    // store the numbers that constitute the array
    for(int i = 0 ; i < num ; ++i){
            cin >> numbers[ i ];
    }

    // here we call the quick sort function to sort the array elements
    quickSort( numbers , 0 , 0 , num - 1 );

    cout << "The number of comparisons are using the first element as pivot is : " << quickSortComparisons << endl;

    return 0;
}
