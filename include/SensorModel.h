#pragma once
#include "Module.h"

class SensorModel : public Module {
   protected:
    struct ModuleInfo {
        uint8_t countOfTypes = 0;
        SensorDataType* types = nullptr;
        ModuleInfo(const uint8_t n, ...) : countOfTypes(n) {
            types = new SensorDataType[n];
            va_list factor;
            va_start(factor, n);
            for (size_t i = 0; i < n; i++) {
                types[i] = va_arg(factor, SensorDataType);
            }
            va_end(factor);
        };
        ~ModuleInfo() {
            if (types != nullptr) delete[] types;
        };
    };

   public:
    virtual Variant& getData(SensorDataType type) = 0;
    virtual const ModuleInfo& getModuleInfo() const = 0;
    SensorModel() = default;
    virtual ~SensorModel() = default;
};
