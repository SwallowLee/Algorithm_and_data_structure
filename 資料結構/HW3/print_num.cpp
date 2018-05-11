# include<stdio.h>
# include<bitset>

int main(void)
{
    char input[1000], output[1000];
    unsigned char ch1;
    FILE *in, *out;
    std::bitset<8> ch;

    scanf("%s", input);
    in = fopen(input, "rb");

    fscanf(in, "%c", &ch1);
    while( !feof(in) )
    {

        printf("~%d", ch1);
        fscanf(in, "%c", &ch1);
    }


    return 0;
}
