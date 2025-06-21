#pragma once
#include <memory>
#include <DetectorInterface.h>
#include <VImage.h>
// Forward declaration
class ConfigTracker{

};

struct TrackInfo {
    enum class TrackingState {
        NOT_TRACKING,
        OBJECT_TRACKING,
        OBJECT_LOSS
    };

    struct ObjectInfo {
        float x, y, width, height;
    };

    TrackingState state = TrackingState::NOT_TRACKING;
    ObjectInfo trackedObject;
};

class TrackerInterface {
public:
    virtual ~TrackerInterface() = default;

    // Load tracking algorithm config
    virtual bool config(std::shared_ptr<ConfigTracker> config) = 0;

    // Init the first track from detection result
    virtual bool initTrack(std::shared_ptr<VImage> image, std::shared_ptr<DetectionInfo> detectionInfo) = 0;

    // Process next image from original tracking initialization
    virtual std::shared_ptr<TrackInfo> process(std::shared_ptr<VImage> image) = 0;
};
