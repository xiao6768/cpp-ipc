#include "waiter.h"

#include <string>

#include "def.h"
#include "platform/waiter_wrapper.h"

#undef IPC_PP_CAT_
#undef IPC_PP_JOIN_T__
#undef IPC_PP_JOIN_

#define IPC_PP_CAT_(X, ...)            X##__VA_ARGS__
#define IPC_PP_JOIN_T__(X, ...)        IPC_PP_CAT_(X, __VA_ARGS__)
#define IPC_PP_JOIN_(X, ...)           IPC_PP_JOIN_T__(X, __VA_ARGS__)

namespace ipc {

#undef IPC_OBJECT_TYPE_
#undef IPC_OBJECT_TYPE_OPEN_PARS_
#undef IPC_OBJECT_TYPE_OPEN_ARGS_

#define IPC_OBJECT_TYPE_ mutex
#define IPC_OBJECT_TYPE_OPEN_PARS_
#define IPC_OBJECT_TYPE_OPEN_ARGS_

#include "waiter_template.inc"

bool mutex::lock() {
    return impl(p_)->h_.lock();
}

bool mutex::unlock() {
    return impl(p_)->h_.unlock();
}

#undef IPC_OBJECT_TYPE_
#undef IPC_OBJECT_TYPE_OPEN_PARS_
#undef IPC_OBJECT_TYPE_OPEN_ARGS_

#define IPC_OBJECT_TYPE_ semaphore
#define IPC_OBJECT_TYPE_OPEN_PARS_ , long count
#define IPC_OBJECT_TYPE_OPEN_ARGS_ , count

#include "waiter_template.inc"

bool semaphore::wait() {
    return impl(p_)->h_.wait();
}

bool semaphore::post(long count) {
    return impl(p_)->h_.post(count);
}

#undef IPC_OBJECT_TYPE_
#undef IPC_OBJECT_TYPE_OPEN_PARS_
#undef IPC_OBJECT_TYPE_OPEN_ARGS_

#define IPC_OBJECT_TYPE_ condition
#define IPC_OBJECT_TYPE_OPEN_PARS_
#define IPC_OBJECT_TYPE_OPEN_ARGS_

#include "waiter_template.inc"

bool condition::wait(mutex& mtx) {
    return impl(p_)->h_.wait(impl(mtx.p_)->h_);
}

bool condition::notify() {
    return impl(p_)->h_.notify();
}

bool condition::broadcast() {
    return impl(p_)->h_.broadcast();
}

} // namespace ipc
