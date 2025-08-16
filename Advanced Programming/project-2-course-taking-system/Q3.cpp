#include <iostream>
#include <vector>
using namespace std;

void get_lines (vector<vector<int>>& lines_stations){
    int num_of_lines = 0;
    cin >> num_of_lines;
    int num_of_stations = 0 , connection = 0;
    for(int i = 0;i<num_of_lines;i++){
        cin >> num_of_stations;
        vector<int> stations(num_of_stations);
        for(int j = 0;j<num_of_stations;j++){
            cin >> stations[j];
        }
        lines_stations.push_back(stations);
    }
}

int find_number_of_station_in_another_line(int currentline,vector<int> other_line_stations){
    int number = 1;
    for(int i : other_line_stations){
        if(i == currentline){
            break;
        }
        number ++;
    }
    return number;
}

bool is_in(pair<int,int> new_station , vector<pair<int,int>> path){
    for(pair<int,int> x : path){
        if(new_station == x){
            return true;
        }
    }
    return false;
}

void navigate_line(const vector<vector<int>>& stations_of_lines,int current_line_number
,const pair<int,int>& destination,int source_station_number,int spent_time,
vector <pair<int,int>> path,vector<int>& times){
    int current_station_number = 1;
    for(int s : stations_of_lines[current_line_number-1]){
        if(current_line_number == destination.first and current_station_number == destination.second){
            times.push_back(spent_time + abs(current_station_number - source_station_number));
            return;
        }
        if(s != 0){
            pair<int,int> new_station = make_pair(current_line_number , current_station_number);
            if (is_in(new_station , path)){
                current_station_number++;
                continue;
            }
            int number = find_number_of_station_in_another_line(current_line_number ,
            stations_of_lines[s-1]);
            path.push_back(new_station);path.push_back(make_pair(s , number));

            int temp_time = spent_time + abs(current_station_number - source_station_number) + 2;
            navigate_line(stations_of_lines,s,destination,number,temp_time,path,times);
        }
        current_station_number++;
    }
    return;
}

int find_minimum_element(vector<int> values){
    int temp = values[0];
    for(int i : values){
        if (i < temp){
            temp = i;
        }
    }
    return temp;
}

int main(){
    vector <vector<int>> stations_of_lines;
    get_lines(stations_of_lines);
    int src_dest[4];
    for(int i = 0;i<4;i++){
        cin >> src_dest[i];
    }

    vector<int> times;vector<pair<int,int>> path;
    int spent_time = 0;
    navigate_line(stations_of_lines,src_dest[0],make_pair(src_dest[2] ,  src_dest[3]),
    src_dest[1],spent_time,path,times);
    cout << find_minimum_element(times);
    return 0;
}