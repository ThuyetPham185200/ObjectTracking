#pragma once

#include "TrackerInterface.h"
#include <iostream>

class YahooTracker : public TrackerInterface {
public:
    YahooTracker();
    ~YahooTracker() override;

    bool config(std::shared_ptr<ConfigTracker> config) override;

    bool initTrack(std::shared_ptr<VImage> image, std::shared_ptr<DetectionInfo> detectionInfo) override;

    std::shared_ptr<TrackInfo> process(std::shared_ptr<VImage> image) override;

private:
    bool isTracking = false;
    TrackInfo::ObjectInfo lastTrackedObject;
};
