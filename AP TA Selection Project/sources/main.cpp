#include "../includes/handler.hpp"

using namespace std;

int main(){
    while(true){
        Tree* tree = new Tree();
        Handler* handler = new Handler(tree);

        try{
            handler->get_descriptions(); //I assumed that the descriptions will have no problems and need no handlings.
            handler->validate_configs();
            delete(tree);
            delete(handler);
        }

        catch(runtime_error r){
            delete(tree);
            delete(handler);
            break;
        }
    }

    return 0;
}