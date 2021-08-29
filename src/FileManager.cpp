#include "FileManager.h"

#define END_MESSAGE "END"


Threads::FileManager::~FileManager()
{
	ShutDown();
}

void Threads::FileManager::Start()
{
	m_bRunning = true;

	ReadFile();
	
	for (int i = 0; i < NUM_THREADS; i++)
	{
		m_poolWorkesA.push_back(std::thread(&FileManager::RunWorkerA, this));
	}
	for (int i = 0; i < NUM_THREADS; i++)
	{
		m_poolWorkesB.push_back(std::thread(&FileManager::RunWorkerB, this));
	}

	while (m_bRunning);
}



void Threads::FileManager::ShutDown()
{
	std::cout << "Shutdowning" << std::endl;
	m_bRunning = false;
	for (std::thread& every_thread : m_poolWorkesA)
	{
		if(every_thread.joinable())
			every_thread.join();
	}

	for (std::thread& every_thread : m_poolWorkesB)
	{
		if (every_thread.joinable())
			every_thread.join();
	}

	m_poolWorkesA.clear();
	m_poolWorkesB.clear();
	
}

void Threads::FileManager::ReadBuffer()
{
	std::ofstream fileB{ "FileOutput.txt",std::ios::app };

	if (!fileB)
		return;

	while (m_bRunning) 
	{
		std::string msg;
		{
			std::scoped_lock<std::mutex> sl(m_bufferMutex);
			if (m_buffer.empty())
				continue;
			
			msg = m_buffer.front();
			
			m_buffer.erase(m_buffer.begin());
			if (msg == END_MESSAGE && m_buffer.empty())
				break;
		}
		WriteFile(fileB, msg);
	}

	m_bRunning = false;
}

void Threads::FileManager::WriteBuffer(const std::string& msg)
{
	if (msg.empty())
		return;

	std::scoped_lock<std::mutex> sl(m_bufferMutex);

	m_buffer.push_back(msg);
}

void Threads::FileManager::ReadLines()
{
	while (m_bRunning) 
	{
		std::string line;
		{
			std::scoped_lock<std::mutex> sl(m_linesMutex);
			if (m_lines.empty())
			{
				break;
			}
			line = m_lines.front();
			m_lines.erase(m_lines.begin());
		}
		WriteBuffer(line);
	}
	if (!m_sentEndMsg) 
	{
		m_sentEndMsg = true;
		WriteBuffer(END_MESSAGE);
	}
}

void Threads::FileManager::ReadFile()
{
	//std::scoped_lock<std::mutex> sl(m_fileMutex);
	std::ifstream fileA{ "FileData.txt" };
	std::string output;
	
	if (!fileA.is_open()) 
	{
		std::cout << strerror(errno);
	}
	
	
	while(std::getline(fileA, output))
	{
#ifdef _DEBUG
		
#endif // _DEBUG
		m_lines.push_back(output);
	}
}

void Threads::FileManager::WriteFile(std::ofstream& fileB, const std::string& msg)
{
	std::scoped_lock<std::mutex> sl(m_fileMutex);
	if (fileB) 
	{
		std::thread::id this_id = std::this_thread::get_id();
		std::cout << "this " << this_id << " writes :" << msg << "\n";
		fileB << msg << "\n";
	}
	else 
	{
		std::thread::id this_id = std::this_thread::get_id();
		std::cout << "this " << this_id << " could no write :" << msg << "\n";
	}
}

void Threads::FileManager::RunWorkerA()
{
	std::cout << "Starting WorkerA" << std::endl;
	ReadLines();
}

void Threads::FileManager::RunWorkerB()
{
	std::cout << "Starting WorkerB" << std::endl;
	ReadBuffer();
}