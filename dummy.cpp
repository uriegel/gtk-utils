#include <napi.h>
using namespace Napi;
using namespace std;

Value get_setting(const CallbackInfo& info) {
    return String::New(info.Env(), "");
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "getSetting"), Function::New(env, get_setting));
    return exports;
}

NODE_API_MODULE(extension, Init)