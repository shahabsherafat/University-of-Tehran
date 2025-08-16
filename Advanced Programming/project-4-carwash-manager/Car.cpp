#include "Car.hpp"

Car::Car (string init_id, vector<string> init_stages){
    id = init_id;
    stages = init_stages;
}

string Car::get_id(){return id;}

void Car::take_out_of_queue_and_print_report(const int& time){
    cout << time << CAR_WORD_FOR_REPORT << id << QUEUE_WORD_FOR_REPORT << stages[num_of_spent_stages]
    << TO_STAGE_WORD_FOR_REPORT << stages[num_of_spent_stages] << endl;
    is_in_queue = false;
}

string Car::take_out_of_current_stage(){
    num_of_spent_stages ++;

    return stages[num_of_spent_stages - 1];
}

void Car::enqueue(){
    is_in_queue = true;
}

string Car::next_stage_id(){
    if(num_of_spent_stages != stages.size())
        return stages[num_of_spent_stages];
    
    return "";
}

void Car::report_status(){
    if(num_of_spent_stages == stages.size()){
        cout << DONE_WORD_FOR_REPORT << endl;
        return;
    }

    if(is_in_queue){
        cout << IN_LINE_WORD_FOR_REPORT << stages[num_of_spent_stages] << endl;
    }

    else{
        cout << IN_SERVICE_WORD_FOR_REPORT << stages[num_of_spent_stages] << endl;
    }
}
