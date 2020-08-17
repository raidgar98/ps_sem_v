#pragma once

// STL
#include <algorithm>
#include <functional>

// Project includes
#include "../../types.hpp"
#include "../../logger/include/logger.h"

template <class _iterable>
class round_manager : Log<round_manager<_iterable> >
{

	using collection_t = _iterable;
	using iterator_t = decltype(((collection_t *)(nullptr))->begin());
	using win_check = std::function<bool(const collection_t &)>;
	using value_type = typename collection_t::value_type;

public:
	class round_iterator : Log<round_iterator>
	{
	public:
		void operator++(int) { update(mgr.get_it(nm)); }
		void operator++() { update(mgr.get_it(nm)); }
		bool operator!=(const round_iterator &it) { return nm != it.nm; }
		round_manager::value_type &operator*()
		{
			// round_iterator::log << nm;
			assert(nm >= 0);
			auto it = mgr.players.begin();
			std::advance(it, nm);
			return *it;
		}
		round_manager::value_type &operator->()
		{
			assert(nm >= 0);
			auto it = mgr.players.begin();
			std::advance(it, nm);
			return *it;
		}

	private:
		round_iterator(const round_manager &_mgr, const number nm) : mgr{_mgr}, nm{nm} {}
		void update(const round_iterator& it)
		{
			nm = it.nm;
		}
		const round_manager<_iterable> &mgr;
		number nm;

		friend class round_manager;
	};

	friend class round_iterator;

	round_iterator begin() const
	{
		return get_it(players.size());
	}

	round_iterator end() const
	{
		return get_it(-2);
	}

	round_manager(collection_t& players, win_check check) : players{ players }, is_win{ check } { assert( players.size() >= 2 ); }

private:
	collection_t &players;
	win_check is_win;

	round_iterator get_it(const number nm) const
	{
		const round_manager& me = *this;
		if (is_win(players) or nm == -2)
			return round_iterator(me, -1);
		else
		{
			if (nm >= players.size() - 1)
				return round_iterator(me, 0);
			else
				return round_iterator(me, nm + 1);
		}
	}
};
