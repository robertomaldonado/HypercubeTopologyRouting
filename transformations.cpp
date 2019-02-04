#include <iostream>
#import <math.h>
#import <vector>
#import <map>
#include "transformations.h"

std::string map_to_bin_str(std::map<int, std::vector<int> > &nodes_map , int n_size){
    int bit_size = log2(n_size); //Stores how many bits long is each node 
    std::string output = "";
    //For each node in the map, print it with the corresponding neighbors
    for(std::map<int,std::vector<int> >::iterator nodes_map_it = nodes_map.begin(); nodes_map_it != nodes_map.end(); ++nodes_map_it){
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

// Receives the bits needed and an integer value to convert
// Returns string in format #(000...) 
std::string int_to_bin_str(int bit_size, int node){
    int tmp_count = 0;
    std::vector<bool> node_bits;
    std::string output_str = "";
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

int bin_vector_to_int(int bit_size, std::vector<bool >node){
    int translated_node = 0;
    // cout << "Began translation..."<<endl;
    for(int i=0; i < node.size(); i++){
        // cout << pow(2, i) * node[i] << endl;
        translated_node += pow(2, i) * node[i];
    }
    return translated_node;
}

std::vector<bool> int_to_bin_vector(int bit_size, int node){

    int tmp_count = 0;
    std::vector<bool> node_bits;
    std::string output_str = "";
    // output_str += std::to_string(node) + "(";
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

    return node_bits;
}