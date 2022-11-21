#pragma once 

#include "Resource.hpp"
#include "Variant.hpp"
#include "ArrayView.hpp"

namespace YAWN {
    class AnimationKeyframe {
    public:
        AnimationKeyframe() = default;

        AnimationKeyframe(float32 time, const Variant& value);

        float32 Time() const;

        const Variant& Value() const;

    private:
        float32 _time = 0.0f;
        Variant _value;
    };

    class AnimationTrack : public Reference {
    public:
        AnimationTrack(const ArrayView<const AnimationKeyframe>& keyframes);

        ArrayView<const AnimationKeyframe> Keyframes() const;

    private:
        Array<AnimationKeyframe> _keyframes;
    };

    class Animation : public Resource {
    public:
        Animation(const ArrayView<const Managed<AnimationTrack>>& tracks);

        virtual ~Animation() = default;

        ArrayView<const Managed<AnimationTrack>> Tracks() const;

    private:
        Array<Managed<AnimationTrack>> _tracks;
    };
}