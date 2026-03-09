#pragma once
#include "framework.h"
#include <string>
#include <optional>
#include "resource.h"

namespace App
{
    template <typename DeriveForm>
	class FormBase
	{
	public:

        FormBase() :
            m_class_name{ L"form1" },
            m_window_name{ L"FormName" },
            m_rect_window{ RECT{.left{50}, .top{50}, .right{800}, .bottom{600}} },
            m_hinstance{},
            m_hwnd{}
        {
        }

        inline FormBase& setWindowName(std::wstring window_name)&
        {
            m_window_name = std::move(window_name);
            return *this;
        }

        inline FormBase& setClassName(std::wstring class_name)&
        {
            m_class_name = std::move(class_name);
            return *this;
        }

        inline FormBase& setStartWindowPoint(POINT pos)&
        {
            m_rect_window.left = pos.x;
            m_rect_window.top = pos.y;
            return *this;
        }

        inline FormBase& setHeight(LONG height)&
        {
            m_rect_window.bottom = height;
            return *this;
        }

        inline FormBase& setWidth(LONG width)&
        {
            m_rect_window.right = width;
            return *this;
        }

        inline [[nodiscard]] bool
        create(HINSTANCE hinstance)
        {
            if (!MyRegisterClass(hinstance, m_class_name))
                return false;

            CreateWindowW(m_class_name.c_str(), m_window_name.c_str(), WS_OVERLAPPEDWINDOW,
                m_rect_window.left, m_rect_window.top, m_rect_window.right, m_rect_window.bottom, nullptr, nullptr, hinstance, this);

            return true;
        }

        inline void eventLoop(int cmd_show) const
        {
            ShowWindow(m_hwnd, cmd_show);
            UpdateWindow(m_hwnd);

            HACCEL hAccelTable{ LoadAccelerators(m_hinstance, MAKEINTRESOURCE(IDC_APP)) };

            for (MSG msg; GetMessage(&msg, nullptr, 0, 0);)
            {
                if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }

        inline [[nodiscard]] HWND getHWND() const noexcept
        {
            return m_hwnd;
        }

        inline [[nodiscard]] HINSTANCE getHINSTANCE() const noexcept
        {
            return m_hinstance;
        }

    private:

        LRESULT localWndProc(UINT message, WPARAM wParam, LPARAM lParam) noexcept
        {
            return static_cast<DeriveForm*>(this)->callbackWndProc(message, wParam, lParam);
        }

        static bool MyRegisterClass(HINSTANCE hInstance, const std::wstring& class_name)
        {

            WNDCLASSEXW wcex;

            wcex.cbSize = sizeof(WNDCLASSEX);

            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = WndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = 0;
            wcex.hInstance = hInstance;
            wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
            wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_APP);
            wcex.lpszClassName = class_name.c_str();
            wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

            return RegisterClassExW(&wcex);
        }

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            FormBase* form_ptr{};

            if (message == WM_NCCREATE)
            {
                auto createParams{ reinterpret_cast<LPCREATESTRUCT>(lParam)->lpCreateParams };
                form_ptr = static_cast<FormBase*>(createParams);
                form_ptr->setHWND(hWnd);
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createParams));
            }
            else
                form_ptr = reinterpret_cast<FormBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

            if (form_ptr)
                return form_ptr->localWndProc(message, wParam, lParam);

            return ::DefWindowProc(hWnd, message, wParam, lParam);
        }

        void setHWND(HWND hwnd)
        {
            m_hwnd = hwnd;
        }
    private:
        std::wstring m_class_name;
        std::wstring m_window_name;
        RECT m_rect_window;
        HINSTANCE m_hinstance;
        HWND m_hwnd;
	};
}