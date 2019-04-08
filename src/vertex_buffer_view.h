#pragma once

#include <vector>

#include "renderer.h"

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    unsigned int normalized;

    static unsigned int sizeof_gl_type(unsigned int type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        default:
            return 0;
        }
    }
};

class VertexBufferView {
  public:
    VertexBufferView() : stride(0) {}

    void push_float(unsigned int count) {
        elements.push_back({GL_FLOAT, count, GL_FALSE});
        stride += VertexBufferElement::sizeof_gl_type(GL_FLOAT);
    }

    void push_uint(unsigned int count) {
        elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride += count * VertexBufferElement::sizeof_gl_type(GL_UNSIGNED_INT);
    }

    void push_uchar(unsigned int count) {
        elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride += count * VertexBufferElement::sizeof_gl_type(GL_UNSIGNED_BYTE);
    }

    inline unsigned int get_stride() const { return stride; }

    inline const std::vector<VertexBufferElement> get_elements() const {
        return elements;
    }

  private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};