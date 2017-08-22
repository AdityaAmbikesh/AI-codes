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
    int mat[3][3];
    int x,y;
};

Node* newnode(int arr[3][3],int x,int y,int newX,int newY,Node *parent)
{
    Node *node = new Node;
    memcpy(node->mat,arr,sizeof node->mat);
    swap(node->mat[x][y],node->mat[newX][newY]);
    node->x=newX;
    node->y=newY;
    return node;
}

bool check(int arr[3][3],int final[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            if(arr[i][j]!=final[i][j])
                return false;
    }
    return true;
}

void printMatrix(int arr[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }

}

int issafe(int x,int y)
{
    return (x>=0 && x<3 && y>=0 && y<3);
}

void printPath(Node* node)
{
    if(node==NULL)
        return;
    printPath(node->parent);
    printMatrix(node->mat);
    cout<<endl;
}

int dr[]={1,0,-1,0};
int dc[]={0,1,0,-1};

void solve(int initial[3][3],int x,int y,int final[3][3])
{
    stack<Node* ,vector<Node*> > st;
    Node *root = newnode(initial,x,y,x,y,NULL);
    st.push(root);
    while(!st.empty())
    {
        Node* temp = st.top();
        st.pop();
        printMatrix(temp->mat);
        cout<<endl;
        if(check(temp->mat,final))
        {
            printPath(temp);
            return;
        }
        for(int i=0;i<4;i++)
        {
            if(issafe(temp->x+dr[i],temp->y+dc[i]))
            {
                Node* child=newnode(temp->mat,temp->x,temp->y,temp->x+dr[i],temp->y+dc[i],temp);
                st.push(child);
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
 int initial[3][3],final[3][3];
for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
        cin>>initial[i][j];
}
for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
        cin>>final[i][j];
}
solve(initial,2,1,final);
return 0;

}