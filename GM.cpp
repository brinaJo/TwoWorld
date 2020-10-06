#include "GM.h"

GM* GM::instance = NULL;

GM::GM()
{
    highScore = 0;
    isIntroOnce = false;
}

GM* GM::Getinstance()
{
	if (!instance)
	{
		instance = new GM;
	}
	return instance;
}
bool GM::GetSound()
{
    return UserDefault::getInstance()->getBoolForKey("SOUNDKEY");
}

bool GM::GetEffect()
{
    return UserDefault::getInstance()->getBoolForKey("EFFECTKEY");
}
