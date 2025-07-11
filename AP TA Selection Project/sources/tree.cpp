#include "../includes/tree.hpp"

Tree::Tree(){
}

Tree::~Tree(){
    for(auto i : nodes){
        delete(i.second);
    }
}

void Tree::change_root_name(string name){
    root_name = name;
}

void Tree::add_node(string parent_name, Node* new_node, string new_node_name){
    if(new_node_name != root_name){
        Node* parent = nodes[parent_name];
        parent->add_child(new_node);
    }
    
    nodes[new_node_name] = new_node;
}

bool Tree::investigate(list<string>& names, string cur_node_name){
    Node* cur_node = nodes[cur_node_name];

    if(cur_node->get_type() != ROOT_TYPE){
        if(!cur_node->is_parent_in(names)){
            return false;
        }
    }
    else{
        return cur_node->is_satisfied(names, cur_node->get_children_type());
    }
    
    return cur_node->is_satisfied(names, cur_node->get_children_type()) && investigate(names, cur_node->get_parent_name());
}

void Tree::change_children_type(string parent_name, string new_children_type){
    nodes[parent_name]->change_children_type(new_children_type);
}

bool Tree::does_exist(string name){
    for(auto i : nodes){
        if(i.first == name){
            return true;
        }
    }

    return false;
}