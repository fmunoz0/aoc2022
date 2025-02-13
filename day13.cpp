#include <iostream>
#include <list>
#include <fstream>

using namespace std;

struct Value {
	int type; // 1=integer, 2=list
	void* ptr;
	Value(int val) : type(1), ptr(new int(val)) {}
	explicit Value(const list<Value> &lst) : type(2), ptr(new list<Value>(lst)) {}
	Value(const Value &other) : type(other.type), ptr(other.ptr) {}
	bool isInt() { return type == 1; }
	bool isList() { return type == 2; }
	int getInt() { return *(int*)ptr; }
	list<Value>& getList() { return *(list<Value>*)ptr; }
};

int compare(Value left, Value right);

int compare(const list<Value> &left, const list<Value> &right) {
	auto leftIt = left.begin();
	auto rightIt = right.begin();
	
	while (leftIt != left.end() && rightIt != right.end()) {
		int ret = compare(*leftIt, *rightIt);
		if (ret != 0)
			return ret;
		
		leftIt++;
		rightIt++;
	}
	
	if (left.size() == right.size())
		return 0;
	
	return left.size() < right.size() ? -1 : 1;
}

int compare(int left, int right) {
	if (left == right)
		return 0;
	
	int res = left < right ? -1 : 1;
	//cout << res << endl;
	return res;
}

ostream& operator<<(ostream &os, Value v) {
	if (v.isInt())
		return os << v.getInt();
	
	os << "[";
	size_t i = 0;
	for (Value &val : v.getList())
		os << val << (i++ == v.getList().size() - 1 ? "" : ",");
	os << "]";
	return os;
}

int compare(Value left, Value right) {
	//cout << "compare " << left << " vs " << right << endl;
	
	if (left.isInt() && right.isInt())
		return compare(left.getInt(), right.getInt());
	
	if (left.isList() && right.isList())
		return compare(left.getList(), right.getList());
	
	if (left.isInt() && right.isList())
		return compare({ Value(left) }, right.getList());
	
	return compare(left.getList(), { Value(right) });
}

Value parseValue(const string &str, size_t* len = nullptr) {
	if (str.at(0) == '[') { // list
		list<Value> lst;
		size_t pos = 1;
		while (str.at(pos) != ']') {
			size_t valueLen;
			lst.push_back(parseValue(str.substr(pos), &valueLen));
			pos += valueLen;
			if (str.at(pos) == ',')
				pos++;
		}
		if (len != nullptr)
			*len = pos + 1;
		return Value(lst);
	}
	// integer
	size_t end = str.find_first_of(",]");
	int val = stoi(str.substr(0, end));
	if (len != nullptr)
		*len = end;
	return Value(val);
}

struct Pair {
	Value v1, v2;
};

list<Pair> readPairs(const string &fn) {
	ifstream ifs(fn);
	list<Pair> pairs;
	while (!ifs.eof()) {
		string line;

		getline(ifs, line);
		Value v1 = parseValue(line.substr(0, line.size()-1));

		getline(ifs, line);
		Value v2 = parseValue(line.substr(0, line.size()-1));

		pairs.push_back({v1, v2});
		
		getline(ifs, line); // skip empty line
	}
	return pairs;
}

int main() {
	list<Pair> pairs = readPairs("day13.txt");
	int idx = 1;
	int sum = 0;
	for (const Pair &p : pairs) {
		if (compare(p.v1, p.v2) < 0) {
			//cout << idx << endl;
			sum += idx;
		}
		
		idx++;
	}

	cout << sum << endl;
	
	return 0;
}

