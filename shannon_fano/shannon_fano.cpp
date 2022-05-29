#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

bool cmp(std::pair<char, int>& a,
	std::pair<char, int>& b)
{
	return a.second < b.second;
}

std::pair<std::string, std::string> lessDiff(std::string in, std::vector<std::pair<char, int>> probMap)
{
	//create product map with symbols existing in string
	std::vector<std::pair<char, int>> newProbMap;
	for (size_t i = 0; i < probMap.size(); i++)
	{
		for (size_t j = 0; j < in.length(); j++)
		{
			if (probMap[i].first == in[j])
			{
				newProbMap.push_back(std::pair<char, int>(probMap[i].first, probMap[i].second));
			}
		}
	}

	int l = 0;
	std::string lstr = "";
	for (size_t i = 0; i < newProbMap.size(); i++)
	{
		int rest = 0;
		for (size_t j = i + 1; j < newProbMap.size(); j++)
		{
			rest += newProbMap[j].second;
		}
		if (rest > l)
		{
			l += newProbMap[i].second;
			lstr += newProbMap[i].first;
		}
	}
	std::string rstr = in.substr(lstr.length(), in.length());
	return std::pair<std::string, std::string>(lstr, rstr);
}

class Node
{
public:

	std::string data;
	int value;
	Node* left;
	Node* right;
	std::vector<std::pair<std::string, std::string>> ssval;
	std::string zeros;
	std::string ones;
	std::vector<std::pair<std::string, int>> test;
	std::vector<std::pair<std::string, std::string>> codes;
	bool isSsvalSet;

	Node()
	{
		left = nullptr;
		right = nullptr;
		isSsvalSet = false;
		value = 0;
	}

	Node(std::string ndata) : data(ndata), value(0) {
		left = nullptr;
		right = nullptr;
		isSsvalSet = false;
		value = 0;
	}
	Node(std::string ndata, int nvalue) : data(ndata), value(nvalue) {
		left = nullptr;
		right = nullptr;
		isSsvalSet = false;
	}

	bool makeLeaves(Node* actual, std::vector<std::pair<char, int>> sorted_symbols)
	{
		if (isSsvalSet == false)
		{
			for (size_t i = 0; i < sorted_symbols.size(); i++)
			{
				ssval.push_back(std::pair(std::string(1, sorted_symbols[i].first), ""));
			}
			isSsvalSet = true;
		}
		
		if (actual != nullptr && actual->data.length() > 1)
		{
			actual->left = new Node(lessDiff(actual->data, sorted_symbols).first, 0);
			actual->right = new Node(lessDiff(actual->data, sorted_symbols).second, 1);
			bool a = makeLeaves(actual->left, sorted_symbols);
			bool b = makeLeaves(actual->right, sorted_symbols);
			return a && b;
		}
		else
		{
			return false;
		}
		return false;
	}

	bool print(Node* node, std::vector<std::pair<std::string, int>>& vec)
	{
		if (node!=nullptr)
		{
			//std::cout <<  node->data << " " << node->value << std::endl;
			vec.push_back(std::pair<std::string, int>(node->data, node->value));
			bool a = node->print(node->left, vec);
			bool b = node->print(node->right, vec);
			return a&&b;
		}
		else
		{
			
			return false;
		}
		std::cout << "#\n";
	}

	void printCodes(std::vector<std::pair<char, int>> &ss)
	{
		for (size_t i = 0; i < ss.size(); i++)
		{
			codes.push_back(std::pair < std::string, std::string>(std::string(1, ss[i].first), ""));
		}

		test.erase(test.begin());
		for (size_t i = 0; i < test.size(); i++)
		{
			std::string str = test[i].first;
			std::string value = std::to_string(test[i].second);

			for (size_t j = 0; j < str.length(); j++)
			{
				for (size_t k = 0; k < codes.size(); k++)
				{
					std::string letter(1, str[j]);
					if (letter == codes[k].first)
					{
						codes[k].second += value;
					}
				}
			}

		}


		

		//show codes
		for (size_t i = 0; i < codes.size(); i++)
		{
			std::cout << codes[i].first << " " << codes[i].second << std::endl;
		}

	}

	~Node()
	{
		delete left;
		delete right;
	}

};

int main()
{
	std::string str = "";   //aaaaabbbbcccdde d = 1110 e=1111
	std::cout << "Podaj ciag znakow: ";
	std::cin >> str;
	std::map<char, int> symbols;

	for (size_t i = 0; i < str.length(); i++)
	{
		symbols[str[i]]++;
	}

	std::vector<std::pair<char, int> > sorted_symbols;
	for (auto it = symbols.cbegin(); it != symbols.cend(); ++it)
	{
		std::cout << it->first << " " << it->second << "\n";
		sorted_symbols.push_back(std::make_pair(it->first, it->second));
	}
	std::cout << "\n";

	std::sort(sorted_symbols.begin(), sorted_symbols.end(), cmp);
	std::reverse(sorted_symbols.begin(), sorted_symbols.end());

	std::string sss = "";

	for (size_t i = 0; i < sorted_symbols.size(); i++)
	{
		sss += sorted_symbols[i].first;
	}

	for (size_t i = 0; i < sorted_symbols.size(); i++)
	{
		std::cout << sorted_symbols[i].first << " " << sorted_symbols[i].second << std::endl;
	}

	Node tree;
	tree.data = sss;

	tree.makeLeaves(&tree, sorted_symbols);

	Node* actual = &tree;

	bool working = true;
	do
	{
		working = actual->makeLeaves(actual, sorted_symbols);
	} while (working != false);

	actual->print(actual, actual->test);
	actual->printCodes(sorted_symbols);
	char b = 'b';
}


