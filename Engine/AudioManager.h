#pragma once
#include <string>
#include <xaudio2.h>
#include <vector>

struct AudioData {
	XAUDIO2_BUFFER buffer = {};
	IXAudio2SourceVoice** sourceVoice = nullptr;
	std::string fileName;
};

struct Chunk {
	char id[5] = "";
	unsigned int size = 0;
};

/// <summary>
/// 音声ファイルを管理する名前空間
/// </summary>
namespace AudioManager {

	/// <summary>
	/// AudioManagerを初期化する関数
	/// </summary>
	void InitManager();

	/// <summary>
	/// 音声ファイルを読み込む関数
	/// </summary>
	/// <param name="fileName">読み込みたい音声ファイルのパス</param>
	/// <param name="loop">ループ再生にするか</param>
	/// <returns>成功した場合は0以上のIDを返す。失敗した場合は-1を返す。</returns>
	int Load(std::string fileName, bool loop = false);

	/// <summary>
	/// 音声ファイルを再生する関数
	/// </summary>
	/// <param name="id">ID</param>
	void Play(int id);

	/// <summary>
	/// 音声ファイルを止める関数
	/// </summary>
	/// <param name="id">ID</param>
	void Stop(int id);

	/// <summary>
	/// 音量を変える関数
	/// </summary>
	/// <param name="volume">音量</param>
	void ChangeVolume(int id, int volume);

}