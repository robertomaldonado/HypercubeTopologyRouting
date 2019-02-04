#include <iostream>
#import <string.h>
#import <stdlib.h>
#import <math.h>
#import <vector>
#import <map>
#include "checker.h"

int MAX_PATH = 200;
int MAXZ_PATH_LEN = 200;

using namespace std;

int dim_order_routing(int src, int dst, int *path); /* return path length */
int allpath_routing(int src, int dst, int allpath[MAX_PATH][MAXZ_PATH_LEN]); /* return number of paths */
string map_to_bin_str(map<int, vector<int> > &, int);
void create_map(map<int, vector<int> > &, int);
string int_to_bin_str(int, int);

int main(int argc, char * argv[]){
    //Check arguments for right input
    if ( !isArgCountCorrect ( argc ) ) return 1;
    int n_size = std::stoi(argv[1]);
    if ( !isPowerOfTwo(n_size) ) return 1;
    string routing_model = argv[2];
    if ( !isValidOption(routing_model) ) return 1;

    //Create a vector to hold a binary representation
    map<int, vector<int> > nodes_map;
    create_map( nodes_map , n_size);
    
    cout << map_to_bin_str( nodes_map, n_size);

    //TO-DO: Get source and destination from the console*/
    int source = 1;
    int destination = 6;
    int path = 10;

    if( routing_model == "dim" ){

        int len = dim_order_routing(source, destination, &path );
        cout<<"Dimensional order routing" <<endl;
        cout<< "input src dst : ";

        if( (source > (n_size - 1)) ||  (destination > (n_size - 1)) ){
            cout<<"dim_order_routing: src " << source << ", dst " << destination;
            cout << ", out of bound 0.."<< n_size << endl;
        }
    }else if(routing_model == "all"){

        // int len = dim_order_routing(source, destination, &path );
        // int allpath[MAX_PATH][MAXZ_PATH_LEN];
        // int allpath_routing(source, destination, allpath);
        cout<<"All shortest path routing" <<endl;
        cout<< "input src dst : ";

        if( (source > (n_size - 1)) ||  (destination > (n_size - 1)) ){
            cout<<"dim_order_routing: src " << source << ", dst " << destination;
            cout << ", out of bound 0.."<< n_size << endl;
        }
    }

    return 0;
}

int dim_order_routing( int source, int destination, int *path ){
    int length = 10;
    return length;
}

// Receives ref  to the map, and the size
// Creates the map by reference 
void create_map(  map<int, vector<int> > &nodes_map , int n_size){

    vector<int> vector_nodes;
    vector<int> x_ors;
    vector<int> tmp_neighbors;

    //Initialize the vector for nodes
    for(int i=0; i < n_size; i++)
        vector_nodes.push_back(i);
    //Initialize the bits to Xor against
    int last_bit = 1;
    for(int i=0; i < log2(n_size); i++){
        x_ors.push_back(last_bit);
        last_bit = last_bit << 1;
    }
    //For each node, get the neighbors
    for(int j=0; j < vector_nodes.size(); j++){
        //Generate the neighbors
        for(int i=0; i < x_ors.size(); i++)
            tmp_neighbors.push_back( vector_nodes[j]^x_ors[i] );
        //Add node and neigborg to map
        nodes_map[ vector_nodes[j] ] = tmp_neighbors;
        tmp_neighbors.clear();
    }
    vector_nodes.clear();
    x_ors.clear();
}