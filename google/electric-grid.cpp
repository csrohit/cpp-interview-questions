#include <iostream>
#include <vector>

using namespace std;

// Function to find and list all the cities in the map
vector<pair<int, int>> findCities(int** map, int rows, int cols) {
    vector<pair<int, int>> cityCoordinates;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == -1) {
                cityCoordinates.push_back(make_pair(i, j));
            }
        }
    }

    return cityCoordinates;
}

int main() {
    // Example map (from the provided image)
    int rows = 6;
    int cols = 6;

    int** map = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        map[i] = new int[cols];
    }

    // Initialize the map with values from the image
    map[0][0] = 1; map[0][1] = 1; map[0][2] = 1; map[0][3] = 1; map[0][4] = 1; map[0][5] = -1;
    map[1][0] = 1; map[1][1] = 0; map[1][2] = 0; map[1][3] = 0; map[1][4] = 0; map[1][5] = 1;
    map[2][0] = 1; map[2][1] = 0; map[2][2] = -1; map[2][3] = 0; map[2][4] = 0; map[2][5] = 1;
    map[3][0] = 1; map[3][1] = 0; map[3][2] = 1; map[3][3] = 1; map[3][4] = 1; map[3][5] = 1;
    map[4][0] = 1; map[4][1] = 0; map[4][2] = 1; map[4][3] = 0; map[4][4] = 0; map[4][5] = 1;
    map[5][0] = 1; map[5][1] = 1; map[5][2] = 1; map[5][3] = 1; map[5][4] = 1; map[5][5] = -1;

    // Find the city coordinates
    vector<pair<int, int>> cities = findCities(map, rows, cols);

    // Print the city coordinates
    cout << "List of Cities:" << endl;
    for (const auto& city : cities) {
        cout << "(" << city.first << ", " << city.second << ")" << endl;
    }

    // Deallocate the memory
    for (int i = 0; i < rows; ++i) {
        delete[] map[i];
    }
    delete[] map;

    return 0;
}

