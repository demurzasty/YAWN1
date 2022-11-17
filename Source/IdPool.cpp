#include <YAWN/IdPool.hpp>
#include <YAWN/Error.hpp>

using namespace YAWN;

Id IdPool::Acquire() {
    if (_disposed == None) {
        const Id newId = Id(_pool.Size());
        _pool.PushBack(newId);
        return newId;
    }

    const Id recycledId = _disposed;
    _disposed = _pool[usize(_disposed)];
    return _pool[usize(recycledId)] = recycledId;
}

void IdPool::Dispose(Id id) {
    CheckReturn(IsValid(id), "Id(%zu) is not valid.", usize(id));

    _pool[usize(id)] = _disposed;
    _disposed = id;
}

bool IdPool::IsValid(Id id) const {
    return usize(id) < _pool.Size() && _pool[usize(id)] == id;
}
