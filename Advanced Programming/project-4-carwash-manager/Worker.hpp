#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Worker{
    public:
        Worker(string init_id, string init_stage_id, int init_time_to_finish);

        Worker();

        bool pass_one_second(vector<pair<string,string>>& finished_and_dequeued_cars_ids);

        void start_working(string car_id);

        bool is_working();

        int get_time_to_finish();

        string get_id();

        void report_status();


    private:
        string id;
        string stage_id;
        int time_to_finish;
        bool working_situation = false;
        string servicing_car_id;
        int left_time;
};