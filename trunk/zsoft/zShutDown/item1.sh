#!/bin/sh
#######################
#   Linuxmod          #
#   LinXtend          #
#######################
if [ "$LX_ENV" != "true" ]
then
	. /ezxlocal/LinXtend/etc/initenv
fi
/sbin/poweroff
