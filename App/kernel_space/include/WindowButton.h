#pragma once

#include "../framework.h"
#include <string>
#include <unordered_map>
#include <functional>
#include "WindowBase.h"

namespace App::detail
{
	inline std::unordered_map<WORD, std::function<void()> > G_LIST_BATTON_HANDLERS;
}

namespace App
{
	class WindowButton final : public WindowBase
	{
	public:
		explicit WindowButton(std::wstring id) :
			WindowBase{ std::move(id) },
			m_resourse_id{},
			m_hwnd{}
		{
		}

		template <typename ButtonHandler>
			requires std::invocable<ButtonHandler>
		WindowButton& setHandler(ButtonHandler&& handler)&
		{
			detail::G_LIST_BATTON_HANDLERS.emplace(m_resourse_id, std::forward<ButtonHandler>(handler));
			return *this;
		}

		inline [[nodiscard]] bool create(HINSTANCE hinstance) override
		{
			HWND hwnd{
					 CreateWindowW(L"button", p_text.c_str(), p_dw_style,
					 p_pos.left, p_pos.top, p_pos.right, p_pos.bottom, p_root_hwnd, reinterpret_cast<HMENU>(m_resourse_id), hinstance, nullptr)
			};
			if (!hwnd) [[unlikely]]
				return false;

			m_hwnd = hwnd;

			return true;
		}

		inline WindowButton& setResourceID(WORD resourse_id)&
		{
			m_resourse_id = resourse_id;
			return *this;
		}

		inline HWND getHWND() const&
		{
			return m_hwnd;
		}

		static void setMaxCountButtons(size_t max_count)
		{
			detail::G_LIST_BATTON_HANDLERS.reserve(max_count);
		}

		static [[nodiscard]] bool buttonHandler(WORD resourse_id)
		{
			const auto fn{ detail::G_LIST_BATTON_HANDLERS.find(resourse_id) };
			if (fn == std::cend(detail::G_LIST_BATTON_HANDLERS))
				return false;

			std::invoke(fn->second);
			return true;
		}

	private:
		WORD m_resourse_id;
		HWND m_hwnd;
	};

}