#include <stdio.h>
#include "../common/Packets.h"

int main()
{
	S_PT_SESSION_U data;
	data.sessionId = 50;
	
	BYTE buffer[1000];
	WRITE_PT_SESSION_U(buffer, data);

	S_PT_SESSION_U data2;
	READ_PT_SESSION_U(buffer, data2);

	printf("%d\n", data2.sessionId);	

	return 0;
}
