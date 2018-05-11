#include <msgpack.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;
struct information{
	string type;
	int cost, attack, defense;
	
};

int c[10001], f[10001];
vector<information> content, follower, spell;
bool compare(information i, information j)
{
	if (i.attack > j.attack)
		return true;
	else
		return false;
}
bool compare_s(information i, information j)
{
	if (i.attack / i.cost > j.attack / j.cost)
		return true;
	else
		return false;
}
int calculate(int point)
{
	for (int i = 0; i < content.size(); i++)
	{
		//cout << "QQ " << follower[i].attack << endl;
		for (int j = point; j >= content[i].cost; j--)
			if (c[j - content[i].cost] + content[i].attack > c[j])
			{
				if (content[i].type == "follower")
					if (f[j] < 5)
					{
						c[j] = c[j - content[i].cost] + content[i].attack;
						f[j]++;
					}
					else;
				else
					c[j] = c[j - content[i].cost] + content[i].attack;
			}
	}
	
	if (f[point] > 0)
		c[point] += 2;
	//cout << c[point] << endl;
	return c[point];
}
int calculate_s(int point, int num)
{
	int k;
	bool taken;
	if (num > follower.size())
		return 0;
	
	taken = false;
	for (int i = 0, k = 1; i < follower.size(); i++)
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
			if (k >= num)
				break;
			else
			{
				k++;
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
	information temp;
	stringstream infor;
	int bufsize, num, cards, point = 0, i, j, ans, ans1;
	char *buf = NULL;
	msgpack::sbuffer sbuf;
	
	input.open("input.txt", fstream::in | fstream::binary);
	output.open("output.txt", fstream::out | fstream::binary);
	
	input.seekg(0, ios::end);
	bufsize = input.tellg();
	input.seekg(0);
	
	buf = (char*)malloc(bufsize * sizeof(char));
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
		for (vector<string>::iterator it = arr.begin(); it != arr.end(); it++)
		{
			infor << *it;
			infor >> temp.type;
			infor << *it;
			infor >> temp.cost;
			infor << *it;
			infor >> temp.attack;
			infor << *it;
			infor >> temp.defense;
			content.push_back(temp);
			if (temp.type == "follower")
				follower.push_back(temp);
			else
				spell.push_back(temp);
			infor.str("");
			infor.clear();
		}
		if (i == 5)
		{
			for (j = 0; j <= point; j++)
			{
				c[j] = 0;
				f[j] = 0;
			}
			sort(content.begin(), content.end(), compare);
			ans = calculate(point);
		}
		else if (i == 3)
		{
			sort(follower.begin(), follower.end(), compare_s);
			sort(spell.begin(), spell.end(), compare_s);
			ans = 0;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			ans1 = calculate_s(point, 5);
			if (ans1 > ans)
				ans = ans1;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			ans1 = calculate_s(point, 4);
			if (ans1 > ans)
				ans = ans1;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			//cout << "three" << endl;
			ans1 = calculate_s(point, 3);
			if (ans1 > ans)
				ans = ans1;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			//cout << "two" << endl;
			ans1 = calculate_s(point, 2);
			if (ans1 > ans)
				ans = ans1;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			ans1 = calculate_s(point, 1);
			if (ans1 > ans)
				ans = ans1;
			for (int k = 0; k <= point; k++)
				c[k] = 0;
			ans1 = calculate_s(point, 0);
			if (ans1 > ans)
				ans = ans1;
		}
		else
		{
			for (j = 0; j <= point; j++)
			{
				c[j] = 0;
				f[j] = 0;
			}
			sort(content.begin(), content.end(), compare_s);
			ans = calculate(point);
		}
		//cout << ans<<" " << ans1 << endl;
		//system("Pause");
		output << ans << endl;
		content.clear();
		follower.clear();
		spell.clear();
	}
	input.close();
	output.close();
	free(buf);
	return 0;

}