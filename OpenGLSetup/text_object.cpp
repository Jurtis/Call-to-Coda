#include "text_object.h"

TextObject::TextObject() : Text ("Lorem Ipsum"), X(0.0f), Y(0.0f), Scale(1.0f), Color(1.0f) { }

TextObject::TextObject(std::string text, float x, float y, float scale, glm::vec3 color) : Text(text), X(x), Y(y), Scale(scale), Color(color) { }

void TextObject::Draw(TextRenderer& renderer)
{
		renderer.DrawText(this->Text, this->X, this->Y, this->Scale, this->Color);
}