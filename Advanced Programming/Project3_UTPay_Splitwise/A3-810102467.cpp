#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

const string EQUAL_DIVISION_TYPE = "equally";
const string UNEQUAL_DIVISION_TYPE = "unequally";
const string ADJUSTING_TYPE = "adjustment";
const string EMPTY = "";
const string BETWEEN_DEBTOR_AND_CREDITOR = " -> ";
const string BETWEEN_CREDITOR_AND_AMOUNT = ": ";
const double ZERO_THRESHHOLD = 0.0000001;

typedef struct Transactions{
    string debtor;
    string creditor;
    double amount;
}transaction;

string assign_passengers(map<string,double>& balances, ifstream& names_file){
    string passenger_name;string last_passenger;
    getline(names_file, passenger_name);

    while(getline(names_file, passenger_name)){
        balances[passenger_name] = 0;
        last_passenger = passenger_name;
    }

    return last_passenger;
}

vector<string> split(string s, string delimiter = ","){
    int start = 0, end = 0;
    vector <string> result;

    while (end != -1) {
        end = s.find(delimiter, start);
        result.push_back(s.substr(start, end - start));
        start = end + delimiter.size();
    }

    return result;
}

string get_expense_if_there_is(ifstream& expenses_file){
    string expense;

    if(getline(expenses_file, expense)){
        return expense;
    }

    else{
        return EMPTY;
    }
}

string map_money_to_passengers(const vector<string>& input, map<string,int>& output){
    vector<string> temp_splitted;
    string last_passenger;

    for(string s : input){
        temp_splitted = split(s, ":");
        output[temp_splitted[0]] = stoi(temp_splitted[1]);
        last_passenger = temp_splitted[0];
    }

    return last_passenger;

}

void upgrade_balances_equally(map<string,double>& balances, vector<string>& payers 
,vector<string>& borrowers,const string& last_passenger){
    map<string,int> payers_and_costs;
    int total_cost = 0;
    map_money_to_passengers(payers, payers_and_costs);

    for(auto element = payers_and_costs.begin();element != payers_and_costs.end();element++){
        total_cost += element->second;
        balances[element->first] += element->second;
    }

    if(borrowers.size() == 0){
        // auto last_element = payers_and_costs.end()--;
        double each_borrowers_share = (int)((double)total_cost/balances.size() * 100) / 100.0;
        for(auto element = balances.begin();element != balances.end();element++){
            element->second -= each_borrowers_share;
        }
        double fill_out_value = total_cost - balances.size() * each_borrowers_share;
        balances[last_passenger] -= fill_out_value;
    }

    else{
        double each_borrowers_share = (int)((double)total_cost/borrowers.size() * 100) / 100.0;
        
        for(string passenger_name : borrowers){
            balances[passenger_name] -= each_borrowers_share;
        }

        double fill_out_value = total_cost - borrowers.size() * each_borrowers_share;
        balances[borrowers.back()] -= fill_out_value;
    }
}

void upgrade_balances_unequally(map<string,double>& balances, vector<string>& payers 
,vector<string>& borrowers,const string& last_passenger){
    map<string,int> payers_and_costs, borrowers_and_debts;
    map_money_to_passengers(payers, payers_and_costs);
    map_money_to_passengers(borrowers, borrowers_and_debts);

    for(auto element = payers_and_costs.begin();element != payers_and_costs.end();element++){
        balances[element->first] += element->second;
    }

    for(auto element = borrowers_and_debts.begin();element != borrowers_and_debts.end();element++){
        balances[element->first] -= element->second;
    }

}

void upgrade_balances_adjustedly(map<string,double>& balances, vector<string>& payers 
,vector<string>& borrowers){
    map<string,int> payers_and_costs, borrowers_and_extradebts;
    int total_cost = 0;
    map_money_to_passengers(payers, payers_and_costs);
    string last_passenger = map_money_to_passengers(borrowers, borrowers_and_extradebts);

    for(auto element = payers_and_costs.begin();element != payers_and_costs.end();element++){
        total_cost += element->second;
        balances[element->first] += element->second;
    }

    for(auto element = borrowers_and_extradebts.begin();element != borrowers_and_extradebts.end();element++){
        total_cost -= element->second;
        balances[element->first] -= element->second;
    }

    double each_borrowers_share = (int)((double)total_cost/balances.size() * 100) / 100.0;

    for(auto element = balances.begin();element != balances.end();element++){
        element->second -= each_borrowers_share;
    }

    double fill_out_value = total_cost - balances.size() * each_borrowers_share;
    balances[last_passenger] -= fill_out_value;
}

void classify_expense(map<string,double>& balances, string expense, const string& last_passenger){
    vector<string> expense_factors = split(expense);
    vector<string> payers = split(expense_factors[1], ";");
    vector<string> borrowers = split(expense_factors[2], ";");

    if(borrowers.size() == 1 and borrowers[0] == ""){
        borrowers.pop_back();
    }

    if(expense_factors[0] == EQUAL_DIVISION_TYPE){
        upgrade_balances_equally(balances, payers, borrowers, last_passenger);
    }

    else if(expense_factors[0] == UNEQUAL_DIVISION_TYPE){
        upgrade_balances_unequally(balances, payers, borrowers, last_passenger);
    }
    
    else if(expense_factors[0] == ADJUSTING_TYPE){
        upgrade_balances_adjustedly(balances, payers, borrowers);
    }
    
}

void make_debtors_and_creditors_vectors(const map<string, double>& balances, vector<pair<string,double>>& debtors, 
vector<pair<string,double>>& creditors){
    for(auto element = balances.begin();element != balances.end();element++){
        if(element->second < 0){
            debtors.push_back(make_pair(element->first, element->second));
        }

        else{
            creditors.push_back(make_pair(element->first, element->second));
        }
    }
}

void sort_pairs(vector<pair<string,double>>& balances_vector){
    int size = balances_vector.size();
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size-i;j++){
            if(abs(balances_vector[j].second) < abs(balances_vector[j+1].second)){
                swap(balances_vector[j], balances_vector[j+1]);
            }

            else if(balances_vector[j].second == balances_vector[j+1].second){
                if(balances_vector[j].first > balances_vector[j+1].first){
                    swap(balances_vector[j], balances_vector[j+1]);
                }
            }
        }
    }
}

void determine_transactions(vector<transaction>& transactions, const vector<pair<string,double>>& debtors, 
vector<pair<string,double>> creditors){
    int paid_creditors_number = 0;
    
    for(pair<string,double> debtor_person : debtors){
        while(-debtor_person.second > ZERO_THRESHHOLD){
            if(-debtor_person.second >= creditors[paid_creditors_number].second){
                transaction temp;
                temp.debtor = debtor_person.first;
                temp.creditor = creditors[paid_creditors_number].first;
                temp.amount = creditors[paid_creditors_number].second;
                transactions.push_back(temp);
                debtor_person.second += creditors[paid_creditors_number].second;
                paid_creditors_number ++;
            }

            else{
                transaction temp;
                temp.debtor = debtor_person.first;
                temp.creditor = creditors[paid_creditors_number].first;
                temp.amount = -debtor_person.second;
                transactions.push_back(temp);
                creditors[paid_creditors_number].second += debtor_person.second;
                debtor_person.second = 0;
            }
        }
    }
}

void sort_transactions(vector <transaction>& transactions){
    int size = transactions.size();
    for(int i = 0;i<size;i++){
        for(int j = 0;j<size-i;j++){
            if(transactions[j].amount < transactions[j+1].amount){
                swap(transactions[j], transactions[j+1]);
            }

            else if(transactions[j].amount == transactions[j+1].amount){
                if((transactions[j].debtor > transactions[j+1].debtor) or 
                (transactions[j].debtor == transactions[j+1].debtor and transactions[j].creditor > transactions[j+1].creditor)){
                    swap(transactions[j], transactions[j+1]);
                }
            }
        }
    }
}

void print_transactions(vector<transaction> transactions){
    for(transaction t : transactions){
        cout << t.debtor << BETWEEN_DEBTOR_AND_CREDITOR << t.creditor << BETWEEN_CREDITOR_AND_AMOUNT << t.amount << endl; 
    }
}

int main(int argc, char* addresses[3]){
    map<string, double> balances;
    ifstream names_file(addresses[1]);
    ifstream expenses_file(addresses[2]);

    string last_passenger = assign_passengers(balances, names_file);
    string expense = get_expense_if_there_is(expenses_file);
    expense = get_expense_if_there_is(expenses_file);
    
    while(expense != EMPTY){
        classify_expense(balances, expense, last_passenger);
        expense = get_expense_if_there_is(expenses_file);
    }

    vector<pair<string,double>> debtors;
    vector<pair<string,double>> creditors;
    make_debtors_and_creditors_vectors(balances, debtors, creditors);
    sort_pairs(debtors);
    sort_pairs(creditors);
    
    vector<transaction> transactions;
    determine_transactions(transactions, debtors, creditors);
    sort_transactions(transactions);
    print_transactions(transactions);
    
    return 0;
}