#ifndef COMPONENT_DSL
#define COMPONENT_DSL

#define Component(type, name) \
	type name##Component; \
	int name##ComponentisInitialized; \
	type create##name(); \
	type* init##name##Component() \
	{ \
		if (!name##ComponentisInitialized) \
		{ \
			name##Component = create##name(); \
			name##ComponentisInitialized++; \
		} \
		return &name##Component; \
	} \
	type create##name()

#define Create(name) create##name()

#define Get(name) init##ame##Component()


#endif
