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

// these constants help in performing the search routine on the Delhi Metro Map
const int WHITE = -1;
const int GRAY = 0;
const int BLACK = 1;

// this constant is used in forming the parent child relationships, initially no vertex has a
// parent hence this is helpful in initialization step
const int PARENT = -1;

// one can set these variables for performing searches
int sourceVertex = 5;
int destinationVertex = 26;

// this structure is used to model the a Node that will be used in forming the adjacency list
// of the graph, which is used to store the adjacency information of the vertices in the graph
struct GraphNode{

    // this variable stores the vertex which is adjacent to the vertex in whose list we insert
    // this node
    int adjacentVertex;

    // this variable is a pointer to a GraphNode type which is helpful in forming the adjacency
    // list of the graph and points to the node that succeeds this node in the list
    struct GraphNode *next;
};

// this structure is used to model the graph data type that we will be using to model the Metro
// Rail Map.
struct Graph{

    // this variable will store the number of vertices in the graph, which corresponds to the
    // number of stations in the Delhi Metro Map
    int nVertices;

    // this variable stores the number of edges in the graph, which corresponds to the number
    // of links amongst stations in the Delhi Metro Map
    int nEdges;

    // this double pointer will be used in forming the adjacency list for the graph, which is used
    // to store the adjacecny information of stations in the Delhi Metro Map
    struct GraphNode **adjacencyList;

    // this pointer will be used to store the color of the vertex in the graph at any point
    // during the search procedure operates on the graph
    int *color;

    // this pointer will be used to store the ancestor and descendant relationships amongst
    // stations in Delhi Metro Map
    int *parent;
};

// this is the global graph variable that will be used to store the Delhi Metro Map, its made
// global so that its available to all the other functions that require it for performing computations
struct Graph *G = NULL;

// this is the basic functions that does all the initialization operations before beginning the
// search operation like allocating memory to the graph and forming the adjacency list for the
// Delhi Metro Map
int basicFunc(int nVertices , int nEdges);

// this function is used to form the links in the Delhi Metro Map, by inserting an edge between
// station1 and station2 and hence forming the adjacency list of the graph
int insertEdge(int vertex1 , int vertex2 , bool graphType);

// this function is used to display the Delhi Metro Map
int displayGraph();

// this function is used to return the name of the station
string returnStationName(int vertex);

// this function is used to search the Delhi Metro Map for the shortest route, what this search
// procedure does is a Breadth First Search traversal of the Delhi Metro Map and hence used to form
// the Breadth First Tree which gives the shortest route from a source vertex to a destination vertex
int doBFS();

int main(){

    // this function will be used to scan the Delhi Metro Map from a file on the disk, one can
    // change the path inside the function to the location where one downloads the file on his/her
    // system
    freopen("/home/ankit/Desktop/Programming in C++/Delhi Metro Search Application/MetroMap.txt" , "rb" , stdin);

    // this function is used to write the results of the search operation to a specified file on
    // the disk, one can change the location in the function to any other file on one's disk, if
    // one desires
    freopen("/home/ankit/Desktop/Programming in C++/Delhi Metro Search Application/MetroMapResults.txt" , "wb" , stdout);

    // this variable stores the number of stations in the Delhi Metro Map
    int nVertices;
    cin >> nVertices;

    // this variable stores the number of links among stations in the Delhi Metro Map
    int nEdges;
    cin >> nEdges;

    // perform the basic initialization operations
    basicFunc( nVertices , nEdges );

    return 0;
}

int basicFunc(int nVertices , int nEdges){

    // the first thing to do is to allocate memory to the graph
    G = ( struct Graph * ) malloc ( sizeof( Graph ) );

    // now assign values to the attributes of the graph
    (G -> nVertices)     = nVertices;
    (G -> nEdges   )     = nEdges   ;
    (G -> parent   )     = ( int * ) malloc ( sizeof( int ) * nVertices );
    (G -> color   )     =  ( int * ) malloc ( sizeof( int ) * nVertices );
    (G -> adjacencyList) = NULL;

    for(int i = 0 ; i < nVertices ; ++i){

        // as all vertices in the graph initially have no parent at all
        (G -> parent[ i ]) = PARENT;

        // as we haven't yet explored any vertex we color the vertices white
        (G -> color[ i ] ) = WHITE;
    }

    // let us now allocate memory for the adjacency list of the graph
    (G -> adjacencyList) = ( struct GraphNode ** ) malloc ( sizeof( struct GraphNode * ) * nVertices );

    // as no adjacency relations have been established yet we initialize all adjacency lists to
    // NULL
    for(int i = 0 ; i < nVertices ; ++i)
        (G -> adjacencyList[ i ]) = NULL;

    // now we starting inserting the edges in the graph to form the adjacency list of the graph
    // these 2 vertex variables correspond to the 2 stations in the Delhi Metro Map between which
    // we want to insert a link
    int vertex1 , vertex2;

    for(int i = 0 ; i < nEdges ; ++i){

        // scan the 2 stations from the file
        cin >> vertex1 >> vertex2;

        // now call the insertEdge function to insert the edge in the graph and we indicate that
        // the graph is undirected
        insertEdge( vertex1 , vertex2 , true);
    }

    cout <<"The route from " << returnStationName( sourceVertex ) << " to " << returnStationName( destinationVertex ) << " is as follows : \n\n";

    // perform the Breadth First Search Procedure on the Graph
    doBFS();

    int tempVertex = destinationVertex;

    // this vector stores the route vector from the source to destination vertex
    vector< string > routeVector;

    routeVector.PB( returnStationName( destinationVertex ) );

    while( G -> parent[ tempVertex ] != PARENT ){

        routeVector.PB( returnStationName( G -> parent[ tempVertex ] ) );
        tempVertex = G -> parent[ tempVertex ];
    }

    // reverse the route vector
    reverse( ALL( routeVector ) );

    for(int i = 0 ; i < SZ( routeVector ) - 1 ; ++i)
        cout << routeVector[ i ] << " - ";

    cout << routeVector[ SZ( routeVector ) - 1 ] << endl;
}

int insertEdge(int vertex1 , int vertex2 , bool graphType){

    // this temporary pointer will be used to insert a node in vertex1's adjacency list
    struct GraphNode *temp = (struct GraphNode * ) malloc ( sizeof( struct GraphNode ) );

    (temp -> adjacentVertex)          = vertex2;
    (temp -> next          )          = (G -> adjacencyList[ vertex1 ]);
    (G -> adjacencyList[ vertex1 ])   = temp;

    // as the graph is undirected we need to call insertEdge once more
    if( graphType )
        insertEdge(vertex2 , vertex1 , false);
}

int doBFS(){

    // as we have a source vertex we begin our search from this source vertex and hence color
    // the source vertex GRAY as we have discovered this vertex during our search
    G -> color[ sourceVertex ] = GRAY;

    // this queue actually represents the frontier between discovered and undiscovered vertices
    // during the search
    queue< int > searchQueue;

    // enqueue the source vertex to the search queue
    searchQueue.push( sourceVertex );

    while( !searchQueue.empty() ){

        // dequeue the element from the front of the queue
        int dequeuedVertex = searchQueue.front();

        // scan this dequeuedVertex's adjacency list
        struct GraphNode * temp = G -> adjacencyList[ dequeuedVertex ];

        while( temp != NULL ){

            if( G -> color[ temp -> adjacentVertex ] == WHITE ){

                // change the color and parent of the adjacent vertex
                G -> color[ temp -> adjacentVertex ] = GRAY;
                G -> parent[ temp -> adjacentVertex ] = dequeuedVertex;

                // enqueue this vertex to the queue
                searchQueue.push( temp -> adjacentVertex );
            }

            temp = temp -> next;
        }

        G -> color[ dequeuedVertex ] = BLACK;

        // remove the vertex from the head of the queue
        searchQueue.pop();
    }
}

int displayGraph(){

    for(int i = 0 ; i < (G -> nVertices) ; ++i){

        // this temporary pointer is used for scanning the adjacency list
        struct GraphNode *temp = G -> adjacencyList[ i ];

        cout << returnStationName( i ) << " --> ";

        while( temp != NULL ){
            cout << returnStationName( temp -> adjacentVertex ) << " -> ";
            temp = temp -> next;
        }

        cout << endl;
    }
}

string returnStationName(int vertex){

    switch( vertex ){

        case 0 :
            return "Mundka";
        break;

        case 1:
            return "Rajdhani Park";
        break;

        case 2:
            return "Nangloi Railway Station";
        break;

        case 3:
            return "Nangloi";
        break;

        case 4:
            return "Surajmal Stadium";
        break;

        case 5:
            return "Udyog Nagar";
        break;

        case 6:
            return "Peera Garhi";
        break;

        case 7:
            return "Paschim Vihar West";
        break;

        case 8:
            return "Paschim Vihar East";
        break;

        case 9:
            return "Madipur";
        break;

        case 10:
            return "Shivaji Park";
        break;

        case 11:
            return "Punjabi Bagh";
        break;

        case 12:
            return "Ashok Park Main";
        break;

        case 13:
            return "Inderlok";
        break;

        case 14:
            return "Rithala";
        break;

        case 15:
            return "Rohini West";
        break;

        case 16:
            return "Rohini East";
        break;

        case 17:
            return "Pitam Pura";
        break;

        case 18:
            return "Kohat Enclave";
        break;

        case 19:
            return "Netaji Subhash Place";
        break;

        case 20:
            return "Keshav Puram";
        break;

        case 21:
            return "Kanhaiya Nagar";
        break;

        case 22:
            return "Shastri Nagar";
        break;

        case 23:
            return "Pratap Nagar";
        break;

        case 24:
            return "Pulbangash";
        break;

        case 25:
            return "Tishazari";
        break;

        case 26:
            return "Kashmere Gate";
        break;

        case 27:
            return "Shastri Park";
        break;

        case 28:
            return "Seelampur";
        break;

        case 29:
            return "Welcome";
        break;

        case 30:
            return "Shahdara";
        break;

        case 31:
            return "Mansarover Park";
        break;

        case 32:
            return "Jhilmil";
        break;

        case 33:
            return "Dilshad Garden";
        break;

        default:
        break;
    }
}
