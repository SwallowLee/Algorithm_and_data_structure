# include<stdio.h>

int main(void)
{
    char input[1000], output[1000];
    unsigned char ch1, ch2;
    FILE *in, *out;
    int wrong = 0, total = 0, in_w = 0, out_w = 0;

    scanf("%s", input);
    scanf("%s", output);
    in = fopen(input, "rb");
    out = fopen(output, "rb");

    fscanf(in, "%c", &ch1);
    fscanf(out, "%c", &ch2);
    while( !feof(in) && !feof(out) )
    {
        if( ch1 != ch2 )
        {
            printf("Wrong QQ\n");
            wrong++;
        }
        total++;
        in_w++;
        out_w++;
        fscanf(in, "%c", &ch1);
        fscanf(out, "%c", &ch2);
    }

    if( !feof(in) || !feof(out) )
    {
        printf("Wrong QQ\n");
        while( !feof(in) )
        {
            in_w++;
            fscanf(in, "%c", &ch1);
        }
        while( !feof(out) )
        {
            out_w++;
            fscanf(out, "%c", &ch2);
        }
        printf("in %d words, out %d words\n", in_w, out_w);
    }
    else
        printf("YES!!!!!!!\n");

    printf("total %d words, %d character wrong\n", total, wrong);

    return 0;
}
