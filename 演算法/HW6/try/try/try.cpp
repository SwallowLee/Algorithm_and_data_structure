#include <msgpack.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
int graph[1000][1000], max_num[100000], row, column, type;
vector<int>  max_i, max_j;

int DFS(int direction, int i, int j, int max_type, vector<int> map, int time)
{
	int fin = 0, side = 0;
	if (max_num[map[i*column + j]-1] != -1)
	{
		if (time == 0)
		{
			if (j + 1 < column && direction != 1)
			{
				if (map[i*column + j] == map[i*column + j + 1])
				{
					side++;
					if (graph[i][j + 1] == 0)
					{
						graph[i][j + 1]++;
						DFS(3, i, j + 1, max_type+1, map, 0);
					}
					else
						fin++;
				}
			}
			if (i + 1 < row && direction != 2)
			{
				if (map[i*column + j] == map[(i + 1)*column + j])
				{
					side++;
					if (graph[i + 1][j] == 0)
					{
						graph[i + 1][j]++;
						DFS(4, i + 1, j, max_type+1, map, 0);
					}
					else 
						fin++;
				}
			}
			if (j - 1 >= 0 && direction != 3)
			{
				if (map[i*column + j] == map[i*column + j - 1])
				{
					side++;
					if (graph[i][j - 1] == 0)
					{
						graph[i][j - 1]++;
						DFS(1, i, j - 1, max_type+1, map, 0);
					}
					else 
						fin++;
				}
			}
			if (i - 1 >= 0 && direction != 4)
			{
				if (map[i*column + j] == map[(i - 1)*column + j])
				{
					side++;
					if (graph[i - 1][j] == 0)
					{
						graph[i - 1][j]++;
						DFS(2, i - 1, j, max_type+1, map, 0);
					}
					else
					{
						fin++;
					}
				}
			}
			if (side == fin && side != 0)
			{
				max_num[map[i*column + j] - 1] = -1;
				return 0;
			}
			if (max_type > max_num[map[i*column + j]-1] && max_num[map[i*column + j]-1] != -1)
			{
				max_num[map[i*column + j]-1] = max_type;
				max_i.clear();
				max_j.clear();
				max_i.push_back(i);
				max_j.push_back(j);
			}
			else if (max_type == max_num[map[i*column + j]-1])
			{
				max_i.push_back(i);
				max_j.push_back(j);
			}
		}
		else
		{
			if (j + 1 < column && direction != 1)
			{
				if (map[i*column + j] == map[i*column + j + 1])
				{
					side++;
					if (graph[i][j + 1] == 1)
					{
						graph[i][j + 1]++;
						DFS(3, i, j + 1, max_type + 1, map, 1);
					}
					else
						fin++;
				}
			}
			if (i + 1 < row && direction != 2)
			{
				if (map[i*column + j] == map[(i + 1)*column + j])
				{
					side++;
					if (graph[i + 1][j] == 1)
					{
						graph[i + 1][j]++;
						DFS(4, i + 1, j, max_type + 1, map, 1);
					}
					else
						fin++;
				}
			}
			if (j - 1 >= 0 && direction != 3)
			{
				if (map[i*column + j] == map[i*column + j - 1])
				{
					side++;
					if (graph[i][j - 1] == 1)
					{
						graph[i][j - 1]++;
						DFS(1, i, j - 1, max_type + 1, map, 1);
					}
					else
						fin++;
				}
			}
			if (i - 1 >= 0 && direction != 4)
			{
				if (map[i*column + j] == map[(i - 1)*column + j])
				{
					side++;
					if (graph[i - 1][j] == 1)
					{
						graph[i - 1][j]++;
						DFS(2, i - 1, j, max_type + 1, map, 1);
					}
					else
						fin++;
				}
			}
			if (side == fin && side != 0)
			{
				max_num[map[i*column + j] - 1] = -1;
				return 0;
			}
			if (max_type > max_num[map[i*column + j] - 1] && max_num[map[i*column + j] - 1] != -1)
			{
				max_num[map[i*column + j]-1] = max_type;
			}
		}
	}
	return 0;
}

int main(void) {
	fstream input, output;
	size_t off = 0;
	int bufsize, num, i, j, k;
	char *buf = NULL;
	string str;
	msgpack::sbuffer sbuf;
	vector<int> map;
	vector<string> ans;
	vector<int>::iterator it, it2;

	input.open("input.txt", fstream::in | fstream::binary);
	
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
		oh.get().convert(row);
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(column);
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(type);
		oh = msgpack::unpack(buf, bufsize, off);
		oh.get().convert(map);
		for (j = 0; j < type; j++)
			max_num[j] = 0;
		for (j = 0; j < row; j++)
			for (k = 0; k < column; k++)
				graph[j][k] = 0;
		for (j = 0; j < row; j++)
		{
			for (k = 0; k < column; k++)
			{
				if (graph[j][k] == 0)
				{
					graph[j][k] = 1;
					DFS(0, j, k, 0, map, 0);
				}
				for (it = max_i.begin(); it != max_i.end(); it++)
				{
					for (it2 = max_j.begin(); it2 != max_j.end(); it2++)
					{
						if (graph[*it][*it2] == 1)
						{
							graph[*it][*it2] = 2;
							DFS(0, *it, *it2, 0, map, 1);
						}
					}
				}
				max_i.clear();
				max_j.clear();
			}
		}
		for (j = 0; j < type; j++)
		{
			if (max_num[j] == -1)
			{
				str = "cycle";
				ans.push_back(str);
				//cout << ans[0] << endl;
				//printf("cycle ");
			}
			else
			{
				str = to_string(max_num[j]);
				ans.push_back(str);
				//cout << ans[0] << endl;
				//printf("%d ", max_num[j]);
			}
		}
		//printf("\n");
		msgpack::pack(sbuf, ans);
		map.clear();
		ans.clear();
	}
	//system("Pause");
	//delete[] buf;
	input.close();
	output.open("output.txt", fstream::out | fstream::binary);
	output.write(sbuf.data(), sbuf.size());
	output.close();
	free(buf);
	return 0;

}