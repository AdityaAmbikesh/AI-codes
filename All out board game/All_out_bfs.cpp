//working bfs solution works very well with small inputs....


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
#define N 3
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef vector <ii> vii;
typedef vector <ll> vi;



struct Node
{
    Node *parent;
    int mat[N][N];
    int x,y;
    int cost;
    int level;
};

int row[]={1,0,-1,0};
int col[]={0,-1,0,1};

int isSafe(int x,int y)
{
    return(x>=0 && x<N && y>=0 && y<N);
}

void printMatrix(int mat[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            cout<<mat[i][j]<<" ";
        cout<<endl;
    }
}

Node *newnode(int mat[N][N],int level,int x,int y)
{
    Node *node=new Node;
   // node->parent = parent;
    memcpy(node->mat,mat,sizeof(node->mat));
    if(node->mat[x][y]==1)
        node->mat[x][y]=0;
    else
        node->mat[x][y]=1;
    for(int i=0;i<4;i++)
    {
        if(isSafe(x+row[i],y+col[i]))
        {
            if(node->mat[x+row[i]][y+col[i]]==1)
                node->mat[x+row[i]][y+col[i]]=0;
            else
                node->mat[x+row[i]][y+col[i]]=1;
        }
    }
    node->cost=INF;
    node->level = level;
    return node;
}



int claculateCost(int arr[N][N])
{
    int cnt=0;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(arr[i][j])
                cnt++;
    return cnt;
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

void solve(int initial[N][N])
{
    queue<Node* > myqueue;
    Node *temp;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
                temp=newnode(initial,0,i,j);
                temp->cost = claculateCost(temp->mat);
                cout<<"level = "<<temp->level<<"index of tapping "<<i<<" "<<j<<endl;
                printMatrix(temp->mat);
                cout<<endl;
                myqueue.push(temp);
                if(claculateCost(temp->mat)==0)
                {
                    cout<<"YESS"<<endl;
                    return;
                }
        }
    }
    while(!myqueue.empty())
    {
        temp=myqueue.front();
        myqueue.pop();
        if(claculateCost(temp->mat)==0)
        {
            cout<<"YESS"<<endl;
            return;
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                Node* child = newnode(temp->mat,temp->level+1,i,j);
                child->cost = claculateCost(child->mat);
                myqueue.push(child);
                cout<<"level = "<<child->level<<"index of tapping "<<i<<" "<<j<<endl;
                printMatrix(child->mat);
                cout<<endl;
                if(claculateCost(child->mat)==0)
                {
                    cout<<"YESS"<<endl;
                    return;
                }
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

 int initial[N][N],goal[N][N];
for(int i=0;i<N;i++)
{
    for(int j=0;j<N;j++)
        cin>>initial[i][j];
}

for(int i=0;i<N;i++)
{
    for(int j=0;j<N;j++)
        goal[i][j]=0;
}
//printMatrix(initial);
//printMatrix(goal);
int x,y,f=0;
for(int i=0;i<N;i++)
{
    for(int j=0;j<N;j++)
    {
        if(initial[i][j]==1)
        {
            x=i,y=j;f=1;
            break;
        }
    }
    if(f==1)
        break;
}

solve(initial);
return 0;

}