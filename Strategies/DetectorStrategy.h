#pragma once
#include "StrategyInterface.h"
#include "DetectorInterface.h"

class DetectorStrategy : public StrategyInterface<DetectorInterface> {
public:
    // Optional: You can extend this class to call current->process(...) directly
    std::shared_ptr<DetectionInfo> detect(std::shared_ptr<VImage> image, std::shared_ptr<DetectionSpace> space) {
        if (current) {
            return current->process(image, space);
        }
        std::cerr << "No detector strategy selected.\n";
        return nullptr;
    }
};
