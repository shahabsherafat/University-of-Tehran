#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include "orders_implementation.hpp"
#include "Carwash.hpp"

using namespace std;

int main(int argc, char* addresses[3]){
    ifstream stages_file(addresses[1]);
    ifstream workers_file(addresses[2]);
    Carwash cw;
    cw.assign_stages(stages_file);
    cw.assign_workers(workers_file);
    get_and_implement_orders(cw);
    return 0;
}