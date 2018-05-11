#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;
struct information{
	string type;
	int cost, attack, defense;
};

int c[10001], f[10001], follower_num;
vector<information> content;
bool compare(information i, information j)
{
	if (i.attack > j.attack)
		return true;
	else
		return false;
}
int calculate(int point)
{
	int i, w, k;

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

		cin >> cards;
		cin >> point;
		j = 0;
		for (i = 0; i < cards; i++)
		{
			cin >> name;
			cin >> temp.cost;
			cin >> temp.attack;
			cin >> temp.defense;
			content.push_back(temp);
			infor.str("");
			infor.clear();
		}
		sort(content.begin(), content.end(), compare);
		ans = calculate(point);
		//cout << "ans " << ans << endl;
		//system("Pause");
		cout << ans << endl;
		content.clear();
	return 0;

}

