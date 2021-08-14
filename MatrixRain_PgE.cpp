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
		std::string sText;
	};

	void PrepareStreamer(sStreamer *s)
	{
		s->sText = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}

	std::list<sStreamer> listStreamers;
	int nMaxStreamers = 1;


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
			
			s.fPosition += 10.0f * fElapsedTime;

			for (int i = 0; i < s.sText.size(); i++)
			{

				DrawString(s.nColumn, (int)s.fPosition, s.sText, olc::GREEN);

			}
		}

		return true;
	}
};

int main()
{
	MatrixRain demo;
	if (demo.Construct(128, 80, 8, 8))
		demo.Start();

	return 0;
}

