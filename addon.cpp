#include <napi.h>
#include <gio/gio.h>
using namespace Napi;
using namespace std;

// TODO: sudo apt-get install libglib2.0-dev

auto v8_value_to_utf8_string(const string& str) {
	auto utf8_string = static_cast<char*>(g_malloc(str.length() + 1));
	strcpy(utf8_string, str.c_str());
	return utf8_string;
}

Value Test(const CallbackInfo& info) {
    auto schema_id = v8_value_to_utf8_string(info[0].As<String>().Utf8Value());
    auto key = v8_value_to_utf8_string(info[1].As<String>().Utf8Value());

    auto schema_source = g_settings_schema_source_get_default();
    auto schema = g_settings_schema_source_lookup (schema_source, schema_id, FALSE);

    auto gsettings_key = g_settings_schema_get_key(schema, key);

    auto settings = g_settings_new(schema_id);
    auto variant = g_settings_get_value(settings, key);

    auto is_da = schema != nullptr;
    g_free(static_cast<void*>(schema_id));
    g_free(static_cast<void*>(key));

    auto erg = g_variant_get_string(variant, nullptr);

    auto result = String::New(info.Env(), erg);

    return result;
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "test"), Function::New(env, Test));
    return exports;
}

NODE_API_MODULE(extension, Init)