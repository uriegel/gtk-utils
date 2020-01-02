#include <napi.h>
#include <gio/gio.h>
using namespace Napi;
using namespace std;

// TODO: sudo apt-get install libglib2.0-dev

auto v8_string_to_gtk_string(const string& str) {
	auto gtk_string = static_cast<char*>(g_malloc(str.length() + 1));
	strcpy(gtk_string, str.c_str());
	return gtk_string;
}

Value get_setting(const CallbackInfo& info) {
    auto schema_id = v8_string_to_gtk_string(info[0].As<String>().Utf8Value());
    auto key = v8_string_to_gtk_string(info[1].As<String>().Utf8Value());

    auto schema_source = g_settings_schema_source_get_default();
    if (!schema_source) {
        g_free(static_cast<void*>(schema_id));
        g_free(static_cast<void*>(key));
        throw Napi::Error::New(info.Env(), "No schema");
    }
    
    auto schema = g_settings_schema_source_lookup (schema_source, schema_id, FALSE);
    if (!schema) {
        g_free(static_cast<void*>(schema_id));
        g_free(static_cast<void*>(key));
        throw Napi::Error::New(info.Env(), "No schema: "s + schema_id);
    }

    auto gsettings_key = g_settings_schema_get_key(schema, key);
    if (!gsettings_key) {
        g_free(static_cast<void*>(schema_id));
        g_free(static_cast<void*>(key));
        throw Napi::Error::New(info.Env(), "Invalid key: "s + key);
    }

    auto settings = g_settings_new(schema_id);
    auto variant = g_settings_get_value(settings, key);

    g_free(static_cast<void*>(schema_id));
    g_free(static_cast<void*>(key));
    
    auto erg = g_variant_get_string(variant, nullptr);
    return String::New(info.Env(), erg);
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "getSetting"), Function::New(env, get_setting));
    return exports;
}

NODE_API_MODULE(extension, Init)