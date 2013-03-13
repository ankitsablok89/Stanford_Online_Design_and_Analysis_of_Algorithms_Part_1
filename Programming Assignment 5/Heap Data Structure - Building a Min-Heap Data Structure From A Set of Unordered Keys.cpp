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

// this function is used to display the array contents at any point of time
void display(int *elements , int size);

// this function is used to return the parent of any node with index i
inline int returnParent(int i){ return i/2; }

// this function is used to return the left child of any node at index i in the heap
inline int returnLeft(int i){ return 2*i; }

// this function is used to return the right child of any node at index i in the heap
inline int returnRight(int i){ return 2*i + 1; }

// this function is used to restore the min-heap property in the heap data structure represented
// as an array, it accepts an index element i which may or may not violate the min-heap property
int restoreMinHeapify(int *elements , int size , int i);

// this function is used to build a max-heap from an unordered set of array elements
int buildMinHeap(int *elements , int size);

int main(){

    // this variable stores the number of elements that one wants to sort using heapsort
    int nElements;
    cout << "Enter the number of elements that you want to build a min-heap from : ";
    cin >> nElements;

    // this array is used to store the elements that one needs to sort using the heapsort algorithm
    int elements[ nElements + 1 ];

    for(int i = 1 ; i < nElements + 1 ; ++i){

        cout << "Please enter element number " << i << " : ";
        cin >> elements[ i ];

    }

    cout << "The elements of the array as entered by the user are as follows : ";
    // display the array contents
    display(elements , nElements + 1);

    // we call this function to build the min-heap data structure
    buildMinHeap(elements , nElements + 1);

    return 0;
}

void display(int *elements , int size){

    for(int i = 1 ; i < size ; ++i)
        cout << elements[ i ] << " ";

    cout << endl << endl;
}

int restoreMinHeapify(int *elements , int size , int i){

    // first we isolate the indexes of the left and right child of nodes in the heap
    int left = returnLeft(i);
    int right = returnRight(i);

    // as we are building a min-heap we want to keep track of the minimum element at every point
    int smallest;

    if( left < size && elements[ left ] < elements[ i ] )
        smallest = left;
    else
        smallest = i;

    if( right < size && elements[ right ] < elements[ smallest ] )
        smallest = right;

    if( smallest != i ){

        // swap the elements in the two indexes
        swap( elements[ i ] , elements[ smallest ] );

        // as the element that we have swapped might in turn violate the max-heap property in
        // successive subtrees we make a recursive call to max-heapify
        restoreMinHeapify(elements , size , smallest);
    }
}

int buildMinHeap(int *elements , int size){

    // we try building the heap from the array elements in a bottom up manner making n/2 calls to
    // restore max-heapify procedure which maintains the invariant that every node from index
    // i/2 + 1 , i/2 + 2 , ..... is a node of a max-heap

    for(int i = size/2 ; i >= 1 ; --i)
        restoreMinHeapify(elements , size , i);

    cout << "The elements of the array after the build max heap operation : ";
    display(elements , size);

}
