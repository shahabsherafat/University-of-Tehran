#include <iostream>
#include <vector>
using namespace std;

typedef struct Item{
    string name;
    vector <int> children;
}item;

void make_item_line(const vector <item> &items_list , const vector <int> children , 
string passed_prefix , int depth ,const int &max_depth){
    if (depth > max_depth){
        return;
    }
    
    for (int i = 0;i<children.size();i++){
        cout << passed_prefix + "|__" + items_list[children[i]].name << endl;
        if (i!=children.size() - 1)
            make_item_line(items_list , items_list[children[i]].children , passed_prefix + "|  " , depth + 1 , max_depth);
        else
            make_item_line(items_list , items_list[children[i]].children , passed_prefix + "   " , depth + 1 , max_depth);
    }
    return;
}

int main(){
    int num_of_items = 0,max_depth = 0;
    cin >> num_of_items >> max_depth;
    vector <item> items_list(1);

    for (int i = 1;i<=num_of_items;i++){
        item current_item;int current_item_parent;
        cin >> current_item.name >> current_item_parent;
        items_list.push_back(current_item);
        items_list[current_item_parent].children.push_back(i);
    }

    make_item_line(items_list , items_list[0].children , "" , 1 , max_depth);
    return 0;
}