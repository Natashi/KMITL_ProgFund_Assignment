#define _CRT_SECURE_NO_WARNINGS		//Screw your safety nets

#pragma warning(disable : 4244)		//Conversion, possible loss of data
#pragma warning(disable : 6294)		//Ill-defined for-loop

#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <iostream>
#include <list>
#include <time.h>
#include <conio.h>
#include <windows.h>

HANDLE timerQueueHandle = nullptr;
HANDLE stdoutHandle = nullptr;
constexpr const int BOUND_L = 0;
constexpr const int BOUND_T = 2;
constexpr const int BOUND_R = 80;
constexpr const int BOUND_B = 30;
constexpr const size_t MAX_SHOT = 20;
constexpr const size_t MAX_ASTEROID = 25;

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
public:
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
		Drawable::Draw();
		Console::GotoXY(px_, py_);
		puts("<-0->");
	}
};
class ShotObj : public Drawable {
public:
	ShotObj(float x, float y) : Drawable(x, y), vx_(0), vy_(0), bDelete_(false) {}
	~ShotObj() {
		this->Erase();
	}

	virtual void Update(float dx, float dy) {
		Drawable::Update(vx_, vy_);
		y_ = max(y_, BOUND_T + 1);
		y_ = min(y_, BOUND_B - 2);
	}
	virtual void Draw() {
		this->Erase();
		Drawable::Draw();
		Console::GotoXY(px_, py_);
		puts(".");
	}
	void Erase() {
		Console::GotoXY(px_, py_);
		puts(" ");
	}

	void SetSpeed(float x, float y) {
		vx_ = x;
		vy_ = y;
	}

	void DeleteInClip() {
		if (x_ <= BOUND_L + 1 || x_ >= BOUND_R - 2
			|| y_ <= BOUND_T + 1) 
		{
			bDelete_ = true;
		}
	}
public:
	float vx_;
	float vy_;
	bool bDelete_;
};
class AsteroidObj : public Drawable {
public:
	AsteroidObj(float x, float y) : Drawable(x, y), bDelete_(false), bCollided_(false) {}
	~AsteroidObj() {
		this->Erase();
	}

	virtual void Update(float dx, float dy) {
		Drawable::Update(dx, dy);
	}
	virtual void Draw() {
		//this->Erase();
		Drawable::Draw();
		Console::GotoXY(px_, py_);
		puts("O");
	}
	void Erase() {
		Console::GotoXY(px_, py_);
		puts(" ");
	}

	void DeleteInClip() {
		if (x_ <= BOUND_L + 1 || x_ >= BOUND_R - 2
			|| y_ <= BOUND_T + 1)
			bDelete_ = true;
	}
public:
	bool bDelete_;
	bool bCollided_;
};

class IntersectionSpace {
public:
	IntersectionSpace() {}
	~IntersectionSpace() {}

	std::list<Drawable*>::iterator AddObject(Drawable* obj) {
		return listObject_.insert(listObject_.end(), obj);
	}
	void RemoveObject(std::list<Drawable*>::iterator itrObj) {
		listObject_.erase(itrObj);
	}
	bool CheckCollision(Drawable* obj, float biasX, float biasY, float radius, std::list<Drawable*>::iterator* itrRes) {
		float rr = radius * radius;

		for (auto itrTarget = listObject_.begin(); itrTarget != listObject_.end(); ++itrTarget) {
			if (*itrTarget == nullptr) continue;

			float dx = (obj->GetX() + biasX) - (*itrTarget)->GetX();
			float dy = (obj->GetY() + biasY) - (*itrTarget)->GetY();

			if (dx * dx + dy * dy <= rr) {
				if (itrRes) *itrRes = itrTarget;
				return true;
			}
		}

		return false;
	}
private:
	std::list<Drawable*> listObject_;
};

class SoundThread {
public:
	SoundThread() {
		::CreateTimerQueueTimer(&timer_, timerQueueHandle,
			SoundThreadProcess, (PVOID)this,
			200, 100, WT_EXECUTEDEFAULT);
		hEvent_ = ::CreateEventW(nullptr, false, false, nullptr);
	};
	~SoundThread() {
		::DeleteTimerQueueTimer(timerQueueHandle, timer_, nullptr);
	};

	static void CALLBACK SoundThreadProcess(PVOID lpParameter, BOOLEAN timerOrWaitFired) {
		if (!timerOrWaitFired) return;		//Timer was timed out rather than an event was triggered
		SoundThread* ptrThis = (SoundThread*)lpParameter;

		HRESULT hr = WaitForMultipleObjects(1, &ptrThis->hEvent_, false, 0);
		if (hr == WAIT_OBJECT_0) {
			Beep(2300, 200);	//Why must it be synchronous aaaaaaaaa
		}
	}
public:
	HANDLE timer_;
	HANDLE hEvent_;
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
	if (stdoutHandle == nullptr) {
		printf("Error acquiring console handle.");
		return -1;
	}
	timerQueueHandle = ::CreateTimerQueue();
	if (timerQueueHandle == nullptr) {
		printf("Error creating a timer queue.");
		return -1;
	}

	CONSOLE_SCREEN_BUFFER_INFO orgTextAttrib;
	GetConsoleScreenBufferInfo(stdoutHandle, &orgTextAttrib);

	Console::SetCursor(20, false);

	bool mapState[6];
	memset(mapState, 0x00, sizeof(bool) * 6);
	auto ObtainKeyStateMap = [&](int index) -> bool {
		if (mapState[index]) {
			mapState[index] = false;
			return true;
		}
		return false;
	};

	SoundThread* threadSound = new SoundThread();

	IntersectionSpace* space = new IntersectionSpace();

	ShipObj* objShip = new ShipObj(36, BOUND_B - 4);
	std::list<ShotObj*> listShot;
	std::list<std::pair<AsteroidObj*, std::list<Drawable*>::iterator>> listAsteroid;

	auto AddAsteroid = [&](int left, int top, int right, int bottom) {
		int x = GetRand(left, right);
		int y = GetRand(top, bottom);
		AsteroidObj* asteroid = new AsteroidObj(x, y);

		while (space->CheckCollision(asteroid, 0, 0, 0.6f, nullptr)) {
			asteroid->x_ = GetRand(left, right);
			asteroid->y_ = GetRand(top, bottom);
		}

		asteroid->px_ = asteroid->x_;
		asteroid->py_ = asteroid->y_;

		std::pair<AsteroidObj*, std::list<Drawable*>::iterator> pairAsteroid;
		pairAsteroid.first = asteroid;
		pairAsteroid.second = space->AddObject(asteroid);
		listAsteroid.push_back(pairAsteroid);
	};

	int64_t playerScore = 0;

	//Populate the field with asteroids
	{
		for (size_t i = 0; i < MAX_ASTEROID; ++i)
			AddAsteroid(BOUND_L + 1, BOUND_T + 1, 
				BOUND_R - 2, BOUND_T + (BOUND_B - BOUND_T) * 0.65f);
	}

	size_t frame = 0;

	bool bFinish = false;
	while (!bFinish) {
		//Key update
		{
			auto IsKeyPressed = [](int vk) -> bool {
				return GetKeyState(vk) & 0x8000;
			};
			mapState[0] |= IsKeyPressed(0x58);	//x
			mapState[1] |= IsKeyPressed(VK_SPACE);
			mapState[2] |= IsKeyPressed(0x57);	//w
			mapState[3] |= IsKeyPressed(0x41);	//a
			mapState[4] |= IsKeyPressed(0x53);	//s
			mapState[5] |= IsKeyPressed(0x44);	//d
		}

		if (ObtainKeyStateMap(0))
			bFinish = true;

		if (frame % 5 == 0) {
			//Update
			{
				if (ObtainKeyStateMap(1) && frame % 20 == 0) {
					ShotObj* newShot = new ShotObj(objShip->GetX() + 2, objShip->GetY());
					newShot->SetSpeed(0, -1);
					if (listShot.size() < MAX_SHOT)
						listShot.push_back(newShot);
				}

				{
					bool bUp = ObtainKeyStateMap(2);	//w
					bool bLeft = ObtainKeyStateMap(3);	//a
					bool bDown = ObtainKeyStateMap(4);	//s
					bool bRight = ObtainKeyStateMap(5);	//d
					objShip->Update(bLeft ? -2 : (bRight ? 2 : 0),
						bUp ? -1 : (bDown ? 1 : 0));
				}

				for (auto itr = listShot.begin(); itr != listShot.end();) {
					ShotObj* iShot = *itr;

					iShot->DeleteInClip();

					if (!iShot->bDelete_) {
						std::list<Drawable*>::iterator itrCol;
						bool bCollision = space->CheckCollision(iShot, 0, 0, 1.4f, &itrCol);
						if (bCollision) {
							iShot->bDelete_ = true;

							::SetEvent(threadSound->hEvent_);
							//MessageBeep(MB_OK);

							if (AsteroidObj* objAsteroid = dynamic_cast<AsteroidObj*>(*itrCol)) {
								objAsteroid->bCollided_ = true;
								objAsteroid->Erase();
							}
						}
					}

					if (!iShot->bDelete_) {
						iShot->Update(0, 0);
						++itr;
					}
					else {
						delete iShot;
						itr = listShot.erase(itr);
					}
				}
				for (auto itr = listAsteroid.begin(); itr != listAsteroid.end();) {
					auto& ptrAsteroid = itr->first;
					auto& itrAsteroid = itr->second;

					ptrAsteroid->DeleteInClip();

					if (!ptrAsteroid->bDelete_) {
						if (!ptrAsteroid->bCollided_) {
							ptrAsteroid->Update(0, 0);
							++itr;
						}
						else {
							space->RemoveObject(itrAsteroid);
							itr = listAsteroid.erase(itr);

							AddAsteroid(BOUND_L + 1, BOUND_T + 1, 
								BOUND_R - 2, BOUND_T + (BOUND_B - BOUND_T) * 0.65f);
							playerScore += 500;
						}
					}
					else {
						delete ptrAsteroid;
						space->RemoveObject(itrAsteroid);
						itr = listAsteroid.erase(itr);
					}
				}
			}

			//Draw
			{
				Console::GotoXY(1, 0);
				Console::SetColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("Score: %lld", playerScore);
				Console::SetColor(orgTextAttrib.wAttributes);

				for (auto itr = listAsteroid.begin(); itr != listAsteroid.end(); ++itr)
					itr->first->Draw();
				for (auto itr = listShot.begin(); itr != listShot.end(); ++itr)
					(*itr)->Draw();
				objShip->Draw();
			}
		}

		++frame;
		frame %= 1000;
		Sleep(10);
	}

	for (auto& i : listAsteroid)
		delete i.first;
	for (auto& i : listShot)
		delete i;
	delete objShip;
	delete space;
	delete threadSound;

	::DeleteTimerQueue(timerQueueHandle);

	Console::SetColor(orgTextAttrib.wAttributes);
	Console::GotoXY(0, BOUND_B + 3);
	return 0;
}