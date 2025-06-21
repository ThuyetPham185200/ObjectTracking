#pragma once
#include <memory>
#include <VImage.h>
class ConfigDetector {

};

struct DetectionSpace {
    float x, y, width, height;
};


struct DetectionInfo {

    enum class DetectionResultState {
        HAS_OBJECT,
        NO_OBJECT
    };

    struct ObjectInfo {
        float x, y, width, height;
    };

    DetectionResultState state = DetectionResultState::NO_OBJECT;
    ObjectInfo detectedObject;
};

class DetectorInterface {
public:
    virtual ~DetectorInterface() = default;

    // Load detection algoritn config
    virtual bool config(std::shared_ptr<ConfigDetector> config) = 0;

    // Process image from the dection space
    virtual std::shared_ptr<DetectionInfo> process(
        std::shared_ptr<VImage> image,
        std::shared_ptr<DetectionSpace> space
    ) = 0;
};
