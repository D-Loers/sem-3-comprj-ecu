#pragma once

#include <functional>
#include <WebSocketsClient.h>
#include <cstdint>

class WebSocket {
public:
    using MessageCallback = std::function<void(const char*)>;

    static WebSocket& getInstance(const char* ip);

    void startTask(); // Starts the WebSocket task
    void send(const char* msg); // Sends a message over the WebSocket
    void onReceive(MessageCallback callback); // Sets the callback for received messages

private:
    WebSocket(const char* ip);
    ~WebSocket();

    void loop(); // Keeps the WebSocket alive
    static void websocketTask(void* param); // Task for managing WebSocket
    static void handleWebSocketEvent(WStype_t type, uint8_t* payload, size_t length);

    static WebSocket* instance;
    WebSocketsClient webSocket;
    bool initialized = false;
    const char* ip;
    MessageCallback messageCallback;
};
