#pragma once
#include "node.hpp"

class Tree{
    private:
        map<string, Node*> nodes;
        string root_name;

    public:
        Tree();
        ~Tree();
        string get_root_name();
        bool investigate(list<string>& names, string cur_node_name);
        void add_node(string parent_name, Node* new_node, string new_node_name);
        void change_root_name(string name);

        void change_children_type(string parent_name, string new_children_type);
        bool does_exist(string name);
};