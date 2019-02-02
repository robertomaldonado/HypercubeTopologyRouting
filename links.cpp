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

    return 0;
}

std::string map_to_bin_str(map<int, vector<int> > &nodes_map , int n_size){
    int bit_size = log2(n_size); //Stores how many bits long is each node 
    string output = "";
    //For each node in the map, print it with the corresponding neighbors
    for(std::map<int,vector<int> >::iterator nodes_map_it = nodes_map.begin(); nodes_map_it != nodes_map.end(); ++nodes_map_it){
        //Print the current node in binary
        output += int_to_bin_str( bit_size, nodes_map_it->first);
        output += ": ";
        //Print the neighbors in binary of the current node
        for( std::vector<int>::iterator nei_it = nodes_map_it->second.begin(); nei_it != nodes_map_it->second.end(); ++nei_it){
            output += int_to_bin_str( bit_size, *nei_it);
            if(nei_it+1 != nodes_map_it->second.end() )
                output += " ";
        }
        output += "\n";
    }
    return output;
}

string int_to_bin_str(int bit_size, int node){
    int tmp_count = 0;
    vector<bool> node_bits;
    string output_str = "";
    output_str += std::to_string(node) + "(";
    //Keep adding the bits based on the parity of bits
    while(node != 0){
        if( (node % 2) == 0 ){
            node_bits.push_back(0); node = floor(node/2);
        }else{
            node_bits.push_back(1); node = floor(node/2);
        }
    }
    //Push into the vector of node_bits
    tmp_count = node_bits.size();
    while(  tmp_count < bit_size ){
        node_bits.push_back(0);
        tmp_count++;
    }
    //Add the bits to the output string
    for(int i = node_bits.size()-1; i >= 0; i--)
        output_str += std::to_string(node_bits[i]);
    output_str += ")";

    return output_str;
}

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