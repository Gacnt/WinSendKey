#include <node.h>
#include <windows.h>
#include <sendkey.h>

namespace NodeSendKey
{
    
    KeySender::KeySender(WCHAR InKeyToSend = 'c')
    {
        HKL CurrentKBL = GetKeyboardLayout(0);
        KeyToSend = VkKeyScanEx(InKeyToSend, CurrentKBL);
    }

    KeySender::~KeySender(){}

    void KeySender::SendKey()
    {
        // Send They First Key
        INPUT Inp;
        Inp.type = INPUT_KEYBOARD;
        Inp.ki.wScan = 0;
        Inp.ki.time = 0;
        Inp.ki.dwExtraInfo = 0;
        Inp.ki.wVk = KeyToSend;
        Inp.ki.dwFlags = 0;

        // Send The Key
        SendInput(1, &Inp, sizeof(INPUT));

        // Release The Key
        Inp.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &Inp, sizeof(INPUT));

    }

    void KeySender::UpdateKeyToSend(WCHAR InKeyToSend = 'c')
    {
        HKL CurrentKBL = GetKeyboardLayout(0);
        KeyToSend = VkKeyScanEx(InKeyToSend, CurrentKBL);
    }

    void SendKeyMethod(const v8::FunctionCallbackInfo<v8::Value>& Args)
    {
        v8::Isolate* isolate = Args.GetIsolate();

        if (!Args[0]->IsString())
        {
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Argument 1 must be a string")));
            Args.GetReturnValue().Set(v8::Boolean::New(isolate, false));
            return;
        }

        v8::String::Utf8Value KeyToSendMeta(Args[0]->ToString());
        
        if (KeyToSendMeta.length() == 0 || KeyToSendMeta.length() > 1)
        {
            char str[] = "Argument 0 must be 1 letter. You entered: %d";
            char str2[1000];
            sprintf(str2, str, KeyToSendMeta.length());
            isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, 
                str2)));
            return;
        }

        std::string Crouch(*KeyToSendMeta);

        KeySender KeySendee(Crouch[0]);
        KeySendee.SendKey();
    }


    void init(v8::Local<v8::Object> exports)
    {
        NODE_SET_METHOD(exports, "sendKey", SendKeyMethod);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init)

} // namespace NodeSendKey



