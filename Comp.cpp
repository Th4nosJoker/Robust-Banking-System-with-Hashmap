#include "Comp.h"
void Comp::insertown(int e,std::vector <int> &v){
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

bool Comp::fun(std::string id,int count, std::vector<Account> &HT1,std::vector<Account> &HT2,int value){
    int h1=hash(id);
    int h2=hash2(id);
    if(value==1){
        if(HT1[h1].id==""){
            Account A;
            A.id=id;
            A.balance=count;
            HT1[h1]=A;
            return true;
        }
        else{
            Account D;
            D.id=HT1[h1].id;
            D.balance=HT1[h1].balance;//saving the displaced keys info
            Account A;
            A.id=id;
            A.balance=count;
            HT1[h1]=A;//displaced
            return fun(D.id,D.balance,HT1,HT2,2);
        }
    }
    else{
        if(HT2[h2].id==""){
            Account A;
            A.id=id;
            A.balance=count;
            HT2[h2]=A;
            return true;
        }
        else{
            Account D;
            D.id=HT2[h2].id;
            D.balance=HT2[h2].balance;//saving the displaced keys info
            Account A;
            A.id=id;
            A.balance=count;
            HT2[h2]=A;//displaced
            return fun(D.id,D.balance,HT1,HT2,1);
        }
    }
}


void Comp::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    fun(id,count,CompHT1,CompHT2,1);
    size+=1;
    insertown(count,topk);
}

std::vector<int> Comp::getTopK(int k) {
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

int Comp::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        return -1;
    }

    else{
        int h1=hash(id);
        int h2=hash2(id);
        if(CompHT1[h1].id==id){
            return CompHT1[h1].balance;
        }
        else{
            return CompHT2[h2].balance;
        }
    }
    return 0;
}

void Comp::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(doesExist(id)==false){
        createAccount(id,count);
    }
    else{
        int h1=hash(id);
        int h2=hash2(id);
        int oldbalance;
        if(CompHT1[h1].id==id){
            oldbalance=CompHT1[h1].balance;
            CompHT1[h1].balance+=count;
        }
        else if (CompHT2[h2].id==id){
            oldbalance=CompHT2[h2].balance;
            CompHT2[h2].balance+=count;
        }
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

bool Comp::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h1=hash(id);
    int h2=hash2(id);
    if(CompHT1[h1].id==id || CompHT2[h2].id==id){
        return true;
    }
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    if (doesExist(id)==false){
        return false;
    }
    
    int h1=hash(id);
    int h2=hash2(id);
    int count=0;

    if(CompHT1[h1].id==id){
        count=CompHT1[h1].balance;
        CompHT1[h1].id="";
        CompHT1[h1].balance=-1;
    }
    else if(CompHT2[h2].id==id){
        count=CompHT2[h2].balance;
        CompHT2[h2].id="";
        CompHT2[h2].balance=-1;
    }
    size-=1;
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
}
int Comp::databaseSize() {
    // IMPLEMENT YOUR CODE HERE

    return size; // Placeholder return value
}
int Comp::hash2(std::string id){
    int a=41;
    int hashv=0;
    int k=id.length();
    int m=200003;
    int a_pow=1;
    for(int i=k-1;i>=0;i--){
        hashv=(hashv+(id[i]*a_pow)%m)%m;
        a_pow=(a_pow*a)%m;
    }
    return hashv%m;

}


int Comp::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int a=33;
    int hashv=0;
    int k=id.length();
    int m=200003;
    int a_pow=1;
    for(int i=k-1;i>=0;i--){
        hashv=(hashv+(id[i]*a_pow)%m)%m;
        a_pow=(a_pow*a)%m;
    }
    return hashv%m;
    
}
