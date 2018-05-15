class CGame
{
public:
	const std::string GetGameTitle(){return mGameTitle;}
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void init();
	void shutdown();
	static const uint32_t mScreenWidth = 1024/2;
	static const uint32_t mScreenHeight = 1024/2; //768
	static const uint32_t mBitsPerPixel = 32;

private:
	static const std::string mGameTitle;
	static CGame *sInstance;
	CGame(){};
};