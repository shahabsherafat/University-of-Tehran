#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n = 0 , m = 0 , hour_train = 00 , minute_train = 00 ,hour_user = 00 , minute_user = 00;
    string name ,source ,destination ,time ,number;
    cin >> n >> m;
    vector<vector<string>> trains(n);
    for(int i = 0;i<n;i++){
        cin >> name >> source >> destination >> time >> number;
        trains[i].push_back(name);trains[i].push_back(source);
        trains[i].push_back(destination);trains[i].push_back(time);
        trains[i].push_back(number);
    }
    for(int i = 0;i<m;i++){
        cin >> source >> destination >> time >> number;
        for (int j = 0;j<n;j++){
            if (source == trains[j][1]){
                if (destination == trains[j][2]){
                    hour_train = stoi(trains[j][3].substr(0 , 2));
                    minute_train = stoi(trains[j][3].substr(3 , 5));
                    hour_user = stoi(time.substr(0 , 2));
                    minute_user = stoi(time.substr(3 , 5));

                    if ((hour_train == hour_user and minute_train > minute_user) 
                    or (hour_train > hour_user)){
                        if (stoi(number) <= stoi(trains[j][4])){
                            cout << trains[j][0] << " " << trains[j][3] << " " << trains[j][4] << endl;
                        }
                    }
                }
            }
        }
        cout << "----------" << endl;
    }
    return 0;
}