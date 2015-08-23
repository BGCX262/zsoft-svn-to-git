#!/bin/sh
#######################
#   Linuxmod          #
#   LinXtend          #
#######################
if [ "$LX_ENV" != "true" ]
then
	. /ezxlocal/LinXtend/etc/initenv
fi
kill `pidof am`
	sleep 1s
	kill `pidof phone`
