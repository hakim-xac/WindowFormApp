#pragma once

#include <vector>
#include <algorithm>
#include <type_traits>
#include "WindowButton.h"
#include "WindowLabel.h"
#include "FormBase.h"

namespace App::FormResources
{
    enum ID : WORD {
        EXIT, BUT, RB, CB,
        CB2, CB3, CB4, CB5
    };
}

namespace App
{
	class Form : public FormBase<Form>
	{
	private:
        friend FormBase<Form>;
        //------------------------

        inline LRESULT callbackWndProc(UINT message, WPARAM wParam, LPARAM lParam) noexcept
        {
            const auto root_hwnd{ getHWND() };

            switch (message)
            {
            case WM_CREATE:
            {
                initControls();
                break;
            }
            case WM_COMMAND:
            {
                const WORD command_id{ LOWORD(wParam) };

                if (WindowButton::buttonHandler(command_id))
                    return DefWindowProc(root_hwnd, message, wParam, lParam);

                switch (command_id)
                {
                    case IDM_EXIT:
                    DestroyWindow(root_hwnd);
                    break;
                default:
                    return DefWindowProc(root_hwnd, message, wParam, lParam);
                }
            } break;
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                break;
            }
            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(root_hwnd, &ps);
                // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
                EndPaint(root_hwnd, &ps);
            }
            break;
            default:
                return DefWindowProc(root_hwnd, message, wParam, lParam);
            }
            return DefWindowProc(root_hwnd, message, wParam, lParam);
        }

        //------------------------

        inline void initControls()
        {
            const auto root_hwnd{ getHWND() };

            WindowButton::setMaxCountButtons(2);

            m_controls.reserve(3);

            {
                auto control{ std::make_unique<WindowLabel>(L"lab") };
                control->setRectPos(RECT{ 20, 20, 100, 20 })
                    .setText(L"fvghg")
                    .setRootHWND(root_hwnd);
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"bt")};
                control
                    ->setResourceID(App::FormResources::ID::BUT)
                    .setHandler([this] {
                        const auto fn_opt{ findID<WindowButton>(L"rb") };
                        if (fn_opt)
                        {
                            if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                                SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            else
                                SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                        }
                    })
                    .setRectPos(RECT{ 50, 50, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fghgfhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON)
                    ;
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"rb")};
                control
                    ->setResourceID(App::FormResources::ID::RB)
                    .setHandler([root_hwnd, this] {
                        const auto fn_opt{ findID<WindowButton>(L"rb") };
                        if (fn_opt)
                        {
                            if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                                SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            else
                                SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                        }
                    })
                    .setRectPos(RECT{ 150, 50, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fghgfhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON)
                    ;
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"cb")};
                control
                    ->setResourceID(App::FormResources::ID::CB)
                    .setHandler([this] {
                        const auto fn_opt{ findID<WindowButton>(L"cb") };
                        if (fn_opt)
                        {
                            //if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            //else
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                        }
                    })
                    .setRectPos(RECT{ 350, 50, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fjjhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX)
                    ;
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"cb2")};
                control
                    ->setResourceID(App::FormResources::ID::CB2)
                    .setHandler([this] {
                        const auto fn_opt{ findID<WindowButton>(L"cb2") };
                        if (fn_opt)
                        {
                            //if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            //else
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                        }
                    })
                    .setRectPos(RECT{ 350, 150, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fjjhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_AUTO3STATE)
                    ;
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"cb3")};
                control
                    ->setResourceID(App::FormResources::ID::CB3)
                    .setHandler([this] {
                        const auto fn_opt{ findID<WindowButton>(L"cb3") };
                        if (fn_opt)
                        {
                            //if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            //else
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                        }
                    })
                    .setRectPos(RECT{ 250, 150, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fjjhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_AUTO3STATE | BS_LEFTTEXT | BS_TOP )
                    ;
                m_controls.emplace_back(std::move(control));
            }
            {
                auto control{ std::make_unique<WindowButton>(L"cb4")};
                control
                    ->setResourceID(App::FormResources::ID::CB4)
                    .setHandler([this, root_hwnd] {
                        const auto fn_opt{ findID<WindowButton>(L"cb4") };
                        if (fn_opt)
                        {
                            //if (SendMessageW(fn_opt.value(), BM_GETCHECK, 0, 0) == BST_CHECKED)
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_UNCHECKED, 0);
                            //else
                            //    SendMessageW(fn_opt.value(), BM_SETCHECK, BST_CHECKED, 0);
                            MessageBoxW(root_hwnd, L"+++", L"-", MB_OK);
                        }
                    })
                    .setRectPos(RECT{ 150, 150, 100, 100 })
                    .setRootHWND(root_hwnd)
                    .setText(L"fjjhfg")
                    .setStyle(WS_VISIBLE | WS_CHILD | BS_AUTO3STATE | BS_LEFTTEXT | BS_BITMAP )
                    ;
                m_controls.emplace_back(std::move(control));
            }



            for (auto& control : m_controls)
                control->create(getHINSTANCE());
        }

        //------------------------

    private:
        template <typename DeriveWindow>
            requires std::is_base_of_v<WindowBase, DeriveWindow>
        inline [[nodiscard]] std::optional<HWND> findID(const std::wstring& id) const
        {
            const auto fn{ std::ranges::find_if(m_controls, [&id = id](const std::unique_ptr<WindowBase>& uptr) {
                return uptr->getID() == id;
                }) };
            return fn == std::cend(m_controls) ? std::nullopt : std::optional{ dynamic_cast<const DeriveWindow*>(fn->get())->getHWND() };
        }
    private:
        std::vector<std::unique_ptr<WindowBase> > m_controls;
	};
}
