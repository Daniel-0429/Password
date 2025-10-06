#include <bits/stdc++.h>
#include "../include/sodium.h"
using namespace std;

string hex2bin(const string &hex) {
    string bin;
    for(size_t i = 0; i < hex.length(); i += 2) {
        string byte = hex.substr(i, 2);
        char c = (char)strtol(byte.c_str(), NULL, 16);
        bin += c;
    }
    return bin;
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
    if(crypto_kx_server_session_keys(rx, tx, pk, sk, other_pk) != 0){
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
        cout << "请输入要解密的文本：";
        string ciphertext_hex;
        cin >> ciphertext_hex;
        string ciphertext_bin = hex2bin(ciphertext_hex);  // 用string存储二进制密文，避免指针失效
        const unsigned char* ciphertext = reinterpret_cast<const unsigned char*>(ciphertext_bin.data());
        unsigned long long ciphertext_len = ciphertext_bin.size();
        if(ciphertext_len < crypto_secretbox_MACBYTES){
            cout << "密文长度错误！" << endl;
            return 0;
        }
        cout << "请输入临时密钥(nonce，十六进制)：";
        string nonce_hex;
        cin >> nonce_hex;
        string nonce_bin = hex2bin(nonce_hex);
        if(nonce_bin.size() != crypto_secretbox_NONCEBYTES){
            cout << "nonce长度错误！" << endl;
            return 0;
        }
        const unsigned char* nonce = reinterpret_cast<const unsigned char*>(nonce_bin.data());
        unsigned char* plaintext = new unsigned char[ciphertext_len - crypto_secretbox_MACBYTES];
        unsigned long long plaintext_len;
        if(crypto_secretbox_open_easy(plaintext, ciphertext, ciphertext_len, nonce, rx) != 0){
            cout << "解密失败（密文被篡改或密钥错误）！" << endl;
            delete[] plaintext;
            return 0;
        }
        plaintext_len = ciphertext_len - crypto_secretbox_MACBYTES;
        cout << "解密结果：" << string(reinterpret_cast<char*>(plaintext), plaintext_len) << endl;
        delete[] plaintext;
    }
    return 0;
}