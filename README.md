# API_Cpp
•⁠ ⁠Create a new Deribit Test account
•⁠ ⁠Generate a set of API Keys

Functions:
- Place order
- Cancel order
- Modify order
- Get orderbook
- View current positions

Scope:
•⁠ ⁠Spot, futures and options
•⁠ ⁠All supported symbols

Focus:
- Full functionality of above functions with low latency


--Implementation 

This project implements a low-latency trading system in C++ for the Deribit test environment. The system includes essential trading features such as placing, canceling, and modifying orders, fetching the order book, and viewing open positions.

Features
Order Management: Place, cancel, and modify orders on Deribit using a simple API client.
Market Data: Fetch real-time order book data for supported symbols.
WebSocket Server: Provides real-time order book updates to subscribed clients for specified trading symbols, ensuring up-to-date market data with low latency.
Setup
Clone this repository.
Install dependencies: cpprestsdk for REST API calls and uWebSockets for WebSocket support.
Obtain Deribit test API keys and add them to DeribitClient.cpp.
Usage
Run the program to authenticate and interact with the Deribit test environment.
Use the WebSocket server for real-time updates by subscribing to symbols like BTC-PERPETUAL.