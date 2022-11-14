#include "Color.hpp"

Color::Modifier::Modifier(void): m_code(Color::FG_DEFAULT) {}

Color::Modifier::Modifier(Code code): m_code(code) {}

Color::Modifier::Modifier(Modifier const& other): m_code(other.m_code) {}

Color::Modifier::~Modifier(void) {}

Color::Modifier& Color::Modifier::operator=(Modifier const& other) {
	this->m_code = other.m_code;
	return *this;
}

Color::Code Color::Modifier::getCode(void) const {
	return m_code;
}

std::ostream& Color::operator<<(std::ostream& os, Modifier const& mod) {
	return os << "\033[" << mod.getCode() << "m";
}
