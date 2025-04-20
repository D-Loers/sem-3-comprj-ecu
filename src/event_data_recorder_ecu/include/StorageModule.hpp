#pragma once

#include <string>
#include <SPI.h>
#include <SD.h>
#include "IStorage.hpp"
#include "MessageFormatter.hpp"

class StorageModule : public IStorage {
public:
    StorageModule(MessageFormatter &);
    ~StorageModule();
    bool Write(can_frame &) override;

private:
    const int kSCLKPin = 14;
    const int kMISOPin = 27;
    const int kMOSIPin = 13;
    const int kSSPin = 16;
    const std::string filePath = "/message_log.csv";
    const std::string columnNames = "Source,Type,Data";
    
    SPIClass hspi;
    MessageFormatter &formatter;
    File messageLog;

    bool OpenFile(File &);
};