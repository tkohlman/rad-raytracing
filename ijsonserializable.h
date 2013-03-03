#ifndef IJSONSERIALIZABLE_H_INCLUDED
#define IJSONSERIALIZABLE_H_INCLUDED

#include <json.h>

class IJsonSerializable
{
public:
    virtual ~IJsonSerializable() {};

    virtual Json::Value serialize() const = 0;
};

#endif // IJSONSERIALIZABLE_H_INCLUDED
