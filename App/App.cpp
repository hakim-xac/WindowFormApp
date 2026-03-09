// App.cpp : Определяет точку входа для приложения.
//
#include "App.h"
#include <iostream>

#include "kernel_space/framework.h"
#include "user_space/Form.h"

#include <thread>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    std::jthread th{
    [&] {
        App::Form form{};
        form
            .setWindowName(L"qwqwqqqqqqqq")
            .setClassName(L"Form1")
            .setStartWindowPoint(POINT{ 100, 150 })
            .setHeight(600)
            .setWidth(800)
            ;

        if (!form.create(hInstance)) [[unlikely]]
        {
            std::cout << "--\n";
            return;
        }

        form.eventLoop(nCmdShow);
        } };

    std::jthread th2{
    [&] {
        App::Form form{};
        form
            .setWindowName(L"qqq")
            .setClassName(L"Form2")
            .setStartWindowPoint(POINT{ 950, 150 })
            .setHeight(600)
            .setWidth(800)
            ;

        if (!form.create(hInstance)) [[unlikely]]
        {
            std::cout << "--\n";
            return;
        }

        form.eventLoop(nCmdShow);
        } };

    return 0;
}