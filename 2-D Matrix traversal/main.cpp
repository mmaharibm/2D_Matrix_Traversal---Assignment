#include <cmath>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Function to read the indexes from file
vector<pair<int, int>> readIndexesFromFile(string filename) {
    vector<pair<int, int>> indexes;
    int n, m;

    ifstream infile(filename);
    while (infile >> n >> m) {
        indexes.push_back({n, m});
    }
    infile.close();

    return indexes;
}

// Function to color the indexes in the matrix
void colorIndexesInMatrix(vector<vector<int>>& matrix, vector<pair<int, int>>& indexes) {
    for (auto index : indexes) {
        matrix[index.first][index.second] = 255;

    }

}

// Function to write the matrix to a PPM file
void writePPM(vector<vector<int>>& matrix, string filename) {
    ofstream outfile(filename);
    outfile << "P3" << endl;
    outfile << matrix[0].size() << " " << matrix.size() << endl;
    outfile << "255" << endl;

    for (auto row : matrix) {
        for (auto value : row) {
            outfile << value << " " << value << " " << value << " ";
        }
        outfile << endl;
    }

    outfile.close();
}

// Function to generate the image
void generateImage(string input, string output) {
    // Create a 2D array of integers with dimensions 480 x 844
    vector<vector<int>> matrix(480, vector<int>(844, 0));

    // Read the indexes to color from file
    vector<pair<int, int>> indexes = readIndexesFromFile(input);

    // Color the indexes in the matrix
    colorIndexesInMatrix(matrix, indexes);

    // Write the matrix to a PPM file
    writePPM(matrix, output);
  
    cout << "Image generated successfully." << endl;
}

//Function to read the data file into a 2d array
void readFileToArray(int map[480][844]) {
  ifstream file("map.txt");
  if (!file.is_open()) {
    cout << "file not found";
    return;
  }
  for (int i = 0; i < 480; i++) {
    for (int j = 0; j < 844; j++) {
      file >> map[i][j];
    }
  }
  file.close();
}

//Function to find Optimal Path for Scenario 1A
void findPathQ1A(int map[480][844], int startingPoint) {
  srand(time(nullptr));
  ofstream write("Q1A.txt");
  write << startingPoint << " " << 0 << "\n";
  int sum = 0;
  int upward = 999999999;
  int forward = 999999999;
  int downward = 999999999;
  for (int i = 0; i < 843; i++) {
    if (startingPoint > 0 && startingPoint < 480) {
      upward = abs(map[startingPoint][i] - map[startingPoint - 1][i + 1]);
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
      downward = abs(map[startingPoint][i] - map[startingPoint + 1][i + 1]);
    } else if (startingPoint == 0) {
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
      downward = abs(map[startingPoint][i] - map[startingPoint + 1][i + 1]);
    } else {
      upward = abs(map[startingPoint][i] - map[startingPoint - 1][i + 1]);
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
    }
    if (upward < forward && upward < downward) {
      startingPoint -= 1;
      sum += upward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (forward < upward && forward < downward) {
      sum += forward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (downward < upward && downward < forward) {
      startingPoint += 1;
      sum += downward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (upward==forward){
      int choice = rand() % 2;
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else if(upward == downward){
      int choice = rand() % 2;
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else if(forward == downward){
      int choice = rand() % 2;
      if (choice == 0){
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else{
      int choice = rand() % 3; 
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      }else if (choice == 1){
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    }
    upward = 999999999;
    forward = 999999999;
    downward = 999999999;
  }

  write.close();

  ofstream write2("Q1A_energy.txt");
  write2 << "\nenergy required: " << sum;
  write2.close();
}

//Function to time Secnario 1A
void Q1A(int map[480][844], int startingPoint) {
  double start = clock();
  readFileToArray(map);
  findPathQ1A(map, startingPoint);
  double end = clock();
  double duration = (end - start) / CLOCKS_PER_SEC;
  cout << "time for Q1A is sec: " << duration << endl;

}
//Same function as findPathQ1A but returns int
int findPathQ1B(int map[480][844], int startingPoint) {
  ofstream write("Q1B.txt");
  write << startingPoint << " " << 0 << "\n";
  int sum = 0;
  int upward = 9999999;
  int forward = 9999999;
  int downward = 9999999;
  for (int i = 0; i < 844 - 1; i++) {
    if (startingPoint > 0 && startingPoint < 480) {
      upward = abs(map[startingPoint][i] - map[startingPoint - 1][i + 1]);
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
      downward = abs(map[startingPoint][i] - map[startingPoint + 1][i + 1]);
    } else if (startingPoint == 0) {
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
      downward = abs(map[startingPoint][i] - map[startingPoint + 1][i + 1]);
    } else {
      upward = abs(map[startingPoint][i] - map[startingPoint - 1][i + 1]);
      forward = abs(map[startingPoint][i] - map[startingPoint][i + 1]);
    }
    if (upward < forward && upward < downward) {
      startingPoint -= 1;
      sum += upward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (forward < upward && forward < downward) {
      sum += forward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (downward < upward && downward < forward) {
      startingPoint += 1;
      sum += downward;
      write << startingPoint << " " << (i + 1) << "\n";
    } else if (upward==forward){
      int choice = rand() % 2;
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else if(upward == downward){
      int choice = rand() % 2;
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else if(forward == downward){
      int choice = rand() % 2;
      if (choice == 0){
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    } else{
      int choice = rand() % 3; 
      if (choice == 0){
        startingPoint -= 1;
        sum += upward;
        write << startingPoint << " " << (i + 1) << "\n";
      }else if (choice == 1){
        sum += forward;
        write << startingPoint << " " << (i + 1) << "\n";
      } else{
        startingPoint += 1;
        sum += downward;
        write << startingPoint << " " << (i + 1) << "\n";
      }
    }
    upward = 9999999;
    forward = 9999999;
    downward = 9999999;
  }
  write.close();

  ofstream write2("Q1B_energy.txt");
  write2 << "\nenergy required: " << sum;
  
  write2.close();
  
  return sum;
}

//Function to time Secnario 1B and to Finf optimal Path
void Q1B(int map[480][844]) {
  int shortestPath = 9999999;
  int shortestStartingPoint = 9999999;

  double start = clock();
  readFileToArray(map);
  for (int i = 0; i < 480; i++) {
    int sum = findPathQ1B(map, i);
    if (sum < shortestPath) {
      shortestStartingPoint = i;
      shortestPath = sum;
    }
  }
  findPathQ1B(map, shortestStartingPoint);
  double end = clock();
  double duration = (end - start) / CLOCKS_PER_SEC;
  cout << "time for Q1B is sec: " << duration << endl;
}

//Function to find optimal path for a starting point
int findPathQ2(int map[480][844], int startingPoint) {
  ofstream write("Q2.txt");
  write << startingPoint << " " << 0 << "\n";
  int sum = 0;
  int min = 9999999;
  for (int i = 0; i < 844 - 1; i++) {
    for (int j=0; j<480;j++){
      if(abs(map[startingPoint][i]-map[j][i+1]) < min){
        min = abs(map[startingPoint][i]-map[j][i+1]);
        startingPoint=j;
      }
    }
    sum+=min;
    write << startingPoint << " " << (i + 1) << "\n";
    
    min=9999999;
}    
  write.close();

  ofstream write2("Q2_energy.txt");
  write2 << "\nenergy required: " << sum;
  write2.close();
  
  return sum;
}

//Function to Time and Find optimal path for Scenario 2
void Q2(int map[480][844]) {
  int shortestPath = 9999999;
  int shortestStartingPoint = 9999999;
  
  double start = clock();
  
  readFileToArray(map);
  for (int i = 0; i < 480; i++) {
    int sum = findPathQ2(map, i);
    if (sum < shortestPath) {
      shortestStartingPoint = i;
      shortestPath = sum;
    }
  }
  findPathQ2(map, shortestStartingPoint);
  double end = clock();
  double duration = (end - start) / CLOCKS_PER_SEC;
  cout << "time for Q2 is sec: " << duration << endl;
}

int main() {

  int startingPoint = 2;
  int map[480][844];
  Q1A(map, startingPoint);
  Q1B(map);
  Q2(map);
  
  cout<<"\nFor Scenario 2, the total number of paths considered is m^(n-2), wher m is the number of columns and n is the number of rows\n\n";

  generateImage("Q1A.txt", "Q1A_image.ppm");
  generateImage("Q1B.txt", "Q1B_image.ppm");
  generateImage("Q2.txt", "Q2_image.ppm");
  return 0;
}