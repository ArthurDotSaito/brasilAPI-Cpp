#include <drogon/drogon.h>
#include <drogon/HttpClient.h>
#include <json/json.h>
#include <gtest/gtest.h>

int main(){
    drogon::app()
        .setLogLevel(trantor::Logger::LogLevel::kTrace)
        .run();
    
    return 0;
}
