#include "renderer.h"

VertexBufferHandle
RendererContext::createVertexBuffer(const void* data, const unsigned int size,
                                    const VertexBufferView view) {

    vertexBuffers[handle.index].create(memory.size, memory.data);
}