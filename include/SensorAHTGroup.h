#pragma once
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSans9pt7b.h>
#include <SPI.h>
#include <Wire.h>

#include "SensorModel.h"

class SensorAHTGroup : public SensorModel {
   private:
    // TODO The module address needs to be processed
    uint8_t module_address_;  // Device address for communication
    const ModuleInfo moduleInfo_ = {2, SensorDataType::Temperature, SensorDataType::Humidity};
    Variant temperature_;
    Variant humidity_;
    Adafruit_AHTX0 aht_;
    sensors_event_t hum_, temp_;

   public:
    SensorAHTGroup(ValueType type = ValueType::FLOAT, uint8_t module_address_ = 0x34);
    Variant& getData(SensorDataType type) override;
    const ModuleInfo& getModuleInfo() const override;
    bool Init() override;
    void Update() override;
    ~SensorAHTGroup() = default;
};
