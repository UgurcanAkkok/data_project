#include "murmurFunction.hpp"

#include <string>
#include <iostream>
using namespace std;
int main(){
    std::string key = "5A512";
    uint64_t *hash = new uint64_t[2];
    murmur(key.c_str(), key.length(), rand(), hash);
    cout << hash[0] << endl;
    cout << hash[1] << endl;
}

