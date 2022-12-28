#include <iostream>
#include <locale.h>
#include <queue>
#include <string>
#include <vector>
#include <stack>
using namespace std;


class Node
{
public:
	Node(char data = int(), Node *pLeft = nullptr, Node *pRight = nullptr)
	{
		this->data = data;
		this->pLeft = pLeft;
		this->pRight = pRight;
	}

	char data;
	Node *pLeft, *pRight;
};


bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

void preorder(Node *node)
{
	if (node != nullptr)
	{
		cout << node->data << " ";
		preorder(node->pLeft);
		preorder(node->pRight);
	}
}

void inorder(Node *node, bool isLeft = false, bool isRight = false)
{
	if (node != nullptr)
	{
		inorder(node->pLeft, true);
		if (isLeft && !isOperator(node->data)) cout << "(";
		cout << node->data;
		if (isRight && !isOperator(node->data)) cout << ")";
		cout << " ";
		inorder(node->pRight, false, true);
	}
}

void postorder(Node *node)
{
	if (node != nullptr)
	{
		postorder(node->pLeft);
		postorder(node->pRight);
		cout << node->data << " ";
	}
}

void bfs(Node *node)
{
	if (node != nullptr)
	{
		queue <Node*> q;
		q.push(node);

		while (q.empty() == false)
		{
			Node *temp = q.front();
			cout << " " << temp->data;
			q.pop();

			if (temp->pLeft != nullptr)
				q.push(temp->pLeft);

			if (temp->pRight != nullptr)
				q.push(temp->pRight);
		}
	}
	cout << endl;
}

void printRight(Node *node, int level = 0);
void printLeft(Node *node, int level = 0);

void printRight(Node *node, int level)
{
	if (node->pRight != nullptr) printRight(node->pRight, level + 1);
	system("color 03");				//С наступающим Новым годом!
	for (int i = 0; i < level - 1; i++)
		cout << "    ";
	if (level)
		cout << "/```";
	cout << node->data << endl;
	if (node->pLeft != nullptr) printLeft(node->pLeft, level + 1);
}

void printLeft(Node *node, int level)
{
	if (node->pRight != nullptr) printRight(node->pRight, level + 1);
	system("color 02");
	for (int i = 0; i < level - 1; i++)
		cout << "    ";
	if (level)
		cout << "\\...";
	cout << node->data << endl;
	if (node->pLeft != nullptr) printLeft(node->pLeft, level + 1);
}

void print(Node *node, int level = 0)
{
	Node *temp = node;
	while (temp->pLeft != nullptr || temp->pRight != nullptr)
	{
		if (node->pRight != nullptr)
		{
			//print(temp->pRight, level + 1);
			printRight(temp->pRight, level + 1);
		}
		/*for (int i = 0; i < level-1; i++)
				cout << "    ";
		if (level)
			cout << "\\---";*/
		cout << temp->data << endl;
		if (temp->pLeft != nullptr)
		{
			//print(temp->pRight, level + 1);
			printLeft(temp->pLeft, level + 1);
		}
		cout << endl;
		system("color 07");
		return;
	}
}



Node* postfix_to_tree(string str)
{
	stack<Node*> s;

	for (int i = 0; i < str.size(); i++)
	{
		if (isOperator(str[i]))
		{
			Node *x = s.top();
			s.pop();

			Node *y = s.top();
			s.pop();

			Node *node = new Node(str[i], y, x);

			s.push(node);
		}
		else if (str[i] != ' ')
		{
			s.push(new Node(str[i]));
		}
	}

	return s.top();
}

Node* prefix_to_tree(string str)
{
	stack<Node*> s;

	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (isOperator(str[i]))
		{
			Node *x = s.top();
			s.pop();

			Node *y = s.top();
			s.pop();

			Node *node = new Node(str[i], x, y);

			s.push(node);
		}
		else if (str[i] != ' ')
		{
			s.push(new Node(str[i]));
		}
	}

	return s.top();
}

const string priority = "(+-*/";

bool whoIsPriorititityyy(char a, char b)
{
	int newa;
	int newb;
	for (int i = 0; i < priority.size(); i++)
	{
		if (a == priority[i]) newa = i;
		if (b == priority[i]) newb = i;
	}
	return newa > newb;
}

Node* infix_to_tree(string str)
{
	/*int sizestr = str.size();
	stack<Node*> s;
	queue<char> q;
	int newstr;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] != ' ') newstr += str[i];
	}

	for (int i = 0; i < priority.size(); i++)
	{
		for (int j = 0; i < str.size(); j++)
		{

		}
	}


	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
		{
			string newstr;
			i++;
			while (str[i] != ')')
			{
				newstr += str[i];
				i++;
			}
			Node *temp = infix_to_tree(newstr);

			if (q.empty())
				s.push(temp);
			else
			{
				Node *x = temp;
				Node *y = s.top();
				s.pop();

				Node *node = new Node(q.front(), y, x);
				q.pop();
				s.push(node);
			}
		}
		else if (isOperator(str[i]))
		{
			q.push(str[i]);
			/*char o = str[i];
			Node *x = s.top();
			s.pop();

			
			do
			{
				i++;
			} while (str[i] == ' ');
			Node *y = new Node(str[i]);

			Node *node = new Node(o, x, y);

			s.push(node);*/
		/*}
		else if (str[i] != ' ')
		{
			if (q.empty())
				s.push(new Node(str[i]));
			else
			{
				Node *x = new Node(str[i]);
				Node *y = s.top();
				s.pop();
				if (isOperator(y->data))
				{
					const string priority = "+-*\/";
					int a;
					int b;
					for (int j = 0; j < priority.size(); j++)
					{
						if (y->data == priority[j]) a = j;
						if (str[i] == priority[j]) b = j;
					}
					if (a > b)
					{
						Node *node = new Node(q.front(), y, x);
						q.pop();
						s.push(node);
					}
				}

				Node *node = new Node(q.front(), y, x);
				q.pop();
				s.push(node);
			}

		}
	}

	return s.top();*/
	stack<char> s;
	queue<char> q;

	/*for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
		{
			s.push(str[i]);
		}
		if (str[i] == ')')
		{
			while (s.top() != '(')
			{
				q.push(s.top());
				s.pop();
			}
			s.pop();
		}
		if (str[i] == '+' || str[i] == '-')
		{
			if (s.empty() || s.top() == '(')
			{
				s.push(str[i]);
			}
			else if (s.top() == '*' || s.top() == '/')
			{
				while (s.top() != '+' || s.top() != '-' || s.top() != '(')
				{
					q.push(s.top());
					s.pop();
				}
				s.push(str[i]);
			}
			else
			{
				s.push(str[i]);
			}
		}
		if (str[i] == '*' || str[i] == '/')
		{
			if (s.top() == '*' || s.top() == '/')
			{
				s.pop();
			}
				s.push(str[i]);
		}
		else if (str[i] != ' ')
		{
			q.push(str[i]);
		}
	}*/


	for (int i = 0; i < str.size(); i++)
	{
		if (isOperator(str[i]))
		{
			if (s.empty() || s.top() == '(')
			{
				s.push(str[i]);
			}

			else if (whoIsPriorititityyy(str[i], s.top()))
			{
					s.push(str[i]);
			}
			else if (whoIsPriorititityyy(s.top(), str[i]) || s.top() == str[i])
			{
				while (s.top() != '(' || whoIsPriorititityyy(str[i], s.top()) || !s.empty())
				{
					q.push(s.top());
					s.pop();
				}
				s.push(str[i]);
			}
		}
		else if (str[i] == '(')
		{
			s.push(str[i]);
		}
		else if (str[i] == ')')
		{
			while (s.top() != '(')
			{
				q.push(s.top());
				s.pop();
			}
			s.pop();
		}
		else if (str[i] != ' ')
		{
			q.push(str[i]);
		}
	}
	while (!s.empty())
	{
		q.push(s.top());
		s.pop();
	}

	string newstr;
	while (!q.empty())
	{
		newstr += q.front();
		q.pop();
	}
	cout << newstr << endl;
	return postfix_to_tree(newstr);
}

int main() {
	setlocale(LC_ALL, "ru");

	cout << "Введите префиксное выражение (используются только +, -, *, \\" << endl;
	string str;
	getline(cin, str);
	Node *tree1 = prefix_to_tree(str);
	print(tree1);
	cout << "Инфиксная запись: ";
	inorder(tree1);
	cout << endl;
	cout << "Постфиксная запись: ";
	postorder(tree1);
	cout << endl;

	cout << "Введите инфиксное выражение (используются только +, -, *, \\" << endl;
	getline(cin, str);
	Node *tree2 = infix_to_tree(str);
	print(tree2);
	cout << "Префиксная запись: ";
	preorder(tree2);
	cout << endl;
	cout << "Постфиксная запись: ";
	postorder(tree2);
	cout << endl;

	cout << "Введите постфиксное выражение (используются только +, -, *, \\" << endl;
	getline(cin, str);
	Node *tree3 = postfix_to_tree(str);
	print(tree3);
	cout << endl;
	cout << "Инфиксная запись: ";
	inorder(tree3);
	cout << endl;
	cout << "Префиксная запись: ";
	preorder(tree3);
	cout << endl;

}


