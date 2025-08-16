#include <iostream>
using namespace std;

int calculate_num_of_ones(long long n){
    if (n == 0){
        return 0;
    }

    long long current_1digits = 1;
    int answer = 1;
    while (current_1digits < n){
        current_1digits *= 10;
        current_1digits ++;
        answer ++;
    }
    if(abs(current_1digits - n) >= abs((current_1digits-1)/10 - n)){
        answer --;
        current_1digits = (current_1digits - 1) / 10;
    }
    
    answer += calculate_num_of_ones(abs(current_1digits - n));
    return answer;
}

int main(){
    long long number = 0;
    cin >> number;
    cout << calculate_num_of_ones(number);
    return 0;
}