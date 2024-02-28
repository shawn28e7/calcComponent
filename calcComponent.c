#include <stdio.h>
#include <stdlib.h>

/*
input a 2-d matrix with zeros ans ones
calculate the area which is surrounded by ones
by doing BFS twice
1. BFS started from the edge, go through every zero which isn't surrounded
by ones
2. BFS from ones, calculate each component's size
output the number of component and each size of them
example:

input:
0 1 1 0
1 0 0 1
0 1 1 0

output:
1
8

input:
0 1 1 0
1 0 0 0
0 1 1 0

output:
1
5

input:
0 1 0 0 0 0 0 0
0 1 0 1 1 1 0 0
0 1 0 1 0 1 1 0
0 0 0 0 1 0 0 1
0 0 0 0 0 0 0 0
1 1 1 1 1 0 0 1
1 0 1 0 0 1 0 1
1 1 1 1 1 1 1 1

output:
3
3 9 21
*/


int *calcComponent(int *arr, const int length, const int height)
{
    int **map = (int **)malloc(height * sizeof(int *));

    int i, j, k, l = 0, r = 0, sum, head, x, y;
    int queue[500000] = {}; // [i][j] -> i * length + j;

    int diry4[4] = {0, 1, 0, -1};
    int dirx4[4] = {1, 0, -1, 0};

    int diry8[8] = {0, 1, 0, -1, 1, 1, -1, -1};
    int dirx8[8] = {1, 0, -1, 0, -1, 1, -1, 1};

    int ans[1000] = {};
    int ptr = 0;
	
    for (i = 0; i < height; i++)
    {
        map[i] = (int *)malloc(length * sizeof(int));
    }
    
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < length; j++)
        {
            map[i][j] = arr[i * length + j];
        }
    }
	
    // BFS from four edges
    for (i = 0; i < height; i++)
    {
        queue[r] = i * length;
        r++;
        queue[r] = i * length + length - 1;
        r++;
    }
    for (j = 0; j < length; j++)
    {
        queue[r] = j;
        r++;
        queue[r] = (height - 1) * length + j;
        r++;
    }


    // first BFS
    while (l != r)
    {
        head = queue[l];
        l++;
        x = head % length;
        y = head / length;

        if (map[y][x] != 0)
            continue;
        map[y][x] = -1;
        for (k = 0; k < 4; k++)
        {
            if (y + diry4[k] >= 0 && y + diry4[k] < height && x + dirx4[k] >= 0 && x + dirx4[k] < length)
            {
                if (map[y + diry4[k]][x + dirx4[k]] == 0)
                    queue[r] = (y + diry4[k]) * length + x + dirx4[k];
                    r++;
            }
        }
    }
	
    // second BFS
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < length; j++)
        {
            if (map[i][j] != -1)
            {
                l = 0;
                r = 1;
                queue[0] = i * length + j;
                sum = 0;

                while (l != r)
                {
                    head = queue[l++];
                    x = head % length;
                    y = head / length;

                    if (map[y][x] == -1)
                        continue;
                    map[y][x] = -1;
                    sum++;
                    for (k = 0; k < 8; k++)
                    {
                        if (y + diry8[k] >= 0 && y + diry8[k] < height && x + dirx8[k] >= 0 && x + dirx8[k] < length)
                        {
                            if (map[y + diry8[k]][x + dirx8[k]] != -1)
                                queue[r++] = (y + diry8[k]) * length + x + dirx8[k];
                        }
                    }
                }
                ans[ptr++] = sum;
            }
        }
    }

    int *ret = calloc(ptr + 1, sizeof(int));
    for (i = 1; i <= ptr; i++)
    {
        *(ret + i) = ans[i - 1];
    }
    *ret = ptr;
    
    for (int i = 0; i < height; i++)
	{
	    free(map[i]);
	}
	free(map);
	
    return ret;
}

int main()
{
    int map[8][8] = {{0, 1, 0, 0, 0, 0, 0, 0},
                     {0, 1, 0, 1, 1, 1, 0, 0},
                     {0, 1, 0, 1, 0, 1, 1, 0},
                     {0, 0, 0, 0, 1, 0, 0, 1},
                     {0, 0, 0, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 0, 0, 1},
                     {1, 0, 1, 0, 0, 1, 0, 1},
                     {1, 1, 1, 1, 1, 1, 1, 1}};
    int *ans = calcComponent((int *)map, 8, 8); // ans[0] = number of components
    int i;
    printf("%d\n", ans[0]);
    for (i = 1; i <= ans[0]; i++)
    {
        printf("%d ", ans[i]);
    }
    free(ans);
    return 0;
}