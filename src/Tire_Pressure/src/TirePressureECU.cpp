#include "TirePressureECU.hpp"

TirePressureECU::TirePressureECU(IPressureSensor& pressureSensor, IMessageSender& sender)
    : pressureSensor(pressureSensor), sender(sender){}

void TirePressureECU::start(void){
    xTaskCreate(
        checkPressure,
        "Pressure Reading Task",
        8192,
        this,
        1,
        NULL
    );
}

// Static method to be ran as task
void TirePressureECU::checkPressure(void *param){
    auto ecu = static_cast<TirePressureECU*>(param);

    for(;;){
        // Check pressure against standard range, if exceeds, send warning
        float pressure = ecu->pressureSensor.getPressure();

        if (pressure >= 35 || pressure <= 20){
            ecu->sender.sendTirePressureWarning();
        }

        ecu->sender.sendTirePressureUpdate(pressure);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}