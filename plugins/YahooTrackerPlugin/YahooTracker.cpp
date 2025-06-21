#include "YahooTracker.h"

YahooTracker::YahooTracker() {
    std::cout << "[YahooTracker] Constructed\n";
}

YahooTracker::~YahooTracker() {
    std::cout << "[YahooTracker] Destructed\n";
}

bool YahooTracker::config(std::shared_ptr<ConfigTracker> config) {
    std::cout << "[YahooTracker] Configured\n";
    return true;
}

bool YahooTracker::initTrack(std::shared_ptr<VImage> image, std::shared_ptr<DetectionInfo> detectionInfo) {
    if (detectionInfo && detectionInfo->state == DetectionInfo::DetectionResultState::HAS_OBJECT) {
        lastTrackedObject = {
            detectionInfo->detectedObject.x,
            detectionInfo->detectedObject.y,
            detectionInfo->detectedObject.width,
            detectionInfo->detectedObject.height
        };
        isTracking = true;
        std::cout << "[YahooTracker] Tracking initialized\n";
        return true;
    }

    std::cout << "[YahooTracker] No object to track\n";
    return false;
}

std::shared_ptr<TrackInfo> YahooTracker::process(std::shared_ptr<VImage> image) {
    auto result = std::make_shared<TrackInfo>();

    if (!isTracking) {
        result->state = TrackInfo::TrackingState::NOT_TRACKING;
        std::cout << "[YahooTracker] Not tracking\n";
        return result;
    }

    // Giả lập vị trí object di chuyển một chút
    lastTrackedObject.x += 1.0f;
    lastTrackedObject.y += 0.5f;

    result->state = TrackInfo::TrackingState::OBJECT_TRACKING;
    result->trackedObject = lastTrackedObject;

    std::cout << "[YahooTracker] Tracking object at: "
              << result->trackedObject.x << ", "
              << result->trackedObject.y << "\n";

    return result;
}
