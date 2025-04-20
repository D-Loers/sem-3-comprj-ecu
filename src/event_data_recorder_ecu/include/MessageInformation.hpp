#pragma once

enum class MessageSource {
    EngineController = 0b000,
    Infotainment = 0b011,
    BodyController = 0b001,
    TirePressureMonitor = 0b010,
    Telematics = 0b100,
};

enum class MessageTypes {
    EngineOverheatWarning = 0b00011,
    BrakePressedEvent = 0b10101,
    BrakeCommand = 0b00100,
    EnginePowerControl = 0b00010,
    HeadlightToggle = 0b01000,
    TirePressureWarning = 0b10000,
    TirePressureUpdate = 0b10001,
    UserInputForBlinkers = 0b10100,
    GasPedalInput = 0b11001,
    EngineTemperatureUpdate = 0b11110,
};