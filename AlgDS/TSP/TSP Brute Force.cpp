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

    for (int i = 0; i < cityAmount; i++) { 
        for (int j = 0; j < cityAmount; j++) {
            cout << distance[i][j] << " ";
        }
        cout << endl;
    }

    const auto end = chrono::steady_clock::now();
    const chrono::duration<double> time = end-start;
    cout << time.count() << "s" << endl;

    cout << "Кратчайшее расстояние: " << minCost << endl;
    cout << "< ";
    for (int i = 0; i < cityAmount + 1; i++) {
        cout << best_path[i] << " ";
    }
    cout << ">";

    return 0;
}
