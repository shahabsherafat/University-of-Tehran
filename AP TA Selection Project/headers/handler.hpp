#pragma once
#include "tree.hpp"

class Handler{
    private:
        Tree* coffee_maker;
        string find_node_type(string line);

    public:
        Handler(Tree* init_coffee_maker);
        void get_descriptions();
        void validate_configs();

};