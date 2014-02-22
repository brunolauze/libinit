
#ifndef __AUDITD_H__
#define __AUDITD_H__
#include "../default.h"

#define PROVIDE		auditd
#define REQUIRE 	{ "syslogd" }
#define BEFORE 		{ DAEMON	 }
#define KEYWORD 	{ NOJAIL, SHUTDOWN }

#define AUDITD_COMMAND "/usr/sbin/" NAME
#define COMMAND AUDITD_COMMAND
#define PID_FILE "/var/run/" NAME
#define REQUIRE_FILES { "/etc/security/audit_class", "/etc/security/audit_control", "/etc/security/audit_event", "/etc/security/audit_user", "/etc/security/audit_warn" }
#define AUDITD_STOP_FLAGS	"-t"

#include "../common.h"

#endif

