#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct rules {
    string left;
    string right;
    bool last=false;
    rules* next;
    ~rules();
}*rule;

rules::~rules(){
    rules *temp=rule;
    while (temp->next!=NULL){
        temp=temp->next;
        delete rule;
        rule=temp;
    }
}

void addRule(string buf,bool lOrR){
    rules *temp;
    if (lOrR){
        //right
        temp = rule;
        while (temp->next !=NULL){
            temp=temp->next;

        }
        temp->right=buf;
        if (temp->right[0]=='.')
            temp->last=true;
    }
    else{
        //left
        rules *new_Rule = new rules;
        new_Rule->left=buf;
        new_Rule->next=NULL;

        if (rule == NULL ){
            rule = new_Rule;
        }
        else {
            temp = rule;
            while (temp->next!=NULL){
                temp=temp->next;
            }
            temp->next = new_Rule;
        }
    }
    return;
}

string * readTheRest (string in, string un, int i){
    int unLength = un.size();
    int inLength = in.size();
    string * ans = new string;
    for (;i<inLength;i++){
        ans->push_back (in [i]);
    }
    return ans;
}

string * readUntilString(string in, string un, int &index){
    int unLength = un.size();
    int inLength = in.size();
    string temp;
    string *ans = new string;
    for (int i = 0; i < in.size(); i++ ){
        if (i+unLength-1<inLength){
            for (int j=i; j <i+unLength; j++){
                temp.push_back (in[j]);
            }
            if (temp == un){
                index = i+unLength;
                return ans;
            }
            else {
                temp.clear();
            }
        }
        ans->push_back (in[i]);
    }
    return ans;
}

void readFile (){
    string buf;
    fstream input ("algorithm1.txt");
    int i;
    string temp;
    while (getline(input, temp)){
        addRule(*readUntilString(temp," -> ",i),0);
        addRule(*readTheRest(temp," -> ", i),1);
        buf.clear();
        temp.clear();
    }
    input.close();
    return;
}

void out(rules *a){
    while (a->next!=NULL){
        cout<<a->left<<" -> "<<a->right<<endl;
        a=a->next;
    }
    cout<<a->left<<" -> "<<a->right<<endl;
    return;
}

bool isTheSame(string in, string un, int &index){
    int unLength = un.size();
    int inLength = in.size();
    string temp;
    for (int i = 0; i < in.size(); i++ ){
        if (i+unLength-1<inLength){
            for (int j=i; j <i+unLength; j++){
                temp.push_back (in[j]);
            }
            if (temp == un){
                index = i;
                return true;
            }
            else {
                temp.clear();
            }
        }
    }
    return false;
}

bool change (string what, string &where, rules *r, int index){
    where.erase (index,what.size());

    if (r->right[0] == '.'){
        where.insert(index,r->right,1,r->right.size()-1);
        return true;
    }
    else{
        where.insert (index,r->right);
        return false;
    }
}

void doCheck(string &input, rules *r){
    int index;
    rules *temp = r;
    while (temp->next!=NULL){
        if (isTheSame(input,temp->left,index)){
            cout<<input<<endl;
            if (change (temp->left,input,temp,index)){
                return;
            }
        }
        else{
            temp=temp->next;
        }
    }

    if (isTheSame(input,temp->left,index)){
        cout<<input<<endl;
            if (change (temp->left,input,temp,index)){
                return;
            }
    }
    return;
}

void del (rules *b){
    rules *e;
    while (b->next!=NULL){
        e=b->next;
        delete b;
        b=e;
    }
}

int main(){
    readFile();
    out(rule);
    string buf;
    cout<<"Enter a string - ";
    getline(cin,buf);
    doCheck(buf,rule);
    cout<<buf;
    return 0;
}
