#include <iostream>
#include <vector>
#include "orders_implementation.hpp"

using namespace std;

void get_and_implement_orders(Carwash& cw){
    string order;
    while(getline(cin, order)){
        vector<string> order_factors = split(order, SPACE_DELIMITER);

        if(order_factors[0] == PASS_TIME_ORDER){
            cw.pass_time_and_report(stoi(order_factors[1]));
        }

        else if(order_factors[0] == CAR_ARRIVAL_ORDER){
            vector<string> stages(order_factors.size() - 1);

            for(int i = 0;i<order_factors.size() - 1;i++){
                stages[i] = order_factors[i+1];
            }

            cw.add_new_car_and_print_report(stages);
        }

        else if(order_factors[0] == GET_CAR_STATUS){
            cw.report_car_status(order_factors[1]);
        }

        else if(order_factors[0] == GET_WORKER_STATUS){
            cw.report_worker_status(order_factors[1]);
        }

        else if(order_factors[0] == GET_STAGE_STATUS_ORDER){
            cw.report_stage_status(order_factors[1]);
        }
    }

    cw.remove_all_cars();
    cw.remove_all_stages();
    cw.remove_all_workers();
}
