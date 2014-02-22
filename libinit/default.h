

#define CAT(X,Y) X ## Y
#define CAT2(X,Y) CAT(X,Y)
#define CAT3(X,Y,Z) CAT2(X,CAT2(Y,Z))
#define CAT4(X,Y,Z,A) CAT2(X,CAT3(Y,Z,A))

#define STR(x)	#x
#define S(x)	STR(x)

#define NAME		S(PROVIDE)

/* Requirements */
#define LOGIN "LOGIN"
#define DAEMON "DAEMON"
#define FILESYSTEMS "FILESYSTEMS"
#define NETWORK "NETWORK"
#define NETWORKING "NETWORKING"
#define SERVERS	"SERVERS"
#define NETIF "netif"

/* Keywords */
#define NOJAIL "nojail"
#define NOJAILVNET "nojailvnet"
#define SHUTDOWN "shutdown"

#define NO	"NO"
#define YES "YES"
