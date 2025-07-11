#include "../includes/node.hpp"

Node::Node(string init_name, string init_type, string init_parent_name, string init_children_type){
    name = init_name;
    type = init_type;
    children_type = init_children_type;
    parent_name = init_parent_name;
}

string Node::get_type(){
    return type;
}

string Node::get_children_type(){
    return children_type;
}

string Node::get_parent_name(){
    return parent_name;
}

void Node::add_child(Node* child){
    children.push_back(child);
}

bool Node::is_satisfied_combination(list<string>& names){
    for(Node* child : children){
        if(child->type == MANDATORY_TYPE){
            if(find(names.begin(), names.end(), child->name) == names.end()){
                return false;
            }
        }
    }

    return true;
}

bool Node::is_satisfied_or(list<string>& names){
    for(Node* child : children){
        if(find(names.begin(), names.end(), child->name) != names.end()){
            return true;
        }
    }

    return false;
}

bool Node::is_satisfied_xor(list<string>& names){
    bool flag = false;

    for(Node* child : children){
        if(find(names.begin(), names.end(), child->name) != names.end()){
            if(flag)
                return false;
            else
                flag = true;
        }
    }

    return flag;
}

bool Node::is_satisfied(list<string>& names, const string& type){
    if(type == COMBINATION_TYPE)
        return is_satisfied_combination(names);

    else if(type == ALTERNATIVE_TYPE)
        return is_satisfied_xor(names);

    else if(type == OR_TYPE)
        return is_satisfied_or(names);
    
    else if(type == NO_CHILD)
        return true;
}

bool Node::is_parent_in(list<string>& names){
    return find(names.begin(), names.end(), parent_name) != names.end();
}

void Node::change_children_type(string new_children_type){
    children_type = new_children_type;
}