#include "EventDataRecorder.hpp"

/* ------ Constructor ------ */

EventDataRecorder::EventDataRecorder() 
    : receiver(), formatter(), storage(formatter) {
    this->networkToMediatorQueue = xQueueCreate(this->defaultQueueSize, sizeof(can_frame));
    this->mediatorToStorageQueue = xQueueCreate(this->defaultQueueSize, sizeof(can_frame));

    this->networkManager = new NetworkManager(this->receiver, this->networkToMediatorQueue);
    this->mediator = new Mediator(this->networkToMediatorQueue, this->mediatorToStorageQueue);
    this->storageManager = new StorageManager(this->storage, this->mediatorToStorageQueue);
}

/* ------ Destructor ------ */

EventDataRecorder::~EventDataRecorder() {
    vTaskDelete(this->networkManagerTaskHandle);
    vTaskDelete(this->mediatorTaskHandle);
    vTaskDelete(this->storageManagerTaskHandle);
    delete this->networkManager;
    delete this->mediator;
    delete this->storageManager;
}

/* ------ Public methods ------ */

void EventDataRecorder::Setup() {
    xTaskCreate(EventDataRecorder::NetworkManagerTask,
                "Task handles network communication",
                this->defaultStackSize,
                (void*) this->networkManager,
                this->defaultTaskPriority,
                &this->networkManagerTaskHandle);

    xTaskCreate(EventDataRecorder::MediatorTask,
                "Task handles inter task communication",
                this->defaultStackSize,
                (void*) this->mediator,
                this->defaultTaskPriority,
                &this->mediatorTaskHandle);

    xTaskCreate(EventDataRecorder::StorageManagerTask,
                "Task handles storage",
                this->defaultStackSize,
                (void*) this->storageManager,
                this->defaultTaskPriority,
                &this->storageManagerTaskHandle);
}

void EventDataRecorder::NetworkManagerTask(void *param) {
    NetworkManager *manager = static_cast<NetworkManager *>(param);

    while (1) {
        manager->Run();
        vTaskDelay(10);
    }
    
    vTaskDelete(NULL);
}

void EventDataRecorder::MediatorTask(void *param) {
    Mediator *mediator = static_cast<Mediator *>(param);

    while (1) {
        mediator->Run();
        vTaskDelay(10);
    }
    
    vTaskDelete(NULL);
}

void EventDataRecorder::StorageManagerTask(void *param) {
    StorageManager *manager = static_cast<StorageManager *>(param);

    while (1) {
        manager->Run();
        vTaskDelay(10);
    }
    
    vTaskDelete(NULL);
}