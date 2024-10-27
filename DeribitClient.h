// DeribitClient.h

#pragma once
#include <string>
#include <cpprest/http_client.h>
using namespace std:

class DeribitClient {
public:
    DeribitClient(const std::string& client_id, const std::string& client_secret);
    void authenticate();
    void placeOrder(const std::string& symbol, double amount, double price);
    void cancelOrder(const std::string& order_id);
    void modifyOrder(const std::string& order_id, double new_price);
    void getOrderBook(const std::string& symbol);
    void viewPositions();

private:
    string client_id_;
    string client_secret_;
    string access_token_;
    web::http::client::http_client client_;

    web::http::http_response sendRequest(const web::http::method& method, const std::string& path, const web::json::value& body);
};
