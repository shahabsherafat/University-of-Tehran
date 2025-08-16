#include "Carwash.hpp"

Carwash::Carwash(){
    last_car_id = 0;
    current_time = 0;
}

void Carwash::assign_stages(ifstream& stages_file){
    string line;
    getline(stages_file, line);
    
    while(getline(stages_file, line)){
        vector<string> factors = split(line);
        Stage *s = new Stage(factors[0], stoi(factors[1]));
        all_stages.push_back(s);
    }
}

void Carwash::assign_workers(ifstream& workers_file){
    string line;
    getline(workers_file, line);

    while(getline(workers_file, line)){
        vector<string> factors = split(line);
        Worker* temp = new Worker(factors[0], factors[1], stoi(factors[2]));
        all_workers.push_back(temp);
        
        for(Stage* s : all_stages){
            if(s->get_id() == factors[1]){
                s->add_worker(temp);
                break;
            }
        }
    }

    for(Stage* s : all_stages){
        s->sort_workers();
    }
}

void Carwash::move_to_next_stage(Car* car){
    string former_stage_id = car->take_out_of_current_stage();
    string next_stage_id = car->next_stage_id();

    if(next_stage_id != ""){
        for(Stage* s : all_stages){
            if(s->get_id() == next_stage_id){
                s->push_car_and_print_report(car, former_stage_id, current_time);
                break;
            }
        }
    }
    else{
        cout << current_time << CAR_WORD_FOR_MOVE << car->get_id() 
        << FROM_STAGE_WORD_FOR_MOVE << former_stage_id << TO_DONE_WORD_FOR_MOVE << endl;
    }
}

void Carwash::pass_time_and_report(const int& time){
    for(int i = 0;i<time;i++){
        vector<pair<string,string>> finished_and_dequeued_cars_ids;

        for(Stage* s : all_stages){
            s->pass_one_second_and_report_finished_cars(finished_and_dequeued_cars_ids);
        }
        current_time ++;

        sort(finished_and_dequeued_cars_ids.begin(), finished_and_dequeued_cars_ids.end(), compare_by_first);

        for(pair<string, string> p : finished_and_dequeued_cars_ids){
            if(p.second == FINISHED_WORD){
                move_to_next_stage(all_cars[stoi(p.first) - 1]);
            }

            else if(p.second == DEQUEUED_WORD){
                all_cars[stoi(p.first) - 1]->take_out_of_queue_and_print_report(current_time);
            }
        }
    }
}

void Carwash::add_new_car_and_print_report(vector<string> stages_ids){
    last_car_id ++;
    Car* temp = new Car(to_string(last_car_id), stages_ids);
    all_cars.push_back(temp);
    for(Stage* s : all_stages){
        if(s->get_id() == stages_ids[0]){
            s->push_car_and_print_report(temp, ARRIVED_WORD, current_time);
            break;
        }
    }
}

void Carwash::report_stage_status(string intended_stage_id){
    for(Stage* s : all_stages){
        if(s->get_id() == intended_stage_id){
            s->report_status();
            break;
        }
    }
}

void Carwash::report_worker_status(string intended_worker_id){
    for(Worker* w : all_workers){
        if(w->get_id() == intended_worker_id){
            w->report_status();
            break;
        }
    }
}

void Carwash::report_car_status(string intended_car_id){
    for(Car* c : all_cars){
        if(c->get_id() == intended_car_id){
            c->report_status();
            break;
        }
    }
}

void Carwash::remove_all_cars(){
    for(Car *temp : all_cars){
        delete(temp);
    }
}

void Carwash::remove_all_workers(){
    for(Worker *temp : all_workers){
        delete(temp);
    }
}

void Carwash::remove_all_stages(){
    for(Stage *temp : all_stages){
        delete(temp);
    }
}
