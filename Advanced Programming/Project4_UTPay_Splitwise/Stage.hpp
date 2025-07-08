#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "split_and_compares.hpp"
#include "Car.hpp"
#include "Worker.hpp"

using namespace std;

bool compare_workers_by_time_to_finish(Worker* w1, Worker* w2);

class Stage{
    public:
        Stage(string init_id, int init_price);
        
        Stage(){}
        
        string get_id();

        void add_worker(Worker* worker);

        void sort_workers();

        void pass_one_second_and_report_finished_cars(vector<pair<string,string>>& finished_and_dequeued_cars_ids);

        void push_car_and_print_report(Car* car, string former_stage_id, int time);

        void report_status();


    private:
        string id;
        int price;
        vector<Worker*> workers;
        int num_of_servicing_cars = 0;
        list<Car*> queue;
        int num_of_washed_cars = 0;
        long long income = 0;

        void manage_queue(vector<pair<string,string>>& finished_and_dequeued_cars_ids){
            if(queue.size()){
                for(Worker* w : workers){
                    if(!w->is_working()){
                        w->start_working(queue.front()->get_id());
                        num_of_servicing_cars ++;
                        finished_and_dequeued_cars_ids.push_back(make_pair(queue.front()->get_id(), "dequeued"));
                        queue.pop_front();

                        if(queue.size()){
                            continue;
                        }

                        break;
                    }
                }
            }
        }
};