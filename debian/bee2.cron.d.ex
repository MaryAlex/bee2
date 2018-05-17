#
# Regular cron jobs for the bee2 package
#
0 4	* * *	root	[ -x /usr/bin/bee2_maintenance ] && /usr/bin/bee2_maintenance
