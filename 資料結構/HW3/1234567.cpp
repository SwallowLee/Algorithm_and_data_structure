# include<stdio.h>
# include<string.h>
# include<vector>
# include<bitset>
# include<algorithm>
# include<string>

struct word
{
    unsigned char chara;
    long long unsigned int times;
    struct word *right, *left;
};

struct code
{
    unsigned char letter;
    unsigned int code_len;
    char bit[1000];
    std::vector<bool> code_num{std::vector<bool> (10000)};
};

bool compare( struct word *i,  struct word *j )
{
    return i->times < j->times;
}

std::vector<bool> fin_code{std::vector<bool> (10000)};
std::vector<bool>::iterator it3;
std::vector<struct code> convert{std::vector<struct code> (256)};
int convert_len;

int give_code( struct word *root, unsigned int num )
{
    unsigned int i;
    if(root->left != NULL)
    {
        if( num + 1 > fin_code.size())
        {
            fin_code.insert(fin_code.end(), false);
        }
        else
        {
            fin_code[num] = false;
        }

        give_code( root->left, num + 1 );
    }

    if(root->right != NULL)
    {
        if( num + 1 > fin_code.size())
        {
            fin_code.insert(fin_code.end(), true);
        }
        else
        {
            fin_code[num] = true;
        }

        give_code( root->right, num + 1 );
    }

    if(root->left == NULL && root->right == NULL)
    {
        struct code node;
        node.letter = root->chara;
        node.code_len = num;

        for( i = 0; i < num; i++ )
        {
            node.code_num[i] = fin_code[i];
        }
        for(it3 = fin_code.begin(), i = 0; i < num; i++, it3++)
        {
            if( *it3 == false )
                node.bit[i] = '0';
            else
                node.bit[i] = '1';
        }

        if( convert_len == convert.size() )
            convert.insert( convert.end(), node );
        else
            convert[ convert_len ] = node;

        convert_len++;
    }

    return 0;
}

int compress(FILE *in, FILE *out)
{
    unsigned char ch;
    bool exist;
    unsigned int count_size;
    int num, i, j;
    struct word *root, *r, new_ch[256];
    std::bitset<8> change;
    std::vector<struct word*> count_num(10000);
    std::vector<struct word*>::iterator it;
    std::vector<struct code>::iterator it2;
    fpos_t pos;
    // calculate appear times
    count_size = 0;
    convert_len = 0;
    fgetpos(in, &pos);
    j = 0;
    ch = fgetc(in);
    while( !feof(in) )
    {
        exist = false;
        for( i = 0; i < count_size; i++ )
        {
            if( count_num[i]->chara == ch )
            {
                exist = true;
                count_num[i]->times++;
                break;
            }
        }

        if( exist == false )
        {
            new_ch[j].chara = ch;
            new_ch[j].times = 1;
            new_ch[j].right = NULL;
            new_ch[j].left = NULL;
            if( count_size == count_num.size() )
            {
                count_num.insert(count_num.end(), &new_ch[j]);
            }
            else
            {
                count_num[count_size] = &new_ch[j];
            }
            count_size++;
            j++;
        }

        ch = fgetc(in);
    }
    std::sort(count_num.begin(), count_num.begin() + count_size, compare);
    // create tree
    num = 0;
    j = 0;
    struct word parent[count_size - 1];
    while( num + 1 != count_size ) // root is at the last time of creating the tree
    {
        parent[j].chara = '0';
        parent[j].left = count_num[num];
        parent[j].right = count_num[num + 1];
        parent[j].times = count_num[num]->times + count_num[num + 1]->times;
        exist = false;
        for( it = count_num.begin(), i = 0; i < count_size; i++, it++ )
        {
            r = *it;
            if( parent[j].times < r->times )
            {
                count_num.insert(it, &parent[j]);
                count_size++;
                exist = true;
                break;
            }
        }
        if( exist == false )
        {
            if(count_size > count_num.size())
                count_num.insert(it, &parent[j]);
            else
            {
                count_num[count_size] = &parent[j];
                count_size++;
            }
        }
        if( num + 3 == count_size )
        {
            root = &parent[j];
        }
        num = num + 2;
        j++;
    }

    give_code(root, 0);
    fprintf(out, "%d ", convert_len);
    for( it2 = convert.begin(), i = 0; i < convert_len; i++, it2++ )
    {
        fputc(it2->letter, out);
        fputc(it2->code_len, out);
        num = 7;
        for(j = 0; j < 8; j++)
        {
            change.set(j, 0);
        }
        for( j = 0; j < it2->code_len; j++)
        {
            change.set(num, it2->code_num[j]);
            num--;
            if(num == -1)
            {
                fputc((int)change.to_ulong(), out);
                num = 7;
            }
        }

        if(num != 7)
        {
            fputc((int)change.to_ulong(), out);
        }
    }

    fsetpos(in, &pos);
    ch = fgetc(in);
    num = 7;
    change.set();
    while( !feof(in) )
    {
        for( it2 = convert.begin(), i = 0; i < convert_len; i++, it2++ )
        {
            if( it2->letter == ch )
            {
                for( j = 0; j < it2->code_len; j++ )
                {
                    change.set(num, it2->code_num[j]);
                    num--;
                    if( num == -1 )
                    {
                        //compress into char
                        fputc((int)change.to_ulong(), out);
                        change.set();
                        num = 7;
                    }
                }
                break;
            }
        }
        ch = fgetc(in);
    }
    if(num != 7)
    {
        fputc((int)change.to_ulong(), out);
        change.set();
    }

    fputc(num, out);

    convert_len = 0;
    count_size = 0;
}

word *add(struct word *node, unsigned char ch)
{
    node = new word();
    node->chara = ch;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int make_tree( struct word *root, char *binary, struct word *node, int i )
{
    if( binary[i] == '0' )
    {
        if( root->left == NULL )
        {
            root->left = add(root->left, '0');
        }

        make_tree( root->left, binary, node, i + 1 );
    }
    if( binary[i] == '1' )
    {
        if( root->right == NULL )
        {
            root->right = add(root->right, '0');
        }

        make_tree( root->right, binary, node, i + 1 );
    }
    if( binary[i] == '\0' )
    {
        root->chara = node->chara;
        return 0;
    }
}

int extract(FILE *in, FILE *out)
{
    unsigned char ch, check1, check2;
    unsigned int num;
    int i, j, k;
    struct word node[256], *tree, *cur;
    std::string binary;
    std::vector<struct code> chara{std::vector<struct code> (256)};

    tree = add(tree, '0');

    fscanf(in, "%d", &num);
    fscanf(in, "%c", &ch);

    for( i = 0; i < num; i++ )
    {
        ch = fgetc(in);
        chara[i].letter = ch;

        ch = fgetc(in);
        chara[i].code_len = ch;

        j = 0;
        while( j < chara[i].code_len )
        {
            ch = fgetc(in);
            std::bitset<8> a_ch(ch);
            binary = a_ch.to_string();

            for( k = 0; j < chara[i].code_len && k < 8; k++ )
            {
                if( j < chara[i].code_len )
                    chara[i].bit[j] = binary[k];
                else
                    break;
                j++;
            }
        }
        chara[i].bit[chara[i].code_len] = '\0';

        node[i].chara = chara[i].letter;
        node[i].left = NULL;
        node[i].right = NULL;

        make_tree( tree, chara[i].bit, &node[i], 0 );
    }

    cur = tree;
    while( !feof(in) )
    {
        ch = fgetc(in);
        check1 = fgetc(in);
        check2 = fgetc(in);
        if( feof(in) )
        {
	    if( check1 == 7 )
		num = 0;
	    else
            	num = check1;
        }
        else
        {
            num = 0;
            ungetc(check2, in);
            ungetc(check1, in);
        }
        std::bitset<8> byte(ch);
        binary = byte.to_string();
        for( i = 0; i < 8 - num; i++ )
        {
            if( binary[i] == '0' )
            {
                if( cur->left == NULL )
                {
                    fputc(cur->chara, out);
                    cur = tree->left;
                }
                else
                    cur = cur->left;
            }
            else
            {
                if( cur->right == NULL )
                {
                    fputc(cur->chara, out);
                    cur = tree->right;
                }
                else
                    cur = cur->right;
            }
        }
    }
}

int main(void)
{
    char command[10], input[1000], output[1000];
    FILE *in_file, *out_file;
    printf("Input command : ");
    scanf("%s", command);
    while( strcmp(command, "quit") != 0 )
    {
        if( strcmp(command, "Compress") != 0 && strcmp(command, "Extract") != 0 )
        {
            printf("It isn't the available command.\n");
            printf("Input command : ");
            scanf("%s", command);
            continue;
        }

        printf("Input file name: ");
        scanf("%s", input);
        printf("Output file name: ");
        scanf("%s", output);

        in_file = fopen(input, "rb");
        if( !in_file )
        {
            printf("can't open the input file\n");
            printf("Input command : ");
            scanf("%s", command);
            continue;
        }

        out_file = fopen(output, "wb");
        if( !out_file )
        {
            printf("can't open the output file\n");
            printf("Input command : ");
            scanf("%s", command);
            continue;
        }

        if( strcmp(command, "Compress") == 0 )
        {
            convert_len = 0;
            compress(in_file, out_file);
        }
        else if( strcmp(command, "Extract") == 0 )
            extract(in_file, out_file);

        fclose(in_file);
        fclose(out_file);

        printf("Input command : ");
        scanf("%s", command);
    }

    return 0;
}
