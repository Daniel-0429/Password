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
    if(sodium_init()<0){
        cout<<"初始化失败！"<<endl;
        return 0;
    }
    
    unsigned char pk[crypto_kx_PUBLICKEYBYTES], sk[crypto_kx_SECRETKEYBYTES];
    crypto_kx_keypair(pk, sk);
    
    cout<<"我方公钥：";
    for(int i=0; i<crypto_kx_PUBLICKEYBYTES; i++){
        printf("%02x", pk[i]);
    }
    cout<<endl;
    
    cout<<"请输入对方公钥：";
    string other_pk_hex;
    cin>>other_pk_hex;
    
    unsigned char other_pk[crypto_kx_PUBLICKEYBYTES];
    for(int i=0; i<crypto_kx_PUBLICKEYBYTES; i++){
        sscanf(other_pk_hex.c_str() + 2*i, "%02hhx", &other_pk[i]);
    }
    
    // 使用 client_session_keys
    unsigned char rx[crypto_kx_SESSIONKEYBYTES], tx[crypto_kx_SESSIONKEYBYTES];
    if(crypto_kx_client_session_keys(rx, tx, pk, sk, other_pk) != 0){
        cout<<"会话密钥生成失败！"<<endl;
        return 0;
    }
    
    cout<<"请输入要加密的文本：";
    string plaintext;
    cin.ignore();
    getline(cin, plaintext);
    
    string ciphertext = plaintext;
    for(int i=0; i<ciphertext.size(); ++i){
        ciphertext[i] ^= tx[i % crypto_kx_SESSIONKEYBYTES];
        if(i>=1){
            ciphertext[i] ^= plaintext[i - 1];
        }
    }
    
    cout<<"加密结果(十六进制)："<<bin2hex(ciphertext)<<endl;
    return 0;
}