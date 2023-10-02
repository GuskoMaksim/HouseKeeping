#pragma once

#include "MHZ19_uart.h"
#include "SensorModel.h"

class SensorMHz19B : public SensorModel {
   private:
    const ModuleInfo moduleInfo_ = {1, SensorDataType::Co2};
    Variant Co2_;
    int8_t RX_MHZ_;
    int8_t TX_MHZ_;
    MHZ19_uart mhz19_;

   public:
    SensorMHz19B(ValueType type = ValueType::INT16_T, int8_t RX_MHZ = 2, int8_t TX_MHZ = 3);
    Variant& getData(SensorDataType type) override;
    const ModuleInfo& getModuleInfo() const override;
    bool Init() override;
    void Update() override;
    ~SensorMHz19B() = default;
};
