#include "LinearProbing.h"
void LinearProbing::insertown(int e,std::vector <int> &v){
        if (v.size()==0){
            v.push_back(e);
        }
        else if(v.size()==1){
            if (v[0]<e){
                v.insert(v.begin(),e);
            }
            else if (v[0]>e){
                v.push_back(e);
            }
        }
        else if(v.size()>1){
            int l=0;
            int r=v.size()-1;
            int m=0;
            while (l<=r){
                m=l+((r-l)/2);
                if (v[m]>e){
                    l=m+1;
                }
                else if (v[m]<e){
                    r=m-1;
                }
                else if(v[m]==e){
                    break;
                }
            }
            
            if(v[m]==e){
                v.insert(v.begin()+m,e);
            }
            else if (r==-1){
                v.insert(v.begin(),e);
            }
            else if(r==v.size()-1){
                v.push_back(e);
            }
            else{
                v.insert(v.begin()+l,e);
            }
        }
}//correct
void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hashcv=hash(id);
    Account A;
    int m=100019;
    A.balance=count;
    A.id=id;
   
    if(bankStorage1d[hashcv].id==""  ||  bankStorage1d[hashcv].id=="x"){
        bankStorage1d[hashcv]=A;
        size+=1;
        insertown(count,topk);
    }
    else{
        while(bankStorage1d[hashcv].id!="" && bankStorage1d[hashcv].id!="x"){//not empty
            hashcv=(hashcv+1)%m;
        }
        bankStorage1d[hashcv]=A;//found an empty slot
        size+=1;
        insertown(count,topk);
    }
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    if (k<=0){
        return std::vector<int>();
    }
    else if (size==0){
        return std::vector<int>();
    }
    int x = topk.size();
    int end=std::min(k , x);//ending index
    int start=0;//starting index
    return std::vector<int>(topk.begin()+start, topk.begin()+end);
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        return -1;
    }
    //matlab hai
    int hashcv=hash(id);
    int mod=100019;
    int value = -1;
    while(bankStorage1d[hashcv].id!=id){
        hashcv=(hashcv+1)%mod;
    }
    value=bankStorage1d[hashcv].balance;
    return value;
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        createAccount(id,count);
    }
    else{
    int hashcv=hash(id);
    int mod=100019;
    int oldbalance;
    while(bankStorage1d[hashcv].id!=id){
        hashcv=(hashcv+1)%mod;
    }
    oldbalance=bankStorage1d[hashcv].balance;
    bankStorage1d[hashcv].balance+=count;//updation
    int l=0;
    int r=topk.size()-1;
    
    int m=0;
    while(l<=r){
        m=l+((r-l)/2);
        if (topk[m]>oldbalance){
            l=m+1;
        }
        else if (topk[m]<oldbalance){
            r=m-1;
        }
        else if(topk[m]==oldbalance){
            break;
        }
    }
    topk.erase(topk.begin()+m);//erase the previous
    insertown(oldbalance+count,topk);//add new fresh value
    }
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hashcv=hash(id);
    int intial=hashcv;
    int mod=100019;
    while(bankStorage1d[hashcv].id!=id){
        hashcv=(hashcv+1)%mod;
        if(bankStorage1d[hashcv].id==""){//found empty
            return false;
        }
        else if(hashcv==intial){//came to the same place
            return false;
        }
        
    }
    return true; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        return false;
    }
    int hashcv=hash(id);
    int mod=100019;
    while(bankStorage1d[hashcv].id!=id){
        hashcv=(hashcv+1)%mod;
    }
    int count=bankStorage1d[hashcv].balance;
    bankStorage1d[hashcv].id="x";// made it empty
    bankStorage1d[hashcv].balance=-1;//made it empty
    size-=1;
    int l=0;
    int r=topk.size()-1;
    int m=0;
    while(l<=r){
        m=l+((r-l)/2);
        if (topk[m]>count){
            l=m+1;
        }
        else if (topk[m]<count){
            r=m-1;
        }
        else if(topk[m]==count){
            break;
        }
    }
    topk.erase(topk.begin()+m);
    return true;


    
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE

    return size; // Placeholder return value
}






int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int a=33;
    int hashv=0;
    int k=id.length();
    int m=100019;
    int a_pow=1;
    for(int i=k-1;i>=0;i--){
        hashv=(hashv+(id[i]*a_pow)%m)%m;
        a_pow=(a_pow*a)%m;
    }
    return hashv%m;
    
}


   