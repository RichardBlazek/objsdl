#pragma once

void MainLoop(std::function<void(const Event&)> evt_handler, std::function<bool()> update, uint32 looptime_ms)
{
	bool repeat=true;
	std::chrono::milliseconds looptime(looptime_ms);
	std::chrono::steady_clock::time_point lasttime=std::chrono::steady_clock::now();
	while(!SDL::events::Quit()&&repeat)
	{
		for(auto& evt:events::Handler())
		{
			evt_handler(evt);
		}
		repeat=update();
		std::this_thread::sleep_until(lasttime+looptime);
		lasttime=std::chrono::steady_clock::now();
	}
}