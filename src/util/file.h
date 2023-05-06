#ifndef FILE_H_
#define FILE_H_

#include <SDL.h>

#include <filesystem>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace file
{
	static std::string GetBasePath()
	{
		// get full path
		std::string full_path = SDL_GetBasePath();
		std::stringstream full_path_ss(full_path);

		// split into segments (we're looking for "/out")s
		std::vector<std::string> path_list;
		std::string segment;
		while (std::getline(full_path_ss, segment, '\\'))
		{
			path_list.push_back(segment);
		}

		// make new vector string:))) & then add everything before the out dir [THANKS SDL]
		std::vector<std::string> real_path_list;
		for (std::string path : path_list)
		{
			if (path == "out")
				break;

			real_path_list.push_back(path);
		}

		// set the asset path with "/"s
		std::string basepath;
		for (std::string path : real_path_list)
		{
			basepath.append(path);
			basepath.append("/");
		}

		return basepath;
	}

	static std::string get_datetimestr()
	{
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y-%H-%M-%S");
		auto str = oss.str();

		return str;
	}

	static std::string basepath = GetBasePath();
	static std::vector<std::string> GetLinesFromFile(std::string filepath)
	{
		std::vector<std::string> lines;
		std::ifstream file(basepath + "data/" + filepath);
		for (std::string line; std::getline(file, line);)
		{
			lines.push_back(line);
		}
		return lines;
	}

	static std::string datetimestr = get_datetimestr();
	static std::string logdir = basepath + "logs/" + datetimestr + "/";
	static std::string logfile = logdir + "logs.g";
	static void CreateLogFile()
	{
		std::filesystem::create_directories(logdir);
		std::ofstream out(logfile);
		out << "LOGS@ " << datetimestr << "\n";
		out.close();
	}

	static void AppendLogFile(std::string data)
	{
		std::ofstream out(logfile, std::ios_base::app);
		out << data << "\n";
		out.close();
	}

	static void AppendAgentFile(std::string id, std::string data)
	{
		auto dir = logdir + "agents/";

		std::ofstream out(dir + id + ".g", std::ios_base::app);
		if (std::filesystem::create_directories(dir))
		{ out << "AGENT" << "\n"; }
		out << data;
		out.close();
	}
}
#endif