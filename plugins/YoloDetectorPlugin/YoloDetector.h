#pragma once

#include "DetectorInterface.h"
#include <iostream>

class YoloDetector : public DetectorInterface {
public:
    YoloDetector();
    ~YoloDetector() override;

    bool config(std::shared_ptr<ConfigDetector> config) override;

    std::shared_ptr<DetectionInfo> process(
        std::shared_ptr<VImage> image,
        std::shared_ptr<DetectionSpace> space
    ) override;
};
