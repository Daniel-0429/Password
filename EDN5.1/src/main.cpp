#include <bits/stdc++.h>
using namespace std;
int main(int argc,char* argv[]){
    if(argc!=1){
    	if(argc==2){
	    if(strcmp(argv[1],"-e")==0){
	    	system("e.exe");
	    }else if(strcmp(argv[1],"-d")==0){
	    	system("d.exe");
	    }else if(strcmp(argv[1],"--about")==0){
	    	system("about.exe");
	    }else{
		cout<<argv[1]<<endl;
	    	cout<<"error!argument error!"<<endl;
		cout<<"Usage: password [arguments]"<<endl;
		cout<<"   or: password"<<endl;
		cout<<"Encrypt and decrypt the string you provide."<<endl;
		cout<<"Arguments:\n";
		cout<<"   --                   Enter the menu\n";
		cout<<"   -e                   Enter encrypt mode\n";
		cout<<"   -d                   Enter decrypt mode\n";
		cout<<"   --about              Print about information\n";
	    }
	    return 0;
	}else{
	    cout<<"Error!Too many argument!"<<endl;
	    cout<<"Usage: password [arguments]"<<endl;
            cout<<"   or: password"<<endl;
            cout<<"Encrypt and decrypt the string you provide."<<endl;
            cout<<"Arguments:\n";
            cout<<"   --                   Enter the menu\n";
            cout<<"   -e                   Enter encrypt mode\n";
            cout<<"   -d                   Enter decrypt mode\n";
            cout<<"   --about              Print about information\n";
	    return 0;
	}
    }
    while(1){
        cout<<"Password V5.1\n";
        cout<<"===========================================================\n";
        cout<<"1.加密方"<<endl;
        cout<<"2.接收方"<<endl;
        cout<<"3.关于"<<endl;
        cout<<"4.退出"<<endl;
        cout<<"请选择："<<endl;
        string a;
        cin>>a;
        if(a=="1") system("e.exe");
        else if(a=="2") system("d.exe");
        else if(a=="3") system("about.exe");
        else if(a=="4") return 0;
        else cout<<"错误！请重新选择！"<<endl;
    }
    return 0;
}
