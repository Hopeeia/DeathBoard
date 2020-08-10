#include "pch.h"

bool DeathBoard_sidebar;

void loadConfig()
{
	std::string config_file = "config\\deathboard.json";
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
		else
		{
			std::cout << "[DeathBoard] " << "config file creation failed, plase create \"config\" folder\n";
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
	loadConfig();
	addListener([](PlayerDeathEvent& ev)
	{
		BDX::runcmdEx("scoreboard players add \"" + ev.getPlayer().getRealName() + " \" deathboard 1");
	});
	addListener([](ServerStartedEvent& ev)
	{
		BDX::runcmd(u8"scoreboard objectives add deathboard dummy ËÀÍö°ñ");
		if (DeathBoard_sidebar) BDX::runcmd("scoreboard objectives setdisplay sidebar deathboard ascending");
	});
	std::cout << "[DeathBoard] Loaded!\n";
}