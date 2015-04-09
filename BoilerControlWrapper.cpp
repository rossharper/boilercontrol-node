#include "BoilerControlWrapper.h"

#include "TransmitPinFactory.h"
#include "boilercontrol.h"

using namespace v8;

Persistent<Function> BoilerControlWrapper::constructor;

BoilerControlWrapper::BoilerControlWrapper(int pin) {
	this->boilercontrol = new BoilerControl(TransmitPinFactory::create(pin));
}

BoilerControlWrapper::~BoilerControlWrapper() {
	delete boilercontrol;
	boilercontrol = 0;
}

void BoilerControlWrapper::Init(Handle<Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();

  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
  tpl->SetClassName(String::NewFromUtf8(isolate, "BoilerControl"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "sendOnSignal", SendOnSignal);
  NODE_SET_PROTOTYPE_METHOD(tpl, "sendOffSignal", SendOffSignal);

  constructor.Reset(isolate, tpl->GetFunction());
  exports->Set(String::NewFromUtf8(isolate, "BoilerControl"),
               tpl->GetFunction());
}

void BoilerControlWrapper::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    int value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    BoilerControlWrapper* obj = new BoilerControlWrapper(value);
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    Local<Value> argv[argc] = { args[0] };
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

  void BoilerControlWrapper::SendOnSignal(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    BoilerControlWrapper* obj = ObjectWrap::Unwrap<BoilerControlWrapper>(args.Holder());
    obj->boilercontrol->sendOnSignal();
  }

  void BoilerControlWrapper::SendOffSignal(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    BoilerControlWrapper* obj = ObjectWrap::Unwrap<BoilerControlWrapper>(args.Holder());
    obj->boilercontrol->sendOffSignal();
  }