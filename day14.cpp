#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Point {
	int x, y;
};

typedef list<Point> Path;

enum class Tile { AIR, SAND, ROCK };

class Simulation {
	vector<vector<Tile>> tiles;
	bool overflowed;
	int sandStartX;
	
	void fillLine(Point a, Point b);
public:
	Simulation(const list<Path> &paths);
	void step();
	bool finished() { return overflowed; };
	void print();
};

Path parsePath(string str) {
	Path path;
	size_t pos = 0;
	while (pos < str.size()) {
		size_t end = str.find(",", pos);
		int x = stoi(str.substr(pos, end-pos));
		pos = end + 1;
		end = str.find(" ", pos);
		int y = stoi(str.substr(pos, end == string::npos ? end : end - pos));
		path.push_back({x, y});
		if (end == string::npos)
			break;
		pos = end + 3; // +3 to skip "-> "
	}
	return path;
}

list<Path> readInput(string filename) {
	list<Path> paths;
	ifstream ifs(filename);
	while (true) {
		string line;
		getline(ifs, line);
		if (ifs.eof())
			break;
		Path p = parsePath(line);
		paths.push_back(p);
	}
	return paths;
}

int main() {
	list<Path> paths = readInput("day14.txt");
	Simulation sim(paths);
	
	unsigned steps = 0;
	
	while (!sim.finished()) {	
		sim.step();
		steps++;
	}
	
	cout << steps << endl;
	
	return 0;
}

Simulation::Simulation(const list<Path> &paths) : overflowed(false) {
	int xMin = 9999, xMax = 0;
	int yMin = 9999, yMax = 0;
	for (const Path &path : paths) {
		for (Point p : path) {
			xMin = p.x < xMin ? p.x : xMin;
			xMax = p.x > xMax ? p.x : xMax;
			yMin = p.y < yMin ? p.y : yMin;
			yMax = p.y > yMax ? p.y : yMax;
		}
	}
	
	int width = xMax * 2;
	int height = yMax + 2 + 1;
	tiles = vector<vector<Tile>>(height, vector<Tile>(width, Tile::AIR));
	sandStartX = 500;
	for (const Path &path : paths) {
		Point prev = path.front();
		for (Point cur : path) {
			fillLine(prev, cur);
			prev = cur;
		}
	}
	fillLine({0,height-1}, {width-1,height-1});
}

void Simulation::step() {
	int x = sandStartX, y = 0;
	
	while (true) {
		if (y + 1 == tiles.size()) {
			overflowed = true;
			break;
		}
			
		Tile bottom = tiles.at(y + 1).at(x);
		if (bottom == Tile::AIR) {
			y++;
			continue;
		}
		
		if (x == 0) {
			overflowed = true;
			break;
		}
		
		Tile bottomLeft = tiles.at(y + 1).at(x - 1);
		if (bottomLeft == Tile::AIR) {
			y++;
			x--;
			continue;
		}
		
		if (x + 1 == tiles.at(0).size()) {
			overflowed = true;
			break;
		}
		
		Tile bottomRight = tiles.at(y + 1).at(x + 1);
		if (bottomRight == Tile::AIR) {
			y++;
			x++;
			continue;
		}
			
		// can't move in any directions
		
		// finish simulation if the source is blocked
		if (x == sandStartX && y == 0)
			overflowed = true;

		// finish simulation step
		tiles.at(y).at(x) = Tile::SAND;
		break;
	}
}

// a and b are points inside the tile matrix
void Simulation::fillLine(Point a, Point b) {
	int xMin = min(a.x, b.x);
	int xMax = max(a.x, b.x);
	int yMin = min(a.y, b.y);
	int yMax = max(a.y, b.y);
	
	for (int y = yMin; y <= yMax; y++)
		for (int x = xMin; x <= xMax; x++)
			tiles.at(y).at(x) = Tile::ROCK;
}

void Simulation::print() {
	for (int y = 0; y < tiles.size(); y++) {
		for (int x = 0; x < tiles.at(0).size(); x++) {
			if (y == 0 && x == sandStartX)
				cout << "+";
			else {
				switch (tiles.at(y).at(x)) {
					case Tile::AIR: cout << "."; break;
					case Tile::ROCK: cout << "#"; break;
					case Tile::SAND: cout << "o"; break;
				}
			}
		}
		cout << endl;
	}
}