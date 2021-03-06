#include "pch.h"

bool DeathBoard_sidebar;

void loadConfig()
{
	std::string config_file = "plugins\\DeathBoard\\deathboard.json";
	std::ifstream fs;
	fs.open(config_file, std::ios::in);
	DeathBoard_sidebar = true;
	if (!fs)
	{
		std::cout << "[DeathBoard] " << config_file << " not found, creating file(default value used)\n";
		std::ofstream of(config_file);
		if (of)
		{
			of << "{\n\"enableSidebar\": true\n}";
		}
	}
	else
	{
		std::string json;
		char buf[1024];
		while (fs.getline(buf, 1024))
		{
			json.append(buf);
		}
		rapidjson::Document document;
		document.Parse(json.c_str());
		DeathBoard_sidebar = document["enableSidebar"].GetBool();
	}
}

void entry()
{
	filesystem::create_directory("plugins\\DeathBoard");
	loadConfig();
	Event::addEventListener([](ServerStartedEV ev) {
		liteloader::runcmdEx(u8"scoreboard objectives add deathboard dummy ËÀÍö°ñ");
		if (DeathBoard_sidebar) liteloader::runcmdEx("scoreboard objectives setdisplay sidebar deathboard descending");
		});
	Event::addEventListener([](PlayerDeathEV ev)
		{
			std::string playerName = offPlayer::getRealName(ev.Player);
			liteloader::runcmdEx("scoreboard players add \"" + playerName + " \" deathboard 1");
		});
	std::cout << "[DeathBoard] Loaded!\n";
}