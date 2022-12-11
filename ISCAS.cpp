#include <conio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <regex>
#include <math.h>
#include <cstring>

using namespace std;
string myArray[41][8];
int LineNUM = 0;


int Tokenize()
{
	int OT = 0, CL = 0, count = 0;
	ifstream fin;
	string line, s, str, address = "C:\\Users\\Morteza\\Pictures\\c17.isc.txt";
	queue <string> q;
	vector<string> tokens;
	fin.open(address);
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			LineNUM = LineNUM + 1;
			stringstream ss(line);
			q.push(ss.str());
		}
	}
	fin.close();
	const int Nline = OT;
	cout << "The size of queue is: " << q.size() << "\n";
	count = 0;


	while (!q.empty())
	{
		str = q.front();
		q.pop();

		regex reg("\\s+");
		sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
		sregex_token_iterator end;
		vector<string> tokens(iter, end);
		//cout << str << "\n";
		CL = 0;
		//cout << "string is :";
		for (const string &s : tokens) {
			myArray[count][CL] = s;
			//cout << myArray[count][CL] << " ";
			CL = CL + 1;
		}
		//cout << endl;
		count = count + 1;
	}


	return 0;
}
int ANDG(int PI1, int PI2)
{
	if (PI1 == 0 || PI2 == 0)
	{
		return 0;
	}
	else if (PI1 == 1 && PI2 == 1) {
		return 1;
	}
	else {
		return 2;
	}
}
int OR(int PI1, int PI2)
{
	if (PI1 == 1 || PI2 == 1)
	{
		return 1;
	}
	else if (PI1 == 0 && PI2 == 0) {
		return 0;
	}
	else {
		return 2;
	}
}
int NOT(int PI1)
{
	if (PI1 == 1)
		return 0;
	else if (PI1 == 0)
		return 1;
	else
		return 2;
}
int XOR(int PI1, int PI2)
{
	if (PI1 + PI2 == 1)
	{
		return 1;
	}
	else if (PI1 == 0 && PI2 == 0) {
		return 0;
	}
	else if (PI1 == 1 && PI2 == 1) {
		return 0;
	}
	else {
		return 2;
	}
}
int XNOR(int PI1, int PI2)
{
	if (PI1 + PI2 == 1)
	{
		return 0;
	}
	else if (PI1 == 0 && PI2 == 0) {
		return 1;
	}
	else if (PI1 == 1 && PI2 == 1) {
		return 0;
	}
	else {
		return 2;
	}
}
int condition(string str)
{
	if (str == "from")
		return 0;
	if (str == "inpt")
		return 1;
	if (str == "and")
		return 2;
	if (str == "or")
		return 3;
	if (str == "not")
		return 4;
	if (str == "xor")
		return 5;
	if (str == "xnor")
		return 6;
	if (str == "nand")
		return 7;
	if (str == "nor")
		return 8;
	if (str == "buff")
		return 9;
}

int main()
{
	printf("--------------------------ISCAS module----------------------------\n");
	int count=1;
	Tokenize();
	int* node = (int*)malloc(stoi(myArray[6][7]) * sizeof(int));
	int* Input = (int *)malloc(sizeof(int) * (LineNUM - 17));
	cout << "##############################################################################################################"<<endl;
	cout << "Number of Primery input is :  " << stoi(myArray[6][7]) << endl;
	cout << "Please Enter primary inputs" << endl;
	for (int j = 1; j <= LineNUM - 18; j++) {
		if (myArray[j + 17][3] == "inpt")
		{
			cout << "Enter PI " << count << " = ";
			cin >> Input[j];
			count += 1;
		}
		else
		{
			Input[j] = 3;
		}
	}
	for (int i = 18; i < LineNUM; i++) {
		switch (condition(myArray[i][3])) {
		case 0:
			for (int N = 18; N < i; N++)
			{
				if (myArray[i][4] == myArray[N][2])
				{
					Input[stoi(myArray[i][1])] = Input[stoi(myArray[N][1])];
				}
					
			}
			break;
		case 1:
			break;
		case 2:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {

				node[P] = ANDG(node[P - 1], node[P]);

			}
			Input[stoi(myArray[i][1])] = node[stoi(myArray[i][5]) - 1];
			break;
		case 3:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {

				node[P] = OR(node[P - 1], node[P]);

			}
			Input[stoi(myArray[i][1])] = node[stoi(myArray[i][5]) - 1];
			break;
		case 4:
			node[0] = Input[stoi(myArray[i + 1][1])];

			Input[stoi(myArray[i][1])] = NOT(node[0]);
			break;
		case 5:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {

				node[P] = XOR(node[P - 1], node[P]);

			}
			Input[stoi(myArray[i][1])] = node[stoi(myArray[i][5]) - 1];
			break;
		case 6:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {

				node[P] = XNOR(node[P - 1], node[P]);
			}
			Input[stoi(myArray[i][1])] = node[stoi(myArray[i][5]) - 1];
			break;
		case 7:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {

				node[P] = ANDG(node[P - 1], node[P]);

			}
			Input[stoi(myArray[i][1])] = NOT(node[stoi(myArray[i][5]) - 1]);
			break;
		case 8:
			for (int N = 1; N <= stoi(myArray[i][5]); N++)
				node[N - 1] = Input[stoi(myArray[i + 1][N])];

			for (int P = 1; P <= stoi(myArray[i][5]); P++) {
				node[P] = OR(node[P - 1], node[P]);
			}
			Input[stoi(myArray[i][1])] = NOT(node[stoi(myArray[i][5]) - 1]);
			break;
		case 9:
			Input[stoi(myArray[i][1])] = Input[stoi(myArray[i + 1][1])];
			break;
		default:
			break;
		}
	}
	cout << "################################################ OUTPUT ###################################################" << endl;
	count = 1;
	for (size_t i = 18; i < LineNUM; i++)
	{
		if (myArray[i][4]=="0")
		{
			cout << "PO " << count << " = " << Input[stoi(myArray[i][1])] << endl;
			count += 1;
		}

	}




	_getch();
	return 0;
}
