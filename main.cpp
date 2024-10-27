// main.cpp
#include "DeribitClient.h"
#include "WebSocketServer.cpp"
#include <thread>

int main() {
    DeribitClient client("your_client_id", "your_client_secret");

    // Authenticate with the API
    client.authenticate();

    // Place an order
    client.placeOrder("BTC-PERPETUAL", 10, 50000);

    // Start WebSocket server in a separate thread
    WebSocketServer server;
    std::thread ws_thread([&server]() { server.run(); });

    // Fetch order book
    client.getOrderBook("BTC-PERPETUAL");

    // View current positions
    client.viewPositions();

    ws_thread.join();
    return 0;
}
