#include <string>
#include <iostream>
#include <map>

std::map<std::string, std::string> httpheaderParser ( char* httpBuffer, int requistLen ) {

    int i = 0;
    std::string key, val;
    std::map<std::string, std::string> *headerMap = new std::map<std::string, std::string>();
    while ( i <= requistLen ) {
    
        // parse ( method, url, http version ) first 
        if (i == 0) {

            while ( !(httpBuffer[i] == '\r' && httpBuffer[i + 1] == '\n') ) {
                val += httpBuffer[i++];
            }
            i += 2;
            (*headerMap)["Method"] = val;
            val.clear();
        }
        
        // parse header element as key value
        while ( httpBuffer[i] != ':' )
            key += httpBuffer[i++];
        i += 2;
        
        // test for flag of valeu to ("\r\n") or first half of http_end ("\r\n\r\n")
        while ( !( httpBuffer[i] == '\r' && httpBuffer[i + 1] == '\n' ) ) {
            val += httpBuffer[i++];
        }
        i += 2;
        
        // add key, value to map
        (*headerMap)[key] = val;
        
        // clear temporer buffer
        key.clear();
        val.clear();
        
        // test for flag of second half http_end ("\r\n\r\n")
        if ( httpBuffer[i] == '\r' && httpBuffer[i + 1] == '\n' )
                break;
    }
    // add request length
    (*headerMap)["http-header-length"] = std::to_string(i);
    
    // print result;
    for ( std::map<std::string, std::string>::iterator it = (*headerMap).begin(); it != (*headerMap).end(); it++ ) {
        std::cout << it->first << " : " << it->second << std::endl;
    }
    return *headerMap;
}
