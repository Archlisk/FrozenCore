#pragma once

class FrameCounter {
public:

	FrameCounter() {}
	FrameCounter(double interval) 
		: m_interval(interval) {}

	inline double GetFrametime() const { return m_total_frametime / m_sample_count; }
	inline double GetFPS() const { return 1 / GetFrametime(); }

	inline void SetInterval(double interval) { m_interval = interval; }
	inline double GetInterval() const { return m_interval; } 

	void Sample();

private:
	u32 m_sample_count = 0;
	double m_total_frametime = 0.0;
	
	double m_interval = 5.0;
};
