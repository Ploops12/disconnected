#include "TalkBox.h"
#include "raylib.h"
#include "View.h"

static TalkBox talkbox;

void ResizeTalkBox(int x, int y) {
	talkbox.width = x;
	talkbox.height = y;
}

void SetTalkBox(std::string speaker, std::string text) {
	talkbox.speaker = speaker;
	talkbox.text = text;
}

constexpr int TALK_BOX_FONT_SIZE {2};
constexpr int TALK_BOX_BORDER_SIZE {2};
constexpr int TALK_BOX_BOTTOM_MARGIN {5};
constexpr int TALK_BOX_PADDING {12};

void DrawTalkBox() {
	auto speaker_c = talkbox.speaker.c_str();
	auto text_c = talkbox.text.c_str();
	int textSize = MeasureText(text_c, TALK_BOX_FONT_SIZE);
	int textOffset = (talkbox.width - textSize) / 1.8;
	float boxOffset = (GetRenderWidth() - talkbox.width) / 2;
	int speakerMod = TALK_BOX_BORDER_SIZE + TALK_BOX_PADDING;

	Rectangle border{boxOffset, (float)GetRenderHeight() - talkbox.height - TALK_BOX_BOTTOM_MARGIN, (float)talkbox.width, (float)talkbox.height - TALK_BOX_BOTTOM_MARGIN};

	DrawRectangle(boxOffset, GetRenderHeight() - talkbox.height - TALK_BOX_BOTTOM_MARGIN, talkbox.width, talkbox.height - TALK_BOX_BOTTOM_MARGIN, BLACK);

	DrawRectangleLinesEx(border, TALK_BOX_BORDER_SIZE, DEFAULT_ELEMENT_COLOR);

	DrawText(text_c, textOffset, GetRenderHeight() - (talkbox.height / 2) - TALK_BOX_BOTTOM_MARGIN * 1.5, TALK_BOX_FONT_SIZE, DEFAULT_ELEMENT_COLOR);

	DrawText(speaker_c, boxOffset + speakerMod, GetRenderHeight() - talkbox.height - TALK_BOX_BOTTOM_MARGIN + speakerMod, TALK_BOX_FONT_SIZE + 2, DEFAULT_ELEMENT_COLOR);
}
