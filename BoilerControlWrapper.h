#ifndef BOILERCONTROLWRAPPER_H
#define BOILERCONTROLWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>

class BoilerControl;

class BoilerControlWrapper : public node::ObjectWrap {
public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    explicit BoilerControlWrapper(int value = 0);
    ~BoilerControlWrapper();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
    static v8::Persistent<v8::Function> constructor;

private:
    BoilerControl* boilercontrol;
};

#endif
