#include <msgpack.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;
bool compare(pair<char*, char*> i, pair<char*, char*> j)
{
	if (strcmp(i.second, j.second) < 0)
		return true;
	else
		return false;
}
int main(void) {
	fstream input, output;
	size_t off = 0;
	vector<string> arr, finish;
	vector<pair<char*, char*>> ans;
	string fin;
	int bufsize, num, num2, num3, i, j, k, m, p;
	char *buf = NULL;
	msgpack::sbuffer sbuf;

	input.open("input.txt", fstream::in | fstream::binary);

	input.seekg(0, ios::end);
	bufsize = input.tellg();
	input.seekg(0);

	buf = new char[bufsize];
	input.read(buf, bufsize);

	msgpack::object_handle oh;
	oh = msgpack::unpack(buf, bufsize, off);
	oh.get().convert(arr);
	num = stoi(arr[0]);
	for (i = 1; i < 2*num+1; i = i+2)
	{
		num2 = stoi(arr[i]);
		num3 = stoi(arr[i+1]);
		vector<char*> name, number;
		pair<char*, char*> temp;
		char *pch, *pch1, *str1 = new char[arr[i].length() + 1], *str2 = new char[arr[i + 1].length() + 1];
		strcpy(str1, arr[i].c_str());
		strcpy(str2, arr[i+1].c_str());
		pch = strtok(str1, " \n");
		for (j = 0; j < num2; j++)
		{
			pch = strtok(NULL, " \n");
			name.push_back(pch);
			pch = strtok(NULL, " \n");
			number.push_back(pch);
		}
		pch1 = strtok(str2, " \n");
		for (j = 0; j < num3; j++)
		{
			int ans1;
			pch1 = strtok(NULL, " \n");
			int failure[20];
///////////////////////////////////////////////////////////////////////////
			m = -1;
			failure[0] = -1;
			for (k = 0; pch1[k] != '\0'; k++)
			{
				if (k != 0)
				{
					// Failure function
					while (m >= 0 && pch1[m + 1] != pch1[m])
					{
						m = failure[m];
					}
					if (pch1[m + 1] == pch1[m])
					{
						m++;
					}
					failure[k] = m;
				}
			}
			for (p = 0; p < num2; p++)
			{
				for (k = 0, m = 0; number[p][k] != '\0'; k++)
				{
					// KMP
					if (pch1[m] == number[p][k])
					{
						// Decide whether to print
						if (pch1[m + 1] == '\0')
						{
							temp = make_pair(name[p], number[p]);
							ans.push_back(temp);
							break;
						}
						m++;
					}
					else
					{
						while (m >= 0 && pch1[m] != number[p][k])
						{
							if (m > 0)
							{
								m = failure[m - 1];
							}
							else
							{
								m = -1;
							}
						}
						m++;
					}
				}
			}
////////////////////////////////////////////////////////////////////////////////////////
			sort(ans.begin(), ans.end(), compare);
			for (k = 0; k < ans.size(); k++)
			{
				if (j == num3 - 1 && k == ans.size() - 1)
				{
					string one(ans[k].first), two(ans[k].second);
					fin = fin + one + " " + two;
				}
				else
				{
					string one(ans[k].first), two(ans[k].second);
					fin = fin + one + " " + two + " ";
				}
			}
			ans.clear();
		}
		finish.push_back(fin);
		fin.clear();
	}
	msgpack::pack(sbuf,finish);
	delete[] buf;
	input.close();
	output.open("output.txt", fstream::out | fstream::binary);
	output.write(sbuf.data(), sbuf.size());
	output.close();
	return 0;

}

