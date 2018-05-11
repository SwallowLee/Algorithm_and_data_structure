# include<stdio.h>
# include<fstream>
# include<stdlib.h>
# include<sys/time.h>

using namespace std;

int main(int argc, char **argv)
{
    struct timeval start,end;
    // Start to calculate the time
    gettimeofday( &start , 0 );

    int i, ans, j, line, m, failure[2001], num;
    char text_str[2001], pattern_str[2001], text_lower_case, pattern_lower_case[2001];
    fstream pattern, text;

    pattern.open( argv[1], ios::in );
    if( !pattern )
    {
        printf("can't open the pattern file.\n");
    }

    while(pattern.getline( pattern_str, sizeof( pattern_str ), '\n' ) )
    {
        // Change the capital character to the lower case
        num = pattern.gcount();
        pattern_str[ num ] = '\0';
        j = -1;
        failure[0] = -1;
        for( i = 0; pattern_str[i] != '\0' && pattern_str[i] != '\r'; i++ )
        {
            if( pattern_str[i] >= 'A' && pattern_str[i] <= 'Z' )
            {
                pattern_lower_case[i] = pattern_str[i] - 'A' + 'a';
            }
            else
            {
                pattern_lower_case[i] = pattern_str[i];
            }
            if( i != 0 )
            {
                // Failure function
                while( j >= 0 && pattern_lower_case[j+1] != pattern_lower_case[i] )
                {
                    j = failure[j];
                }
                if( pattern_lower_case[j+1] == pattern_lower_case[i] )
                {
                    j++;
                }
                failure[i] = j;
            }

        }
        pattern_lower_case[i] = '\0';

        text.open( argv[2], ios::in );
        if( !text )
        {
            printf("can't open the pattern file.\n");
        }

        for( line = 1; text.getline( text_str, sizeof( text_str ), '\n' ); line++ )
        {
            num = text.gcount();
            text_str[ num ] = '\0';
            for( i = 0, j = 0, ans = 1; text_str[i] != '\0' && text_str[i] != '\r'; i++ )
            {
                // Change the capital character to the lower case
                if( text_str[i] >= 'A' && text_str[i] <= 'Z' )
                {
                    text_lower_case = text_str[i] - 'A' + 'a';
                }
                else
                {
                    text_lower_case = text_str[i];
                }

                // KMP
                if( pattern_lower_case[j] == text_lower_case )
                {
                    // Decide whether to print
                    if( pattern_lower_case[j+1] == '\0' )
                    {
                        printf( "%d %d\"", line, ans );
                        for( m = 0; pattern_lower_case[m] != '\0'; m++ )
                        {
                            printf( "%c",pattern_str[m] );
                        }
                        printf( "\" \"" );
                        for( m = 0; text_str[m] != '\0' && text_str[m] != '\r'; m++ )
                        {
                            printf( "%c",text_str[m] );
                        }
                        printf("\"\n");
                        ans = i - failure[j] + 1;
                        j = failure[j];
                    }

                    j++;
                }
                else
                {
                    while( j>=0 && pattern_lower_case[j] != text_lower_case )
                    {
                        if( j > 0 )
                        {
                            j = failure[j-1];
                        }
                        else
                        {
                            j = -1;
                        }
                    }

                    j++;
                    // Because when i = 0, ans = 1. And we should plus i before compare the word later.
                    ans = i+2;
                }
            }
        }
        text.close();
    }

    // The end of time
    gettimeofday( &end , 0 );
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;

    printf( "%fms\n",sec*1000+(usec/1000.0) );

    return 0;
}
