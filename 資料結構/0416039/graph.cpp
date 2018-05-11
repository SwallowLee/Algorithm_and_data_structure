# include<iostream>
# include<fstream>
# include<stdio.h>

int main( int argc, char** argv )
{
    int vertice, edge, i, j, dot1, dot2, value, mini, next_dot;
    int start, fin;
    bool next;
    char ch = 'z';
    FILE *graph;

    //open the file
    graph = fopen( argv[1], "r" );
    if( graph == NULL )
    {
        printf( "can't open the file.\n" );
    }

    while( ch == 'z' || ch == 'Z' )
    {
        fscanf( graph, "%d", &vertice );
        fscanf( graph, "%d", &edge );

        int connect[ vertice ][ vertice ], distance[ vertice ], parent[ vertice ];
        bool in_tree[ vertice ], spanning_tree, visit[ vertice ];

        for( i = 0; i < vertice; i++ )
        {
            for( j = 0; j < vertice; j++ )
            {
                connect[i][j] = -1;
                connect[j][i] = -1;
            }
        }

        for( i = 0; i < edge; i++ )
        {
            fscanf( graph, "%d %d %d", &dot1, &dot2, &value);

            connect[ dot1 ][ dot2 ] = value;
            connect[ dot2 ][ dot1 ] = value;
        }

        //minimum spanning tree
        distance[0] = 0;
        parent[0] = 0;
        in_tree[ 0 ] = true;
        mini = 1000000000;

        //initial value
        for( i = 1; i < vertice; i++ )
        {
            if( connect[i][0] == -1)
            {
                distance[i] = 1000000000;
            }
            else
            {
                distance[i] = connect[i][0];
                parent[i] = 0;
            }
            in_tree[i] = false;
        }

        //Prim's algorithm
        for( i = 0; i < vertice; i++ )
        {
            for( j = 1; j < vertice; j++ )
            {
                if( distance[j] < mini && in_tree[j] == false )
                {
                    next_dot = j;
                    mini = distance[j];
                }
            }

            in_tree[ next_dot ] = true;

            for( j = 0; j < vertice; j++ )
            {
                if( connect[j][ next_dot ] < distance[j] && connect[j][ next_dot ] != -1 && in_tree[j] == false )
                {
                    distance[j] = connect[j][ next_dot ];
                    parent[j] = next_dot;
                }
            }
            mini = 1000000000;
        }

        //check if the minimum spanning tree is exist or not
        spanning_tree = true;
        for( i = 0; i < vertice; i++ )
        {
            if( in_tree[i] == false )
            {
                spanning_tree = false;
                break;
            }
        }

        if( spanning_tree == false )
        {
            printf( "No spanning tree\n" );
        }
        else
        {
            //print
            for( i = 0; i < vertice; i++ )
            {
                if( i != parent[i] )
                {
                    printf( "(%d,%d); ", parent[i], i );
                }
            }
            printf("\n");
        }
        //shortest path
        next = false;
        start = 0;
        fin = 0;
        fscanf( graph, "%c", &ch );// eat '\n'
        fscanf( graph, "%c", &ch );

        while( ch != 'z' && ch != 'Z' && ch != 'x' && ch != 'X' )
        {
            if( ch >= '0' && ch <= '9' && next == false )
            {
                start = start*10 + ch - '0';
            }
            else if( ch == ' ' )
            {
                next = true;
            }
            else if( ch >= '0' && ch <= '9' && next == true )
            {
                fin = fin*10 + ch - '0';
            }
            else if( ch == '\n' )
            {
                //shortest path
                distance[ start ] = 0;
                parent[ start ] = start;
                visit[ start ] = true;
                mini = 1000000000;

                //initial value
                for( i = 0; i < vertice; i++ )
                {
                    if( i != start )
                    {
                        if( connect[i][start] == -1)
                        {
                            distance[i] = 1100000000;
                        }
                        else
                        {
                            distance[i] = connect[i][start];
                            parent[i] = start;
                        }
                        visit[i] = false;
                    }
                }

                //Di jkstra's algorithm
                for( i = 0; i < vertice; i++ )
                {
                    for( j = 0; j < vertice; j++ )
                    {
                        if( distance[j] < mini && visit[j] == false )
                        {
                            next_dot = j;
                            mini = distance[j];
                        }
                        else if( distance[j] == mini && visit[j] == false && j == fin )
                        {
                            next_dot = j;
                            mini = distance[j];
                        }
                    }

                    visit[ next_dot ] = true;

                    if( next_dot == fin )
                    {
                        for( i = fin ; i != start ; i = parent[i] )
                        {
                            printf( "(%d,%d); ", parent[i], i );
                        }
                        printf( "\n" );
                    }
                    else
                    {
                        for( j = 0; j < vertice; j++ )
                        {
                            if( connect[j][ next_dot ] + distance[ next_dot ] < distance[j] && connect[j][ next_dot ] != -1 && visit[j] == false )
                            {
                                distance[j] = connect[j][ next_dot ] + distance[ next_dot ];
                                parent[j] = next_dot;
                            }
                        }
                    }
                   mini = 1000000000;
                }

                if( start == fin )
                {
                    printf( "(%d,%d);\n", start, fin );
                }
                else if( visit[ fin ] == false )
                {
                    printf( "Not exist\n" );
                }

                next = false;
                start = 0;
                fin = 0;
            }
            fscanf( graph, "%c", &ch );
        }
        printf( "\n" );
    }

    fclose( graph );

    return 0;
}
