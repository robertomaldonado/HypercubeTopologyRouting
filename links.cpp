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

int main(int argc, char * argv[]){
    //Check arguments for right input
    if ( !isArgCountCorrect ( argc ) ) return 1;
    int n_size = std::stoi(argv[1]);
    if ( !isPowerOfTwo(n_size) ) return 1;
    string routing_model = argv[2];
    if ( !isValidOption(routing_model) ) return 1;

    //Create a vector to hold a binary representation
    vector<int> vector_nodes;
    vector<int> x_ors;
    vector<int> tmp_neighbors;
    map<int, vector<int> > grid;
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
        grid[ vector_nodes[j] ] = tmp_neighbors;
        tmp_neighbors.clear();
    }
    vector_nodes.clear();

    for(auto grid_it = grid.begin(); grid_it != grid.end(); ++grid_it){
        //Print the node id
        bitConversion( log2(n_size), grid_it->first);
        cout << ": ";
        //Print the neighbors
        for(auto nei_it = grid_it->second.begin(); nei_it != grid_it->second.end(); ++nei_it){
            bitConversion( log2(n_size), *nei_it);
            if(nei_it+1 != grid_it->second.end() )
                cout<<" ";
        }
        cout << endl;
    }
    return 0;
}
