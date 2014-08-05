//--------------------------------
// Packet Definition
//--------------------------------

PDF_START(PT_SESSION_U)
	PDF_FIELD(unsigned long, sessionId)
PDF_END(PT_SESSION_U)

PDF_START(PT_LOGIN_S)
	PDF_FIELD(unsigned long, sessionId)
	PDF_FIELD_ARRAY(char, id, 32)
	PDF_FIELD_ARRAY(char, password, 16)
PDF_END(PT_LOGIN_S)

PDF_START(PT_MESSAGE)
	PDF_FIELD(unsigned long, sessionId)
	PDF_FIELD_VARRAY(std::vector<char>, message)
PDF_END(PT_MESSAGE)

