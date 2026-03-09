#pragma once

#include "framework.h"
#include "WindowBase.h"
#include <string>
#include <functional>
#include <type_traits>

namespace App
{
	class WindowLabel final : public WindowBase
	{
	public:
		explicit WindowLabel(std::wstring id) :
			WindowBase{ std::move(id)},
			m_hwnd{nullptr}
		{
		}

		inline bool create(HINSTANCE hinstance) override
		{
			HWND hwnd{
					 CreateWindowW(L"static", p_text.c_str(), WS_VISIBLE | WS_CHILD,
					 p_pos.left, p_pos.top, p_pos.right, p_pos.bottom, p_root_hwnd, nullptr, hinstance, nullptr)
			};
			if (!hwnd) [[unlikely]]
				return false;

			m_hwnd = hwnd;
			return true;
		}
	private:
		HWND m_hwnd;
	};
}