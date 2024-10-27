// DeribitClient.cpp

#include "DeribitClient.h"
#include <cpprest/json.h>
#include <iostream>

DeribitClient::DeribitClient(const std::string& client_id, const std::string& client_secret)
    : client_id_(client_id), client_secret_(client_secret),
      client_("https://test.deribit.com/api/v2/") {}

void DeribitClient::authenticate() {
    web::json::value body;
    body[U("grant_type")] = web::json::value::string(U("client_credentials"));
    body[U("client_id")] = web::json::value::string(client_id_);
    body[U("client_secret")] = web::json::value::string(client_secret_);

    auto response = sendRequest(web::http::methods::POST, "public/auth", body);
    auto json = response.extract_json().get();
    access_token_ = json[U("result")][U("access_token")].as_string();
}

void DeribitClient::placeOrder(const std::string& symbol, double amount, double price) {
    web::json::value body;
    body[U("instrument_name")] = web::json::value::string(symbol);
    body[U("amount")] = web::json::value::number(amount);
    body[U("price")] = web::json::value::number(price);

    sendRequest(web::http::methods::POST, "private/buy", body);
}

void DeribitClient::cancelOrder(const std::string& order_id) {
    web::json::value body;
    body[U("order_id")] = web::json::value::string(order_id);
    sendRequest(web::http::methods::POST, "private/cancel", body);
}

void DeribitClient::modifyOrder(const std::string& order_id, double new_price) {
    web::json::value body;
    body[U("order_id")] = web::json::value::string(order_id);
    body[U("price")] = web::json::value::number(new_price);
    sendRequest(web::http::methods::POST, "private/edit", body);
}

void DeribitClient::getOrderBook(const std::string& symbol) {
    sendRequest(web::http::methods::GET, "public/get_order_book?instrument_name=" + symbol, web::json::value());
}

void DeribitClient::viewPositions() {
    sendRequest(web::http::methods::GET, "private/get_position", web::json::value());
}

web::http::http_response DeribitClient::sendRequest(const web::http::method& method, const std::string& path, const web::json::value& body) {
    web::http::http_request request(method);
    request.set_request_uri(path);
    if (!body.is_null()) {
        request.set_body(body);
    }

    if (!access_token_.empty()) {
        request.headers().add(U("Authorization"), U("Bearer ") + access_token_);
    }

    return client_.request(request).get();
}
