#include "Stage.hpp"

bool compare_workers_by_time_to_finish(Worker* w1, Worker* w2){
    if(w2->get_time_to_finish() == w1->get_time_to_finish()){
        return stoi(w1->get_id()) < stoi(w2->get_id());
    }

    return w1->get_time_to_finish() < w2->get_time_to_finish();
}

Stage::Stage(string init_id, int init_price){
    id = init_id;
    price = init_price;
}

string Stage::get_id() {return id;}

void Stage::add_worker(Worker* worker){
    workers.push_back(worker);
}

void Stage::sort_workers(){
    sort(workers.begin(), workers.end(), compare_workers_by_time_to_finish);
}

void Stage::pass_one_second_and_report_finished_cars(vector<pair<string,string>>& finished_and_dequeued_cars_ids){
    bool is_work_finished;
    for(Worker* w : workers){
        is_work_finished = w->pass_one_second(finished_and_dequeued_cars_ids);

        if(is_work_finished){
            num_of_servicing_cars --;
            num_of_washed_cars ++;
            income += price;
        }
    }

    manage_queue(finished_and_dequeued_cars_ids);
}

void Stage::push_car_and_print_report(Car* car, string former_stage_id, int time){
    if(num_of_servicing_cars == workers.size()){
        queue.push_back(car);
        car->enqueue();

        if(former_stage_id != "Arrived"){
            cout << time << " Car " << car->get_id() << ": Stage " << former_stage_id << " -> Queue " 
            << id << endl;
        }

        else{
            cout << time << " Car " << car->get_id() << ": Arrived -> Queue " << id << endl;
        }
        return;
    }

    for(Worker* w : workers){
        if(!w->is_working()){
            w->start_working(car->get_id());
            break;
        }
    }
    
    if(former_stage_id != "Arrived"){
        cout << time << " Car " << car->get_id() << ": Stage " << former_stage_id << " -> Stage " 
        << id << endl;
    }

    else{
        cout << time << " Car " << car->get_id() << ": Arrived -> Stage " << id << endl;
    }
    num_of_servicing_cars ++;
}

void Stage::report_status(){
    cout << "Number of washed cars: " << num_of_washed_cars << endl;
    cout << "Number of cars in queue: " << queue.size() << endl;
    cout << "Number of cars being washed: " << num_of_servicing_cars << endl;
    cout << "Income: " << income << endl;
}

