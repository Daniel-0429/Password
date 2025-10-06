#include "./../include/sodium.h"
#include <bits/stdc++.h>

int main() {
    if (sodium_init() < 0) return 1;

    // A端密钥对
    unsigned char pkA[crypto_kx_PUBLICKEYBYTES], skA[crypto_kx_SECRETKEYBYTES];
    crypto_kx_keypair(pkA, skA);

    // B端密钥对
    unsigned char pkB[crypto_kx_PUBLICKEYBYTES], skB[crypto_kx_SECRETKEYBYTES];
    crypto_kx_keypair(pkB, skB);

    // 会话密钥
    unsigned char rxA[crypto_kx_SESSIONKEYBYTES], txA[crypto_kx_SESSIONKEYBYTES];
    unsigned char rxB[crypto_kx_SESSIONKEYBYTES], txB[crypto_kx_SESSIONKEYBYTES];

    crypto_kx_client_session_keys(rxA, txA, pkA, skA, pkB);
    crypto_kx_server_session_keys(rxB, txB, pkB, skB, pkA);

    // 检查双方会话密钥是否一致
    std::cout << "A端接收密钥 == B端发送密钥 ? " << (memcmp(rxA, txB, crypto_kx_SESSIONKEYBYTES) == 0 ? "是" : "否") << std::endl;
    std::cout << "B端接收密钥 == A端发送密钥 ? " << (memcmp(rxB, txA, crypto_kx_SESSIONKEYBYTES) == 0 ? "是" : "否") << std::endl;

    // 用 rxA/txA/rxB/txB 做加密通信
}