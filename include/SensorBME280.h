#pragma once
#include <GyverBME280.h>

#include "SensorModel.h"

class SensorBME280 : public SensorModel {
   private:
    uint8_t module_address_;          // Device address for communication
    const float mmColumn_ = 132.32f;  // Conversion factor into millimeters of mercury column
    const ModuleInfo moduleInfo_ = {3, SensorDataType::Temperature, SensorDataType::Humidity,
                                    SensorDataType::Pressure};
    Variant temperature_;
    Variant pressure_;
    Variant humidity_;
    GyverBME280 BME280_;

   public:
    SensorBME280(ValueType type = ValueType::FLOAT, uint8_t module_address_ = 0x76);
    Variant& getData(SensorDataType type) override;
    const ModuleInfo& getModuleInfo() const override;
    bool Init() override;
    void Update() override;
    ~SensorBME280() = default;
};
