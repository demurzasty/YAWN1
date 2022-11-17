#pragma once 

#include "Managed.hpp"
#include "Error.hpp"

namespace YAWN {
	template <typename T>
	class Function;

	template <typename TReturnValue, typename... TArgs>
	class Function<TReturnValue(TArgs...)> {
	public:
		Function() = default;

		Function(const Function<TReturnValue(TArgs...)>&) = default;
		Function(Function<TReturnValue(TArgs...)>&&) = default;

		template <typename T>
		Function(T t) {
			_callable = new Callable<T>(t);
		}

		Function<TReturnValue(TArgs...)>& operator=(const Function<TReturnValue(TArgs...)>&) = default;
		Function<TReturnValue(TArgs...)>& operator=(Function<TReturnValue(TArgs...)>&&) = default;

		TReturnValue operator()(const TArgs&... args) const {
			Assert(_callable, "Function is empty.");
			return _callable->Invoke(args...);
		}

		TReturnValue Invoke(const TArgs&... args) const {
			Assert(_callable, "Function is empty.");
			return _callable->Invoke(args...);
		}

		bool CanInvoke() const {
			return _callable.HasReference();
		}

	private:
		class ICallable : public Reference {
		public:
			virtual ~ICallable() = default;
			virtual TReturnValue Invoke(const TArgs&...) = 0;
		};

		template <typename T>
		class Callable : public ICallable {
		public:
			Callable(const T& t) : _t(t) { }

			TReturnValue Invoke(const TArgs&... args) override {
				return _t(args...);
			}

		private:
			T _t;
		};

		Managed<ICallable> _callable;
	};
}
