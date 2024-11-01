#include "../View.h"
#include "../TalkBox.h"
#include "raylib.h"

constexpr int TALK_BOX_FONT_SIZE {2};
constexpr int TALK_BOX_BORDER_SIZE {2};
constexpr int TALK_BOX_BOTTOM_MARGIN {10};

template<>
void View<TalkBox>::draw() {
	auto text = data->text.c_str();
	int textSize = MeasureText(text, TALK_BOX_FONT_SIZE);
	int textOffset = (data->width - textSize) / 1.8;
	float boxOffset = (GetRenderWidth() - data->width) / 2;
	Rectangle border{boxOffset, (float)GetRenderHeight() - data->height - TALK_BOX_BOTTOM_MARGIN, (float)data->width, (float)data->height - TALK_BOX_BOTTOM_MARGIN};
	DrawRectangle(boxOffset, GetRenderHeight() - data->height - TALK_BOX_BOTTOM_MARGIN, data->width, data->height - TALK_BOX_BOTTOM_MARGIN, BLACK);
	DrawRectangleLinesEx(border, TALK_BOX_BORDER_SIZE, DEFAULT_ELEMENT_COLOR);
	DrawText(text, textOffset, GetRenderHeight() - (data->height / 2) - TALK_BOX_BOTTOM_MARGIN * 1.5, TALK_BOX_FONT_SIZE, DEFAULT_ELEMENT_COLOR);
}
