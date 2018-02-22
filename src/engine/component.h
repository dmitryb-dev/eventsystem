#ifndef COMPONENT_DSL
#define COMPONENT_DSL

#define Component(type, Name) \
	type _evs_Component##Name; \
	int _evs_Component##Name##IsInitialized; \
    \
	type _evs_create##Name(); \
	type* _evs_initComponent##Name() \
	{ \
		if (!_evs_Component##Name##IsInitialized) \
		{ \
			_evs_Component##Name = _evs_create##Name(); \
			_evs_Component##Name##IsInitialized++; \
		} \
		return &_evs_Component##Name; \
	} \
    \
	type _evs_create##Name()


#define Create(Name) _evs_create##Name()

#define Get(Name) _evs_initComponent##Name()


#endif
