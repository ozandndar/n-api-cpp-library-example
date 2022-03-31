#define _GLIBCXX_USE_NANOSLEEP
#include <iostream>
#include <napi.h>
#include <string>
#include <thread>

using namespace Napi;
using namespace std;

String Method(const CallbackInfo &info)
{
    Env env = info.Env();
    string str = "hello world";
    return String::New(env, str);
}

Number Add(const CallbackInfo &info)
{
    Env env = info.Env();
    Number first = info[0].As<Number>();
    Number second = info[1].As<Number>();

    int result = first.Int32Value() + second.Int32Value();

    return Number::New(env, result);
}

void getUrlsWithCallback(const CallbackInfo &info)
{
    // your code goes here...
    string in = info[0].As<String>();
    Function cb = info[1].As<Function>();
    Promise::Deferred deferred = Promise::Deferred::New(info.Env());

    // resolve the promise in callback function named cb
    cb.Call({String::New(info.Env(), in)});
}


void task(Env env, const Promise::Deferred &p, string data)
{
    this_thread::sleep_for(chrono::seconds(5));
    p.Resolve(String::New(env, data));
}

Value getUrlsWithPromise(const CallbackInfo &info)
{
    Promise::Deferred deferred = Promise::Deferred::New(info.Env());

    thread myThread1(task, info.Env(), deferred, info[0].As<String>());
    

    myThread1.join();

    // resolve the promise
    // deferred.Resolve(String::New(info.Env(), in));

    return deferred.Promise();
}

Object Init(Env env, Object exports)
{
    exports.Set(String::New(env, "hello"), Function::New(env, Method));
    exports.Set(String::New(env, "add"), Function::New(env, Add));
    exports.Set(String::New(env, "getUrlsWithCallback"), Function::New(env, getUrlsWithCallback));
    exports.Set(String::New(env, "getUrlsWithPromise"), Function::New(env, getUrlsWithPromise));
    return exports;
}

NODE_API_MODULE(myLibrary, Init)