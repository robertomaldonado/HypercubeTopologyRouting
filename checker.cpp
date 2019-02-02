#include <iostream>
#import <math.h>
#import <vector>
#import <map>
#include "checker.h"

using namespace std;

int argCorrect(int arg_count){
    return arg_count <= 1 ? 0 : 1;
}

void bitConversion(int bit_size, int node){
    vector<bool> node_bits;
    cout << node << "(";
    while(node != 0){
        if( (node % 2) == 0 ){
            node_bits.push_back(0);
            node = floor(node/2);
        }else{
            node_bits.push_back(1);
            node = floor(node/2);
        }
    }
    int my_var = node_bits.size();
    while(  my_var < bit_size){
        node_bits.push_back(0);
        my_var++;
    }
    for(int i = node_bits.size()-1; i >= 0; i--)
        cout << node_bits[i];

    cout << ")";
}