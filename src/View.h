#pragma once

#define DEFAULT_ELEMENT_COLOR GREEN

template<typename T>
class View {
public:
	View(T* newData = nullptr) : data(newData) {};
	void update(T* newData) { data = newData; };
	void draw() {};

private:
	T* data{nullptr};
};
