#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <atomic>

namespace Threads
{
#define NUM_THREADS 10

	class FileManager 
	{
	public:
		FileManager() = default;
		~FileManager();
	public:
		void Start();
		void ShutDown();
	private:
		std::vector<std::string> m_buffer;
		std::vector<std::thread> m_poolWorkesA;
		std::vector<std::thread> m_poolWorkesB;
		std::vector<std::string> m_lines;
		std::atomic<bool> m_bRunning{ false };
		std::atomic<bool> m_sentEndMsg{ false };
		std::mutex m_bufferMutex;
		std::mutex m_fileMutex;
		std::mutex m_linesMutex;
	private:
		void ReadBuffer();
		void ReadLines();
		void WriteBuffer(const std::string& msg);
		void ReadFile();
		void WriteFile(std::ofstream& fileB, const std::string& msg);
		void RunWorkerA();
		void RunWorkerB();
	};
};