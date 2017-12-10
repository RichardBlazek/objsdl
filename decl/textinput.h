#pragma once

namespace TextInput
{
	void Start();
	void Stop();
	bool IsActive();
	void SetCandidateListArea(const Rect& area);
}