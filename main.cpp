/*Author :  Amr Khaled Saad */
#include <bits/stdc++.h>
#include<iostream>
#include<conio.h>
#define ll long long
#define pb push_back
#define all(v) v.begin,v.end
#define F first
#define S second

using namespace std;
const int N = 28 ;
int cn=1,p,x=-1,y=-1,a=-1,b=-1;
bool f=1 , EN=0; // 1 -> me & 0 -> comp
vector<pair<int,int>>Dominoes , myDom , compDom ;
stack<pair<int,int>>Rem;
map<pair<int,int>,int>mp;
deque<int>Gam;
map<int,int>cnt;
void Get_Domino(){
    srand(time(0));
    int cnt=0 ;
    for(int i=0;cnt<N;i++){
        int x =rand()%7 , y = rand()%7 ;
        if(!mp[{x,y}] && !mp[{y,x}]) {Dominoes.pb({x,y});cnt++;mp[{x,y}]++;}
    }
}

void Divide_Dom(){
    for(int i=0;i<7;i++){
        int L=Dominoes[i].F , R = Dominoes[i].S ;
        myDom.pb({L,R});
    }
    for(int i=7;i<14;i++){
        int L=Dominoes[i].F , R = Dominoes[i].S ;
        compDom.pb({L,R});
    }
    for(int i=14;i<N;i++){
        int L=Dominoes[i].F , R = Dominoes[i].S ;
        Rem.push({L,R});
    }
}
void Dosh(){
    // Search For Dosh
     int dsh=-1;

        for(int i=0;i<myDom.size();i++){
            if(myDom[i].F==6 && myDom[i].S==6)dsh=1;
        }
        for(int i=0;i<compDom.size();i++){
            if(compDom[i].F==6 && compDom[i].S==6)dsh=0;
        }
        if(dsh==1)f=1;
        else if(dsh==0)f=0;

    if(dsh==1){

        for(int i=0;i<myDom.size();i++){
            if(myDom[i].F==6&&myDom[i].S==6){
                Gam.push_back(6);
                Gam.push_back(6);
                myDom.erase(myDom.begin()+i);
                break;
            }
        }
        cnt[6]+=2;
        f=!f;
    }
    else if(dsh==0){
         for(int i=0;i<compDom.size();i++){
            if(compDom[i].F==6&&compDom[i].S==6){
                Gam.push_back(6);
                Gam.push_back(6);
                compDom.erase(compDom.begin()+i);
                break;
            }
        }
        cnt[6]+=2;
        f=!f;
    }
    else
    {
        int L = compDom[0].F , R = compDom[0].S ;
        compDom.erase(compDom.begin());
        cnt[L]++;
        cnt[R]++;
        Gam.push_back(L);
        Gam.push_back(R);
        f=!f;
    }
}
void show(){
    if(EN)return;
    for(int i=0;i<Gam.size();i+=2){
        cout<<"|"<<Gam[i]<<"|"<<Gam[i+1]<<"|";
    }
    cout<<endl;


}
void get_in(){
     cin >> p ;
}
void borrow(){
    if(!Rem.size()){
        a=-1;b=-1;
        return ;
    }
    a = Rem.top().F ;b=Rem.top().S;
    Rem.pop();
}
void Play(){
    if(!myDom.size())
    {
        cout<<"YOU WIN !"<<endl;
        EN=1;
        return ;
    }
    if(!compDom.size()){
        cout<<"YOU LOSE !"<<endl;
        EN=1;
        return ;
    }
    int fr=Gam.front() , bk = Gam.back();
    if(f)
    {
        cout<<" < Your Turn > "<<endl;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
        cout<<"Your Paper : { ";
        for(int i=0;i<myDom.size();i++){
            int L=myDom[i].F,R=myDom[i].S;
            cout<<i+1<<"-"<<"("<<L<<","<<R<<")"<<"  ";
        }
        cout<<" }"<<endl;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
        int check=0;
        while(!check){
            cout<<"Enter number of Paper or Write 9 to borrow a paper or 0 if You Don't have valid paper"<<endl;
            get_in();
            if(p==0)break;
            --p;
            x = myDom[p].F ; y = myDom[p].S ;
            if(x==fr || x==bk || y==fr || y==bk){
                if(x==fr){Gam.push_front(x);Gam.push_front(y);myDom.erase(myDom.begin()+p);}
                else if(y==fr){Gam.push_front(y);Gam.push_front(x);myDom.erase(myDom.begin()+p);}
                else if(x==bk){Gam.push_back(x);Gam.push_back(y);myDom.erase(myDom.begin()+p);}
                else if(y==bk){Gam.push_back(y);Gam.push_back(x);myDom.erase(myDom.begin()+p);}
                check=1;
                cnt[x]++;
                cnt[y]++;
            }
            else{
                if(p==9){
                    borrow();
                    if(a==-1)break;
                    if(a==fr || a==bk || b==fr || b==bk){
                        if(a==fr){Gam.push_front(a);Gam.push_front(b);}
                        else if(b==fr){Gam.push_front(b);Gam.push_front(a);}
                        else if(a==bk){Gam.push_back(a);Gam.push_back(b);}
                        else if(b==bk){Gam.push_back(b);Gam.push_back(a);}
                        check=1;
                        cnt[a]++;
                        cnt[b]++;
                        break;
                    }
                    myDom.pb({a,b});
                }
            }
        }
        f=!f;
    }
    else
    {
        cout<<" < Robot Turn >"<<endl;
        bool hav=0;
        for(int i=0;i<compDom.size();i++){
            int l = compDom[i].F , r=compDom[i].S;
            if(l==fr || l==bk || r==fr || r==bk){
                hav=1;
                if(l==fr){Gam.push_front(l);Gam.push_front(r);compDom.erase(compDom.begin()+i);}
                else if(r==fr){Gam.push_front(r);Gam.push_front(l);compDom.erase(compDom.begin()+i);}
                else if(l==bk){Gam.push_back(l);Gam.push_back(r);compDom.erase(compDom.begin()+i);}
                else if(r==bk){Gam.push_back(r);Gam.push_back(l);compDom.erase(compDom.begin()+i);}
                cnt[l]++;
                cnt[r]++;
                break;
            }
        }
        if(!hav){
                 int ch=0;
                while(!ch){
                 borrow();
                 if(a==-1)break;
                 if(a==fr || a==bk || b==fr || b==bk){
                 if(a==fr){Gam.push_front(a);Gam.push_front(b);}
                 else if(b==fr){Gam.push_front(b);Gam.push_front(a);}
                 else if(a==bk){Gam.push_back(a);Gam.push_back(b);}
                 else if(b==bk){Gam.push_back(b);Gam.push_back(a);}
                 cnt[a]++;
                 cnt[b]++;
                 ch=1;
                 break;
                }
                compDom.pb({a,b});
            }
        }
        f=!f;
    }
}
int main()
{
   Get_Domino();
   Divide_Dom();
   Dosh();
   while(!EN){
    for(int j=1;j<=6;j++){
        if(cnt[j]==6){
            int me=0 ,cp=0;
            for(int d=0;d<myDom.size();d++){
                me+=myDom[d].F;
                me+=myDom[d].S;
            }
             for(int d=0;d<compDom.size();d++){
                cp+=compDom[d].F;
                cp+=compDom[d].S;
            }
            if(me > cp)cout<<"YOU WIN"<<endl;
            else if(me < cp)cout<<"YOU LOSE"<<endl;
            else cout<<"TIE !"<<endl;
            getch();
            return 0 ;
        }
    }
    cout<<"***************************************************************"<<endl;
    cout<<"=> ";  show();
    cout<<"***************************************************************"<<endl;
    Play();
   }
    getch();
    return 0;
}
