#pragma once

template <class I, class O>
struct force_cast
{
    union {
        I i;
        O o;
    } mm;

    force_cast(I i)
    {
        mm.i = i;
    }

    operator O()
    {
        return cast();
    }

    O cast()
    {
        return mm.o;
    }
};


template <class Fn>
struct ApiHook
{
    Fn ppOriginal_ = nullptr;

    std::wstring name_;
    DWORD_PTR *pTarget_ = nullptr;
    DWORD_PTR *pHooked_ = nullptr;
    bool actived_ = false;

  public:
    ApiHook(const std::wstring &name, DWORD_PTR *pTarget, DWORD_PTR *pHooked)
        : name_(name), pTarget_(pTarget), pHooked_(pHooked), actived_(false)
    {
    }

    ~ApiHook()
    {
        removeHook();
    }

    bool activeHook()
    {
        if (!actived_)
        {
            if (DetourTransactionBegin() != NO_ERROR)
                return false;
            if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
                return false;
            if (DetourAttach((PVOID*)&pTarget_, pHooked_) != NO_ERROR)
            {
                DetourTransactionAbort();
            }
            else
            {
                actived_ = DetourTransactionCommit() == NO_ERROR;
                ppOriginal_ = force_cast<DWORD_PTR*, Fn>(pTarget_);
            }
        }

        return succeed();
    }

    void removeHook()
    {
        if (actived_)
        {
            if (DetourTransactionBegin() != NO_ERROR)
                return;
            if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
                return;
            if (DetourDetach((PVOID*)&pTarget_, pHooked_) != NO_ERROR)
            {
                DetourTransactionAbort();
            }
            else
            {
                DetourTransactionCommit();
                actived_ = false;
                ppOriginal_ = nullptr;
            }
        }
        actived_ = false;
    }

    template <class ReturnType, class... A>
    ReturnType callOrginal(A... args)
    {
        return ppOriginal_(std::forward<A>(args)...);
    }

    Fn orignal()
    {
        return force_cast<DWORD_PTR *, Fn>(pTarget_);
    }

    bool succeed() { return actived_; }
};

inline DWORD_PTR *getVFunctionAddr(DWORD_PTR *object, int index)
{
    DWORD_PTR *vAddr = nullptr;
    if (object)
    {
        DWORD_PTR *vtblPointer = reinterpret_cast<DWORD_PTR *>(*object);
        if (vtblPointer)
        {
            vAddr = reinterpret_cast<DWORD_PTR *>(*(vtblPointer + index));
        }
    }

    return vAddr;
}



inline void hook_init()
{
}

inline void hook_uninit()
{
}