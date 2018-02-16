#pragma once

class Handler;
class Iterator
{
private:
	Optional<Event> event;
public:
	Iterator()=default;
	friend Handler;
	bool operator==(const Iterator& second)const noexcept
	{
		return bool(event)==bool(second.event);
	}
	bool operator!=(const Iterator& second)const noexcept
	{
		return bool(event)!=bool(second.event);
	}
	void operator++()
	{
		if(!SDL_PollEvent(event?&event.Value().event:nullptr))
		{
			event.Clear();
		}
	}
	void operator++(int)
	{
		++*this;
	}
	Event& operator*()
	{
		return event.Value();
	}
};
struct Handler
{
	Iterator begin()const
	{
		Iterator iter;
		iter.event=Event();
		return func::Move(iter);
	}
	Iterator end()const
	{
		return Iterator();
	}
};