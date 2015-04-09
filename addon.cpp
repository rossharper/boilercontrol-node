#include <node.h>
#include "boilercontrolwrapper.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  BoilerControlWrapper::Init(exports);
}

NODE_MODULE(addon, InitAll)

