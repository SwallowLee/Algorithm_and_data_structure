#include<vector>
#include<stdio.h>
#include<algorithm>

using namespace std;

struct node_info{
	int id;
	double res, cap;
};

struct buf_info{
	int id;
	double res, cap, cost;
};

struct ans_info{
	int buffer[20];
	double cost, delay, dscap;
};

bool compare(ans_info i, ans_info j)
{
	if (i.delay != j.delay)
		return i.delay<j.delay;
	else if (i.cost != j.cost)
		return i.cost < j.cost;
	else
		return i.dscap < j.dscap;
}

bool compare_ans(ans_info i, ans_info j)
{
	if (i.cost != j.cost)
		return i.cost<j.cost;
	else if (i.delay != j.delay)
		return i.delay < j.delay;
	else
		return i.dscap < j.dscap;
}

int main(void)
{
	FILE *input, *output;
	int num, node_num, buf_num, i, j, k, p;
	double max_delay;
	node_info node_temp;
	buf_info buf_temp;
	ans_info temp;
	vector<node_info> node;
	vector<buf_info> buf;
	vector<ans_info> ans[21];
	
	input = fopen("input.txt", "r");
	if (input == NULL){
		printf("can't open input file\n");
	}

	output = fopen("output.txt", "w");
	if (output == NULL){
		printf("can't open output file\n");
	}

	fscanf(input, "%d\n", &num);
	while (num > 0)
	{
		fscanf(input, "%lf\n", &max_delay);
		fscanf(input, "%d\n", &node_num);
		for ( i = 0; i < node_num; i++)
		{
			fscanf(input, "%ld", &node_temp.id);
			fscanf(input, "%lf", &node_temp.res);
			fscanf(input, "%lf", &node_temp.cap);
			node.push_back(node_temp);
		}
		fscanf(input, "%d\n", &buf_num);
		for (i = 0; i < buf_num; i++)
		{
			fscanf(input, "%d", &buf_temp.id);
			fscanf(input, "%lf", &buf_temp.res);
			fscanf(input, "%lf", &buf_temp.cap);
			fscanf(input, "%lf", &buf_temp.cost);
			buf.push_back(buf_temp);
		}
		temp.delay = 0;
		temp.cost = 0;
		temp.dscap = 0;
		ans[node.size()].push_back(temp);
		
		///////////////////////////////////////////////
		for (i = node.size() - 1; i >= 0; i--)
		{
			for (k = 0; k < ans[i+1].size(); k++)
			{
				for (j = 0; j < buf.size(); j++)
				{
					temp.dscap = buf[j].cap;
					temp.delay = node[i].res * temp.dscap + 
									buf[j].res * (ans[i+1][k].dscap + node[i].cap) + 
										ans[i+1][k].delay;
					temp.cost = ans[i+1][k].cost + buf[j].cost;
					if (temp.delay <= max_delay)
					{
						for (p = i + 1; p < node.size(); p++)
						{
							temp.buffer[p] = ans[i + 1][k].buffer[p];
						}
						temp.buffer[i] = buf[j].id;
						ans[i].push_back(temp);
					}
				}
				temp.dscap = node[i].cap + ans[i+1][k].dscap;
				temp.delay = node[i].res * temp.dscap + ans[i+1][k].delay;
				temp.cost = ans[i+1][k].cost;
				if (temp.delay <= max_delay)
				{
					for (p = i + 1; p < node.size(); p++)
					{
						temp.buffer[p] = ans[i + 1][k].buffer[p];
					}
					temp.buffer[i] = 0;
					ans[i].push_back(temp);
				}
				
				sort(ans[i].begin(), ans[i].end(), compare);
				for (j = 0; j < ans[i].size(); j++)
				{
					for (p = j + 1; p < ans[i].size(); p++)
					{
						if (ans[i][j].cost <= ans[i][p].cost &&
							ans[i][j].delay <= ans[i][p].delay &&
							ans[i][j].dscap <= ans[i][p].dscap )
						{
							ans[i].erase(ans[i].begin() + p);
							p--;
						}
					}
				}
			}
			ans[i + 1].clear();
		}
		if (ans[0].size() == 0)
		{
			fprintf(output, "NO SOLUTION\n");
		}
		else
		{
			sort(ans[0].begin(), ans[0].end(), compare_ans);
			for (i = 0; i < node.size(); i++)
			{
				if (ans[0][0].buffer[i] != 0)
				{
					fprintf(output, "%d %d ", node[i].id, ans[0][0].buffer[i]);
				}
			}
			fprintf(output, "\n");
		}

		ans[0].clear();
		num--;
		node.clear();
		buf.clear();
	}
	fclose(input);
	fclose(output);

	return 0;
}