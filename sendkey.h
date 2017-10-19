#include <node.h>
#include <windows.h>

namespace NodeSendKey
{

    void init(v8::Local<v8::Object> exports);
    void SendKeyMethod(const v8::FunctionCallbackInfo<v8::Value>& Args);

    class KeySender {
    public:
        KeySender(WCHAR KeyToSend);
        ~KeySender();
        void SendKey();
        void UpdateKeyToSend(WCHAR KeyToSend);

    private:
        SHORT KeyToSend;
    };
} // namespace NodeSendKey