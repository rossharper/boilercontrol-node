#include <node.h>
#include "BoilerControlWrapper.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  BoilerControlWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)

