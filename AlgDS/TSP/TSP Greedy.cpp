#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

int main() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9);

    const auto start = chrono::steady_clock::now();
    
    int cityAmount;
    int cityStart;
    cout << "введите количество городов и номер стартового города" << endl;
    cin >> cityAmount >> cityStart;

    if (cityAmount < cityStart || cityStart < 1) {
        cout << "введен некорректный номер стартового города" << endl;
        return 1;
    }

    vector<vector<int>> distance(cityAmount, vector<int>(cityAmount));

    for (int i = 0; i < cityAmount-1; i++) {
        for (int j = i+1; j < cityAmount; j++) {
            distance[i][j] = distrib(gen);
            distance[j][i] = distance[i][j];
        }
    }

    for (int i = 0; i < cityAmount; i++) {
        for (int j = 0; j < cityAmount; j++) {
            cout << distance[i][j] << " ";       
        }
        cout << endl;
    }   

    vector<int> path = {cityStart};
    int currCity = cityStart;
    int pathCost = 0;

    vector<int> unvisited;
    for (int i = 0;i < cityAmount; i++) {
        if (i != cityStart-1) unvisited.push_back(i+1);
    }

    while (!unvisited.empty()) {
        int currMin = INT_MAX;
        int nextCity;
        int nextCityIndex;

        for (int j = 0; j < unvisited.size(); j++) {
            if (distance[currCity-1][unvisited[j]-1] < currMin) {
                currMin = distance[currCity-1][unvisited[j]-1];
                nextCity = unvisited[j]; 
                nextCityIndex = j;
            }
        }
        pathCost += currMin;
        currCity = nextCity;
        path.push_back(currCity);
        unvisited.erase(unvisited.begin() + nextCityIndex);   
    }
    
    path.push_back(cityStart);
    pathCost += distance[currCity-1][cityStart-1];

    const auto end = chrono::steady_clock::now();
    const chrono::duration<double> time = end-start;
    cout << time.count() << "s" << endl;

    cout << pathCost << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }

    return 0;
}