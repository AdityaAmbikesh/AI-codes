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
#define N 7
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
typedef vector <ii> vii;
typedef vector <ll> vi;


struct Node
{
    Node *parent;
    int mat[N];
    int x;
    int cost;
    int level;
};
struct cmp
{
    bool operator()(const Node *lhs,const Node *rhs) const
    {
        return (lhs->cost+lhs->level)>(rhs->cost+rhs->level);
    }
};

priority_queue<Node*,vector<Node* >,cmp> pq;

int row[4]={-2,-1,1,2};

int isSafe(int x)
{
   return (x>=0 && x<7);
}

void printMatrix(int mat[N])
{
    for(int i=0;i<N;i++)
        cout<<mat[i]<<" ";
    cout<<endl;
}

Node *newnode(int mat[N],int level,int x,int newX,Node* parent)
{
    Node *node=new Node;
    node->parent = parent;
    memcpy(node->mat,mat,sizeof(node->mat));
    swap(node->mat[newX],node->mat[x]);
    node->cost=INF;
    node->level = level;
    node->x=newX;//update the new coordinates of the blank....-important
    return node;
}



int claculateCost(int arr[N],int goal[N])
{
    int cnt=0;
    for(int i=0;i<N;i++)
    {
        if(arr[i]!=goal[i] && arr[i])
        cnt++;
    }
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



void solve(int initial[N],int x,int goal[N],Node* ptr)
{
    while(!pq.empty())
    {
        Node* child = pq.top();
        pq.pop();
        // cout<<"cost= "<<child->cost<<",level= "<<child->level<<", ";
        // printMatrix(child->mat);
        // cout<<endl;
        if(claculateCost(child->mat,goal)==0)
        {
           // cout<<"yess";
            printpath(child);
            return;  
        }
        for(int i=0;i<4;i++)
        {
            //cout<<"index="<<child->x<<" "<<row[i]<<" ";
            if(isSafe(child->x+row[i]))
            {
                Node* temp = newnode(child->mat,child->level+1,child->x,child->x+row[i],child);
                temp->cost= claculateCost(temp->mat,goal);
                pq.push(temp);
              // cout<<"cost= "<<temp->cost<<",level= "<<temp->level<<", ";
               //printMatrix(temp->mat);
                
                
            }
        }
      // cout<<endl;
   }
   
}

int main()
{
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
ios::sync_with_stdio(false);
 cin.tie(0);

 int initial[N],goal[N];
for(int i=0;i<N;i++)
        cin>>initial[i];

for(int i=0;i<N;i++)
        cin>>goal[i];
//printMatrix(initial);
//printMatrix(goal);
Node* node = newnode(initial,0,3,3,NULL);
node->cost=6;
node->x=3;
pq.push(node);
solve(initial,3,goal,node);

return 0;

}