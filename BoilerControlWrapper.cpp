#include "BoilerControlWrapper.h"

#include "TransmitPinFactory.h"
#include "boilercontrol.h"

using namespace v8;

Persistent<Function> BoilerControlWrapper::constructor;

BoilerControlWrapper::BoilerControlWrapper(int pin) {
	this->pin = pin;
  this->nonRealtimeOffset = -1;
}

BoilerControlWrapper::BoilerControlWrapper(int pin, int nonRealtimeOffset) {
  this->pin = pin;
  this->nonRealtimeOffset = nonRealtimeOffset;
}

BoilerControlWrapper::~BoilerControlWrapper() {
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
    int pin = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    BoilerControlWrapper* obj;
    if(args[1]->IsUndefined()) {
      obj = new BoilerControlWrapper(pin);
    }
    else {
      obj = new BoilerControlWrapper(pin, args[1]->NumberValue());
    }
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
    
    TransmitPin* transmitPin;
    if(obj->nonRealtimeOffset != -1) {
      transmitPin = TransmitPinFactory::create(obj->pin, obj->nonRealtimeOffset);
    }
    else {
      transmitPin = TransmitPinFactory::create(obj->pin);
    }

    BoilerControl* boilercontrol = new BoilerControl(transmitPin);
    boilercontrol->sendOnSignal();
    delete boilercontrol;
  }

  void BoilerControlWrapper::SendOffSignal(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    BoilerControlWrapper* obj = ObjectWrap::Unwrap<BoilerControlWrapper>(args.Holder());

    TransmitPin* transmitPin;
    if(obj->nonRealtimeOffset != -1) {
      transmitPin = TransmitPinFactory::create(obj->pin, obj->nonRealtimeOffset);
    }
    else {
      transmitPin = TransmitPinFactory::create(obj->pin);
    }

    BoilerControl* boilercontrol = new BoilerControl(transmitPin);
    boilercontrol->sendOffSignal();
    delete boilercontrol;
  }