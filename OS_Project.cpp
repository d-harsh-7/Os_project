#include<iostream>
#include<climits>
#include<queue>
#include<vector>
using namespace std;
//three objective first allocate 
//second objective print the process
//delete the process which are allocated
//deallocate the resource.....

struct Memory_block{
    bool occupied=false;
    int size;
};
struct Process{
    string pname;
    int psize;
    int allocated_block=-1;
};
void External_Fragmentation(vector<Memory_block>&Block){
    int ans=0;
    cout<<endl;
    cout<<endl;
    cout<<"Block"<<"       "<<"Block Size"<<endl;
    for(int i=0;i<Block.size();i++){
        if(Block[i].occupied==false){
            cout<<"Block "<<i<<"       "<<Block[i].size<<endl;
            ans=Block[i].size+ans;
        }        
    }
    cout<<"total External Fragmentation : "<<ans<<endl;
}
void deallocation(vector<Process>&no_process,vector<Memory_block>&Block){
    vector<Process>temp;
    for(int i=0;i<Block.size();i++){
        Block[i].occupied=false;
    }
    for(int i=0;i<no_process.size();i++){
        if(no_process[i].allocated_block==-1){
            temp.push_back(no_process[i]);
        }
    }
    no_process=temp;
}
int allocate(Process temp,vector<Memory_block> &Block){
    int ans=INT_MAX;
    int index=-1;
    for(int i=0;i<Block.size();i++){
        if(temp.psize<=Block[i].size && ans>Block[i].size && Block[i].occupied!=true){
            ans=Block[i].size;
            index=i;

        }
    }
    if(index==-1){
        return -1;
    }
    return index;

}
bool best_fit_algo(queue<Process> &q1,vector<Process> &no_process,vector<Memory_block> &Block,vector<int>&Internal_Fragmentation){
    int it=0;
    bool flag=false;
    while(!q1.empty() && it<=q1.size()){
        struct Process temp=q1.front();
        int location=allocate(temp,Block);
        if(location>=0){
            Internal_Fragmentation[it]=Block[location].size-temp.psize;
            no_process[it].allocated_block=location;
            Block[location].occupied=true;
            flag=true;
            q1.pop();

        }
        else{
            q1.pop();
            q1.push(temp);

        }
        it++;
    }
    return flag;
}
void print_table(vector<Process> &no_process,vector<Memory_block>& Block,vector<int>Internal_Fragmentation){
    cout<<"Process Name"<<"   "<<"Process Size"<<"   "<<"Block Size"<<"   "<<"Allocate Block"<<"  "<<"Internal_Fragmentation";
    cout<<endl;
    for(int i=0;i<no_process.size();i++){
        if(no_process[i].allocated_block!=-1){
            cout<<no_process[i].pname<<"               "<<no_process[i].psize<<"            "<<Block[no_process[i].allocated_block].size<<"           "<<"Block "<<no_process[i].allocated_block<<"           "<<Internal_Fragmentation[i];
            cout<<endl;
        }
        else{
            cout<<no_process[i].pname<<"               "<<no_process[i].psize<<"            "<<"NONE"<<"           "<<"Block "<<"NONE"<<"      "<<0;
            cout<<endl;
        }
        
    }
}
int main(){
    int n;
    cout<<"no. of process: ";
    cin>>n;
    cout<<endl;
    vector<Process> no_process;
    queue<Process> q1;
    for(int i=0;i<n;i++){
        struct Process temp;
        cout<<"Process name and size: ";
        cin>>temp.pname>>temp.psize;
        no_process.push_back(temp);
        q1.push(temp);
    }
    int m;
    cout<<"no. of Memory block ";

    cin>>m;
    vector<Memory_block> Block;
    vector<int> Internal_Fragmentation(m);
    
    for(int i=0;i<m;i++){
        struct Memory_block temp1;
        cout<<"size of block"<<i<<" ";
        cin>>temp1.size;
        Block.push_back(temp1);
        
    }
    while(best_fit_algo(q1,no_process,Block,Internal_Fragmentation)){
        print_table(no_process,Block,Internal_Fragmentation);
        External_Fragmentation(Block);
        deallocation(no_process,Block);
        
    }
    
    return 0;
}