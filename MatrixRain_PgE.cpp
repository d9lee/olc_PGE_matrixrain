#define OLC_PGE_APPLICATION
#include <list>
#include "olcPixelGameEngine.h"

class MatrixRain : public olc::PixelGameEngine
{
public:
	MatrixRain()
	{
		sAppName = "Example";
	}
	
private:
	struct sStreamer
	{
		int nColumn = 0;
		float fPosition = 0.0f;
		float fSpeed = 10.0f;
		std::string sText;
	};

	void PrepareStreamer(sStreamer *s)
	{
		s->nColumn = rand() % ScreenWidth();
		s->fPosition = 0.0f;
		s->fSpeed = rand() % 60 + 5;
		s->sText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}

	std::list<sStreamer> listStreamers;
	int nMaxStreamers = 200;


public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		for (int n = 0; n < nMaxStreamers; n++)
		{
			sStreamer s;
			PrepareStreamer(&s);
			listStreamers.push_back(s);
		}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::BLACK);

		for (auto& s : listStreamers)
		{
			
			s.fPosition += s.fSpeed * fElapsedTime;

			for (int i = 0; i < s.sText.size(); i++)
			{
				int nCharIndex = (i - (int)s.fPosition) % s.sText.size();

				DrawString(s.nColumn, (int)s.fPosition - i * 8, s.sText.substr(nCharIndex, 1) , olc::GREEN);

			}

			if (s.fPosition - s.sText.size()*8 >= ScreenHeight())
				PrepareStreamer(&s);

		}

		return true;
	}
};

int main()
{
	MatrixRain demo;
	if (demo.Construct(820, 420, 2, 2))
		demo.Start();

	return 0;
}


