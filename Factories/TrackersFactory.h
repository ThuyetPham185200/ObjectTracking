#pragma once
#include "FactoryInterface.h"
#include "TrackerInterface.h"

class TrackersFactory : public FactoryInterface<TrackerInterface> {
protected:
    std::string getCreateSymbolName() const override {
        return "createTracker";
    }

    std::string getDestroySymbolName() const override {
        return "destroyTracker";
    }
};
