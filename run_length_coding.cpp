#include <iostream>
#include <cmath>
#include <string>
using namespace std;

//Function needed to convert int to binary string on the go
string int2bin(int a)
{
	if (a == 0)
		return "0";
	if (a == 1)
		return "1";
	return int2bin(a/2) + to_string(a%2);
}

//Function needed to convert a run length to particular number of bits
string fixlength(string str, int l)
{
	if (str.length() >= l)
		return str;
	return "0" + fixlength(str, l-1);
}

int main()
{
	cout << "Enter binary string data :" << endl;
	string data;
	cin >> data;
	
	//Finding average number of bits required
	int min = 10000, max = 0;
	char state = data[0];
	int count = 0;
	for (int i=0; i<data.length(); i++)
	{
		if(data[i] == state)
			count++;
		else
		{
			if (count < min)
				min = count;
			if (count > max)
				max = count;
			state = data[i];
			count = 1;
		}
	}
	int avg_bits = ceil(log2(min*max)/2);
	cout << "Bits per run = " << avg_bits << endl;

	//Compressing the data
	count = 0;
	state = '0';
	for (int i=0; i<data.length(); i++)
	{
		if(state == data[i])
			count++;
		else
		{
			cout << fixlength(int2bin(count), avg_bits);
			count = 1;
			state = data[i];
		}
		if(count >= pow(2, avg_bits) -1)
		{
			cout << fixlength(int2bin(count), avg_bits);
			count = 0;
			state = (state == '0' ? '1' : '0');
		}
	}
	cout << fixlength(int2bin(count), avg_bits) <<  endl;
}
