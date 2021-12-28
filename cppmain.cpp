
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include "Javamain.h"

const std::string hex_str_texto{"FABADACAFEDEADF00D"};
using namespace std;

void convertHexStringToArray(string str,unsigned char *buffOut)
{
    for (int b = 0, e = str.length(); b != e; b += 2)
        {
            std::stringstream ss;
            ss << std::hex << str.substr(b, 2);
            int valor;
            ss >> valor;
            buffOut[b / 2] = valor;
        }
}

string covertUnsignedCharArrayToString (unsigned char * buf,int len){
    char convert [len * 2 + 1];
    for(int i = 0; i < len ; i++){
        sprintf(&convert[i*2],"%02X",buf[i]);
    }
    string output = convert;
    return output;
}


std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}



JNIEXPORT jstring JNICALL Java_Javamain_test
  (JNIEnv *env, jobject obj, jstring str)
  {
  
  string stringTest = jstring2string(env, str);
  	
  unsigned char *ptr;
   ptr = (unsigned char *)malloc(4);
   convertHexStringToArray(stringTest,ptr);
   for(int i = 0 ; i< 2;i++)
   {
   	*(ptr +i) += 4;
   
   }
   
   string outString = covertUnsignedCharArrayToString(ptr,2);
   char * c = const_cast<char *>(outString.c_str());
   jstring result =  env->NewStringUTF(c);
   return result;
  
  }

