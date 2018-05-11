# include<iostream>
# include<iostream>
# include<stdio.h>
# include<fstream>
# include<sys/time.h>

using namespace std;

int main(int argc, char **argv)
{
    struct timeval start,end;
    gettimeofday( &start , 0 );

    char ch,pattern[2000],str[2000],a[2001],b;
    int i,j,line,k,ans;
    fstream pattern_file, str_file;

    pattern_file.open( argv[1],ios::in );
    if(!pattern_file)
        cout<<"error in open str_file"<<endl;

    while( pattern_file.getline( pattern, sizeof( pattern ), '\n' ) )
    {
        for( i = 0; pattern[i] != '\0' && pattern[i] != '\r'; i++ )
        {
            if( pattern[i] >= 'A' && pattern[i] <= 'Z' )
            {
                a[i] = pattern[i] - 'A' + 'a';
            }
            else
            {
                a[i] = pattern[i];
            }
        }
        str_file.open( argv[2],ios::in );
        if(!str_file)
            cout<<"error in open pattern_file"<<endl;

        for(line=1;str_file.getline( str, sizeof( str ), '\n' );line++)
        {
            ans=1;
            for( i=0 , j=0 ; str[i]!='\0' && str[i] != '\r'; )
            {
                if( str[i]>='A' && str[i]<='Z' )
                    b=str[i]-'A'+'a';
                else
                    b=str[i];
                if(a[j]==b)
                {
                    j++;
                    i++;
                    if( pattern[j]=='\0' )
                    {
                        //output
                        printf( "%d %d\"", line, ans );
                        for( k = 0; pattern[k] != '\0' && pattern[k] != '\r'; k++ )
                        {
                            printf( "%c",pattern[k] );
                        }
                        printf( "\" \"" );
                        for( k = 0; str[k] != '\0' && str[k] != '\r'; k++ )
                        {
                            printf( "%c",str[k] );
                        }
                        printf("\"\n");
                		/*cout<<line<<" "<<ans<<"\"";
                        for( k=0 ; pattern[k]!='\0' ; k++ )
                            cout<<pattern[k];
                        cout<<"\"";
                		cout<<"\"";
                        for( k=0 ; str[k]!='\0' ; k++ )
                            cout<<str[k];
                        cout<<"\""<<endl;*/
                        j=0;
                        i=ans;
                        ans++;
                    }
                }
                else
                {
                    j=0;
                    i=ans;
                    ans++;
                }
            }

        }
        str_file.close();

    }

    gettimeofday( &end , 0 );
    int sec = end.tv_sec - start.tv_sec;
    int usec = end.tv_usec - start.tv_usec;

    printf( "%fms\n",sec*1000+(usec/1000.0) );

    return 0;
}
