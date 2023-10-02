#pragma once
#include <List.hpp>

#include "SensorModel.h"

class ManagerSensor {
   private:
    void addToListAllDataFromSensor(SensorModel* sensor);
    List<SensorModel*> listSensor_;
    List<Variant> listData_;

   public:
    SensorModel* SensorWeather = nullptr;
    ~ManagerSensor() = default;
    bool AddSensor(SensorModel* sensor);
    List<Variant>& GetDataFromSensors();
    void Update();
};
