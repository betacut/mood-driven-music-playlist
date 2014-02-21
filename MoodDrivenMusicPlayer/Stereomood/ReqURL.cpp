#include "requrl.h"

/*-------------------------------------------------------
                    <Max Felinger>

1) Initialize constant variables.
---------------------------------------------------------*/
ReqURL::ReqURL(){
    baseURL = "http://www.stereomood.com/api/search.xml";
    questionMark = "?";

    moodName = "q";
    moodValue = "";

    typeName = "type";
    typeValue = "mood";

    consumerKeyName = "oauth_consumer_key";
    consumerKeyValue = "188b905308b4ad4c03a58466fb3e77f4052fb849c";

    tokenName = "oauth_token";
    tokenValue = "8d85843fca99417b81ddeb1bf27b2090052fb8ef1";

    sigMethodName = "oauth_signature_method";
    sigMethodValue = "HMAC-SHA1";

    sigName = "oauth_signature";
    sigValue = "6a364ce45d252833dfea676df37b9943";

    timestampName = "oauth_timestamp";
    timestampValue = "";

    // Random value for every request. To avoid replay attacks.
    nonceName = "oauth_nonce";
    nonceValue = "";
}

/*-------------------------------------------------------
                    <Max Felinger>

1) Set mood, timestamp and nonce.
2) Build and return final url.
---------------------------------------------------------*/
QString ReqURL::setMood(QString newMood){
    moodValue = newMood;
    timestampValue = QString::number(time(&timer));
    nonceValue = QString::number(rand() % 10000 + 1);
    QString fullURL = buildURL();

    return fullURL;
}

/*-------------------------------------------------------
                    <Max Felinger>

1) Check possible failure source.
2) Build final url and return it.
---------------------------------------------------------*/
QString ReqURL::buildURL(){

    if(moodValue.size() < 1){
        cerr << "Error: No mood!" << endl;
    } else if(timestampValue.size() < 1){
        cerr << "Error: No timestamp!" << endl;
    } else if(nonceValue.size() < 1){
        cerr << "Error: No nonce!" << endl;
    }

    QString fullURL =
                    baseURL + questionMark
                  + moodName + "=" + moodValue
            + "&" + typeName + "=" + typeValue
            + "&" + consumerKeyName + "=" + consumerKeyValue
            + "&" + tokenName + "=" + tokenValue
            + "&" + sigMethodName + "=" + sigMethodValue
            + "&" + sigName + "=" + sigValue
            + "&" + timestampName + "=" + timestampValue
            + "&" + nonceName + "=" + nonceValue;

    return fullURL;
}
