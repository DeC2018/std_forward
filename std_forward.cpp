#include <iostream>

using namespace std;

template<typename T>
void bar(const T& v) { cout << "by const ref" << endl; }

template<typename T>
void bar(T& v) { cout << "by lvalue ref" << endl; }

template<typename T>
void bar(T&& v) { cout << "by rvalue ref" << endl; }

// FUNCTION TEMPLATE forward
template <class _Ty>
[[nodiscard]] constexpr _Ty&& _forward(
    remove_reference_t<_Ty>& _Arg) noexcept
{
    cout << "forward an lvalue as either an lvalue or an rvalue" << endl;
    return static_cast<_Ty&&>(_Arg);
}

template <class _Ty>
[[nodiscard]] constexpr _Ty&& _forward(
    remove_reference_t<_Ty>&& _Arg) noexcept
{
    static_assert(!is_lvalue_reference_v<_Ty>, "bad forward call");
    cout << "forward an rvalue as an rvalue" << endl;
    return static_cast<_Ty&&>(_Arg);
}

// FUNCTION TEMPLATE move
template <class _Ty>
[[nodiscard]] constexpr remove_reference_t<_Ty>&& _move(_Ty&& _Arg) noexcept
{
    cout << "forward _Arg as movable" << endl;
    return static_cast<remove_reference_t<_Ty>&&>(_Arg);
}

template<typename T>
void foo(T&& p)
{
    bar(p);
    bar(_move(p));
    bar(_forward<T>(p));
}

int main()
{
    int i = 0;
    foo(i); // lvalue: T - int&, p - int&
    foo(0); // rvalue: T - int, p - int&&
}