#include "Function.cpp"

PosType NextPos(PosType curpos, int v)
{
	PosType nexpos;
	switch (v)
	{
	case 0:
		nexpos.xpos = curpos.xpos;
		nexpos.ypos = curpos.ypos + 1;
		break;
	case 1:
		nexpos.xpos = curpos.xpos + 1;
		nexpos.ypos = curpos.ypos + 1;
		break;
	case 2:
		nexpos.xpos = curpos.xpos + 1;
		nexpos.ypos = curpos.ypos;
		break;
	case 3:
		nexpos.xpos = curpos.xpos + 1;
		nexpos.ypos = curpos.ypos - 1;
		break;
	case 4:
		nexpos.xpos = curpos.xpos;
		nexpos.ypos = curpos.ypos - 1;;
		break;
	case 5:
		nexpos.xpos = curpos.xpos - 1;
		nexpos.ypos = curpos.ypos - 1;
		break;
	case 6:
		nexpos.xpos = curpos.xpos - 1;
		nexpos.ypos = curpos.ypos;
		break;
	case 7:
		nexpos.xpos = curpos.xpos - 1;
		nexpos.ypos = curpos.ypos + 1;
		break;
	}
	return nexpos;
}

int Pass(PosType pos, int **maze, int **visited, int m, int n)
{
	if (pos.xpos >= 0 && pos.ypos >= 0
		&& pos.xpos < m  && pos.ypos < n 
		&& maze[pos.xpos][pos.ypos] == 0
		&& visited[pos.xpos][pos.ypos] == 0)
		return 1;
	return 0;
}

bool ShortestPath(int **maze, int m, int n, SqStack &S)
{
	DLinkQueue Q;
	InitQueue(Q);
	DqueuePtr p;
	int **visited,i,j;
	visited = new int*[6];

	for(i = 0; i < 6; i++)
		visited[i] = new int[8];
	
	for(i = 0; i < 6; i++)
		for(j = 0; j < 8; j++)
			visited[i][j] = 0;
	
	if(maze[0][0] != 0)
		return false;

	PosType e, curpos, npos;

	e.xpos = 0;
	e.ypos = 0;
	EnQueue(Q, e);
	int found = 0;

	while(!found && !QueueEmpty(Q))
	{
		
		GetHead(Q, curpos);
		for(int v = 0; v < 8 && !found; v++)
		{
			npos = NextPos(curpos, v);
			if( Pass(npos, maze, visited, m, n) )
			{
				EnQueue(Q, npos);
				visited[npos.xpos][npos.ypos] = 1;
			}//if
			if(npos.xpos == m-1 && npos.ypos == n-1)
				found = 1;
		}//for
		DeQueue(Q);
	}//while

	if(found)
	{
		InitStack_Sq(S);
		p = Q.rear;
		while(p)
		{
			Push_Sq(S, p->seat);
			p = p->pre;
		}//while
		return true;
	}//if
	else 
		return false;

}

void main()
{
	int **maze,i,j;
	maze = new int*[6];
	for(i = 0; i < 6; i++)
		maze[i] = new int[8];
	
	for(i = 0; i < 6; i++)
		for(j = 0; j < 8; j++)
			maze[i][j] = 1;

	maze[0][0] = maze[0][2] = maze[0][4] = maze[0][5] = maze[0][6] = maze[1][1] = maze[1][2] = maze[1][5] = maze[1][7] = maze[2][0] = maze[2][3] = maze[2][4]
		= maze[3][1] = maze[3][2] = maze[3][5] = maze[3][6] = maze[4][1] = maze[4][2] = maze[4][3] = maze[4][6] = maze[5][0] = maze[5][4] = maze[5][5] = maze[5][6] = maze[5][7] = 0;

/*		{0, 1, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 1, 0},
		{0, 1, 1, 0, 0, 1, 1, 1},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 1},
		{0, 1, 1, 1, 0, 0, 0, 0}
*/

	printf("迷宫为\n");
	for(i = 0; i < 6; i++)
	{
		for (j = 0; j < 8; j++)
			printf("%d  ",maze[i][j]);
		printf("\n");
	}

	SqStack path;
	printf("路线为\n");
	if (ShortestPath(maze, 6, 8, path))
	{
		while (!StackEmpty_Sq(path))
		{
			PosType pos;
			Pop_Sq(path, pos);
			printf("(%d,%d)\n",pos.xpos,pos.ypos);
		}
		printf("finish\n");
	}

}