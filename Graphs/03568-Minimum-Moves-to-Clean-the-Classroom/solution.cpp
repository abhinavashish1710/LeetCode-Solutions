class Solution {
public:
    int minMoves(vector<string>& a, int E) {
        int m=a.size(),n=a[0].size(),k=0,sr,sc;
        for(int i=0;i<m;i++)for(int j=0;j<n;j++){
            if(a[i][j]=='L') a[i][j]='0'+k++;
            if(a[i][j]=='S') sr=i,sc=j;
        }

        int all=(1<<k)-1;
        if(!k)return 0;

        vector<signed char> best(m*n*(1<<k),-1);
        auto id=[&](int r,int c,int mask){return (r*n+c)*(1<<k)+mask;};

        queue<array<int,4>> q;
        q.push({sr,sc,0,E});
        best[id(sr,sc,0)]=E;

        int d=0,dr[]={1,-1,0,0},dc[]={0,0,1,-1};

        while(q.size()){
            int z=q.size();
            while(z--){
                auto [r,c,mask,e]=q.front();q.pop();

                if(e!=best[id(r,c,mask)]) continue;
                if(mask==all)return d;

                if(!e && a[r][c]!='R')continue;
                if(a[r][c]=='R')e=E;

                for(int x=0;x<4;x++){
                    int i=r+dr[x],j=c+dc[x];
                    if(i<0||i>=m||j<0||j>=n||a[i][j]=='X'||!e)continue;

                    int ne=e-1,nm=mask;

                    if(a[i][j]>='0'&&a[i][j]<='9')
                        nm|=1<<(a[i][j]-'0');

                    if(a[i][j]=='R')ne=E;

                    int p=id(i,j,nm);
                    if(ne>best[p]){
                        best[p]=ne;
                        q.push({i,j,nm,ne});
                    }
                }
            }
            d++;
        }
        return -1;
    }
};
