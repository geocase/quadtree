#ifndef FPS_H
#define FPS_H

class cFPS;

class cFPS {
private:
	uint64_t fpsStartTime = 0;
	uint64_t frames = 0;
	uint64_t frameStart = 0;
	uint64_t frameEnd = 0;	
	double frameRate = 0;
public:
	void StartFPSCounter();
	void StartFrame();
	void EndFrame(); 	
	double GetFrameRate();
	double GetFrameTime();
	uint64_t GetFrames();
};

#endif
