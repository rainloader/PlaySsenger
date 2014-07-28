//--------------------------------
// Packet Definition
//--------------------------------

PDF_START(PT_SESSION_U)
	PDF_FIELD(unsigned long, sessionId)
PDF_END(PT_SESSION_U)

PDF_START(PT_LOGIN_S)
	PDF_FIELD(unsigned long, sessionId)
	PDF_FIELD_ARRAY(char, id, 32)
	PDF_FIELD_ARRAYY(char, password, 16)
PDF_END(PT_LOGIN_S)

