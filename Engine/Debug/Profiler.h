#pragma once

#include <Debug/Macros.h>

#include <FC/Singleton.h>
#include <FC/Time.h>
#include <FC/Vector.h>
#include <FC/String.h>

#include <iostream>

class ScopeSampler;

class Profiler
{
Singleton(Profiler);

public:
	class Sample
	{
		public:
			Sample(const String& name)
				: duration(Time::Duration::zero()), name(name) { Profiler::RegisterSample(this); }
			
			Time::Duration duration;
			const String name;
	};

	static void RegisterSample(const Sample* sample) { Profiler::Get().Inter_RegisterSample(sample); }
	static void PrintSamples() { Profiler::Get().Inter_PrintSamples(); }
	
private:
	void Init() {}

	void Inter_RegisterSample(const Sample* sample)	{ m_samples.push_back(sample); }

	void Inter_PrintSamples() 
	{
		struct {
			bool operator() (const Sample* a, const Sample* b) {
				return a->duration > b->duration;
			}
		} custom_sort;
	
		std::sort(m_samples.begin(), m_samples.end(), custom_sort);
	
		Time::Duration profile_duration = std::chrono::duration_cast<Time::Duration>(Time::Now() - m_profile_start);
		
		for (const Sample* sample : m_samples) {
			int time_percent = (float)sample->duration.count() / (float)profile_duration.count() * 100.0f;
			std::cout << sample->duration.count() << "us/" << time_percent << "% -> " << sample->name << std::endl;
		}
	}

	Time::Point m_profile_start = Time::Now();
	Vector<const Sample*> m_samples;
};



class ScopeSampler
{
public:
	ScopeSampler(Profiler::Sample& sample)
		: m_sample(sample), m_start_time(Time::Now()) {}
	
	~ScopeSampler() { m_sample.duration += Time::Since(m_start_time); }

private:
	Profiler::Sample& m_sample;
	Time::Point m_start_time = Time::Now();
};
