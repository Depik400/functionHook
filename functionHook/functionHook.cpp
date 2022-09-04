// functionHook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL
#include "./beaengine/BeaEngine.h"
#include "HookHelper.h"
#include "iostream"

ucptr trampoline = nullptr;

int sim(int a, int b) {
    return a + b;
}

int sim2(int a, int b) {
    return a * b;
}

int main()
{
    DISASM d = { 0 };
    auto see = reinterpret_cast<ucptr> (sim);
    std::cout << &see;
    HookHelper::HookFunction(reinterpret_cast<ucptr> (sim), reinterpret_cast<ucptr> (sim2), trampoline);
    std::cout << sim(10, 5);
    getchar();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
