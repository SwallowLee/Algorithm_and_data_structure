#include <msgpack.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;
struct information{
	int cost, attack, defense;
};

int c[10001], f[10001], follower_num;
vector<information> follower, spell;
bool compare(information i, information j)
{
	if (i.attack/i.cost > j.attack/j.cost)
		return true;
	else
		return false;
}
int calculate(int point, int num)
{
	int i, f, w, k;
	bool taken;
	if (num > follower.size())
		return 0;

	taken = false;
	for (int i = 0, f = 1; i < follower.size(); i++)
	{
		//cout << "QQ " << follower[i].attack << endl;
		for (int j = point; j >= follower[i].cost; j--)
		if (c[j - follower[i].cost] + follower[i].attack > c[j])
		{
			c[j] = c[j - follower[i].cost] + follower[i].attack;
			//cout << c[j] << " "<<j<<" " << follower[i].cost << " " << follower[i].attack << endl;
			taken = true;
			//system("Pause");
		}
		if (taken == true)
		{
			if (f >= num)
				break;
			else
			{
				f++;
				taken = false;
			}
		}
	}
	for (int i = 0; i < spell.size(); i++)
	for (int j = point; j >= spell[i].cost; j--)
	if (c[j - spell[i].cost] + spell[i].attack > c[j])
	{
		c[j] = c[j - spell[i].cost] + spell[i].attack;
	}

	if (num > 0)
		c[point] += 2;
	//cout << c[point] << endl;
	return c[point];
}

int main(void) {
	fstream input, output;
	size_t off = 0;
	vector<string> arr;
	vector<int> finish;
	information temp;
	string fin, name;
	stringstream infor;
	int bufsize, num, cards, point = 0, i, j, ans, ans1;
	char *buf = NULL;
	msgpack::sbuffer sbuf;

	input.open("input.txt", fstream::in | fstream::binary);
	output.open("output.txt", fstream::out | fstream::binary);

	input.seekg(0, ios::end);
	bufsize = input.tellg();
	input.seekg(0);

	buf = new char[bufsize];
	input.read(buf, bufsize);

	msgpack::object_handle oh;
	oh = msgpack::unpack(buf, bufsize, off);
	oh.get().convert(num);
	for (i = 0; i < num; i++)
	{
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(cards);
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(point);
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(arr);
		j = 0;
		for (vector<string>::iterator it = arr.begin(); it != arr.end(); it++, j++)
		{
			infor << *it;
			infor >> name;
			infor << *it;
			infor >> temp.cost;
			infor << *it;
			infor >> temp.attack;
			infor << *it;
			infor >> temp.defense;
			if (name == "follower")
				follower.push_back(temp);
			else
				spell.push_back(temp);
			infor.str("");
			infor.clear();
		}
		sort(follower.begin(), follower.end(), compare);
		sort(spell.begin(), spell.end(), compare);
		ans = 0;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		ans1 = calculate(point, 5);
		if (ans1 > ans)
			ans = ans1;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		ans1 = calculate(point, 4);
		if (ans1 > ans)
			ans = ans1;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		//cout << "three" << endl;
		ans1 = calculate(point, 3);
		if (ans1 > ans)
			ans = ans1;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		//cout << "two" << endl;
		ans1 = calculate(point, 2);
		if (ans1 > ans)
			ans = ans1;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		ans1 = calculate(point, 1);
		if (ans1 > ans)
			ans = ans1;
		for (int k = 0; k <= point; k++)
			c[k] = 0;
		ans1 = calculate(point, 0);
		if (ans1 > ans)
			ans = ans1;
		//cout << "ans " << ans << endl;
		//system("Pause");
		output << ans << endl;
		follower.clear();
		spell.clear();
	}
	input.close();
	output.close();
	return 0;

}

