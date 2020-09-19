#define _CRT_SECURE_NO_WARNINGS		//Screw your safety nets

#pragma warning(disable : 4244)		//Conversion, possible loss of data
#pragma warning(disable : 6294)		//Ill-defined for-loop

#include <iostream>
#include <list>
#include <time.h>
#include <conio.h>
#include <windows.h>

HANDLE stdoutHandle = INVALID_HANDLE_VALUE;
constexpr const int BOUND_L = 0;
constexpr const int BOUND_T = 0;
constexpr const int BOUND_R = 80;
constexpr const int BOUND_B = 28;
constexpr const size_t MAX_SHOT = 5;

class Console {
public:
	static void SetCursor(DWORD size, BOOL visible) {
		CONSOLE_CURSOR_INFO infoCursor;
		infoCursor.dwSize = size;
		infoCursor.bVisible = visible;
		SetConsoleCursorInfo(stdoutHandle, &infoCursor);
	}
	static void GotoXY(SHORT x, SHORT y) {
		SetConsoleCursorPosition(stdoutHandle, { x, y });
	}
	static void SetColor(SHORT high, SHORT low) {
		SetConsoleTextAttribute(stdoutHandle, ((high << 4) & 0xf0) | (low & 0x0f));
	}
	static void SetColor(SHORT color) {
		SetConsoleTextAttribute(stdoutHandle, color);
	}
};

class Drawable {
public:
	Drawable(float x, float y) : x_(x), y_(y) {
		px_ = x;
		py_ = y;
		this->Update(0, 0);
	}
	virtual ~Drawable() {}

	virtual void Update(float dx, float dy) {
		x_ += dx;
		y_ += dy;
	}
	virtual void Draw() {
		px_ = roundf(x_);
		py_ = roundf(y_);
	}

	float GetX() { return x_; }
	float GetY() { return y_; }
protected:
	int px_;
	int py_;
	float x_;
	float y_;
};
class ShipObj : public Drawable {
public:
	ShipObj(float x, float y) : Drawable(x, y) {}

	virtual void Update(float dx, float dy) {
		Drawable::Update(dx, dy);
		x_ = max(x_, BOUND_L + 1);
		x_ = min(x_, BOUND_R - 6);
		y_ = max(y_, BOUND_T + 1);
		y_ = min(y_, BOUND_B - 2);
	}
	virtual void Draw() {
		Console::GotoXY(px_, py_);
		puts("     ");
		Console::GotoXY(roundf(x_), roundf(y_));
		puts("<-0->");
		Drawable::Draw();
	}
};
class ShotObj : public Drawable {
public:
	ShotObj(float x, float y) : Drawable(x, y), vx_(0), vy_(0) {
	}
	~ShotObj() {
		Console::GotoXY(px_, py_);
		puts(" ");
	}

	virtual void Update(float dx, float dy) {
		Drawable::Update(vx_, vy_);
		x_ = max(x_, BOUND_L + 1);
		x_ = min(x_, BOUND_R - 2);
		y_ = max(y_, BOUND_T + 1);
		y_ = min(y_, BOUND_B - 2);
	}
	virtual void Draw() {
		Console::GotoXY(px_, py_);
		puts(" ");
		Console::GotoXY(roundf(x_), roundf(y_));
		puts(".");
		Drawable::Draw();
	}

	void SetSpeed(float x, float y) {
		vx_ = x;
		vy_ = y;
	}
	bool IsDelete() {
		return y_ <= BOUND_T + 1;
	}
private:
	float vx_;
	float vy_;
};

int main() {
#define SKIP_L for (int i = 0; i < BOUND_L; ++i) putchar(' ');
	for (int i = 0; i < BOUND_T; ++i) putchar('\n');

	SKIP_L for (int i = BOUND_L; i < BOUND_R; ++i)
		putchar('*');
	putchar('\n');

	for (int i = BOUND_T + 1; i < BOUND_B - 1; ++i) {
		SKIP_L putchar('*');
		for (int i = BOUND_L + 1; i < BOUND_R - 1; ++i) putchar(' ');
		putchar('*');
		putchar('\n');
	}

	SKIP_L for (int i = BOUND_L; i < BOUND_R; ++i)
		putchar('*');
	putchar('\n');
#undef SKIP_L

	srand(time(nullptr));
	auto GetRand = [](float a, float b) -> float {
		float rnd = rand() / (float)RAND_MAX;
		return a + rnd * (b - a);
	};

	stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdoutHandle == INVALID_HANDLE_VALUE) {
		printf("Error acquiring console handle.");
		return -1;
	}

	Console::SetCursor(20, false);

	bool mapState[6];
	memset(mapState, 0x00, sizeof(bool) * 5);

	ShipObj* objShip = new ShipObj(36, 15);
	std::list<ShotObj*> listShot;

	size_t frame = 0;

	bool bFinish = false;
	while (!bFinish) {
		//Key update
		{
			auto IsKeyPressed = [](int vk) -> bool {
				return GetKeyState(vk) & 0x8000;
			};
			mapState[0] = IsKeyPressed(0x58);	//x
			mapState[1] = IsKeyPressed(VK_SPACE);
			mapState[2] = IsKeyPressed(0x57);	//w
			mapState[3] = IsKeyPressed(0x41);	//a
			mapState[4] = IsKeyPressed(0x53);	//s
			mapState[5] = IsKeyPressed(0x44);	//d
		}

		//Update
		if (mapState[0])
			bFinish = true;
		if (frame % 5 == 0) {
			bool bUp = mapState[2];		//w
			bool bLeft = mapState[3];	//a
			bool bDown = mapState[4];	//s
			bool bRight = mapState[5];	//d
			objShip->Update(bLeft ? -2 : (bRight ? 2 : 0),
				bUp ? -1 : (bDown ? 1 : 0));
		}
		if (mapState[1] && frame % 20 == 0) {
			ShotObj* newShot = new ShotObj(objShip->GetX() + 2, objShip->GetY());
			newShot->SetSpeed(GetRand(-0.15f, 0.15f), -GetRand(0.8f, 1.1f));
			if (listShot.size() < MAX_SHOT)
				listShot.push_back(newShot);
		}

		//Draw
		if (frame % 5 == 0) {
			for (auto itr = listShot.begin(); itr != listShot.end();) {
				ShotObj* iShot = *itr;
				if (!iShot->IsDelete()) {
					iShot->Update(0, 0);
					iShot->Draw();
					++itr;
				}
				else {
					delete iShot;
					itr = listShot.erase(itr);
				}
			}
			objShip->Draw();
		}

		++frame;
		frame %= 1000;
		Sleep(10);
	}

	SetConsoleCursorPosition(stdoutHandle, { (SHORT)0, (SHORT)(BOUND_B + 1) });
	return 0;
}