#include <bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Password V5";
    while(1){
        cout<<"\n==================================\n1.Encryption\n2.Decryption\n3.About\n4.Exit\nYour choose:"<<endl;
        string ch;
        cin>>ch;
        if(ch=="1"){
        system("e.exe");
        }else if(ch=="2"){
            system("d.exe");
        }else if(ch=="3"){
            system("about.exe");
        }else{
            return 0;
        }
    }
    return 0;
}