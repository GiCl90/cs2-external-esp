#pragma once
#include <wtypes.h>

namespace render
{
	void DrawCircle(HDC hdc, int x, int y, int radius, COLORREF color)
	{
		HBRUSH hBrush = CreateSolidBrush(color);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hBrush);
	}

	void DrawBorderBox(HDC hdc, int x, int y, int w, int h, COLORREF borderColor)
	{
		HBRUSH hBorderBrush = CreateSolidBrush(borderColor);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBorderBrush);

		RECT rect = {x, y, x + w, y + h};
		FrameRect(hdc, &rect, hBorderBrush);

		SelectObject(hdc, hOldBrush); // Restore the original brush
		DeleteObject(hBorderBrush);	  // Delete the temporary brush
	}

	void DrawFilledBox(HDC hdc, int x, int y, int width, int height, COLORREF color)
	{
		HBRUSH hBrush = CreateSolidBrush(color);
		RECT rect = {x, y, x + width, y + height};
		FillRect(hdc, &rect, hBrush);
		DeleteObject(hBrush);
	}

	void SetTextSize(HDC hdc, int textSize)
	{
		LOGFONT lf;
		HFONT hFont, hOldFont;

		// Initialize the LOGFONT structure
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = -textSize;			// Set the desired text height (negative for height)
		lf.lfWeight = FW_NORMAL;			// Set the font weight (e.g., FW_NORMAL for normal)
		lf.lfQuality = ANTIALIASED_QUALITY; // Enable anti-aliasing

		// Create a new font based on the LOGFONT structure
		hFont = CreateFontIndirect(&lf);

		// Select the new font into the device context and save the old font
		hOldFont = (HFONT)SelectObject(hdc, hFont);

		// Clean up the old font (when done using it)
		DeleteObject(hOldFont);
	}

	void RenderText(HDC hdc, int x, int y, const char *text, COLORREF textColor, int textSize)
	{
		SetTextSize(hdc, textSize);
		SetTextColor(hdc, textColor);

		int len = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
		wchar_t *wide_text = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, text, -1, wide_text, len);

		TextOutW(hdc, x, y, wide_text, len - 1);

		delete[] wide_text;
	}
}
