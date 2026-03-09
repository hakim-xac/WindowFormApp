#pragma once

#include "../framework.h"
#include <string>

namespace App
{
	class WindowBase
	{
	public:
		explicit WindowBase(std::wstring id) :
			p_id{ std::move(id) },
			p_text{},
			p_dw_style{ WS_VISIBLE | WS_CHILD },
			p_pos{},
			p_root_hwnd{}
		{ }

		inline WindowBase& setText(std::wstring text)&
		{
			std::swap(p_text, text);
			return *this;
		}

		inline WindowBase&& setText(std::wstring text)&&
		{
			std::swap(p_text, text);
			return std::move(*this);
		}

		inline WindowBase& setStyle(DWORD dw_style)&
		{
			p_dw_style = dw_style;
			return *this;
		}

		inline WindowBase&& setStyle(DWORD dw_style)&&
		{
			p_dw_style = dw_style;
			return std::move(*this);
		}

		inline WindowBase& setRectPos(RECT pos)&
		{
			p_pos = pos;
			return *this;
		}

		inline WindowBase&& setRectPos(RECT pos)&&
		{
			p_pos = pos;
			return std::move(*this);
		}

		inline WindowBase& setRootHWND(HWND hwnd)&
		{
			p_root_hwnd = hwnd;
			return *this;
		}

		inline WindowBase&& setRootHWND(HWND hwnd)&&
		{
			p_root_hwnd = hwnd;
			return std::move(*this);
		}

		inline [[nodiscard]] const std::wstring& getID() const&
		{
			return p_id;
		}

		virtual [[nodiscard]] bool create(HINSTANCE hinstance) = 0;
		virtual ~WindowBase() = default;
	protected:
		std::wstring p_id;
		std::wstring p_text;
		DWORD p_dw_style;
		RECT p_pos;
		HWND p_root_hwnd;
	};
}