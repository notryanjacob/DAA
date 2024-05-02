#include<iostream>
using namespace std;

int main(){
    vector<int> nums ={-2,1,-3,4,-1};
    vector<int> maxSub;
    int currentSum=0, maxSum =0,start=0,end=0;
    for(int i =0 ;i<nums.size();i++){
        currentSum+=nums[i];
        if(currentSum>maxSum) {
            maxSum = currentSum;
            maxSub.push_back(i);
            end =i+1;
        }
        if(currentSum < 0) {
            currentSum =0;
            start =i+1;
        }
    }
    cout<<"Max Sum  : "<<maxSum<<endl;
    for(int i=start;i<end;i++){
        cout<<nums[i]<<", ";
    }
    return 0;   
}