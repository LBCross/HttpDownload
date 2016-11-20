#include "../net/mysocket.h"
#include "../init/Config.h"
#include "../init/Log.h"
#include "../init/mydefine.h"

int main() {
	conInit("../etc/config.con");
	print_Key_Value();
    logInit(Value[getValue("logfile")]);
   	printf("%d\n",initSocket(Value[getValue("listenip")],9788));
	work();
	return 0;
}
