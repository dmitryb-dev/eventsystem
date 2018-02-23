#ifndef COMPONENT_DSL
#define COMPONENT_DSL

#define Component(type, name) \
	type name##Component; \
	int _evs_Component##name##IsInitialized; \
    \
	type _evs_create##name(); \
	type* _evs_initComponent##name() \
	{ \
		if (!_evs_Component##name##IsInitialized) \
		{ \
			name##Component = _evs_create##name(); \
			_evs_Component##name##IsInitialized = 1; \
		} \
		return &name##Component; \
	} \
    \
	type _evs_create##name()


#define Create(name) _evs_create##name()

#define Get(name) _evs_initComponent##name()
#define Set(name, value) *Get(name) = value
#define Value(name) (*Get(name))
#define Reset(name) _evs_Component##name##IsInitialized = 0;

#endif
