#include "WebSocket.hpp"
#include <Arduino.h>

WebSocket* WebSocket::instance = nullptr;

WebSocket& WebSocket::getInstance(const char* ip) {
    if (!instance) {
        instance = new WebSocket(ip);
    }
    return *instance;
}

WebSocket::WebSocket(const char* ip)
    : ip(ip), webSocket() {}

WebSocket::~WebSocket() = default;

void WebSocket::startTask() {
    if (!initialized) {
        // Initialize the WebSocket connection
        webSocket.begin(ip, 1880, "/ws");
        webSocket.onEvent(WebSocket::handleWebSocketEvent);
        initialized = true;

        // Start the task for WebSocket management
        xTaskCreate(
            WebSocket::websocketTask,
            "WebSocketTask",
            8192,
            this,
            1,
            nullptr
        );
    }
}

void WebSocket::send(const char* msg) {
    webSocket.sendTXT(msg);
}

void WebSocket::onReceive(MessageCallback callback) {
    messageCallback = callback;
}

void WebSocket::loop() {
    webSocket.loop();
}

void WebSocket::websocketTask(void* param) {
    WebSocket* ws = static_cast<WebSocket*>(param);
    for (;;) {
        ws->loop(); // Keep WebSocket alive
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}

void WebSocket::handleWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    if (!instance) return;

    switch (type) {
        case WStype_TEXT:
            if (instance->messageCallback) {
                // Convert payload to a null-terminated string and invoke the callback
                char* message = new char[length + 1];
                memcpy(message, payload, length);
                message[length] = '\0';
                instance->messageCallback(message);
                delete[] message;
            }
            break;

        case WStype_CONNECTED:
            Serial.println("WebSocket connected");
            break;

        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected");
            break;

        default:
            break;
    }
}
