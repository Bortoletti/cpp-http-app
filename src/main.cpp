#include <iostream>
#include <string>
#include <curl/curl.h>


static size_t callbackF( char *contentsParam, size_t sizeParam, size_t nmemParam, char * bufferParam )
{
    size_t returnValue = sizeParam * nmemParam;
    ((std::string*)bufferParam)->append((char*)contentsParam, returnValue );
    return returnValue;

}



int main( int srgc, char ** argv )
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if( curl )
    {
        curl_easy_setopt( curl, CURLOPT_URL, argv[1] );
        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, callbackF );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, &readBuffer );

        res = curl_easy_perform( curl );
                
        curl_easy_cleanup( curl );

        std::cout << readBuffer << std::endl;
    }

    return 0;
}