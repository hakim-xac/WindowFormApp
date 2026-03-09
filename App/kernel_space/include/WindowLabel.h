#pragma once

#include "../framework.h"
#include <string>
#include "WindowBase.h"

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
			m_hwnd = CreateWindowW(
				L"static", p_text.c_str(), WS_VISIBLE | WS_CHILD,
				p_pos.left, p_pos.top, p_pos.right, p_pos.bottom,
				p_root_hwnd, nullptr, hinstance, nullptr);

			return !!m_hwnd;
		}
	private:
		HWND m_hwnd;
	};
}