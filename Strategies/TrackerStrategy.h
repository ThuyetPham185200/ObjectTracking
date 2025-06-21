#pragma once
#include "StrategyInterface.h"
#include "TrackerInterface.h"

class TrackerStrategy : public StrategyInterface<TrackerInterface> {
public:
    // Optional: Wrapper methods
    bool init(std::shared_ptr<VImage> image, std::shared_ptr<DetectionInfo> detection) {
        if (current) return current->initTrack(image, detection);
        std::cerr << "No tracker strategy selected.\n";
        return false;
    }

    std::shared_ptr<TrackInfo> track(std::shared_ptr<VImage> image) {
        if (current) return current->process(image);
        std::cerr << "No tracker strategy selected.\n";
        return nullptr;
    }
};
