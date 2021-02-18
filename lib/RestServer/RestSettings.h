#ifndef restsettings_h
#define restsettings_h

#ifndef ROUTES_TOTAL
#define ROUTES_TOTAL 5
#endif

#ifndef ROUTES_LENGHT
#define ROUTES_LENGHT 30
#endif

#ifndef QUERY_LENGTH
#define QUERY_LENGTH 50
#endif

#ifndef HTTP_COMMON_HEADER
#define HTTP_COMMON_HEADER "HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: POST, GET, PUT, OPTIONS\r\nContent-Type: text/html\r\nConnection: close\r\n\n"
#endif HTTP_COMMON_HEADER

/*
#ifndef HTTP_REDIRECTION_HEADER
#define HTTP_REDIRECTION_HEADER "HTTP/1.1 302 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: POST, GET, PUT, OPTIONS\r\nLocation: http://octopi.local/static/img/tentacle-32x32.png\r\nConnection: close\r\n"
#endif HTTP_REDIRECTION_HEADER
*/


#ifndef HTTP_REDIRECTION_HEADER
#define HTTP_REDIRECTION_HEADER "HTTP/1.1 302 OK\r\n"
#endif HTTP_REDIRECTION_HEADER


#ifndef OUTPUT_BUFFER_SIZE
#define OUTPUT_BUFFER_SIZE 2000
#endif OUTPUT_BUFFER_SIZE

#define JSON_START() addToBuffer("{ ");
#define JSON_CLOSE() addToBuffer(" }");


#define METHODS_LENGTH 7
#define ANY "*"
#define GET "GET"
#define PUT "PUT"
#define HEAD "HEAD"
#define POST "POST"
#define TRACE "TRACE"
#define DELETE "DELETE"
#define OPTIONS "OPTIONS"

#endif