#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineDirectory.h"
#include "GameEngineString.h"

GameEngineFile::GameEngineFile() 
	: FilePtr(nullptr)
{

}

GameEngineFile::GameEngineFile(const char* _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const std::filesystem::path& _Path)
	: FilePtr(nullptr)
{
	Path_ = _Path;
}

GameEngineFile::GameEngineFile(const GameEngineFile& _Other) 
	: FilePtr(nullptr)
{
	Path_ = _Other.Path_;
}

GameEngineFile::~GameEngineFile() 
{
	GameEngineFile::Close();
}

void GameEngineFile::Close()
{
	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
		FilePtr = nullptr;
	}
}

// "text"
// 

void GameEngineFile::Open(OpenMode _OpenMode, FileMode _FileMode)
{
	// b냐 t냐에 따라서 파일이 저장되었을때의 최종적인 형식이 달라지게 된다.
	std::string OpenMode = "";
	switch (_OpenMode)
	{
	case OpenMode::Read:
		OpenMode += "r";
		break;
	case OpenMode::Write:
		OpenMode += "w";
		break;
	default:
		break;
	}

	switch (_FileMode)
	{
	case FileMode::Text:
		OpenMode += "t";
		break;
	case FileMode::Binary:
		OpenMode += "b";
		break;
	default:
		break;
	}

	// "wb" 쓴다 바이너리
	// "wt" 쓴다 텍스트

	// "rb" 읽는다 바이너리
	// "rt" 읽는다 텍스트

	fopen_s(&FilePtr, Path_.string().c_str(), OpenMode.c_str());

	if (nullptr == FilePtr)
	{
		MsgBoxAssert("파일이 정상적으로 열리지 않았습니다.");
	}
}

void GameEngineFile::Write(const void* _WriteData, size_t _DataSize)
{
	// openmode "wt"
	
	// "aaaaaaa"

	// _Buffer 파일에 쓰려고 한다.
	// _DataSize의 크기만큼
	// 1번
	fwrite(_WriteData, _DataSize, 1, FilePtr);
}

void GameEngineFile::Write(const std::string& _Data)
{
	// 크기를 저장해줘야 합니다.
// string은? 크기가 일정한 데이터를 가지고 있나요?
	int Size = static_cast<int>(_Data.size());
	Write(&Size, sizeof(int));
	Write(_Data.c_str(), _Data.size());
}

void GameEngineFile::Write(const float4& _Data)
{
	Write(&_Data, sizeof(float4));
}

void GameEngineFile::Write(const float4x4& _Data)
{
	Write(&_Data, sizeof(float4x4));
}


void GameEngineFile::Write(const double& _Data)
{
	Write(&_Data, sizeof(double));
}

void GameEngineFile::Write(const float& _Data)
{
	Write(&_Data, sizeof(float));
}

void GameEngineFile::Write(const unsigned int& _Data) 
{
	Write(&_Data, sizeof(unsigned int));
}


void GameEngineFile::Read(void* _Buffer, size_t _BufferSize, size_t _ReadSize)
{
	// 
	fread_s(_Buffer, _BufferSize, _ReadSize, 1, FilePtr);
}

void GameEngineFile::Read(std::string& _Data)
{
	int Size = 0;
	Read(&Size, sizeof(int), sizeof(int));
	_Data.resize(Size);
	Read(&_Data[0], Size, Size);
}

void GameEngineFile::Read(double& _Data)
{
	Read(&_Data, sizeof(double), sizeof(double));
}

void GameEngineFile::Read(float& _Data)
{
	Read(&_Data, sizeof(float), sizeof(float));
}

void GameEngineFile::Read(float4x4& _Data)
{
	Read(&_Data, sizeof(float4x4), sizeof(float4x4));
}

void GameEngineFile::Read(float4& _Data)
{
	Read(&_Data, sizeof(float4), sizeof(float4));
}

void GameEngineFile::Read(unsigned int& _Data)
{
	Read(&_Data, sizeof(unsigned int), sizeof(unsigned int));
}


std::string GameEngineFile::GetString()
{
	std::string AllString;

	uintmax_t Size = GetFileSize();

	AllString.resize(Size);

	Read(&AllString[0], Size, Size);

	return AllString;
}


uintmax_t GameEngineFile::GetFileSize() const
{
	return GetFileSize(Path_);
}

/*static */uintmax_t GameEngineFile::GetFileSize(const std::filesystem::path& _Path)
{
	return std::filesystem::file_size(_Path);
}

GameEngineDirectory GameEngineFile::GetDirectory()
{
	std::string Path = GameEngineString::Replace(Path_.string(), GetFileName().c_str(), "");
	Path.replace(Path.size() - 1, 2, "");
	return GameEngineDirectory(Path.c_str());
}