#include "Chaining.h"
void Chaining::insertown(int e,std::vector <int> &v){
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
void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int hashcv=hash(id);// hash value
    Account A;
    A.balance=count;
    A.id=id;
    size+=1;//size increased
    bankStorage2d[hashcv].push_back(A);//value inserted
    insertown(count,topk);//value inserted in top k
}//correct

std::vector<int> Chaining::getTopK(int k) {
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
}//correct

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        return -1;
    }
    //matlab exist karta hai
    int hashcv=hash(id);// got the hash value
    for(int i =0;i<bankStorage2d[hashcv].size();i++){
        if(bankStorage2d[hashcv][i].id==id){
            return bankStorage2d[hashcv][i].balance;//fount the acc
        }
    }
    return 0;
}//correct

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    
    if(doesExist(id)==false){
        createAccount(id,count);
    }
    else{
    int oldbalance;
    int hashcv=hash(id);
    for(int i =0;i<bankStorage2d[hashcv].size();i++){
        if(bankStorage2d[hashcv][i].id==id){
            oldbalance=bankStorage2d[hashcv][i].balance;
            bankStorage2d[hashcv][i].balance+=count;//found the acc
            break;
        }
    }
    //doing binary search
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
}//correct

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hashcv=hash(id);
    for(int i =0;i<bankStorage2d[hashcv].size();i++){
        if(bankStorage2d[hashcv][i].id==id){
            return true; //found the acc
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int hashcv=hash(id);
    int count=0;
    if (doesExist(id)==false){
        return false;
    }
    //matlab hai
    for(int i =0;i<bankStorage2d[hashcv].size();i++){
        if(bankStorage2d[hashcv][i].id==id){
            count=bankStorage2d[hashcv][i].balance;
            std::swap(bankStorage2d[hashcv][i],bankStorage2d[hashcv].back());
            bankStorage2d[hashcv].pop_back();
            size-=1;//size decreased
                
        }
    }
    //doing binary search
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
    
    
}//correct
int Chaining::databaseSize() {
    return size; // Placeholder return value
}//correct
int Chaining::hash(std::string id) {
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
}//correct

