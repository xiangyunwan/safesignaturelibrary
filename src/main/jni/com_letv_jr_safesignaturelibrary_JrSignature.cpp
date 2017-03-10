#include "com_letv_jr_safesignaturelibrary_JrSignature.h"
/**
* 功能说明： </br>
*
* @author: zhangzhenzhong
* @version: 1.0
* @date: 2017/3/10
* @Copyright (c) 2017. zhangzhenzhong Inc. All rights reserved.
*/
//C++实现
/*MD5: 77:71:E6:45:75:82:4E:ED:6A:E5:76:75:86:0C:90:5B
SHA1: 3A:E5:6F:D4:70:85:17:8B:90:FF:60:7F:92:20:D5:86:A9:9A:3C:09
SHA256: 9E:6B:49:3B:71:E1:36:16:53:EF:9A:7B:68:9D:7E:59:C3:5A:D6:F0:E2:
40:47:B4:48:46:A8:B9:27:9B:32:0F
签名算法名称: SHA256withRSA*/
const char *app_signature_sha1="3AE56FD47085178B90FF607F9220D586A99A3C09";
const char HexCode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
//#define  LOG_TAG    "libJNIExInterface"
//#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
JNIEXPORT jint JNICALL Java_com_letv_jr_safesignaturelibrary_JrSignature_getCompareInt(JNIEnv *env, jclass clz, jobject context_object){
jclass context_class = env->GetObjectClass(context_object);

    //context.getPackageManager()
    jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject package_manager_object = env->CallObjectMethod(context_object, methodId);
        if (package_manager_object == NULL) {
        //LOGE("getPackageManager() Failed!");
        return 1;
    }

    //context.getPackageName()
    methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name_string = (jstring)env->CallObjectMethod(context_object, methodId);
    if (package_name_string == NULL) {
        //LOGE("getPackageName() Failed!");
        return 1;
    }
    env->DeleteLocalRef(context_class);

    //PackageManager.getPackageInfo(Sting, int)
    //public static final int GET_SIGNATURES= 0x00000040;
    jclass pack_manager_class = env->GetObjectClass(package_manager_object);
    methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    env->DeleteLocalRef(pack_manager_class);
    jobject package_info_object = env->CallObjectMethod(package_manager_object, methodId, package_name_string, 0x40);
    if (package_info_object == NULL) {
        //LOGE("getPackageInfo() Failed!");
        return 1;
    }
    env->DeleteLocalRef(package_manager_object);

    //PackageInfo.signatures[0]
    jclass package_info_class = env->GetObjectClass(package_info_object);
    jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");
    env->DeleteLocalRef(package_info_class);
    jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info_object, fieldId);
    if (signature_object_array == NULL) {
        //LOGE("PackageInfo.signatures[] is null");
        return 1;
    }
    jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
    env->DeleteLocalRef(package_info_object);

    //Signature.toByteArray()
    jclass signature_class = env->GetObjectClass(signature_object);
    methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
    env->DeleteLocalRef(signature_class);
    jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_object, methodId);

    //new ByteArrayInputStream
    jclass byte_array_input_class=env->FindClass("java/io/ByteArrayInputStream");
    methodId=env->GetMethodID(byte_array_input_class,"<init>","([B)V");
    jobject byte_array_input=env->NewObject(byte_array_input_class,methodId,signature_byte);

    //CertificateFactory.getInstance("X.509")
    jclass certificate_factory_class=env->FindClass("java/security/cert/CertificateFactory");
    methodId=env->GetStaticMethodID(certificate_factory_class,"getInstance","(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
    jstring x_509_jstring=env->NewStringUTF("X.509");
    jobject cert_factory=env->CallStaticObjectMethod(certificate_factory_class,methodId,x_509_jstring);

    //certFactory.generateCertificate(byteIn);
    methodId=env->GetMethodID(certificate_factory_class,"generateCertificate",("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
    jobject x509_cert=env->CallObjectMethod(cert_factory,methodId,byte_array_input);
    env->DeleteLocalRef(certificate_factory_class);

    //cert.getEncoded()
    jclass x509_cert_class=env->GetObjectClass(x509_cert);
    methodId=env->GetMethodID(x509_cert_class,"getEncoded","()[B");
    jbyteArray cert_byte=(jbyteArray)env->CallObjectMethod(x509_cert,methodId);
    env->DeleteLocalRef(x509_cert_class);

    //MessageDigest.getInstance("SHA1")
    jclass message_digest_class=env->FindClass("java/security/MessageDigest");
    methodId=env->GetStaticMethodID(message_digest_class,"getInstance","(Ljava/lang/String;)Ljava/security/MessageDigest;");
    jstring sha1_jstring=env->NewStringUTF("SHA1");
    jobject sha1_digest=env->CallStaticObjectMethod(message_digest_class,methodId,sha1_jstring);

    //sha1.digest (certByte)
    methodId=env->GetMethodID(message_digest_class,"digest","([B)[B");
    jbyteArray sha1_byte=(jbyteArray)env->CallObjectMethod(sha1_digest,methodId,cert_byte);
    env->DeleteLocalRef(message_digest_class);

    //toHexString
    jsize array_size=env->GetArrayLength(sha1_byte);
    jbyte* sha1 =env->GetByteArrayElements(sha1_byte,NULL);
    char *hex_sha=new char[array_size*2+1];
        for (int i = 0; i <array_size ; ++i) {
            hex_sha[2*i]=HexCode[((unsigned char)sha1[i])/16];
            hex_sha[2*i+1]=HexCode[((unsigned char)sha1[i])%16];
        }
    hex_sha[array_size*2]='\0';
    //LOGE(" %s ",hex_sha);
    //比较签名
    if (strcmp(hex_sha,app_signature_sha1)==0)
    {
        //LOGE("验证通过");
        return 0;
    } else{
        return 1;
    }
}
