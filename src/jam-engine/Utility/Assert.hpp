#ifndef JE_ASSERT_HPP
#define JE_ASSERT_HPP

namespace je
{

void assertFailed(const char *exp, int line, const char *file);

void assertFailed(const char *exp, int line, const char *file, const char *message);

void error(int line, const char *file, const char *message);

}

#define JE_ASSERT(x) \
	do \
	{ \
		if (!(x)) \
			je::assertFailed(#x, __LINE__, __FILE__); \
	} \
	while (0)

#define JE_ASSERT_MSG(x, m) \
	do \
	{ \
		if (!(x)) \
			je::assertFailed(#x, __LINE__, __FILE__, m); \
	} \
	while (0)

#define JE_ERROR(m) \
	do \
	{ \
		je::error(__LINE__, __FILE__, m); \
	} \
	while (0)

#endif
