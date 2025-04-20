#include "StorageModule.hpp"

/* ------ Constructor ------ */

StorageModule::StorageModule(MessageFormatter &formatter) 
    : hspi(HSPI), formatter(formatter) {
    this->hspi.begin(this->kSCLKPin, this->kMISOPin, this->kMOSIPin);
    while (!SD.begin(this->kSSPin, this->hspi));

    if (!OpenFile(this->messageLog)) {
        throw std::runtime_error("Could not open file");
    }

    this->messageLog.println(this->columnNames.c_str());
    this->messageLog.flush();
}

/* ------ Destructor ------ */

StorageModule::~StorageModule() {
    this->messageLog.close();
}

/* ------ Public methods ------ */

bool StorageModule::Write(can_frame &message) {
    bool result = false;

    if (this->messageLog) {
        std::string formattedRow = this->formatter.GetFormattedMessage(message);
        this->messageLog.println(formattedRow.c_str());
        this->messageLog.flush();
        result = true;
    } else {
        while (!SD.begin(this->kSSPin, this->hspi));
        OpenFile(this->messageLog);
    }

    return result;
}

bool StorageModule::OpenFile(File &file) {
    file = SD.open(this->filePath.c_str(), FILE_WRITE);
    return file;
}