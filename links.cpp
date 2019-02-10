#include <iostream>
#import <string.h>
#import <stdlib.h>
#import <math.h>
#import <vector>
#import <map>
#include "checker.h"
#include "transformations.h"

int MAX_PATH = 200;
int MAXZ_PATH_LEN = 200;
int total_nodes;
int bits_for_node;

using namespace std;

int dim_order_routing(int src, int dst, int *path); /* return path length */
int allpath_routing(int src, int dst, int allpath[MAX_PATH][MAXZ_PATH_LEN]); /* return number of paths */
string map_to_bin_str(map<int, vector<int> > &, int);
void create_map(map<int, vector<int> > &);
string int_to_bin_str(int, int);
int factorial(int);
void print_single_route(int, vector<int> &);
void print_multiple_routes( map<int, vector<int> > &);
void recursive_flip( vector<bool>, vector<bool>, vector<bool>);


int main(int argc, char * argv[]){
    //Check arguments for right input
    if ( !isArgCountCorrect ( argc ) ) return 1;
    total_nodes = std::stoi(argv[1]);
    if ( !isPowerOfTwo(total_nodes) ) return 1;
    string routing_model = argv[2];
    if ( !isValidOption(routing_model) ) return 1;
    bits_for_node = log2(total_nodes);

    //Create a vector to hold a binary representation
    map<int, vector<int> > nodes_map;
    create_map( nodes_map );
    printf("%s", map_to_bin_str( nodes_map, total_nodes).c_str() );

    //TO-DO: Get source and destination from the console*/
    int source = 1, destination = 30, path = 10;

    if( routing_model == "dim" ){

        // int len = dim_order_routing(source, destination, &path );
        printf("Dimensional order routing\n");
        while(1){
            printf("input src dst : ");
            cin >> source; cin >> destination; 

            int bits_to_change =  source^destination;

            vector<bool> vector_src = int_to_bin_vector( bits_for_node, source);
            vector<bool> xor_guide = int_to_bin_vector( bits_for_node, bits_to_change);
            vector<int> dim_ord_route;
            int current;
            dim_ord_route.push_back( source );

            for(int i = 0 ; i < xor_guide.size() ; i++){
                if(xor_guide[i]) {
                    vector_src[i] = !vector_src[i];
                    current = bin_vector_to_int( bits_for_node, vector_src);
                    dim_ord_route.push_back( current );
                }
            }
            printf("path from %d to %d: ", source, destination);
            print_single_route(bits_for_node, dim_ord_route);
        
            if( (source > (total_nodes - 1)) ||  (destination > (total_nodes - 1)) ){
                printf( "dim_order_routing: src %d, dst %d, out of bound 0..%d",
                source, destination, total_nodes);
                return 1;
            }
        }

    }else if(routing_model == "all"){

        // int allpath[MAX_PATH][MAXZ_PATH_LEN];
        // int allpath_routing(source, destination, allpath);
        printf("All shortest path routing\n");

        while(1){
            printf("input src dst : ");
            cin >> source; cin >> destination;  

            //XOR to get a get a guide on which bits need to be changed
            int bits_to_change =  source^destination;
            //Convert source and guide to vector of bits
            vector<bool> vector_src = int_to_bin_vector( bits_for_node, source);
            vector<bool> vector_dst = int_to_bin_vector( bits_for_node, destination);
            vector<bool> xor_guide = int_to_bin_vector( bits_for_node, bits_to_change);
            vector<int> all_ord_route;
            //The structure of neighbors is hold in a map.
            //To store here the path for each route found.
            map<int, vector<int> > paths_map;

            int current;
            //The source is the first node
            all_ord_route.push_back( source );
            //For each  bit changed on on the guide, flip the bit
            recursive_flip(vector_src, vector_dst, xor_guide);

            paths_map[ 0 ] = all_ord_route;
            paths_map[ 1 ] = all_ord_route;

            map<int, vector<int> >::iterator it = paths_map.begin();
            int counter = 0;
            for (int i = 0; i < xor_guide.size(); i++ )
                if( xor_guide[i] )
                    counter++;

            printf("%d shortest paths from %d to %d: \n", factorial(counter), source, destination);
            print_multiple_routes(paths_map);

            if( (source > (total_nodes - 1)) ||  (destination > (total_nodes - 1)) ){
                printf( "dim_order_routing: src %d, dst %d, out of bound 0..%d",
                source, destination, total_nodes);
                return 1;
            }
        }
    }
    return 0;
}

void print_multiple_routes( map<int, vector<int> > & mp) {
    for(int k=0; k < mp.size(); k++){ //Print the route
        printf("path %d : ", k);
        print_single_route(bits_for_node, mp[k]);
    }
}

void print_single_route(int bits_for_node, vector<int> &ref_to_route){
    for(int i = 0 ; i < ref_to_route.size() ; i++){
        printf( int_to_bin_str(bits_for_node, ref_to_route[i]).c_str() );
        if( i+1 != ref_to_route.size() )
            printf("->");
        else
            printf("\n");
    }
}

//I am returning the number of the new xor
void recursive_flip( vector<bool> vector_src, vector<bool> vector_dst, vector<bool> current_xor){
    int current;
    vector<bool> vector_original = vector_src;
        //000 to 011
        // 000, 001, 011 //xored is 010
        // 000, 010, 011 //xored is 000
    current = bin_vector_to_int( bits_for_node, vector_src);
    cout << "Currently at node:  " << current << endl;

    int a = bin_vector_to_int(bits_for_node, vector_src);
    int b = bin_vector_to_int(bits_for_node, vector_dst);
    int c = a^b;
    current_xor = int_to_bin_vector(bits_for_node, c);

    if( c == 0 ){
        cout << "Restart.."<<endl;
        a = bin_vector_to_int(bits_for_node, vector_src);
        vector_src = vector_original;
        vector_src = int_to_bin_vector(bits_for_node, 0);
        c = a^b;
        current_xor = int_to_bin_vector(bits_for_node, c);
    }

    for(int i = 0 ; i < current_xor.size() ; i++){

        if(current_xor[i]) { //If the bits need to be flipped
                // current = bin_vector_to_int( bits_for_node, vector_src);
                // cout << "..." << current << endl;
                // current = bin_vector_to_int( bits_for_node, vector_src);
                // cout << "Currently at node:  " << current << endl;

                // int a = bin_vector_to_int(bits_for_node, vector_src);
                // int b = bin_vector_to_int(bits_for_node, vector_dst);
                // int c = a^b;
                // current_xor = int_to_bin_vector(bits_for_node, c);

                vector_src[i] = !vector_src[i]; //Flip a bit
                current = bin_vector_to_int( bits_for_node, vector_src);

                cout << "Hop to node:  " << current << endl << endl;
                // recursive_flip(vector_src, vector_dst, current_xor);
                
        }
                // recursive_flip(vector_src, vector_dst, current_xor);     
    }
}

int factorial(int n){
    int fact = 1;
    while( n>0 ){
      fact = fact*n;
      n--;
    }
    return fact;
}

int dim_order_routing( int source, int destination, int *path ){
    int length = 10;
    return length;
}

// Receives ref  to the map, and the size
// Creates the map by reference 
void create_map(  map<int, vector<int> > &nodes_map){

    vector<int> vector_nodes;
    vector<int> x_ors;
    vector<int> tmp_neighbors;

    //Initialize the vector for nodes
    for(int i=0; i < total_nodes; i++)
        vector_nodes.push_back(i);
    //Initialize the bits to Xor against
    int last_bit = 1;
    for(int i=0; i < bits_for_node; i++){
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