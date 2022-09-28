#ifndef COLOR_H
#define COLOR_H

#include <ostream>

namespace Color
{
	enum Code {
		FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
	};

	class Modifier {

		Code m_code;

		public:

			Modifier(void);
			Modifier(Code code);
			Modifier(Modifier const& other);
			~Modifier(void);

			Modifier& operator=(Modifier const& other);

			Code getCode(void) const;

	};

	std::ostream& operator<<(std::ostream& os, Modifier const& mod);

} // namespace Color


#endif
