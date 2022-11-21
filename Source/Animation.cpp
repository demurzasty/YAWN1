#include <YAWN/Animation.hpp>

using namespace YAWN;

AnimationKeyframe::AnimationKeyframe(float32 time, const Variant& value)
    : _time(time), _value(value) {
}

float32 AnimationKeyframe::Time() const {
    return _time;
}

const Variant& AnimationKeyframe::Value() const {
    return _value;
}

AnimationTrack::AnimationTrack(const ArrayView<const AnimationKeyframe>& keyframes)
    : _keyframes(keyframes.Data(), keyframes.Size()) {
}

ArrayView<const AnimationKeyframe> AnimationTrack::Keyframes() const {
    return _keyframes;
}

Animation::Animation(const ArrayView<const Managed<AnimationTrack>>& tracks)
    : _tracks(tracks.Data(), tracks.Size()) {
}

ArrayView<const Managed<AnimationTrack>> Animation::Tracks() const {
    return _tracks;
}
