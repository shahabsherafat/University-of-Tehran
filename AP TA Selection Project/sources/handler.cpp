#include "../includes/handler.hpp"

Handler::Handler(Tree* init_coffee_maker){
    coffee_maker = init_coffee_maker;
}

string Handler::find_node_type(string line){
    if(line.find(OR_SIGN) != std::string::npos)
        return OR_TYPE;

    else if(line.find(XOR_SIGN) != std::string::npos)
        return ALTERNATIVE_TYPE;

    else
        return COMBINATION_TYPE;
}

void Handler::get_descriptions(){
    string line;
    string temp;
    string parent_name;
    string node_type;
    bool is_root = true;

    getline(cin, line);

    if(line == END_OF_TESTS){
        throw runtime_error(EMPTY_STRING);
    }

    while(line != END_OF_DESCRIPTIONS){
        string cleaned_line = regex_replace(line, regex(R"(\s*([=+?|^])\s*)"), " $1 ");
        cleaned_line = regex_replace(cleaned_line, regex(R"(\?([a-zA-Z]))"), "? $1");
        node_type = find_node_type(cleaned_line);

        stringstream line_stream(cleaned_line);
        line_stream >> parent_name;
        line_stream >> temp;

        if(is_root){
            coffee_maker->change_root_name(parent_name);
            Node* root = new Node(parent_name, ROOT_TYPE, EMPTY_STRING, node_type);
            coffee_maker->add_node(ROOT_TYPE, root, parent_name);
            is_root = false;
        }

        while(line_stream >> temp){
            if(node_type == COMBINATION_TYPE){
                if(temp == QUESTION_MARK){
                    line_stream >> temp;
                    Node* new_node = new Node(temp, OPTIONAL_TYPE, parent_name);
                    coffee_maker->add_node(parent_name, new_node, temp);
                }

                else{
                    Node* new_node = new Node(temp, MANDATORY_TYPE, parent_name);
                    coffee_maker->add_node(parent_name, new_node, temp);
                }

                line_stream >> temp;
                continue;
            }

            Node* new_node = new Node(temp, node_type, parent_name);
            coffee_maker->add_node(parent_name, new_node, temp);
            line_stream >> temp;
        }

        coffee_maker->change_children_type(parent_name, node_type);

        getline(cin, line);
    }
}

void Handler::validate_configs(){
    string line;
    string temp;

    getline(cin, line);
    while(line != END_OF_CONFIGS){
        string cleaned_line = regex_replace(line, regex("[{},]"), " ");
        stringstream line_stream(cleaned_line);
        list<string> config;
        bool flag = true;

        while(line_stream >> temp){
            if(find(config.begin(), config.end(), temp) != config.end()){
                cout << INVALID_CONFIG << endl;
                getline(cin, line);
                flag = false;
                break;
            }
            config.push_back(temp);
        }

        if(!flag){
            continue;
        }

        for(string name : config){
            if(!coffee_maker->does_exist(name)){
                cout << INVALID_CONFIG << endl;
                flag = false;
                break;
            }

            if(!coffee_maker->investigate(config, name)){
                cout << INVALID_CONFIG << endl;
                flag = false;
                break;
            }
        }

        if(flag)
            cout << VALID_CONFIG << endl;

        getline(cin, line);
    }
    
    cout << END_OF_RESULTS << endl;
}