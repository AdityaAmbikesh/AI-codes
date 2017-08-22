#include <bits/stdc++.h>
#define M 1000000007
#define INF 999999999
#define EPS 1e-9
#define pb push_back
#define mp make_pair
#define SET(a) memset(a,-1,sizeof(a))
#define CLR(a) memset(a,0,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define MAX 1000005
#define fs first
#define sc second 
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef vector <ii> vii;
typedef vector <ll> vi;



struct Node
{
    Node *parent;
    int mat[3][3];
    int x,y;
    int cost;
    int level;
};

void printMatrix(int mat[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<mat[i][j]<<" ";
        cout<<endl;
    }
}

Node *newnode(int mat[3][3],int x,int y,int newX,int newY,int level,Node *parent)
{
    Node *node=new Node;
    node->parent = parent;
    memcpy(node->mat,mat,sizeof(node->mat));
    swap(node->mat[x][y],node->mat[newX][newY]);
    node->cost=INF;
    node->level = level;
    node->x=newX;
    node->y=newY;
    return node;
}

int row[]={1,0,-1,0};
int col[]={0,-1,0,1};

int claculateCost(int arr[3][3],int goal[3][3])
{
    int cnt=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(goal[i][j]!=arr[i][j] && arr[i][j])
                cnt++;
        }
    }
    return cnt;
}

int isSafe(int x,int y)
{
    return(x>=0 && x<3 && y>=0 && y<3);
}

void printpath(Node *root)
{
    if(root == NULL)
        return;
    printpath(root->parent);
    printMatrix(root->mat);
    cout<<endl;
}

struct cmp
{
    bool operator()(const Node *lhs,const Node *rhs) const
    {
        return (lhs->cost+lhs->level)>(rhs->cost+rhs->level);
    }
};

void solve(int initial[3][3],int x,int y,int final[3][3])
{
    priority_queue<Node*,vector<Node*> ,cmp> pq;
    Node *root = newnode(initial,x,y,x,y,0,NULL);
    root->cost = claculateCost(initial,final);
    pq.push(root);
   // printMatrix(root->mat);
    //cout<<endl;
    while(!pq.empty())
    {
        Node *min= pq.top();
        pq.pop();
        //printMatrix(min->mat);
        //cout<<endl;
        if(min->cost==0)
        {
            printpath(min);
            return;
        }
        for(int i=0;i<4;i++)
        {
            if(isSafe(min->x+row[i],min->y+col[i]))
            {
                Node *child = newnode(min->mat,min->x,min->y,min->x+row[i],min->y+col[i],min->level+1,min);
                child->cost=claculateCost(child->mat,final);
                pq.push(child);
                printMatrix(child->mat);
                cout<<endl;
            }
        }
    }
}

int main()
{
 freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
ios::sync_with_stdio(false);
 cin.tie(0);

 int initial[3][3],goal[3][3];
for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
        cin>>initial[i][j];
}

for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
        cin>>goal[i][j];
}
//printMatrix(initial);
//printMatrix(goal);

int x=1;
int y=2;
solve(initial,x,y,goal);
return 0;

}