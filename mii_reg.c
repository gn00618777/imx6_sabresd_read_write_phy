#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/mman.h>
#include <zlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/sockios.h>
#include <linux/mii.h>
#include <linux/if.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
        struct ifreq ifreq;
        struct mii_ioctl_data *mii = (void *)&ifreq.ifr_data;

	if (argc != 4)
	{
		printf("%s ifname phy reg\n", argv[0]);
		exit(1);
	}
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0)
	{
		perror("socket");
		exit(1);
	}
	strcpy(ifreq.ifr_name, argv[1]);	
	mii->phy_id = strtoul(argv[2], NULL, 0);
	mii->reg_num = strtoul(argv[3], NULL, 0);
        if (ioctl(fd, SIOCGMIIREG, &ifreq) < 0)
        {
        	perror("ioctl: SIOCGMIIREG");
        	exit(1);
        }
        printf("val=%x\n", mii->val_out);
	return 0;
}
