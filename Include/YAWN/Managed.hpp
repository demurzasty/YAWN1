#pragma once 

#include "Reference.hpp"

namespace YAWN {
    template<typename TReference>
    class Managed {
    public:
        Managed() = default;

        Managed(decltype(nullptr)) {}

        Managed(TReference* reference)
            : _reference(reference) {
            _Retain();
        }

        Managed(const Managed<TReference>& managed)
            : _reference(managed._reference) {
            _Retain();
        }

        Managed(Managed<TReference>&& managed) noexcept
            : _reference(managed._reference) {
            managed._reference = nullptr;
        }

        ~Managed() {
            _Release();
        }

        Managed<TReference>& operator=(decltype(nullptr)) {
            _Release();
            _reference = nullptr;
            return *this;
        }

        Managed<TReference>& operator=(const Managed<TReference>& managed) {
            _Release();
            _reference = managed._reference;
            _Retain();
            return *this;
        }

        Managed<TReference>& operator=(Managed<TReference>&& managed) noexcept {
            _Release();
            _reference = managed._reference;
            managed._reference = nullptr;
            return *this;
        }

        void Reset() {
            *this = Managed<TReference>();
        }

        bool HasReference() const {
            return _reference != nullptr;
        }

        TReference& operator*() {
            return *_reference;
        }

        TReference* operator->() const {
            return _reference;
        }

        TReference* Get() const {
            return _reference;
        }

        operator TReference* () const {
            return _reference;
        }

        bool operator==(const Managed<TReference>& managed) const {
            return _reference == managed._reference;
        }

        bool operator!=(const Managed<TReference>& managed) const {
            return _reference != managed._reference;
        }

        template<typename DerivedType>
        Managed<DerivedType> CastTo() const {
            return dynamic_cast<DerivedType*>(_reference);
        }

    private:
        inline void _Retain() {
            if (_reference) {
                _reference->Retain();
            }
        }

        inline void _Release() {
            if (_reference) {
                _reference->Release();
            }
        }

    private:
        TReference* _reference = nullptr;
    };
}
