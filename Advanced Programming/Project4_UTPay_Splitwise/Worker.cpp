#include "Worker.hpp"

Worker::Worker(string init_id, string init_stage_id, int init_time_to_finish){
    id = init_id;
    stage_id = init_stage_id;
    time_to_finish = init_time_to_finish;
}

Worker::Worker(){}

bool Worker::pass_one_second(vector<pair<string,string>>& finished_and_dequeued_cars_ids){
    if(working_situation == true){
        left_time --;

        if(left_time == 0){
            working_situation = false;
            finished_and_dequeued_cars_ids.push_back(make_pair(servicing_car_id, "finished"));
            servicing_car_id = "";
            return true;
        }
    }
    return false;
}

void Worker::start_working(string car_id){
    servicing_car_id = car_id;
    working_situation = true;
    left_time = time_to_finish;
}

bool Worker::is_working() {return working_situation;}

int Worker::get_time_to_finish() {return time_to_finish;}

string Worker::get_id() {return id;}

void Worker::report_status(){
    if(working_situation){
        cout << "Working: " << servicing_car_id << endl;
    }
    else{
        cout << "Idle" << endl;
    }
}
