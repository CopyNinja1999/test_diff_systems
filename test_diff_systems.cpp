#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cmath>
#include <deque>
#include <queue>
#include <string>
#include <sstream>
//#include "Vertice.h"
//#include "Graph.h";
using namespace std;
using std::vector;
using std::stack;//neccessary
using std::queue;
vector<vector<int> > adj;//record the neighbours
struct vertice {
	size_t postOrder = 0;
	size_t preOrder = 0;
	size_t ccNum = 0;
	size_t index = 0;
	bool visited = false;
};
vertice* v;//record the status
size_t random(int r, int b) {
	size_t random;
	random = (rand() % (b - r + 1)) + r;//represents [r,b]

//	cout << random << endl;
	return random;
}
bool equal(vector<int>& temp, size_t x) {
	//if one veritce adjecancy list temp owns the same element x, this function will return true
	size_t n = temp.size();
	bool equal = false;
	if (n == 0) {
		return false;
	}
	else {
		for (size_t c = 0; c < n; c++)
		{
			if (c >= n || c < 0) {
				cout << "vetcor out of range" << endl;
				break;
			}
			if (temp[c] == (int)x)
			{
				equal = true;
				return equal;
			}

		}
		return equal;
	}
}
void generateD(size_t n, size_t m)
{

	cout << "Directed graph generated:" << endl;
	cout << "n=" << n << " m=" << m << endl;
	adj = vector<vector<int> >(n, vector<int>());
	v = new vertice[n];
	for (size_t i = 0; i < n; i++) {
		v[i].index = i;
	}
	for (size_t i = 0; i < m; i++)//push m lines in template vector
	{
		size_t j, k;
		j = random(1, n); //[1,n]
		while (true) {
			if (adj[j - 1].size() == n - 1)
			{
				j = random(1, n);
			}
			else
				break;
		}
		k = random(1, n);
		while (true) {
			if (j == k) {
				k = random(1, n);

			}
			else break;
		}
		if (!equal(adj[j - 1], k - 1))  // if elements are not repeatd or are empty, return false, push element to the back
		{
			adj[j - 1].push_back(k - 1);
		}
		else {
			//make sure there are exactly m edges in the graph, in case the vector has the same elements.
			while (true)
			{
				k = random(1, n);
				if (!equal(adj[j - 1], k - 1) && k != j)//
				{
					adj[j - 1].push_back(k - 1);
					break;
				}
			};

		}
	}
}
void dfsStack() {
	//using naive c++ stl stack
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	stack<vertice> S;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) { continue; }
		else
			v[k].visited = true;//start point v[0]
		S.push(v[k]);
		while (!S.empty())
		{
			vertice u = S.top();
			S.pop();//these two steps represent the operation pop
			size_t m = adj[u.index].size();
			int  index = -1;
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					index = i;
					break;
				}
			}
			if (index != -1)
			{
				S.push(u);
				v[index].visited = true;
				S.push(v[index]);
			}
		}
	}


	//S.~stack<vertice>();//release memory
}
void dfsDeque() {
	size_t n = adj.size();
	for (size_t i = 0; i < n; i++)
	{
		v[i].visited = false;
	}
	deque<vertice> D;
	for (size_t k = 0; k < n; k++) {
		if (v[k].visited) { continue; }
		else
			v[k].visited = true;//start point v[0]
		D.push_front(v[k]);
		while (!D.empty())
		{
			vertice u = D.front();
			D.pop_front();
			size_t m = adj[u.index].size();
			int index = -1;
			for (size_t j = 0; j < m; j++)
			{
				size_t i = adj[u.index][j];
				if (!v[i].visited)
				{
					index = i;
					break;
				}
			}
			if (index != -1)
			{
				D.push_front(u);
				v[index].visited = true;
				D.push_front(v[index]);
			}
		}
	}
	//D.~deque<vertice>();//release memory

}
void test_directed() {
	ofstream exp_data("directed_test.txt");// For the convenience of analyzing
	size_t n, m;

	for (size_t i = 1; i < 50; i++) {
		n = 10000 * i;
		m = n + 2;
		//m = (size_t)(pow(n, 2) - n - 2) / 2;// m ->n^2
		//generateD(n, m);
		generateD(n, m);
		clock_t t1, t2, t3;
		t1 = clock();//get current time
		dfsStack();
		t2 = clock();
		double dif1, dif2;
		dif1 = difftime(t2, t1);
		dfsDeque();
		t3 = clock();
		dif2 = difftime(t3, t2);
		exp_data << n << " " << dif1 << " " << dif2 << "\n";
	}
	exp_data.close();
}
int main(int argc, char* argv[]) {

srand((int)time(NULL));  // generate random seeds, use and only use once, ensure that every execuation is random
	test_directed();
	return 0;
}