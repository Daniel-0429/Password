#include <bits/stdc++.h>
#include "../include/sodium.h"
using namespace std;
string bin2hex(const string &bin) {
    string hex;
    for(unsigned char c : bin) {
        char buf[3];
        sprintf(buf, "%02x", c);
        hex += buf;
    }
    return hex;
}
int main(){
    if(sodium_init() < 0){
        cout << "初始化失败！" << endl;
        return 0;
    }
    unsigned char pk[crypto_kx_PUBLICKEYBYTES], sk[crypto_kx_SECRETKEYBYTES];
    crypto_kx_keypair(pk, sk);
    cout << "我方公钥：";
    for(int i = 0; i < crypto_kx_PUBLICKEYBYTES; i++){
        printf("%02x", pk[i]);
    }
    cout << endl;
    cout << "请输入对方公钥：";
    string other_pk_hex;
    cin >> other_pk_hex;
    unsigned char other_pk[crypto_kx_PUBLICKEYBYTES];
    for(int i = 0; i < crypto_kx_PUBLICKEYBYTES; i++){
        sscanf(other_pk_hex.c_str() + 2*i, "%02hhx", &other_pk[i]);
    }
    unsigned char rx[crypto_kx_SESSIONKEYBYTES], tx[crypto_kx_SESSIONKEYBYTES];
    if(crypto_kx_client_session_keys(rx, tx, pk, sk, other_pk) != 0){
        cout << "会话密钥生成失败！" << endl;
        return 0;
    }
    while(1){
        cout<<"===========================================================\n";
        cout<<"1.继续连接"<<endl;
        cout<<"2.回到主菜单(连接不保存)"<<endl;
        cout<<"请选择："<<endl;
        string a;
        cin>>a;
        if(a=="2") return 0;
        else if(a!="1"){
            cout<<"错误！请重新选择！"<<endl;
            system("pause");
            continue;
        }
        cout<<"请输入要加密的文本：";
        string plaintext_str;
        cin.ignore();
        getline(cin,plaintext_str);
        const unsigned char* plaintext=reinterpret_cast<const unsigned char*>(plaintext_str.data());
        unsigned long long plaintext_len=plaintext_str.size();
        unsigned char nonce[crypto_secretbox_NONCEBYTES];
        randombytes_buf(nonce,sizeof(nonce));
        unsigned char* ciphertext=new unsigned char[plaintext_len+crypto_secretbox_MACBYTES];
        if(crypto_secretbox_easy(ciphertext,plaintext,plaintext_len,nonce,tx)!=0){
            cout<<"加密失败！"<<endl;
            delete[] ciphertext;
            continue;
        }
        cout<<"加密结果："<<bin2hex(string(reinterpret_cast<char*>(ciphertext),plaintext_len+crypto_secretbox_MACBYTES))<<endl;
        cout<<"临时密钥："<<bin2hex(string(reinterpret_cast<char*>(nonce),sizeof(nonce)))<<endl;
        delete[] ciphertext;
    }
    return 0;
}