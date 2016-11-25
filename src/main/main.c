#include "../net/mysocket.h"
#include "../init/Config.h"
#include "../init/Log.h"
#include "../init/mydefine.h"

int main() {
	conInit("../etc/config.con");
	print_Key_Value();
    logInit(Value[getValue("logfile")]);
    int tmp = initSocket(Value[getValue("listenip")],9788);
   	printf("%d\n",tmp);
   	if(tmp==1) work();
	return 0;
}
