#include<iostream>
using namespace std;

class Sd{
    public:
    static double sd(vector<int> x, vector<int> f){
        int n = x.size();
        int e_fx2=0;
        int e_fx=0,ef=0;
        for(int i=0;i<x.size();i++){
            ef +=f[i];
            e_fx2 += f[i]*x[i]*x[i];
            e_fx += f[i]*x[i];   
        }
        cout<<"ef : "<<ef<<endl;
        return sqrt(e_fx2/ef - pow(e_fx/ef,2));
    }
};
int main(){
    Sd s;
    vector<int> x = {10,20,30,40,50,60,70,80};
    vector<int> f = {10,40,85,125,160,200,220,280};
    cout<<s.sd(x,f);
    return 0;
}