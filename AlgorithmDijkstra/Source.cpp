#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

const int INF = 9999; // "бесконечность"

void InputSize(ifstream& input, int& n) { // кол-во вершин
	string x;
	input >> x;
	n = stoi(x);
}

void InputData(int& n, vector<vector<int>>& mas, vector<int>& distance, vector<int>& p, int& a, int& b, ifstream& input) {
	string x;
	// матрица смежности с расстояниями
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			input >> x;
			if (x != "~") mas[i][j] = stoi(x);
			else mas[i][j] = INF;
		}
	input >> x;
	a = stoi(x) - 1; // индекс исходной вершины
	input >> x;
	b = stoi(x) - 1; // индекс конечной вершины
	for (int i = 0; i < n; i++) {
		distance[i] = INF; // массив с расстояниями
		p[i] = -1; // для хранения пути
	}
	distance[a] = 0;
}

int TakeNextW(vector<int>& distance, int n, vector<bool>& checked) {
	int minW = 0, min = INF;
	for (int i = 0; i < n; i++)
		if (distance[i] < min && checked[i] == false) {
			minW = i;
			min = distance[i];
		}
	return minW;

}

void WorkDijkstra(vector<vector<int>>& mas, vector<int>& distance, vector<int>& p, vector<bool>& checked, int n, int a) {
	int w = a; // текущая рассматриваемая вершина
	checked[w] = true;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++)
			if (checked[i] == false && mas[w][i] + distance[w] < distance[i]) {
				distance[i] = mas[w][i] + distance[w];
				p[i] = w;
			}
		w = TakeNextW(distance, n, checked);
		checked[w] = true;
	}
}

void Way(int b, vector<int>& p, ofstream& output) {
	deque<int> res;
	res.push_back(b + 1);
	int temp = b;
	while (p[temp] != -1) {
		temp = p[temp];
		res.push_front(temp + 1);
	}
	for (int elem : res) output << elem << ' ';
}

int main() {
	int start = clock();
	int n, a, b;
	ifstream input("input.txt");
	ofstream output("output.txt");
	string x;
	InputSize(input, n);
	vector<vector<int>> mas(n, vector<int>(n));
	vector <int> distance(n);
	vector <int> p(n);
	vector <bool> checked(n);
	InputData(n, mas, distance, p, a, b, input);
	WorkDijkstra(mas, distance, p, checked, n, a);
	output << distance[b] << endl;
	Way(b, p, output);
	int end = clock();
	output << endl << "Time: " << (end - start); // время работы в секундах
	input.close();
	output.close();
}