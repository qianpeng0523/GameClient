//
// Copyright (c) 2014-2015 purelib - All Rights Reserved
//
#ifndef _CRYPTO_UTILS_H_
#define _CRYPTO_UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "aes.h"
#include "md5.h"
#include "libb64.h"
#include "mathext.h"

//#ifdef __cplusplus
//extern "C" 
//{
//#endif

/*
 * This package supports both compile-time and run-time determination of CPU
 * byte order.  If ARCH_IS_BIG_ENDIAN is defined as 0, the code will be
 * compiled to run only on little-endian CPUs; if ARCH_IS_BIG_ENDIAN is
 * defined as non-zero, the code will be compiled to run only on big-endian
 * CPUs; if ARCH_IS_BIG_ENDIAN is not defined, the code will be compiled to
 * run on either big- or little-endian CPUs, but will run slightly less
 * efficiently on either one than if ARCH_IS_BIG_ENDIAN is defined.
 */

#define CODEC_OK         0
#define CODEC_BAD_ALLOC -2


/* basic char convertors */
uint8_t     hex2uchr(const uint8_t hex);

uint8_t     uchr2hex(const uint8_t ch);

uint8_t     hex2chr(const uint8_t hex);

uint8_t     chr2hex(const uint8_t ch);

char*       hex2chrp(const uint8_t hex, char charp[2]);

uint8_t     chrp2hex(const char* charp[2]);

/* convert hexstream to charstream */
void        hexs2chars(const void* source, unsigned int sourceLen,
                                   char* dest, unsigned int destLen);
/* -- end of basic convertors -- */

/* Simple MD5 implementation, the return is a hexstream */
void        md5(const void* initial_msg, size_t initial_len, void* digest);

/* Simple MD5 implementation, the return is a hexstream */
void        md5chars(const void* initial_msg, size_t initial_len, char chars[32]);

/* MD5 V3: implement by call the openssl-md5 library, the return is a hexstream*/
// void        md5_v3(const void* source, unsigned int sourceLen, void* dest);

/* Simple MD6 implementation, the return is a hexstream*/
void        md6(const void* source, unsigned int sourceLen, void* dest, unsigned int hashByteLen);

/* Simple MD6 implementation, the return is a hexstream*/
void        md6chars(const void* source, unsigned int sourceLen, char* dest, unsigned int hashByteLen);

/* base 64 encode: destLen should be set sourceLen * 2 */
int         base64enc(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen); 
/* base 64 decode: destLen should be set sourceLen */
int         base64dec (const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

/* urlencode(RFC1738 standard implement): destLen should be sourceLen * 3.
**
** remark: php urlencode ' ' to '+'; but php urldecode can decode both
**         RFC1738 encode-text and php urlencode.
*/
int         urlenc(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

/* urldecode: the destLen should be sourceLen
**
*  remark: support decode RFC1738 encode-text and php urlencode.
*/
int         urldec(const void *source, unsigned int sourceLen,
                                 void *dest,   unsigned int *destLen);

//#ifdef __cplusplus
//}  /* end extern "C" */
//#endif

///
/// all follow api regardless input as alignment BLOCK_SIZE: 16
/// overlapped api
///

#include <string>
#include <vector>

namespace crypto {

    namespace aes {

        // ժҪ:
        //     ָ�����ڼ��ܵĿ�����ģʽ��
        enum CipherMode
        {
            // ժҪ:
            //     ������� (CBC) ģʽ�����˷�����ÿ�����ı����ڼ���ǰ��ͨ����λ����򡱲�����ǰһ����������ı���ϡ�����ȷ���˼�ʹ���ı����������ͬ�Ŀ飬��Щ���е�ÿһ��Ҳ�����Ϊ��ͬ�������ı��顣�ڼ��ܿ�֮ǰ����ʼ������ͨ����λ����򡱲������һ�����ı����ϡ���������ı�������һ��λ������Ӧ�Ĵ��ı���Ҳ���������⣬����Ŀ�����ԭ����λ��λ����ͬ��λҲ������
            CBC = 1,
            //
            // ժҪ:
            //     �������뱾 (ECB) ģʽ�ֱ����ÿ���顣����ζ���κδ��ı���ֻҪ��ͬ������ͬһ��Ϣ�У�����������ͬ����Կ���ܵĲ�ͬ��Ϣ�У�������ת����ͬ���������ı��顣���Ҫ���ܵĴ��ı����������ظ��Ŀ飬������ƽ������ı��ǿ��еġ����⣬��ʱ׼�������Ķ��ֿ�������û�в�������������ͽ�������Ŀ顣��������ı�������һ��λ������Ӧ���������ı���Ҳ������
            ECB = 2,
            //
            // ժҪ:
            //     ������� (OFB) ģʽ�����������Ĵ��ı�����������ı���������һ�δ��������顣��ģʽ�� CFB ���ƣ�������ģʽ��Ψһ�������λ�Ĵ�������䷽ʽ��ͬ����������ı�����һ��λ�������ı�����Ӧ��λҲ���������ǣ���������ı����ж������ȱ�ٵ�λ�����Ǹ�λ֮��Ĵ��ı���������
            OFB = 3,
            //
            // ժҪ:
            //     ���뷴�� (CFB) ģʽ�����������Ĵ��ı�����������ı���������һ�δ��������顣��ģʽʹ���ڳ�����Ϊһ�����ұ���Ϊ�����ֵ���λ�Ĵ��������磬������СΪ
            //     8 ���ֽڣ�����ÿ�δ���һ���ֽڣ�����λ�Ĵ�������Ϊ 8 �����֡���������ı�����һ��λ������һ�����ı�λ����������λ�Ĵ����𻵡��⽫���½��������ɴε����Ĵ��ı�����ֱ������λ����λ�Ĵ������Ƴ�Ϊֹ��
            CFB = 4,
            //
            // ժҪ:
            //     �����ı����� (CTS) ģʽ�����κγ��ȵĴ��ı������������봿�ı�����ƥ��������ı�����������������ı����⣬�������������飬��ģʽ�� CBC
            //     ģʽ����Ϊ��ͬ��
            CTS = 5,
        };

        // ժҪ:
        //     ָ������Ϣ���ݿ�ȼ��ܲ��������ȫ���ֽ�����ʱӦ�õ�������͡�
        enum PaddingMode
        {
            // ժҪ:
            //     ����䡣
            None = 1,
            //
            // ժҪ:
            //     PKCS #7 ����ַ�����һ���ֽ�������ɣ�ÿ���ֽ������ֽ����еĳ��ȡ�
            PKCS7 = 2,
            //
            // ժҪ:
            //     ����ַ���������Ϊ����ֽ���ɡ�
            Zeros = 3,
            //
            // ժҪ:
            //     ANSIX923 ����ַ�����һ���ֽ�������ɣ����ֽ����е����һ���ֽ�����ֽ����еĳ��ȣ������ֽھ���������㡣
            ANSIX923 = 4,
            //
            // ժҪ:
            //     ISO10126 ����ַ�����һ���ֽ�������ɣ����ֽ����е����һ���ֽ�����ֽ����еĳ��ȣ������ֽ����������ݡ�
            ISO10126 = 5,
        };

        #define _BYTE_SEQ_CONT _ByteSeqCont

        static const char* DEFAULT_KEY = "ZQnNQmA1iIQ3z3ukoPoATdE88OJ0qsMm";
        
        namespace detail {

            namespace padding{

                template<typename _ByteSeqCont>
                inline size_t PKCS7(_BYTE_SEQ_CONT& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(typename _BYTE_SEQ_CONT::value_type) == 1, "PKCS7: only allow stl sequently byte conatiner!");
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        plaintext.push_back((char)padding_size);
                    }
                    return padding_size;
                }

                template<typename _ByteSeqCont>
                inline size_t ZEROS(_BYTE_SEQ_CONT& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ZEROS: only allow stl sequently byte conatiner!");
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        plaintext.push_back((char)0);
                    }
                    return padding_size;
                }

                template<typename _ByteSeqCont>
                inline size_t ANSIX923(_BYTE_SEQ_CONT& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ANSIX923: only allow stl sequently byte conatiner!");
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        plaintext.push_back((char)0);
                    }
                    plaintext.push_back((char)padding_size);
                    return padding_size;
                }

                template<typename _ByteSeqCont>
                inline size_t ISO10126(_BYTE_SEQ_CONT& plaintext, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ISO10126: only allow stl sequently byte conatiner!");
                    size_t padding_size = blocksize - plaintext.size() % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        plaintext.push_back((char)(unsigned char)mathext::rrand(0, 256));
                    }
                    plaintext.push_back((char)padding_size);
                    return padding_size;
                }

                template<typename _ByteSeqCont = std::string>
                inline _BYTE_SEQ_CONT PKCS7(size_t datasize, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ISO10126: only allow stl sequently byte conatiner!");
                    _BYTE_SEQ_CONT padding;
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        padding.push_back((char)padding_size);
                    }
                    return std::move(padding);
                }

                template<typename _ByteSeqCont = std::string>
                inline _BYTE_SEQ_CONT ZEROS(size_t datasize, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ISO10126: only allow stl sequently byte conatiner!");
                    _BYTE_SEQ_CONT padding;
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        padding.push_back((char)0);
                    }
                    return std::move(padding);
                }

                template<typename _ByteSeqCont = std::string>
                inline _BYTE_SEQ_CONT ANSIX923(size_t datasize, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ISO10126: only allow stl sequently byte conatiner!");
                    _BYTE_SEQ_CONT padding;
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        padding.push_back((char)0);
                    }
                    padding.push_back((char)padding_size);
                    return std::move(padding);
                }

                template<typename _ByteSeqCont = std::string>
                inline _BYTE_SEQ_CONT ISO10126(size_t datasize, size_t blocksize = AES_BLOCK_SIZE)
                {
                    static_assert(sizeof(_BYTE_SEQ_CONT::value_type) == 1, "ISO10126: only allow stl sequently byte conatiner!");
                    _BYTE_SEQ_CONT padding;
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size - 1; ++offst)
                    {
                        padding.push_back((char)(unsigned char)mathext::rrand(0, 256));
                    }
                    padding.push_back((char)padding_size);
                    return std::move(padding);
                }


                inline size_t PKCS7(size_t datasize, char padding[16], size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        padding[AES_BLOCK_SIZE - 1 - offst] = (unsigned char)padding_size;
                    }
                    return padding_size;
                }

                inline size_t ZEROS(size_t datasize, char padding[16], size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - datasize % blocksize;
                    for (size_t offst = 0; offst < padding_size; ++offst)
                    {
                        padding[AES_BLOCK_SIZE - 1 - offst] = 0;
                    }
                    return padding_size;
                }

                inline size_t ANSIX923(size_t datasize, char padding[16], size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - datasize % blocksize;
                    padding[AES_BLOCK_SIZE - 1] = (unsigned char)padding_size;
                    for (size_t offst = 1; offst < padding_size; ++offst)
                    {
                        padding[AES_BLOCK_SIZE - 1 - offst] = 0;
                    }
                    return padding_size;
                }

                inline size_t ISO10126(size_t datasize, char padding[16], size_t blocksize = AES_BLOCK_SIZE)
                {
                    size_t padding_size = blocksize - datasize % blocksize;
                    padding[AES_BLOCK_SIZE - 1] = (unsigned char)padding_size;
                    for (size_t offst = 1; offst < padding_size; ++offst)
                    {
                        padding[AES_BLOCK_SIZE - 1 - offst] = (unsigned char)mathext::rrand(0, 256);
                    }
                    return padding_size;
                }
            }

            /// AES ecb
            void ecb_encrypt(const void* in, size_t inlen,
                void* out, size_t outlen, const void* private_key, int keybits = 256);
            void ecb_decrypt(const void* in, size_t inlen,
                void* out, size_t& outlen, const void* private_key, int keybits = 256);

            /// AES cbc
            void cbc_encrypt(const void* in, size_t inlen,
                void* out, size_t outlen, const void* private_key, int keybits = 256);

            void cbc_decrypt(const void* in, size_t inlen,
                void* out, size_t& outlen, const void* private_key, int keybits = 256);

            /// AES cbc partial encrypt/decrypt
            void set_ivec(const void* ivec, size_t len = AES_BLOCK_SIZE /* always AES_BLOCK_SIZE 16*/);
			
			/// the size always 16 bytes
			const void* get_ivec();

            void cbc_encrypt_init(const void* private_key, int keybits = 256);

            void cbc_decrypt_init(const void* private_key, int keybits = 256);

            void cbc_encrypt_init(const void* in, size_t inlen,
                void* out, size_t outlen,
                const void* private_key, int keybits = 256);

            void cbc_decrypt_init(const void* in, size_t inlen,
                void* out, size_t outlen,
                const void* private_key, int keybits = 256);

            void cbc_encrypt_block(const void* in, size_t inlen,
                void* out, size_t outlen);

            void cbc_decrypt_block(const void* in, size_t inlen,
                void* out, size_t outlen);
        };
    };
};

#endif /* _CRYPTO_UTILS_H_ */
/*
* Copyright (c) 2012-2016 by halx99 ALL RIGHTS RESERVED.
* Consult your license regarding permissions and restrictions.
V2.0:2016 */
