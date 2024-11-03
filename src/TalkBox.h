#pragma once

#include <string>

struct TalkBox {
	int width{200};
	int height{150};
	std::string speaker;
	std::string text;
};

void ResizeTalkBox(int x, int y);
void SetTalkBox(std::string speaker, std::string text);
void DrawTalkBox();
