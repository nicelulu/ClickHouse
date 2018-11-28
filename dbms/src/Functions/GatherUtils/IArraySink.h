#pragma once

#include <Functions/GatherUtils/ArraySinkVisitor.h>
#include <Common/Exception.h>

namespace DB
{

namespace ErrorCodes
{
    extern const int NOT_IMPLEMENTED;
}

namespace GatherUtils
{

struct IArraySink
{
    virtual ~IArraySink() = default;

    virtual void accept(ArraySinkVisitor &)
    {
        throw Exception("Accept not implemented for " + demangle(typeid(*this).name()), ErrorCodes::NOT_IMPLEMENTED);
    }
};

template <typename Derived>
class ArraySinkImpl : public Visitable<Derived, IArraySink, ArraySinkVisitor> {};

}

}
