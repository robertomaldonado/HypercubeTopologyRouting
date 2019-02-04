#include <iostream>
#import <math.h>
#import <vector>
#import <map>
#include "checker.h"

using namespace std;

int isArgCountCorrect(int arg_count){
    if (arg_count != 3){
        cout << "Usage: ./executable Nsize [dim|all]" << endl;
        return 0;
    }else{
        return 1;
    }
}

int isPowerOfTwo(int n_size){

    if ( (ceil(log2(n_size)) == floor(log2(n_size))) ){
        return 1;
    }else{
        cout << "Error: Nsize must be a power of 2 for hypercube." << endl;
        return 0;
    }
}

int isValidOption(string routing_model){

    if ( routing_model.compare("dim") == 0 || routing_model.compare("all") == 0  ){
        return 1;
    }else{
        cout << "Usage: ./executable Nsize [dim|all]" << endl;
        return 0;
    }
}