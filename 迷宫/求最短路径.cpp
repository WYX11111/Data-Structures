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

bool Pass(PosType pos, int maze[6][8], int visited[6][8], int m, int n)
{
	if (pos.xpos >= 0 && pos.ypos >= 0
		&& pos.xpos <= m - 1 && pos.ypos <= n - 1
		&& maze[pos.xpos][pos.ypos] == 0
		&& !visited[pos.xpos][pos.ypos])
		return true;
	return false;
}

bool ShortestPath(int maze[6][8], int m, int n, SqStack &S)
{
	DLinkQueue Q;
	InitQueue(Q);
	DqueuePtr p;
	int visited[6][8];
	
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < n; j ++)
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
		for(int v = 0; v < 8 && !found; v ++)
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
		return true;

}

void main()
{
	int maze[6][8] = {
		{0, 1, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 0, 1, 0},
		{0, 1, 1, 0, 0, 1, 1, 1},
		{1, 0, 0, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 1},
		{0, 1, 1, 1, 0, 0, 0, 0}
	};

	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 8; j++)
			printf("%d  ",maze[i][j]);
		printf("\n");
	}
	SqStack path;

	if (ShortestPath(maze, 6, 8, path))
	{
		while (!StackEmpty_Sq(path))
		{
			PosType pos;
			GetTop_Sq(path, pos);
			printf("(%d,%d)\n", pos.xpos, pos.ypos);
			Pop_Sq(path, pos);
		}
		printf("finish\n");
	}
}