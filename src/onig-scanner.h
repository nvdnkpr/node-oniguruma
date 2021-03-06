#ifndef SRC_ONIG_SCANNER_H_
#define SRC_ONIG_SCANNER_H_

#include <node.h>

#include <string>
#include <vector>
#include <memory>

using ::v8::Arguments;
using ::v8::Array;
using ::v8::Handle;
using ::v8::Number;
using ::v8::Object;
using ::v8::String;
using ::v8::Value;

using ::std::string;
using ::std::unique_ptr;
using ::std::vector;

class OnigRegExp;
class OnigResult;

class OnigScanner : public node::ObjectWrap {
  public:
    static void Init(Handle<Object> target);

  private:
    static Handle<Value> New(const Arguments& args);
    static Handle<Value> FindNextMatch(const Arguments& args);
    explicit OnigScanner(Handle<Array> sources);
    ~OnigScanner();

    Handle<Value> FindNextMatch(Handle<String> v8String, Handle<Number> v8StartLocation, Handle<Value> v8Scanner);
    Handle<Value> CaptureIndicesForMatch(OnigResult* result);
    void ClearCachedResults();

    vector<unique_ptr<OnigRegExp>> regExps;
    vector<unique_ptr<OnigResult>> cachedResults;
    string lastMatchedString;
    int maxCachedIndex;
    int lastStartLocation;
};

#endif  // SRC_ONIG_SCANNER_H_
