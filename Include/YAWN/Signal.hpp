#pragma once 

#include "Array.hpp"
#include "Function.hpp"

namespace YAWN {
    template<typename... TArgs>
    class Signal : public NonCopyable {
    public:
        void Connect(Function<void(TArgs...)> function) {
            _connections.PushBack(function);
        }

        template<typename TBase>
        void Connect(TBase* base, void(TBase::*func)(TArgs...)) {
            Connect([base, func](TArgs... args) {
                (base->*func)(args...);
            });
        }

        void Emit(TArgs... args) {
            for (const Function<void(TArgs...)>& connection : _connections) {
                if (connection.CanInvoke()) {
                    connection.Invoke(args...);
                }
            }
        }

    private:
        Array<Function<void(TArgs...)>> _connections;
    };
}
