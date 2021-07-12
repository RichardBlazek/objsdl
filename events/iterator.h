#pragma once

namespace events
{
	class Handler;
	class Iterator
	{
	private:
		Optional<Event> event;
	public:
		constexpr Iterator():event(){}
		friend Handler;
		bool operator==(const Iterator& second)const noexcept
		{
			return bool(event)==bool(second.event);
		}
		bool operator!=(const Iterator& second)const noexcept
		{
			return bool(event)!=bool(second.event);
		}
		Iterator& operator++()
		{
			if(!SDL_PollEvent(event?&event.Value().event:nullptr))
			{
				event.Clear();
			}
			return *this;
		}
		Iterator& operator++(int)
		{
			++*this;
			return *this;
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
}