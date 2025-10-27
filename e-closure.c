#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 50

bool epstable[MAX][MAX]={false};
int notrans,nostates;

void get_enfa()
{
        char transition[MAX],*p;
        printf("ENter the no of transiiotns:\n");
        scanf("%d",&notrans);
        printf("Enter the no of states\n");
        scanf("%d",&nostates);

        printf("ENter the transitions like q0aq1 # for epsilon\n");
        for(int i=0;i<notrans;i++)
        {
                scanf("%s",transition);
                //printf("%s\n",transition);
                if((p=strchr(transition,'#'))!=NULL)  //check if # is present
                {
                        int i,j;
                        sscanf(transition,"q%d",&i);  //store transiiton to i
                        j=atoi(p+2);
                        epstable[i][j]=true;
                }
        }

}

//recursive dfs that finds all states reachable voa e-transiiotn

void findclose(int state,bool visited[])
{
        visited[state]=true;

        for(int i=0;i<nostates;i++)
        {
                if(epstable[state][i]&&!visited[i])
                {
                           findclose(i,visited);
                }
        }
}

void printclose()
{
        for(int i=0;i<nostates;i++)
        {
                bool visited[MAX]={false};
                char outstr[MAX]={'\0'},tempstr[MAX]={'\0'};
                findclose(i,visited);
                printf("E-closure(q%d)={",i);
                for(int j=0;j<nostates;j++)
                {
                        if(visited[j])
                        {
                                sprintf(tempstr,"q%d,",j);
                                strcat(outstr,tempstr);
                        }
                }
                outstr[strlen(outstr)-1]='\0';
                printf("%s\n",outstr);
        }
}

int main()
{
        get_enfa();
        printclose();
        return 0;
}
