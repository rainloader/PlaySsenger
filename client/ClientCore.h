#ifndef _CLIENTCORE_H
#define _CLIENTCORE_H

class ClientCore
{
	public:
		static ClientCore& GetInstance();
		void Run();
	private:
		ClientCore() {}
		static ClientCore* sm_instance;
};

#endif
