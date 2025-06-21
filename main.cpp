#include <iostream>
#include "DetectorInterface.h"
#include "TrackerInterface.h"
#include "VImage.h"

// Factories to load .so plugins
#include "DetectorsFactory.h"
#include "TrackersFactory.h"

// Strategy managers
#include "DetectorStrategy.h"
#include "TrackerStrategy.h"

int main() {
    std::string detectorPath = "./libYoloDetector.so";
    std::string trackerPath  = "./libYahooTracker.so";


    // Load detector plugin
    DetectorsFactory detectorFactory;
    if (!detectorFactory.load("Yolo", detectorPath)) {
        std::cerr << "Failed to load detector plugin.\n";
        return 1;
    }

    auto detector = detectorFactory.get("Yolo");
    if (!detector) {
        std::cerr << "Detector not found.\n";
        return 1;
    }

    // Register detector into strategy
    DetectorStrategy detectorStrategy;
    detectorStrategy.registerStrategy("Yolo", detector);
    detectorStrategy.selectStrategy("Yolo");

    // Load tracker plugin
    TrackersFactory trackerFactory;
    if (!trackerFactory.load("Yahoo", trackerPath)) {
        std::cerr << "Failed to load tracker plugin.\n";
        return 1;
    }

    auto tracker = trackerFactory.get("Yahoo");
    if (!tracker) {
        std::cerr << "Tracker not found.\n";
        return 1;
    }

    // Register tracker into strategy
    TrackerStrategy trackerStrategy;
    trackerStrategy.registerStrategy("Yahoo", tracker);
    trackerStrategy.selectStrategy("Yahoo");

    
    // Dummy image & space
    auto image = std::make_shared<VImage>();
    auto space = std::make_shared<DetectionSpace>();
    space->x = 0;
    space->y = 0;
    space->width = 100;
    space->height = 100;

    // Run detector
    auto detectionResult = detectorStrategy.detect(image, space);
    if (detectionResult && detectionResult->state == DetectionInfo::DetectionResultState::HAS_OBJECT) {
        std::cout << "Object detected at: "
                  << detectionResult->detectedObject.x << ", "
                  << detectionResult->detectedObject.y << ", "
                  << detectionResult->detectedObject.width << ", "
                  << detectionResult->detectedObject.height << "\n";
    } else {
        std::cout << "No object detected.\n";
        return 1;
    }


    // Initialize tracker with detection
    if (!trackerStrategy.init(image, detectionResult)) {
        std::cerr << "Failed to initialize tracker.\n";
        return 1;
    }

    // Simulate next frame
    auto trackResult = trackerStrategy.track(image);
    if (trackResult && trackResult->state == TrackInfo::TrackingState::OBJECT_TRACKING) {
        std::cout << "Tracking object at: "
                  << trackResult->trackedObject.x << ", "
                  << trackResult->trackedObject.y << ", "
                  << trackResult->trackedObject.width << ", "
                  << trackResult->trackedObject.height << "\n";
    } else {
        std::cout << "Tracking lost.\n";
    }

    return 0;
}
