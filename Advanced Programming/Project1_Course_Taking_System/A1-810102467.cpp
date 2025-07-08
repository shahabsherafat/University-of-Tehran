#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef struct Offered_course{
    string name;
    int units;
    vector <string> prerequisites;
}offered;
typedef struct Passed_course{
    string name;
    int units;
    float grade;
}passed;

vector<string> Split(string s , string delimiter){
    int start = 0, end = 0;
    vector <string> result;
    while (end != -1) {
        end = s.find(delimiter, start);
        result.push_back(s.substr(start, end - start));
        start = end + delimiter.size();
    }
    return result;
}

int Istaken(string demanded_coursename ,vector<passed> passed_list,int num_of_passed){
    for(int i = 0;i<num_of_passed;i++){
        if(demanded_coursename == passed_list[i].name){
            return 1;
        }
    }
    return 0;
}

int Are_prerequisites_not_met(offered course , vector<passed> passed_list,int num_of_passed){
    int num_of_prerequisites = course.prerequisites.size();
    for(int i = 0;i<num_of_prerequisites;i++){
        for(int j = 0;j<num_of_passed;j++){
            if(course.prerequisites[i] == passed_list[j].name){
                break;
            }
            if(j == num_of_passed - 1){
                return 1;
            }
        }
    }
    return 0;
}

int Num_of_units_validation(int sum_of_scores , int sum_of_units , int demanded_units){
    float mean = sum_of_scores / sum_of_units;
    if (mean >= 17){
    if(demanded_units < 12){
        return 1;
    }
    if(demanded_units > 24){
        return 2;
    }
    }
    else if (mean >= 12 and mean < 17){
    if(demanded_units < 12){
        return 1;
    }
    if(demanded_units > 20){
        return 2;
    }
    }
    else{
    if(demanded_units < 12){
        return 1;
    }
    if(demanded_units > 14){
        return 2;
    }
    }

    return 0;
}

int main(){
    vector<offered> offered_list;
    vector<passed> passed_list;
    int demanded_units = 0 , sum_of_scores = 0 , sum_of_units = 0;

    int m = 0;
    cin >> m;
    offered temp_offered;
    string prerequisites_string;
    for(int i = 0;i<m;i++){
        cin >> temp_offered.name >> temp_offered.units >> prerequisites_string;
        temp_offered.prerequisites = Split(prerequisites_string , ",");
        offered_list.push_back(temp_offered);
    }
    
    int n = 0;
    cin >> n;
    passed temp_passed;
    for(int i = 0;i<n;i++){
        cin >> temp_passed.name >> temp_passed.units  >> temp_passed.grade;
        sum_of_scores += temp_passed.grade * temp_passed.units;
        sum_of_units += temp_passed.units;
        if(temp_passed.grade < 10){
            continue;
        }
        passed_list.push_back(temp_passed);
    }

    int k = 0;
    cin >> k;
    string demanded_coursename;
    for(int i = 0;i<k;i++){
        cin >> demanded_coursename;
        if(Istaken(demanded_coursename , passed_list , n)){
            cout << "Course Already Taken!";
            return -1;
        }
        for(int j = 0;j<m;j++){
            if(demanded_coursename == offered_list[j].name){
                if(Are_prerequisites_not_met(offered_list[j] , passed_list , n)){
                    cout << "Prerequisites Not Met!";
                    return -1;
                }
                demanded_units += offered_list[j].units;
                break;
            }
            if (j==m-1){
                cout << "Course Not Offered!";
                return -1;
            }
        }
    }

    int situation = Num_of_units_validation(sum_of_scores,sum_of_units,demanded_units);
    switch (situation)
    {
    case 1:
        cout << "Minimum Units Validation Failed!";
        break;
    
    case 2:
        cout << "Maximum Units Validation Failed!";
        break;

    case 0:
        cout << "OK!";
        break;
    }
    return 0;
}