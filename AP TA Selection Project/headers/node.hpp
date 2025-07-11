#pragma once
#include "global.hpp"

class Node{
    private:
        string type;
        string children_type;
        string name;
        string parent_name;
        vector<Node*> children;

        bool is_satisfied_or(list<string>& names);
        bool is_satisfied_xor(list<string>& names);
        bool is_satisfied_combination(list<string>& names);

    public:
        Node(string init_name, string init_type, string init_parent_name, string init_children_type = NO_CHILD);
        void add_child(Node* child);
        bool is_satisfied(list<string>& names, const string& type);
        bool is_parent_in(list<string>& names);

        string get_type();
        string get_children_type();
        string get_parent_name();

        void change_children_type(string new_children_type);
};