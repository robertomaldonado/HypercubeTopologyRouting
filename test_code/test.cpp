#include <iostream>
#import <string.h>
#import <stdlib.h>
#import <math.h>
#import <vector>
#import <map>

using namespace std;

int bin_vector_to_int(int bit_size, vector<bool >node){
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
    vector<bool> node_bits;
    string output_str = "";
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

    // output_str += ")";

    return node_bits;
}

int main(int argc, char * argv[]){
    int i = 0;
    int src = 0;
    int dst = 6;
    int bits_to_change = 0;
    bits_to_change =  src^dst;

    vector<bool> vector_src =  int_to_bin_vector( 3, src);
    vector<bool> xor_guide =  int_to_bin_vector( 3, bits_to_change);
    vector<int> dim_ord_route;

    int bit_count = 0;
    int current = 0;
    dim_ord_route.push_back( src );
    for(int i = 0 ; i < xor_guide.size() ; i++){
        
        cout<< std::to_string(xor_guide[i]);
        if(xor_guide[i]) {
            bit_count++;
            vector_src[i] = !vector_src[i];
            current = bin_vector_to_int( 3, vector_src);
            // cout << "storing: " << current<<endl;
            dim_ord_route.push_back( current );
        }

    }
    cout << endl;
    // cout << "Different bits count: " << bit_count << endl;
    // cout << bits_to_change <<endl;

    cout << "Route: " << endl;
    for(int i = 0 ; i < dim_ord_route.size() ; i++){
        cout << dim_ord_route[i];
    }

    // int number = bin_vector_to_int(3, vector_src);
    // cout << "My tranaslated number is: "<< number << endl;
    return 0;
}

