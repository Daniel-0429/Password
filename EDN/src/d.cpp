#include <bits/stdc++.h>
#include "../include/sodium.h"
using namespace std;

string hex2bin(const string &hex) {
    string bin;
    for(size_t i=0; i<hex.length(); i+=2) {
        string byte = hex.substr(i, 2);
        char c = (char)strtol(byte.c_str(), NULL, 16);
        bin += c;
    }
    return bin;
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
    
    // 使用 server_session_keys
    unsigned char rx[crypto_kx_SESSIONKEYBYTES], tx[crypto_kx_SESSIONKEYBYTES];
    if(crypto_kx_server_session_keys(rx, tx, pk, sk, other_pk) != 0){
        cout<<"会话密钥生成失败！"<<endl;
        return 0;
    }
    
    cout<<"请输入要解密的文本(十六进制)：";
    string ciphertext_hex;
    cin>>ciphertext_hex;
    
    string ciphertext = hex2bin(ciphertext_hex);
    

    string plaintext = ciphertext;
    for(int i=0; i<plaintext.size(); ++i){
        if(i>=1){
            plaintext[i] ^= plaintext[i - 1];
        }
        plaintext[i] ^= rx[i % crypto_kx_SESSIONKEYBYTES];  // 注意：这里用 rx 而不是 tx
    }
    
    cout<<"解密结果："<<plaintext<<endl;
    
    // 调试信息
    cout<<"调试 - 使用的会话密钥(rx)：";
    for(int i=0; i<min(16, crypto_kx_SESSIONKEYBYTES); i++){
        printf("%02x", rx[i]);
    }
    cout<<endl;
    
    return 0;
}