#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include <algorithm>
using namespace std;

struct Node
{
	string name;
	Node* left_child;
	Node* right_child;
	Node* parent;
	int level;
};

class RelationshipNodes
{
public:	
	void insert( string parent,  string child)
	{
		Node* node_parent = this->search(parent);
		//if (node_parent == nullptr)
		Node* node_child = this->search(child);
		
		if (node_parent == nullptr && node_child == nullptr)
		{
			node_parent = new Node{ parent, nullptr, nullptr, nullptr, 0 };
			this->nodes.push_back(node_parent);

			node_child = new Node{ child, nullptr, nullptr, node_parent, 1 };
			this->nodes.push_back(node_child);
		}
		else if (node_parent && node_child == nullptr)
		{
			node_child = new Node{ child, nullptr, nullptr, node_parent, node_parent->level + 1 };
			this->nodes.push_back(node_child);
			this->resetLevel(node_child);
		}
		else if (node_parent == nullptr && node_child)
		{
			node_parent = new Node{ parent, nullptr, nullptr, nullptr, 0 };
			this->nodes.push_back(node_parent);

			node_child->parent = node_parent;
			this->resetLevel(node_child);
		}
		else
		{
			node_child->parent = node_parent;
			this->resetLevel(node_child);
		}

		if (node_parent->left_child)
		{
			if (parent.compare(child) >= 0)
				node_parent->right_child = node_child;
			else
			{
				node_parent->right_child = node_parent->left_child;
				node_parent->left_child = node_child;
			}
		}
		else
		{
			node_parent->left_child = node_child;
		}
	}
	Node* search( string name)
	{
		for (Node* node : this->nodes)
		{
			if (node->name.compare(name) == 0)
				return node;
		}
		return nullptr;
	}
	void printRelationshipNodes()
	{
		 vector< vector< string>> levels;
		for (Node* node : this->nodes)
		{
			while (node->level >= levels.size())
			{
				levels.push_back( vector< string>());
			}
			levels[node->level].push_back(node->name);
		}
		for (int i = 0; i < levels.size(); i++)
		{
			sort(levels[i].begin(), levels[i].end(),  greater< string>());
			 cout << "Level " << i + 1;
			for (int j = 0; j < levels[i].size(); j++)
			{
				if (j == 0)
					 cout << ": ";
				else
					 cout << ", ";
				 cout << levels[i][j];
			}
			 cout <<  endl;
		}
	}
	 vector< string> findDistance( string name1,  string name2)
	{
		Node* node1 = this->search(name1);
		Node* node2 = this->search(name2);

		 vector< string> path1;
		 vector< string> path2;

		while (node1 != node2)
		{
			if (node1->level > node2->level)
			{
				path1.push_back(node1->name);
				node1 = node1->parent;
			}

			else if (node1->level < node2->level)
			{
				path2.push_back(node2->name);
				node2 = node2->parent;
			}

			else
			{
				path1.push_back(node1->name);
				path2.push_back(node2->name);

				node1 = node1->parent;
				node2 = node2->parent;
			}
		}
		 vector< string> path;
		for (int i = 0; i < path1.size(); i++)
		{
			path.push_back(path1[i]);
		}
		path.push_back(node1->name);
		for (int i = path2.size() - 1; i >= 0; i--)
		{
			path.push_back(path2[i]);
		}
		return path;
	}
private:
	void resetLevel(Node* node)
	{
		if (node)
		{
			node->level = node->parent->level + 1;
			this->resetLevel(node->left_child);
			this->resetLevel(node->right_child);
		}
	}
	 vector<Node*> nodes;
};


int main() {
	RelationshipNodes RelationshipNodes;
	int N, M;
	std::cin >> N;
	while (N--)
	{
		std::string P, C;
		std::cin >> P >> C;
		RelationshipNodes.insert(P, C);
	}
	RelationshipNodes.printRelationshipNodes();

	std::cin >> M;
	while (M--)
	{
		std::string A, B;
		std::cin >> A >> B;
		std::vector<std::string> path = RelationshipNodes.findDistance(A, B);
		for (int i = 1; i < path.size(); i++)
		{
			std::cout << "Distance Count: " << i << std::endl;
			std::cout << path[i] << std::endl;
		}
		std::cout << path.size() - 1 << std::endl;
	}
	return 0;
}