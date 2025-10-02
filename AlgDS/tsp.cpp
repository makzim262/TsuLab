#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

int tspBruteForce(vector<vector<int>>& distance, int cityAmount, int cityStart) {

    const auto start = chrono::steady_clock::now();
    
    vector<int> cities;
    for (int i = 0; i < cityAmount; i++) {
        if (i!=cityStart-1) {
            cities.push_back(i+1);
        }
    }

    vector<int> best_path;
    int minCost = INT_MAX;

    do {
        vector<int> path;
        path.push_back(cityStart);
        path.insert(path.end(), cities.begin(), cities.end());

        int cost = 0;
        for (int i = 0; i < cityAmount-1; i++) {
            cost += distance[path[i]-1][path[i+1]-1];
        }
        cost += distance[path[cityAmount-1]-1][path[0]-1];

        if (cost < minCost) { 
            best_path = path;
            minCost = cost;
        }
        
    } while (next_permutation(cities.begin(), cities.end()));

    best_path.push_back(cityStart);

    const auto end = chrono::steady_clock::now();
    const chrono::duration<double> time = end-start;
    cout << time.count() << "s \n";

    cout << "полный перебор: \n";
    cout << "расстояние: " << minCost << "\n";
    cout << "< ";
    for (int i = 0; i < cityAmount + 1; i++) {
        cout << best_path[i] << " ";
    }
    cout << ">";
    return 1;
}

int tspGreedy(vector<vector<int>>& distance, int cityAmount, int cityStart) {
    
    const auto start = chrono::steady_clock::now();

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

    cout << "жадный алгоритм: \n";
    cout << "расстояние: " << pathCost << "\n";
    cout << "< ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << "> \n";

    const auto end = chrono::steady_clock::now();
    const chrono::duration<double> time = end-start;
    cout << time.count() << "s" << "\n\n";

    return 0;
}

int main() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1,9);
    
    int cityAmount;
    int cityStart;
    cout << "введите количество городов и номер стартового города" << "\n";
    cin >> cityAmount >> cityStart;

    if (cityAmount < cityStart || cityStart < 1) {
        cout << "введен некорректный номер стартового города" << "\n";
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
        cout << "\n";
    }
    cout << "\n";

    tspGreedy(distance, cityAmount, cityStart);
    tspBruteForce(distance, cityAmount, cityStart);

    return 0;
}