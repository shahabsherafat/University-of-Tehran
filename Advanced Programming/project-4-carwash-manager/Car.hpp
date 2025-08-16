#pragma once

#include <iostream>
#include <vector>
using namespace std;

const string CAR_WORD_FOR_REPORT = " Car ";
const string QUEUE_WORD_FOR_REPORT = ": Queue ";
const string TO_STAGE_WORD_FOR_REPORT = " -> Stage ";
const string DONE_WORD_FOR_REPORT = "Done";
const string IN_LINE_WORD_FOR_REPORT = "In line: ";
const string IN_SERVICE_WORD_FOR_REPORT = "In service: ";

class Car{
    public:
        Car (string init_id, vector<string> init_stages);
        string get_id();
        void take_out_of_queue_and_print_report(const int& time);
        string take_out_of_current_stage();
        void enqueue();
        string next_stage_id();
        void report_status();


    private:
        string id;
        vector<string> stages;
        int num_of_spent_stages = 0;
        bool is_in_queue;
};