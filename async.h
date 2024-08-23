#ifndef BULKMT_ASYNC_H
#define BULKMT_ASYNC_H

#include <cstddef>

namespace async {

    using handle_t = void *;

    handle_t connect(std::size_t bulk);

    void receive(handle_t handle, const char *data, std::size_t size = 0);

    void disconnect(handle_t handle);

}


#endif //BULKMT_ASYNC_H
