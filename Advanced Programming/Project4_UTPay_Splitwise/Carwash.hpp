#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <algorithm>
#include "Stage.hpp"
#include "Car.hpp"
#include "Worker.hpp"

const string CAR_WORD_FOR_MOVE = " Car ";
const string FROM_STAGE_WORD_FOR_MOVE = ": Stage ";
const string TO_DONE_WORD_FOR_MOVE = " -> Done";
const string FINISHED_WORD = "finished";
const string DEQUEUED_WORD = "dequeued";
const string ARRIVED_WORD = "Arrived";

using namespace std;

class Carwash{
    public:
        Carwash();
        
        void assign_stages(ifstream& stages_file);

        void assign_workers(ifstream& workers_file);

        void move_to_next_stage(Car* car);

        void pass_time_and_report(const int& time);

        void add_new_car_and_print_report(vector<string> stages_ids);

        void report_stage_status(string intended_stage_id);

        void report_worker_status(string intended_worker_id);

        void report_car_status(string intended_car_id);
        
        void remove_all_cars();

        void remove_all_workers();

        void remove_all_stages();

    private:
        int current_time;
        int last_car_id;
        vector<Stage*> all_stages;
        vector<Worker*> all_workers;
        vector<Car*> all_cars;
};