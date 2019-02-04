#ifndef CHECKER_H_INCLUDED
#define CHECKER_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>


std::string map_to_bin_str(std::map<int, std::vector<int> > &nodes_map , int n_size);

// Receives the bits needed and an integer value to convert
// Returns string in format #(000...) 
std::string int_to_bin_str(int bit_size, int node);

std::vector<bool> int_to_bin_vector(int bit_size, int node);
std::string int_to_bin_str(int bit_size, int node);

#endif // CHECKER_H_INCLUDED