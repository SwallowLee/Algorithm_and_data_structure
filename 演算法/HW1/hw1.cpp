#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    FILE *input, *output;
    int num, i, put;
    char ch;
    vector<int> a;
    vector<int>::iterator it;

    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("can't open input file\n");
    }

    output = fopen("output.txt", "w");
    if(output == NULL){
        printf("can't open output file\n");
    }

    fscanf(input, "%d\n", &num);
    for( i = 0; i < num; i++){
        ch = ' ';
        while(ch != '\n' && !feof(input)){
            fscanf(input, "%d", &put);
            a.push_back(put);
            fscanf(input, "%c", &ch);
        }
        sort(a.begin(), a.end());
        for( it = a.begin(); it != a.end(); it++){
            fprintf(output, "%d ", *it);
        }
        fprintf(output, "\n");
        a.clear();
    }

    return 0;
}
