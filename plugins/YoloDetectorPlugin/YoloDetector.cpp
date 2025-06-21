#include "YoloDetector.h"

YoloDetector::YoloDetector() {
    std::cout << "[YoloDetector] Constructed\n";
}

YoloDetector::~YoloDetector() {
    std::cout << "[YoloDetector] Destructed\n";
}

bool YoloDetector::config(std::shared_ptr<ConfigDetector> config) {
    // Giả lập config thành công
    std::cout << "[YoloDetector] Configured\n";
    return true;
}

std::shared_ptr<DetectionInfo> YoloDetector::process(
    std::shared_ptr<VImage> image,
    std::shared_ptr<DetectionSpace> space
) {
    std::cout << "[YoloDetector] Processing image in space: "
              << space->x << ", " << space->y << ", "
              << space->width << ", " << space->height << "\n";

    auto result = std::make_shared<DetectionInfo>();

    // Giả lập kết quả phát hiện: luôn phát hiện 1 vật thể
    result->state = DetectionInfo::DetectionResultState::HAS_OBJECT;
    result->detectedObject = {
        space->x + 10.0f,
        space->y + 10.0f,
        space->width / 2.0f,
        space->height / 2.0f
    };

    return result;
}
